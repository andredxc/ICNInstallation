/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2014-2018,  The University of Memphis,
 *                           Regents of the University of California,
 *                           Arizona Board of Regents.
 *
 * This file is part of NLSR (Named-data Link State Routing).
 * See AUTHORS.md for complete list of NLSR authors and contributors.
 *
 * NLSR is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * NLSR is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * NLSR, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include "sync-logic-handler.hpp"
#include "common.hpp"
#include "conf-parameter.hpp"
#include "lsa.hpp"
#include "utility/name-helper.hpp"
#include "logger.hpp"

namespace nlsr {

INIT_LOGGER(SyncLogicHandler);

const std::string NLSR_COMPONENT = "nlsr";
const std::string LSA_COMPONENT = "LSA";

template<class T>
class NullDeleter
{
public:
  void
  operator()(T*)
  {
  }
};

SyncLogicHandler::SyncLogicHandler(ndn::Face& face, const IsLsaNew& isLsaNew,
                                   const ConfParameter& conf)
  : onNewLsa(ndn::make_unique<OnNewLsa>())
  , m_syncFace(face)
  , m_isLsaNew(isLsaNew)
  , m_confParam(conf)
{
}

void
SyncLogicHandler::createSyncSocket(const ndn::Name& syncPrefix, const ndn::time::milliseconds& syncInterestLifetime)
{
  if (m_syncSocket != nullptr) {
    NLSR_LOG_WARN("Trying to create Sync socket, but Sync socket already exists");
    return;
  }

  m_syncPrefix = syncPrefix;

  // Build LSA sync update prefix
  buildUpdatePrefix();

  NLSR_LOG_DEBUG("Creating Sync socket. Sync Prefix: " << m_syncPrefix);

  // The face's lifetime is managed in main.cpp; SyncSocket should not manage the memory
  // of the object
  std::shared_ptr<ndn::Face> facePtr(&m_syncFace, NullDeleter<ndn::Face>());

  const auto fixedSession = ndn::name::Component::fromNumber(0);
  m_syncSocket = std::make_shared<chronosync::Socket>(m_syncPrefix, m_nameLsaUserPrefix, *facePtr,
                                                      std::bind(&SyncLogicHandler::onChronoSyncUpdate, this, _1),
                                                      chronosync::Socket::DEFAULT_NAME, chronosync::Socket::DEFAULT_VALIDATOR,
                                                      syncInterestLifetime, fixedSession);

  if (m_confParam.getHyperbolicState() == HYPERBOLIC_STATE_OFF) {
    m_syncSocket->addSyncNode(m_adjLsaUserPrefix, chronosync::Socket::DEFAULT_NAME, fixedSession);
  }
  else if (m_confParam.getHyperbolicState() == HYPERBOLIC_STATE_ON) {
    m_syncSocket->addSyncNode(m_coorLsaUserPrefix, chronosync::Socket::DEFAULT_NAME, fixedSession);
  }
  else {
    m_syncSocket->addSyncNode(m_adjLsaUserPrefix, chronosync::Socket::DEFAULT_NAME, fixedSession);
    m_syncSocket->addSyncNode(m_coorLsaUserPrefix, chronosync::Socket::DEFAULT_NAME, fixedSession);
  }
}

void
SyncLogicHandler::onChronoSyncUpdate(const std::vector<chronosync::MissingDataInfo>& v)
{
  NLSR_LOG_DEBUG("Received ChronoSync update event");

  for (size_t i = 0; i < v.size(); i++){
    ndn::Name updateName = v[i].session.getPrefix(-1);

    NLSR_LOG_DEBUG("Update Name: " << updateName << " Seq no: " << v[i].high);

    int32_t nlsrPosition = util::getNameComponentPosition(updateName, nlsr::NLSR_COMPONENT);
    int32_t lsaPosition = util::getNameComponentPosition(updateName, nlsr::LSA_COMPONENT);

    if (nlsrPosition < 0 || lsaPosition < 0) {
      NLSR_LOG_WARN("Received malformed sync update");
      return;
    }

    ndn::Name networkName = updateName.getSubName(1, nlsrPosition-1);
    ndn::Name routerName = updateName.getSubName(lsaPosition + 1).getPrefix(-1);

    ndn::Name originRouter = networkName;
    originRouter.append(routerName);

    processUpdateFromSync(originRouter, updateName, v[i].high);
  }
}

void
SyncLogicHandler::processUpdateFromSync(const ndn::Name& originRouter,
                                        const ndn::Name& updateName, const uint64_t& seqNo)
{
  NLSR_LOG_DEBUG("Origin Router of update: " << originRouter);

  // A router should not try to fetch its own LSA
  if (originRouter != m_confParam.getRouterPrefix()) {

    Lsa::Type lsaType;
    std::istringstream(updateName.get(updateName.size()-1).toUri()) >> lsaType;

    NLSR_LOG_DEBUG("Received sync update with higher " << lsaType
               << " sequence number than entry in LSDB");

    if (m_isLsaNew(originRouter, lsaType, seqNo)) {
      if (lsaType == Lsa::Type::ADJACENCY && seqNo != 0 &&
          m_confParam.getHyperbolicState() == HYPERBOLIC_STATE_ON) {
        NLSR_LOG_ERROR("Got an update for adjacency LSA when hyperbolic routing"
                   << " is enabled. Not going to fetch.");
        return;
      }

      if (lsaType == Lsa::Type::COORDINATE && seqNo != 0 &&
          m_confParam.getHyperbolicState() == HYPERBOLIC_STATE_OFF) {
        NLSR_LOG_ERROR("Got an update for coordinate LSA when link-state"
                   << " is enabled. Not going to fetch.");
        return;
      }
      (*onNewLsa)(updateName, seqNo);
    }
  }
}

void
SyncLogicHandler::publishRoutingUpdate(const Lsa::Type& type, const uint64_t& seqNo)
{
  if (m_syncSocket == nullptr) {
    NLSR_LOG_FATAL("Cannot publish routing update; SyncSocket does not exist");

    BOOST_THROW_EXCEPTION(SyncLogicHandler::Error("Cannot publish routing update; SyncSocket does not exist"));
  }

  switch (type) {
  case Lsa::Type::ADJACENCY:
    publishSyncUpdate(m_adjLsaUserPrefix, seqNo);
    break;
  case Lsa::Type::COORDINATE:
    publishSyncUpdate(m_coorLsaUserPrefix, seqNo);
    break;
  case Lsa::Type::NAME:
    publishSyncUpdate(m_nameLsaUserPrefix, seqNo);
    break;
  default:
    break;
  }
}

void
SyncLogicHandler::buildUpdatePrefix()
{
  ndn::Name updatePrefix = m_confParam.getLsaPrefix();
  updatePrefix.append(m_confParam.getSiteName());
  updatePrefix.append(m_confParam.getRouterName());

  m_nameLsaUserPrefix = updatePrefix;
  m_nameLsaUserPrefix.append(std::to_string(Lsa::Type::NAME));

  m_adjLsaUserPrefix = updatePrefix;
  m_adjLsaUserPrefix.append(std::to_string(Lsa::Type::ADJACENCY));

  m_coorLsaUserPrefix = updatePrefix;
  m_coorLsaUserPrefix.append(std::to_string(Lsa::Type::COORDINATE));
}

void
SyncLogicHandler::publishSyncUpdate(const ndn::Name& updatePrefix, uint64_t seqNo)
{
  NLSR_LOG_DEBUG("Publishing Sync Update. Prefix: " << updatePrefix << " Seq No: " << seqNo);

  ndn::Name updateName(updatePrefix);
  std::string data("NoData");

  m_syncSocket->publishData(reinterpret_cast<const uint8_t*>(data.c_str()), data.size(),
                            ndn::time::milliseconds(1000), seqNo, updateName);
}

} // namespace nlsr
