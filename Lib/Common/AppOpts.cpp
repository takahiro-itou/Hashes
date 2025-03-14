﻿//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---   Hash Functions Library   ---                  **
**                                                                      **
**          Copyright (C), 2025-2025, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING or LICENSE files)                     **
**          GNU Affero General Public License (AGPL) version 3,         **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of AppOpts class.
**
**      @file       Common/AppOpts.cpp
**/

#include    "Hashes/Common/AppOpts.h"

#include    <cstdlib>
#include    <getopt.h>
#include    <iostream>


HASHES_NAMESPACE_BEGIN
namespace  Common  {

namespace  {

inline  FileLength
parseSizeText(
        const  std::string  &optarg,
        ErrCode             &retErr)
{
    FileLength  sfactor = 1;
    size_t  idx = 0;
    const  unsigned  long   val = std::stoull(optarg, &idx, 0);

    if ( idx != optarg.size() ) {
        for ( ; idx < optarg.size(); ++ idx ) {
            if ( optarg[idx] == 'b' || optarg[idx] == 'B' ) {
                ++  idx;
                break;
            }

            switch ( optarg[idx] ) {
            case  'g':
            case  'G':
                sfactor *= 1024;
                //  no  break;
            case  'm':
            case  'M':
                sfactor *= 1024;
                //  no  break;
            case  'k':
            case  'K':
                sfactor *= 1024;
                break;
            }
        }
    }
    if ( idx != optarg.size() ) {
        std::cerr   <<  "Invalid argument: "
                    <<  optarg
                    <<  " at " <<   idx
                    <<  optarg[idx]
                    <<  "(" <<  optarg.size() << ")"
                    <<  std::endl;
        retErr  = ErrCode::FAILURE;
    }

    retErr  = ErrCode::SUCCESS;
    return ( val * sfactor );
}

}   //  End of (Unnamed) namespace.


//----------------------------------------------------------------
//    コマンドライン引数を解析する。
//

ErrCode
parseCommandLineArgs(
        AppOpts   & appOpts,
        const  int  argc,
        char *      argv[])
{
    static struct option long_opts[] = {
        { "binary", no_argument, nullptr, 'b' },
        { "check",  no_argument, nullptr, 'c' },
        { "text" ,  no_argument, nullptr, 't' },
        { "ignore-missing", no_argument, nullptr, 0 },
        { "pause",  required_argument, nullptr, 'p' },
        { "resume", required_argument, nullptr, 'r' },
        { "buffer-size", required_argument, nullptr, 's' },
        { 0, 0, 0, 0 },
    };

    ErrCode retErr;
    int     c;
    int     lo_index;

    for (;;) {
        c = getopt_long(
                argc, argv, "bcp:r:s:t", long_opts, &lo_index);
        if ( c == -1 ) {
            break;
        }

        switch ( c ) {
        case  0:
            switch ( lo_index ) {
            case  3:
                appOpts.flagIgnore  = BOOL_TRUE;
                break;
            default:
                std::cerr   <<  "unknown option."   <<  std::endl;
                break;
            }
            break;
        case  'b':
            appOpts.binaryMode  = BOOL_TRUE;
            break;
        case  'c':
            appOpts.checkMode   = BOOL_TRUE;
            break;
        case  'p':
            appOpts.pauseSize   = parseSizeText(optarg, retErr);
            break;
        case  'r':
            appOpts.resumeInfo  = std::string(optarg);
            break;
        case  's':
            appOpts.bufferSize  = parseSizeText(optarg, retErr);
            if ( appOpts.bufferSize <= 16 ) {
                appOpts.bufferSize  = 16;
            }
            break;
        case  't':
            appOpts.textMode    = BOOL_TRUE;
            break;
        default:
            std::cerr   <<  "Invalid Option:"
                        <<  std::endl;
            break;
        }
    }

    for ( ; optind < argc; ++ optind ) {
        appOpts.targetFiles.push_back(argv[optind]);
    }

    return ( ErrCode::SUCCESS );
}

}   //  End of namespace  Common
HASHES_NAMESPACE_END
