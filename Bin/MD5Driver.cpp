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
#include    "Hashes/Common/AppOpts.h"

#include    <iostream>
#include    <string>
#include    <vector>


using   namespace   HASHES_NAMESPACE;

void
computeHash(
        const  std::string  &fileName)
{
    MD5::MD5            hash;
    MD5::MD5::MDCode    reg;
    BtByte              inbuf[1024];
    char                buf[32];

    hash.initializeHash();

    FILE *  fp  = fopen(fileName.c_str(), "rb");
    if ( fp != nullptr ) {
        std::cerr   <<  "File not found:"
                    <<  fileName    <<  std::endl;
        return;
    }

    size_t  cbRead  = 1024;
    while ( cbRead ) {
        cbRead  = fread(inbuf, sizeof(BtByte), 1024, fp);
        if ( cbRead == 0 ) {
            break;
        }
        hash.updateHash(inbuf, cbRead);
    }
    reg = hash.finalizeHash();

    for ( int i = 0; i < 4; ++ i ) {
        const  MD5::MD5::MDWordType val = reg.words[i];
        sprintf(buf + (i << 3),
                "%02x%02x%02x%02x",
                ((val      ) & 0xFF),
                ((val >>  8) & 0xFF),
                ((val >> 16) & 0xFF),
                ((val >> 24) & 0xFF)
        );
    }
    std::cout   <<  buf <<  " *"    <<  fileName    <<  std::endl;
    return;
}

int  main(int argc, char * argv[])
{
    Common::AppOpts     appOpts;
    Common::parseCommandLineArgs(appOpts, argc, argv);

    for ( size_t i = 0; i < appOpts.targetFiles.size(); ++ i ) {
        computeHash(appOpts.targetFiles[i]);
    }

    return ( 0 );
}
