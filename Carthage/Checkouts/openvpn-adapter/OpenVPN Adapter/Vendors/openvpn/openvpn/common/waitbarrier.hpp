//    OpenVPN -- An application to securely tunnel IP networks
//               over a single port, with support for SSL/TLS-based
//               session authentication and key exchange,
//               packet encryption, packet authentication, and
//               packet compression.
//
//    Copyright (C) 2012-2017 OpenVPN Technologies, Inc.
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License Version 3
//    as published by the Free Software Foundation.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program in the COPYING file.
//    If not, see <http://www.gnu.org/licenses/>.

#ifndef OPENVPN_COMMON_WAITBARRIER_H
#define OPENVPN_COMMON_WAITBARRIER_H

#include <openvpn/common/exception.hpp>
#include <openvpn/common/pthreadcond.hpp>

namespace openvpn {
  template <typename THREAD_COMMON>
  inline void event_loop_wait_barrier(THREAD_COMMON& tc,
				      const unsigned int seconds=10)
  {
    // barrier prior to event-loop entry
    switch (tc.event_loop_bar.wait(seconds))
      {
      case PThreadBarrier::SUCCESS:
	break;
      case PThreadBarrier::CHOSEN_ONE:
	tc.user_group.activate();
	tc.show_unused_options();
	tc.event_loop_bar.signal();
	break;
      case PThreadBarrier::TIMEOUT:
	throw Exception("event loop barrier timeout");
      case PThreadBarrier::ERROR:
	throw Exception("event loop barrier error");
      }
  }
}

#endif
