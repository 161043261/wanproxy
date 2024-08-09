/*
 * Copyright (c) 2008-2011 Juli Mallett. All rights reserved.
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

#ifndef    XCODEC_XCODEC_ENCODER_H
#define    XCODEC_XCODEC_ENCODER_H

#include "./xcodec_hash.h"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// File:           xcodec_encoder.h                                           //
// Description:    encoding routines for the xcodex protocol                  //
// Project:        WANProxy XTech                                             //
// Adapted by:     Andreu Vidal Bramfeld-Software                             //
// Last modified:  2016-02-28                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

class XCodecCache;

class XCodecEncoder {
    LogHandle log_;
    XCodecCache *cache_;
    Buffer source_;
    XCodecHash xcodec_hash_;
    int candidate_start_;
    uint64_t candidate_symbol_;

public:
    XCodecEncoder(XCodecCache *);

    ~XCodecEncoder();

    void encode(Buffer &, Buffer &);

    bool flush(Buffer &);

private:
    void encode_declaration(Buffer &, Buffer &, unsigned, uint64_t);

    void encode_escape(Buffer &, Buffer &, unsigned);

    bool encode_reference(Buffer &, Buffer &, unsigned, uint64_t, Buffer &);
};

#endif /* !XCODEC_XCODEC_ENCODER_H */
