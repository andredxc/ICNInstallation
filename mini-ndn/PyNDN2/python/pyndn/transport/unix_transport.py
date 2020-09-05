# -*- Mode:python; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
#
# Copyright (C) 2014-2018 Regents of the University of California.
# Author: Jeff Thompson <jefft0@remap.ucla.edu>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# A copy of the GNU Lesser General Public License is in the file COPYING.

"""
This module defines the UnixTransport class which extends Transport for
communication over a Unix socket.
"""

import socket
from pyndn.util.blob import Blob, Common
from pyndn.transport.transport import Transport
from pyndn.transport.socket_poller import SocketPoller
from pyndn.encoding.element_reader import ElementReader

class UnixTransport(Transport):
    """
    Create a new UnixTransport in the unconnected state.
    """
    def __init__(self):
        self._socket = None
        self._socketPoller = None
        self._buffer = bytearray(Common.MAX_NDN_PACKET_SIZE)
        # Create a Blob and take its buf() since this creates a memoryview
        #   which is more efficient for slicing.
        self._bufferView = Blob(self._buffer, False).buf()
        self._elementReader = None

    class ConnectionInfo(Transport.ConnectionInfo):
        """
        Create a new UnixTransport.ConnectionInfo which extends
        Transport.ConnectionInfo to hold the socket file path for the Unix
        socket connection.

        :param str filePath: The file path of the Unix socket file.
        """
        def __init__(self, filePath):
            self._filePath = filePath

        def getFilePath(self):
            """
            Get the filePath given to the constructor.

            :return: The file path.
            :rtype: str
            """
            return self._filePath

    def isLocal(self, connectionInfo):
        """
        Determine whether this transport connecting according to connectionInfo
        is to a node on the current machine. Unix transports are always local.

        :param UnixTransport.ConnectionInfo connectionInfo: This is ignored.
        :return: True because Unix transports are always local.
        :rtype: bool
        """
        return True

    def isAsync(self):
        """
        Override to return false since connect does not need to use the
        onConnected callback.

        :return: False
        :rtype bool:
        """
        return False

    def connect(self, connectionInfo, elementListener, onConnected):
        """
        Connect according to the info in connectionInfo, and use
        elementListener.

        :param UnixTransport.ConnectionInfo connectionInfo: A
          UnixTransport.ConnectionInfo.
        :param elementListener: The elementListener must remain valid during the
          life of this object.
        :type elementListener: An object with onReceivedElement
        :param onConnected: This calls onConnected() when the connection is
          established.
        :type onConnected: function object
        """
        self.close()
        self._socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        self._socket.connect(connectionInfo.getFilePath())

        self._socketPoller = SocketPoller(self._socket)
        self._elementReader = ElementReader(elementListener)

        if onConnected != None:
            onConnected()

    # This will be set True if send gets a TypeError.
    _sendNeedsStr = False
    def send(self, data):
        """
        Send data to the host.

        :param data: The buffer of data to send.
        :type data: An array type accepted by socket.send
        """
        if UnixTransport._sendNeedsStr:
            # This version of sendall can't use a memoryview, etc., so convert.
            self._socket.sendall(str(bytearray(data)))
        else:
            try:
                self._socket.sendall(data)
            except TypeError:
                # Assume we need to convert to a str.
                UnixTransport._sendNeedsStr = True
                self.send(data)

    def processEvents(self):
        """
        Process any data to receive.  For each element received, call
        elementListener.onReceivedElement.
        This is non-blocking and will silently time out after a brief period if
        there is no data to receive.
        You should repeatedly call this from an event loop.
        You should normally not call this directly since it is called by
        Face.processEvents.
        If you call this from an main event loop, you may want to catch and
        log/disregard all exceptions.
        """
        if not self.getIsConnected():
            return

        # Loop until there is no more data in the receive buffer.
        while True:
            if not self._socketPoller.isReady():
                # There is no data waiting.
                return

            nBytesRead = self._socket.recv_into(self._buffer)
            if nBytesRead <= 0:
                # Since we checked for data ready, we don't expect this.
                return

            # _bufferView is a memoryview, so we can slice efficienty.
            self._elementReader.onReceivedData(self._bufferView[0:nBytesRead])

    def getIsConnected(self):
        """
        Check if the transport is connected.

        :return: True if connected.
        :rtype: bool
        """
        if self._socket == None:
            return False

        # Assume we are still connected.  TODO: Do a test receive?
        return True

    def close(self):
        """
        Close the connection.  If not connected, this does nothing.
        """
        if self._socketPoller != None:
            self._socketPoller.close()
            self._socketPoller = None

        if self._socket != None:
            self._socket.close()
            self._socket = None
