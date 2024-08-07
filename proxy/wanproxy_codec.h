/*
 * Copyright (c) 2010-2013 Juli Mallett. All rights reserved.
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

#ifndef    PROGRAMS_WANPROXY_WANPROXY_CODEC_H
#define    PROGRAMS_WANPROXY_WANPROXY_CODEC_H

#include "./wanproxy_config_type_codec.h"
#include "./wanproxy_config_type_compressor.h"
#include "../xcodec/xcodec_cache.h"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// File:           wanproxy_codec.h                                           //
// Description:    control parameters for each connection endpoint            //
// Project:        WANProxy XTech                                             //
// Adapted by:     Andreu Vidal Bramfeld-Software                             //
// Last modified:  2015-08-31                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

struct WANProxyCodec {
    std::string name_;
    WANProxyConfigCache cache_type_;
    std::string cache_path_;
    size_t cache_size_;
    UUID cache_uuid_;
    XCodecCache *xcache_;
    bool compressor_;
    char compressor_level_;
    bool counting_;
    intmax_t request_input_bytes_;
    intmax_t request_output_bytes_;
    intmax_t response_input_bytes_;
    intmax_t response_output_bytes_;

    WANProxyCodec(void)
            : name_(""),
              cache_type_(WANProxyConfigCacheMemory),
              cache_size_(0),
              xcache_(NULL),
              compressor_(false),
              compressor_level_(0),
              counting_(false),
              request_input_bytes_(0),
              request_output_bytes_(0),
              response_input_bytes_(0),
              response_output_bytes_(0) {}
};

#endif /* !PROGRAMS_WANPROXY_WANPROXY_CODEC_H */
