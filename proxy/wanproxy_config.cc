/*
 * Copyright (c) 2008-2012 Juli Mallett. All rights reserved.
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

#include <deque>
#include <fstream>
#include <sstream>

#include "../config/config.h"
#include "../config/config_class.h"
#include "../config/config_class_log_mask.h"

#include "../event/event_callback.h"

#include "./wanproxy_config.h"
#include "./wanproxy_config_class_codec.h"
#include "./wanproxy_config_class_interface.h"
#include "./wanproxy_config_class_peer.h"
#include "./wanproxy_config_class_proxy.h"
// #include "./wanproxy_config_class_monitor.h"
// #include "./wanproxy_config_class_proxy_socks.h"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// File:           wanproxy_config.cc                                         //
// Description:    high-level configuration parser                            //
// Project:        WANProxy XTech                                             //
// Adapted by:     Andreu Vidal Bramfeld-Software                             //
// Last modified:  2015-04-01                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

WANProxyConfig::WANProxyConfig(void) : log_("/wanproxy/config"), config_(NULL) {}

WANProxyConfig::~WANProxyConfig() {
    delete config_;
}

bool WANProxyConfig::parse(std::deque<std::string> &tokens) {
    std::string command = tokens.front();
    tokens.pop_front();

    if (command == "activate") {
        parse_activate(tokens);
    } else if (command == "create") {
        parse_create(tokens);
    } else if (command == "set") {
        parse_set(tokens);
    } else {
        tokens.clear();
        ERROR(log_) << "Unrecognized configuration command: " << command;
    }

    return tokens.empty();
}

void WANProxyConfig::parse_activate(std::deque<std::string> &tokens) {
    if (tokens.size() != 1) {
        ERROR(log_) << "Wrong number of words in activate (" << tokens.size() << ")";
        return;
    }

    if (!config_->activate(tokens[0])) {
        ERROR(log_) << "Object (" << tokens[0] << ") activation failed.";
        return;
    }
    tokens.clear();
}

void WANProxyConfig::parse_create(std::deque<std::string> &tokens) {
    if (tokens.size() != 2) {
        ERROR(log_) << "Wrong number of words in create (" << tokens.size() << ")";
        return;
    }

    if (!config_->create(tokens[0], tokens[1])) {
        ERROR(log_) << "Object (" << tokens[1] << ") could not be created.";
        return;
    }
    tokens.clear();
}

void WANProxyConfig::parse_set(std::deque<std::string> &tokens) {
    if (tokens.size() != 2) {
        ERROR(log_) << "Wrong number of words in set (" << tokens.size() << ")";
        return;
    }

    std::string::iterator dot = std::find(tokens[0].begin(), tokens[0].end(), '.');
    if (dot == tokens[0].end()) {
        ERROR(log_) << "Identifier (" << tokens[0] << ") is not an object member identifier.";
        return;
    }

    std::string object(tokens[0].begin(), dot);
    std::string member(dot + 1, tokens[0].end());
    if (object == "" || member == "") {
        ERROR(log_) << "Object (" << object << ") or member name (" << member << ") is empty.";
        return;
    }

    if (!config_->set(object, member, tokens[1])) {
        ERROR(log_) << "Set of object member (" << tokens[0] << ") failed.";
        return;
    }
    tokens.clear();
}

bool WANProxyConfig::read_file(const std::string &path) {
    delete config_;
    config_ = NULL;

    INFO(log_) << "Configuring WANProxy.";

    if (path.empty()) {
        ERROR(log_) << "No file name specified";
        return false;
    }

    std::fstream in;
    in.open(path.c_str(), std::ios::in);

    if (!in.good()) {
        ERROR(log_) << "Could not open file: " << path;
        return false;
    }

    config_ = new Config();
    config_->import(&config_class_log_mask);
    config_->import(&wanproxy_config_class_codec);
    config_->import(&wanproxy_config_class_interface);
    //config_->import(&wanproxy_config_class_monitor);
    config_->import(&wanproxy_config_class_peer);
    config_->import(&wanproxy_config_class_proxy);
    //config_->import(&wanproxy_config_class_proxy_socks);

    std::deque<std::string> tokens;

    while (in.good()) {
        std::string line;
        std::getline(in, line);

        if (line[0] == '#' || line.empty())
            continue;

        std::istringstream is(line);
        while (is.good()) {
            std::string word;
            is >> word;
            if (word.empty())
                continue;
            if (word[0] == '#')
                break;
            tokens.push_back(word);
        }
        if (tokens.empty())
            continue;
        if (!parse(tokens)) {
            ERROR(log_) << "Error in configuration directive: " << line;
            delete config_;
            config_ = NULL;
            return false;
        }
        ASSERT(log_, tokens.empty());
    }

    return true;
}

