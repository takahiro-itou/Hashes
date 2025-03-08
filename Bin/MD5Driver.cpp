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
#include    "Hashes/Common/MmapUtils.h"

#include    <iostream>
#include    <string>
#include    <unistd.h>
#include    <vector>


using   namespace   HASHES_NAMESPACE;

void
computeHash(
        const  std::string  &fileName)
{
    MD5::MD5            hash;
    MD5::MD5::MDCode    reg;
    Common::MmapUtils   mmap;
    BtByte              inbuf[1024];
    char                buf[32];
    FileLength          cbRead  = 0;
    const   FileLength  cbBlock = 1024 * 1024;
    ErrCode             retErr;

    hash.initializeHash();

    retErr  = mmap.setupMappingToFile(fileName.c_str());
    const   FileLength  fileLen = mmap.getFileSize();
    std::cerr   <<  "INFO: fileLen = "  <<  fileLen <<  std::endl;

    while ( cbRead + cbBlock <= fileLen ) {
        retErr  = mmap.remapToFile(cbRead, cbBlock);
        hash.updateHash(mmap.getAddress(), cbBlock);
        cbRead  += cbBlock;
    }
    const   FileLength  cbRems  = (fileLen - cbRead);
    if ( cbRead > 0 ) {
        retErr  = mmap.remapToFile(cbRead, cbRems);
        hash.updateHash(mmap.getAddress(), cbRems);
        cbRead  += cbRems;
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
