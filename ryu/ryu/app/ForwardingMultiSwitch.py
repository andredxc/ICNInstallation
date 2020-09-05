# Copyright (C) 2017 Delft University of Technology, TNO, Niels van Adrichem.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
# implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import logging

from ryu.base import app_manager
from ryu.controller import handler

from ryu.topology import event as switch_event

from ryu.ofproto import ofproto_v1_3
from ryu.controller import ofp_event, event

from collections import defaultdict
from collections import namedtuple

from pprint import pprint

from ryu.controller.handler import CONFIG_DISPATCHER

from ryu.lib.packet import packet
from ryu.lib.packet import ethernet
from ryu.lib.packet import ether_types

from ryu.lib import mac

from ryu.lib import ovs

LOG = logging.getLogger(__name__)

class EventMacLookupRequest(event.EventRequestBase):
	def __init__(self, mac):
		super(EventMacLookupRequest, self).__init__()
		self.dst = 'ForwardingMultiSwitch'
		self.mac = mac

	def __str__(self):
		return 'EventMacLookupRequest<src=%s, mac=%s>' % (self.src, self.mac)

class EventMacLookupReply(event.EventReplyBase):
	def __init__(self, dst, switch_port):
		super(EventMacLookupReply, self).__init__(dst)
		self.switch_port = switch_port

	def __str__(self):
		return 'EventMacLookupReply<dst=%s, switch_port=%s>' % (self.dst, self.switch_port)

def mac_lookup(app, mac):
	rep = app.send_request(EventMacLookupRequest(mac))
	return rep.switch_port

class ForwardingMultiSwitch(app_manager.RyuApp):
    OFP_VERSIONS = [ofproto_v1_3.OFP_VERSION]

    def __init__(self, *args, **kwargs):
        super(ForwardingMultiSwitch, self).__init__(*args, **kwargs)

        self.switches = {}
        self.switch_ports = {}
        self.mac_learning = {}
        self.adj = defaultdict(lambda:defaultdict(lambda:None))
        self.cost = defaultdict(lambda:defaultdict(lambda:float("+inf")))
        self.prev = defaultdict(lambda:defaultdict(lambda:None))
        self.fw = defaultdict(lambda:defaultdict(lambda:None))
        self.dpids = lambda:[dpid for dpid in sorted( self.switches.keys() )]

    @handler.set_ev_cls(ofp_event.EventOFPStateChange,  [CONFIG_DISPATCHER])
    def state_change_handler(self, ev):
        
        dp = ev.datapath
        ofp = dp.ofproto
        parser = dp.ofproto_parser        
        
        #Delete any possible currently existing flows.
        del_flows = parser.OFPFlowMod(dp, table_id=ofp.OFPTT_ALL, out_port=ofp.OFPP_ANY, out_group=ofp.OFPG_ANY, command=ofp.OFPFC_DELETE) 
        dp.send_msg(del_flows)
        
        #Make sure deletion is finished using a barrier before additional flows are added
        barrier_req = parser.OFPBarrierRequest(dp)
        dp.send_msg(barrier_req)

    @handler.set_ev_cls(switch_event.EventSwitchEnter)
    def switch_enter_handler(self, ev):
        
        LOG.warn("ForwardingMultiSwitch: "+ str(ev))
        switch = ev.switch
        self.switches[switch.dp.id] = switch
        
        dp = switch.dp
        dpid = dp.id
        ofp = dp.ofproto
        parser = dp.ofproto_parser

        #Configure table-miss entry
        match = parser.OFPMatch()
        actions = [ parser.OFPActionOutput( ofp.OFPP_CONTROLLER, ofp.OFPCML_NO_BUFFER ) ]
        inst = [ parser.OFPInstructionActions( ofp.OFPIT_APPLY_ACTIONS, actions ) ]
        mod = parser.OFPFlowMod(datapath=dp, match=match, instructions=inst, priority=0) #LOWEST PRIORITY POSSIBLE
        dp.send_msg(mod)

        self._print_adj_matrix()
        self.cost[dpid][dpid] = 0
        self.prev[dpid][dpid] = (dpid, 0)
        self.fw  [dpid][dpid] = (dpid, 0)
        self._print_fw_matrix()

    @handler.set_ev_cls(switch_event.EventSwitchLeave)
    def switch_leave_handler(self, ev):
        LOG.warn("ForwardingMultiSwitch: "+ str(ev))
        LOG.error("ForwardingMultiSwitch: To Do, fix what to do upon leaving of a switch")

#    @handler.set_ev_cls(switch_event.EventPortAdd)
#    def port_add_handler(self, ev):
#        LOG.debug("ForwardingMultiSwitch: "+ str(ev))
#
#    @handler.set_ev_cls(switch_event.EventPortDelete)
#    def port_delete_handler(self, ev):
#        LOG.debug("ForwardingMultiSwitch: "+ str(ev))
#
#    @handler.set_ev_cls(switch_event.EventPortModify)
#    def port_modify_handler(self, ev):
#        LOG.debug("ForwardingMultiSwitch: "+ str(ev))

    @handler.set_ev_cls(switch_event.EventLinkAdd)
    def link_add_handler(self, ev):
        LOG.warn("ForwardingMultiSwitch: "+ str(ev))
        link = ev.link
        src = link.src
        dst = link.dst
        
        self.adj[src.dpid][dst.dpid] = src.port_no
        self.switch_ports[src.dpid,src.port_no] = link

        self._print_adj_matrix()        
        self._calc_ForwardingMatrix()
        self._print_fw_matrix()

    @handler.set_ev_cls(switch_event.EventLinkDelete)
    def link_del_handler(self, ev):
        LOG.warn("ForwardingMultiSwitch: "+ str(ev))
        LOG.error("ForwardingMultiSwitch: To Do, fix what to do upon deletion of a link")

    @handler.set_ev_cls(ofp_event.EventOFPPacketIn, handler.MAIN_DISPATCHER)
    def packet_in_handler(self, ev):
        
        def drop():
            LOG.error("\tDropping packet")
            _drop()

	def _drop():
            _output(dpid, [])

        def flood():
            LOG.warn("\tFlooding packet")
            for (iDpid, switch) in self.switches.iteritems():
		if self.fw[dpid][iDpid] is not None: #Check if the destination is in the same broadcast domain as the source.

		        #Initialize ports
		        ports = []
		        #Add local port if that is not the originating port, only necessary in Hardware Testbed
		        #if (iDpid,ofp.OFPP_LOCAL) != (dpid, in_port):
		        #    ports += [ofp.OFPP_LOCAL]

		        #Exclude the inter-switch and possible other incoming ports from flooding
		        ports += [p.port_no for p in switch.ports if (iDpid,p.port_no) != (dpid, in_port) and (iDpid,p.port_no) not in self.switch_ports]
		        
		        if len(ports)>0:
                            _output(iDpid, ports)        
            
        def output(tDpid, port):
            LOG.warn("\tOutputting packet")
            if self.fw[dpid][tDpid] is None:
		LOG.error("\t\tDestination not in domain of source, this should NOT occur! Dropping the packet")
		_drop()
		return		

	    #Drop the packet from the buffer on the incoming switch to prevent buffer overflows.
	    if tDpid != dpid:
                _drop()

            _output(tDpid, [port])

        def _output(tDpid, ports):
	    actions = [parser.OFPActionOutput(port, 0) for port in ports]

	    if buffer_id != None and tDpid == dpid:
                LOG.warn("\t\tOutputting via buffer_id on switch %d ports %s"%(tDpid, ports))
                req = parser.OFPPacketOut(dp, buffer_id = buffer_id, in_port=in_port, actions=actions)
	        dp.send_msg(req)
	        
	    #Forward packet through data-field.
	    elif len(ports)>0:
	        LOG.warn("\t\tOutputting on outgoing switch %d ports %s"%(tDpid, ports))
	        switch = self.switches[tDpid]
	        req = parser.OFPPacketOut(dp, buffer_id = ofp.OFP_NO_BUFFER, in_port=ofp.OFPP_CONTROLLER, actions=actions, data=data)
	        switch.dp.send_msg(req)
            else:
                LOG.warn("\t\tDropped by definition due to no output-ports nor buffer_id")

        msg = ev.msg
        dp = msg.datapath
        dpid = msg.datapath.id
        in_port = msg.match['in_port']
        buffer_id = msg.buffer_id
        
        ofp = msg.datapath.ofproto
        parser = msg.datapath.ofproto_parser        
        
        if msg.reason == ofp.OFPR_NO_MATCH:
            reason = 'NO MATCH'
        elif msg.reason == ofp.OFPR_ACTION:
            reason = 'ACTION'
        elif msg.reason == ofp.OFPR_INVALID_TTL:
            reason = 'INVALID TTL'
        else:
            reason = 'unknown'
        
        data = msg.data        
        pkt = packet.Packet(data)
        eth = pkt.get_protocol(ethernet.ethernet)

        LOG.debug("ForwardingMultiSwitch: New incoming packet from %s at switch %d, port %d, for reason %s"%(eth.src,dpid,in_port,reason))        
        
        if self.CONF.observe_links and eth.ethertype == ether_types.ETH_TYPE_LLDP:
            # ignore LLDP related messages IF topology module has been enabled.
            LOG.debug("\tIgnored LLDP packet due to enabled topology module")
            return

        LOG.warn("ForwardingMultiSwitch: Accepted incoming packet from %s at switch %d, port %d, for reason %s"%(eth.src,dpid,in_port,reason))                
        LOG.debug("\t%s"%(msg))        
        LOG.warn("\t%s"%(pkt))

        SwitchPort = namedtuple('SwitchPort', 'dpid port')        
        
        if (dpid,in_port) not in self.switch_ports:
            # only relearn locations if they arrived from non-interswitch links
            self.mac_learning[eth.src] = SwitchPort(dpid, in_port)    #relearn the location of the mac-address
            LOG.warn("\tLearned or updated MAC address")
        else:
            LOG.warn("\tIncoming packet from switch-to-switch link, this should NOT occur.")
            #DROP it
	if eth.dst == "01:00:5e:00:17:aa":
		LOG.debug("\tIgnored NDN packet")

        elif mac.is_multicast( mac.haddr_to_bin(eth.dst) ):
            self._install_tree(dpid, pkt, in_port)
            flood()
            LOG.warn("\tFlooded multicast packet")

        elif eth.dst not in self.mac_learning:
            flood()
            LOG.warn("\tFlooded unicast packet, unknown MAC address location")
        
        #Create flow and output or forward.
        else:

            self._install_path(dpid, pkt)
            
            #Output the first packet to its destination
            output(self.mac_learning[eth.dst].dpid, self.mac_learning[eth.dst].port)
            LOG.warn("\tProcessed packet, sent to recipient at %s"%(self.mac_learning[eth.dst],))

    def _print_adj_matrix(self):
        mat = self.adj
        dpids = self.dpids()
        
        str = ""
        for dpid in dpids:
            str += "\t%d"%(dpid,)
        str += "\n"
        
        for u in dpids:
            str += "%d"%(u,)
            for v in dpids:
                if mat[u][v] is not None:
                    port = mat[u][v]
                    str += "\t%d"%(port,)
                else:
                    str+="\t"
            str+= "\n"
            
        LOG.warn( str )

    def _print_fw_matrix(self):
        mat = self.fw
        dpids = self.dpids()
        
        str = ""
        for dpid in dpids:
            str += "\t%d"%(dpid,)
        str += "\n"
        
        for u in dpids:
            str += "%d"%(u,)
            for v in dpids:
                if mat[u][v] is not None:
                    (switch, port) = mat[u][v]
                    str += "\t%d"%(switch,)
                else:
                    str+="\t"
            str+= "\n"
            
        LOG.warn( str )

    def _calc_ForwardingMatrix(self):
        #Floyd-Warshall implementation
        LOG.debug("ForwardingMultiSwitch: Calculating forwarding matrix")
        cost = defaultdict(lambda:defaultdict(lambda:float("+inf")))
        prev = defaultdict(lambda:defaultdict(lambda:None))
        fw   = defaultdict(lambda:defaultdict(lambda:None))

        dpids = self.dpids()

        for dpid in dpids:
                cost[dpid][dpid] = 0
                prev[dpid][dpid] = (dpid, 0)
                fw  [dpid][dpid] = (dpid, 0)

        for u in dpids:
            for v in dpids:
                if u != v and self.adj[u][v] != None:
                    cost[u][v] = 1                      #weight of 1 hop count
                    prev[u][v] = (u, self.adj[u][v])    #direct connection
                    fw  [u][v] = (v, self.adj[u][v])

        for k in dpids:
            for i in dpids:
                for j in dpids:
                    if cost[i][k] + cost[k][j] < cost[i][j]:
                        cost[i][j] = cost[i][k] + cost [k][j]
                        prev[i][j] = prev[k][j]
                        fw[i][j]   = fw  [i][k]

        self.cost = cost
        self.prev = prev
        self.fw   = fw

        #LOG.warn("ForwardingMultiSwitch: Computed new forwarding matrix")

    def _get_tree(self, src):
        LOG.warn("\t\tFinding tree from switch %d"%(src,))

        prev = self.prev

        dpids = [dpid for dpid in self.dpids() if prev[src][dpid] is not None] #Check if the destination is in the same broadcast domain as the source.

        _tree={}
        for i in dpids:
                _tree[i] = []

        for i in dpids:
                if i != src:
                    (prevhop, port) = prev[src][i]
                    _tree[prevhop].append(port)

        return _tree

    def _get_path(self, src, dst):
        LOG.warn("\t\tFinding path from switch %d to switch %d"%(src,dst))

        fw = self.fw

        if src == dst:
            return []

        if fw[src][dst] == None:
            return None
        
        (nexthop, port) = fw[src][dst]
        LOG.debug("\t\tTo switch %d over port %d"%(nexthop, port))
        _path = [(nexthop,port)]
        while nexthop != dst:
            (nexthop, port) = fw[nexthop][dst]
            _path.append((nexthop, port))

        return _path

    def _install_tree(self, dpid, pkt, in_port):
        dp = self.switches[dpid].dp
        ofp = dp.ofproto
        parser = dp.ofproto_parser

        eth = pkt.get_protocol(ethernet.ethernet)

        match = parser.OFPMatch(eth_src=eth.src, eth_dst=eth.dst)

        LOG.warn("\tLook up tree from switch %d"%(dpid,))
        tree = self._get_tree(dpid)
        if tree == None:
            LOG.error("\t\tNo tree found")
            return -1

        LOG.warn("\t\tTree found")

        for iDpid in tree:
            #Inter-switch ports:
            ports = tree[iDpid]

            #Add non-switch (thus hosts-)ports
            switch = self.switches[iDpid]
            ports += [p.port_no for p in switch.ports if (iDpid,p.port_no) != (dpid, in_port) and (iDpid,p.port_no) not in self.switch_ports]
            if len(ports)>0:
                LOG.warn("\t\tConfigure switch %d to flood to ports %s"%(iDpid, ports))

                #Send rules
                dp = self.switches[iDpid].dp
                ofp = dp.ofproto
                parser = dp.ofproto_parser

                actions = [parser.OFPActionOutput(port) for port in ports]
                inst = [parser.OFPInstructionActions(ofp.OFPIT_APPLY_ACTIONS, actions)]
                req = parser.OFPFlowMod(datapath=dp, match=match, instructions = inst)
                dp.send_msg(req)

    def _install_path(self, dpid, pkt):
        dp = self.switches[dpid].dp
        ofp = dp.ofproto
        parser = dp.ofproto_parser

        eth = pkt.get_protocol(ethernet.ethernet)
        dst = self.mac_learning[eth.dst]

        match = parser.OFPMatch(eth_src=eth.src, eth_dst=eth.dst)

        LOG.warn("\tLook up path from switch %d to %s"%(dpid, dst))
        path = self._get_path(dpid, dst.dpid)
        if path == None:
            LOG.error("\t\tNo path found")
            return -1

        LOG.warn("\t\tPath found")

        for (nexthop, port) in path:
            LOG.warn("\t\tConfigure switch %d to forward to switch %d over port %d"%(dpid, nexthop,port))

            actions = [parser.OFPActionOutput(port)]
            inst = [parser.OFPInstructionActions(ofp.OFPIT_APPLY_ACTIONS, actions)]
            req = parser.OFPFlowMod(datapath=dp, match=match, instructions = inst)
            dp.send_msg(req)

            dpid = nexthop
            dp = self.switches[dpid].dp
            ofp = dp.ofproto
            parser = dp.ofproto_parser    

        assert dpid == dst.dpid
        port = dst.port
        LOG.warn("\t\tConfigure switch %d to output on port %d"%(dpid,port))

        actions = [parser.OFPActionOutput(port)]
        inst = [parser.OFPInstructionActions(ofp.OFPIT_APPLY_ACTIONS, actions)]
        req = parser.OFPFlowMod(datapath=dp, match=match, instructions = inst)
        dp.send_msg(req)

        LOG.warn("\t\tDone.")
        return -2

    @handler.set_ev_cls(EventMacLookupRequest)
    def mac_lookup_handler(self, req):
        mac = req.mac

	if mac not in self.mac_learning:
            switch_port = None
        else:
            switch_port = self.mac_learning[mac]

        rep = EventMacLookupReply(req.src, switch_port)
        self.reply_to_request(req, rep)

app_manager.require_app('ryu.topology.switches', api_style=False)

