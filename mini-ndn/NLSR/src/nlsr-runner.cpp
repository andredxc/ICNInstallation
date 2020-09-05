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

#include "nlsr-runner.hpp"
#include "conf-file-processor.hpp"
#include "logger.hpp"

namespace nlsr {

INIT_LOGGER(NlsrRunner);

NlsrRunner::NlsrRunner(std::string& configFileName)
  : m_scheduler(m_ioService)
  , m_face(m_ioService)
  , m_nlsr(m_ioService, m_scheduler, m_face, m_keyChain)
{
  m_nlsr.setConfFileName(configFileName);
}

void
NlsrRunner::run()
{
  ConfFileProcessor configProcessor(m_nlsr, m_nlsr.getConfFileName());

  if (!configProcessor.processConfFile()) {
    BOOST_THROW_EXCEPTION(Error("Error in configuration file processing! Exiting from NLSR"));
  }

  /** Because URI canonization needs to occur before initialization,
      we have to pass initialize as the finally() in neighbor
      canonization.
  */
  m_nlsr.canonizeNeighborUris(m_nlsr.getAdjacencyList().getAdjList().begin(),
                              [this] (std::list<Adjacent>::iterator iterator) {
                                m_nlsr.canonizeContinuation(iterator, [this] {
                                    m_nlsr.initialize();
                                  });
                              },
                              [this] {
                                m_nlsr.initialize();
                              });
  try {
    m_nlsr.startEventLoop();
  }
  catch (const std::exception& e) {
    NLSR_LOG_FATAL("ERROR: " << e.what());
    std::cerr << "ERROR: " << e.what() << std::endl;

    m_nlsr.getFib().clean();
  }
}

void
NlsrRunner::printUsage(const std::string& programName)
{
  std::cout << "Usage: " << programName << " [OPTIONS...]" << std::endl;
  std::cout << "   NDN routing...." << std::endl;
  std::cout << "       -f <FILE>   Specify configuration file name" << std::endl;
  std::cout << "       -V          Display version information" << std::endl;
  std::cout << "       -h          Display this help message" << std::endl;
}

} // namespace nlsr
