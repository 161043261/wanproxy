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

#include <unistd.h>
#include "../common/log.h"
#include "../event/event_system.h"
#include "./wanproxy.h"

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// File:           wanproxy.cc                                                //
// Description:    session start and global application management            //
// Project:        WANProxy XTech                                             //
// Adapted by:     Andreu Vidal Bramfeld-Software                             //
// Last modified:  2016-02-28                                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define PROGRAM_VERSION        "3.0.5"

WanProxyCore wanproxy;

static void usage(void);


int main(int argc, char *argv[]) {
    std::string configfile;
    bool quiet, verbose;
    int ch;

    quiet = verbose = false;

    INFO("/wanproxy") << "WANProxy MT " << PROGRAM_VERSION;
    INFO("/wanproxy") << "Copyright (c) 2008-2013 WANProxy.org";
    INFO("/wanproxy") << "Copyright (c) 2013-2018 Bramfeld-Software";
    INFO("/wanproxy") << "All rights reserved.";

    while ((ch = getopt(argc, argv, "c:qv")) != -1) {
        switch (ch) {
            case 'c':
                configfile = optarg;
                break;
            case 'q':
                quiet = true;
                break;
            case 'v':
                verbose = true;
                break;
            default:
                usage();
        }
    }

    if (configfile.empty())
        usage();

    if (quiet && verbose)
        usage();

    if (verbose)
        Log::mask(".?", Log::Debug);
    else if (quiet)
        Log::mask(".?", Log::Error);
    else
        Log::mask(".?", Log::Info);

    if (!wanproxy.configure(configfile)) {
        ERROR("/wanproxy") << "Could not configure proxies.";
        wanproxy.terminate();
        return 1;
    }

    event_system.run();

    wanproxy.terminate();

    return 0;
}

static void usage(void) {
    INFO("/wanproxy/usage") << "wanproxy [-q | -v] -c configfile";
    exit(1);
}

