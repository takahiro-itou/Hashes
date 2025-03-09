//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
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
        const  std::string  &optarg)
{
    FileLength  sfactor = 1;
    size_t  idx = 0;
    const  unsigned  long   val = std::stoull(optarg, &idx, 0);

    if ( idx != optarg.size() ) {
        for ( size_t pos = 0; pos < optarg.size(); ++ pos ) {
            switch ( optarg[pos] ) {
            case  'k':
            case  'K':
                sfactor *= 1024;
                break;
            case  'm':
            case  'M':
                sfactor *= (1024 * 1024);
                break;
            case  'g':
            case  'G':
                sfactor *= (1024 * 1024 * 1024);
                break;
            }
            if ( optarg[pos] == 'b' || optarg[pos] == 'B' ) {
                ++  pos;
                break;
            }
        }
    }
    if ( idx != optarg.size() ) {
        std::cerr   <<  "Invalid argument: "    <<  optarg  <<  std::endl;
    }

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

    int     c;
    int     lo_index;

    for (;;) {
        c = getopt_long(
                argc, argv, "bct", long_opts, &lo_index);
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
            break;
        case  'r':
            appOpts.resumeInfo  = std::string(optarg);
            break;
        case  's':
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
