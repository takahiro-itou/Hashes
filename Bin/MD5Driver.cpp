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


using   namespace   HASHES_NAMESPACE;

int  main(int argc, char * argv[])
{
    static struct option long_opts[] = {
        { "binary", no_argument, 0, 'b' },
        { "check",  no_argument, 0, 'c' },
        { "text" ,  no_argument, 0, 't' },
        { "ignore-missing", no_argument, 0, 0 },
        { 0, 0, 0, 0 },
    };
    int     c;
    int     lo_index;

    while ( (c = getopt_long(argc, argv, "bct", long_opts, &lo_index)) != -1 )
    {
        switch ( c ) {
        case  0:
            switch ( lo_index ) {
            case  3:
                std::cout   <<  "option: ignore-missing"    <<  std::endl;
                break;
            default:
                std::cerr   <<  "unknown option."   <<  std::endl;
                break;
            }
            break;
        case  'b':
            std::cout   <<  "option: -b (--binary)" <<  std::endl;
            break;
        case  'c':
            std::cout   <<  "option: -c (--check)"  <<  std::endl;
            break;
        case  't':
            std::cout   <<  "option: -t (--text)"   <<  std::endl;
            break;
        default:
            std::cerr   <<  "Invalid Option:"
                        <<  std::endl;
            break;
        }
    }

    for ( ; optind < argc; ++ optind ) {
        std::cout   <<  "non-option :"
                    <<  argv[optind]    <<  std::endl;
    }

    return ( 0 );
}
