/*
 * Copyright (c) 2010-2011 Juli Mallett. All rights reserved.
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

#ifndef    CRYPTO_CRYPTO_RANDOM_H
#define    CRYPTO_CRYPTO_RANDOM_H

#include "../event/action.h"
#include "../event/event_callback.h"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// File:           crypto_random.h                                            //
// Description:    basic encryption machinery                                 //
// Project:        WANProxy XTech                                             //
// Adapted by:     Andreu Vidal Bramfeld-Software                             //
// Last modified:  2015-04-01                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

class CryptoRandomMethod;

/*
 * XXX
 * Add a CryptoTypeBest, which will use whatever the best, available method is.
 */
enum CryptoRandomType {
    CryptoTypeRNG,
    CryptoTypePRNG,
};

class CryptoRandomSession {
protected:
    CryptoRandomSession(void) {}

public:
    virtual ~CryptoRandomSession() {}

    //virtual Action *generate(size_t, EventCallback *) = 0;
};

class CryptoRandomMethod {
protected:
    CryptoRandomMethod(void) {}

    virtual ~CryptoRandomMethod() {}

public:
    virtual bool generate(CryptoRandomType, size_t, Buffer *) const = 0;

    virtual CryptoRandomSession *session(CryptoRandomType) const = 0;

    /* XXX Registration API somehow.  */
    static const CryptoRandomMethod *default_method;
};

#endif /* !CRYPTO_CRYPTO_RANDOM_H */
