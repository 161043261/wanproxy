/*
 * Copyright (c) 2009-2011 Juli Mallett. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef    IO_NET_UDP_SERVER_H
#define    IO_NET_UDP_SERVER_H

#include "../socket/socket.h"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// File:           udp_server.h                                               //
// Description:    base class for a datagram network server                   //
// Project:        WANProxy XTech                                             //
// Adapted by:     Andreu Vidal Bramfeld-Software                             //
// Last modified:  2015-04-01                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

class UDPServer {
    LogHandle log_;
    Socket *socket_;

public:
    UDPServer() : log_("/udp/server"), socket_(0) {}

    ~UDPServer() {
        delete socket_;
    }

    bool listen(SocketAddressFamily family, const std::string &name);

    Action *read(EventCallback *cb) {
        return (socket_ ? socket_->read(cb) : 0);
    }

    Action *close(EventCallback *cb) {
        return (socket_ ? socket_->close(cb) : 0);
    }

    std::string getsockname(void) const {
        return (socket_ ? socket_->getsockname() : std::string());
    }
};

#endif /* !IO_NET_UDP_SERVER_H */
