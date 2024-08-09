//
// Created by Tiancheng on 2024/8/9.
//

#ifndef PROGRAMS_WANPROXY_UDP_PROXY_LISTENNER_H
#define PROGRAMS_WANPROXY_UDP_PROXY_LISTENNER_H

#include "../event/action.h"
#include "../event/event.h"
#include "../io/net/udp_server.h"
#include "./wanproxy_codec.h"
#include "../common/log.h"


class UdpProxyListener : public UDPServer {
    LogHandle log_;
    std::string name_;
    WANProxyCodec *local_codec_;
    WANProxyCodec *remote_codec_;
    SocketAddressFamily local_family_;
    std::string local_address_;
    SocketAddressFamily remote_family_;
    std::string remote_address_;
    bool is_cln_, is_ssh_;
    Action *accept_action_;
    Action *stop_action_;
};


#endif // PROGRAMS_WANPROXY_UDP_PROXY_LISTENNER_H
