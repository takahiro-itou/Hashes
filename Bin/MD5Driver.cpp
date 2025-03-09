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

MD5::MD5::MDCode
runCalcHash(
        Common::ResumeInfo  &resInfo,
        const  FileLength   cbBlock)
{
    MD5::MD5            hash;
    MD5::MD5::MDCode    reg;
    Common::MmapUtils   mmap;
    char                buf[64];

    FileLength          cbRead  = 0;
    const   FileLength  cbPause = resInfo.processLen;
    ErrCode             retErr;

    std::cerr   <<  "INFO: BufferSize = "  <<  cbBlock  <<  std::endl;

    if ( resInfo.resumeOffs == 0 ) {
        hash.initializeHash();
    }

    retErr  = mmap.setupMappingToFile(resInfo.targetFile.c_str());
    if ( retErr != ErrCode::SUCCESS ) {
        return;
    }
    const   FileLength  fileLen = mmap.getFileSize();

    while ( cbRead + cbBlock <= fileLen ) {
        retErr  = mmap.remapToFile(cbRead, cbBlock);
        hash.updateHash(mmap.getAddress(), cbBlock);
        cbRead  += cbBlock;
        std::cerr   <<  "\rINFO: read "
                    <<  cbRead  <<  " / "   <<  fileLen
                    <<  " ("    <<  (cbRead * 100 / fileLen)
                    <<  " %)";
    }
    const   FileLength  cbRems  = (fileLen - cbRead);
    if ( cbRead > 0 ) {
        retErr  = mmap.remapToFile(cbRead, cbRems);
        hash.updateHash(mmap.getAddress(), cbRems);
        cbRead  += cbRems;
    }
    std::cerr   <<  "\rINFO: read "
                <<  cbRead  <<  " / "   <<  fileLen
                <<  " ("    <<  (cbRead * 100 / fileLen)
                <<  std::endl;

    if ( cbRead < fileLen ) {
        //  途中の場合は、その時点での内部状態を表示。  //
        reg = hash.getHashValue();
    } else {
        //  最後まで到達していたら終了処理を行う。  //
        reg = hash.finalizeHash();
    }

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
    std::cout   <<  buf;
    if ( cbRead < fileLen ) {
        sprintf(buf, " 0x%08x,", cbRead);
        std::cout   <<  buf;
    }
    std::cout   <<  " *"    <<  fileName    <<  std::endl;

    return ( reg )
}

void
computeHash(
        const  std::string      &fileName,
        const  Common::AppOpts  &appOpts)
{
    Common::ResumeInfo  resInfo;

    resInfo.binaryMode  = appOpts.binaryMode;
    resInfo.resumeOffs  = 0;
    resInfo.processLen  = appOpts.pauseSize;
    resInfo.targetFile  = fileName;

    runCalcHash(resumeInfo, appOpts.bufferSize)
}

int  main(int argc, char * argv[])
{
    Common::AppOpts     appOpts;
    Common::parseCommandLineArgs(appOpts, argc, argv);

    for ( size_t i = 0; i < appOpts.targetFiles.size(); ++ i ) {
        computeHash(appOpts.targetFiles[i], appOpts);
    }

    return ( 0 );
}
