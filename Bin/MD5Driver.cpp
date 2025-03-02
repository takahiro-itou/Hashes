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
**      サンプルプログラム。
**
**      @file       Bin/MD5Driver.cpp
**/

#include    "Hashes/MD5/MD5.h"

#include    <getopt.h>
#include    <iostream>
#include    <string>
#include    <vector>


using   namespace   HASHES_NAMESPACE;

typedef     std::vector<std::string>    StringArray;

struct  AppOpts  {
    Boolean     binaryMode;
    Boolean     textMode;
    Boolean     checkMode;
    Boolean     flagIgnore;
    FileLength  pauseSize;
    Boolean     flagResume;
    StringArray targetFiles;

    AppOpts()
        : binaryMode(BOOL_FALSE),
          textMode(BOOL_FALSE),
          checkMode(BOOL_FALSE),
          flagIgnore(BOOL_FALSE),
          pauseSize(0),
          flagResume(BOOL_FALSE),
          targetFiles()
    { }
};

int  main(int argc, char * argv[])
{
    static struct option long_opts[] = {
        { "binary", no_argument, nullptr, 'b' },
        { "check",  no_argument, nullptr, 'c' },
        { "text" ,  no_argument, nullptr, 't' },
        { "ignore-missing", no_argument, nullptr, 0 },
        { "pause",  required_argument, nullptr, 'p' },
        { "resume", no_argument, nullptr, 'r' },
        { "buffer-size", required_argument, nullptr, 's' },
        { 0, 0, 0, 0 },
    };
    AppOpts appOpts;
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
            appOpts.flagResume  = BOOL_TRUE;
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

    return ( 0 );
}
