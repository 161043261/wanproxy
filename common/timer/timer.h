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


#ifndef    COMMON_TIMER_TIMER_H
#define    COMMON_TIMER_TIMER_H

#include "../log.h"
#include <vector>

typedef unsigned long long uintmax_t;
typedef long long intmax_t;
typedef unsigned int uintptr_t; /* XXX Appears to be in stddef.h!  */
typedef int socklen_t;
typedef unsigned long long uint64_t;

class Timer {
    uintmax_t start_;
    uintmax_t stop_;

    std::vector<uintmax_t> samples_;
public:
    Timer(void)
            : start_(),
              stop_(),
              samples_() {}

    ~Timer() {}

    void reset(void) {
        samples_.clear();
    }

    void start(void);

    void stop(void);

    uintmax_t sample(void) const {
        if (samples_.size() != 1)
            HALT("/timer") << "Requested 1 sample but " << samples_.size() << " available.";
        return (samples_[0]);
    }

    std::vector<uintmax_t> samples(void) const {
        return (samples_);
    }
};

#endif /* !COMMON_TIMER_TIMER_H */
