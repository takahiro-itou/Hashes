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

std::ostream  &
showProgress(
        const   FileLength  cbRead,
        const   FileLength  posLast,
        const   FileLength  fileLen,
        std::ostream       &outStr)
{
    outStr  <<  "\rINFO: read "
            <<  cbRead  <<  " / "   <<  posLast
            <<  " ("    <<  (cbRead * 100 / fileLen)
            <<  " %) [" <<  fileLen <<  "]";
    return ( outStr );
}

ErrCode
runCalcHash(
        Common::ResumeInfo      &resInfo,
        const  FileLength       cbBlock,
        const  Common::AppOpts  &appOpts)
{
    MD5::MD5            hash;
    MD5::MD5::MDCode    reg;
    Common::MmapUtils   mmap;
    char                buf[64];

    if ( appOpts.resumeInfo.empty() ) {
        hash.initializeHash();
    } else {
        hash.resumeHash(appOpts.resumeInfo, resInfo);
    }

    FileLength          cbRead  = resInfo.resumeOffs;
    const   FileLength  cbPause = resInfo.processLen;
    ErrCode             retErr;

    std::cerr   <<  "INFO: BufferSize = "  <<  cbBlock  <<  std::endl;
    std::cerr   <<  "INFO: cbRead = " << cbRead
                <<  ", cbPause = "  <<  cbPause
                <<  std::endl;
    retErr  = mmap.setupMappingToFile(resInfo.targetFile.c_str());
    if ( retErr != ErrCode::SUCCESS ) {
        return ( retErr );
    }

    const   FileLength  fileLen = mmap.getFileSize();
    FileLength  cbTail  = (cbPause > 0 ? (cbRead + cbPause) : fileLen);

    const   FileLength  posLast = (cbTail < fileLen ? cbTail : fileLen);
    while ( cbRead + cbBlock <= posLast ) {
        retErr  = mmap.remapToFile(cbRead, cbBlock);
        hash.updateHash(mmap.getAddress(), cbBlock);
        cbRead  += cbBlock;
        showProgress(cbRead, posLast, fileLen, std::cerr);
    }
    const   FileLength  cbRems  = (posLast - cbRead);
    showProgress(cbRead, posLast, fileLen, std::cerr)   <<  std::endl;
    std::cerr   <<  "INFO: cbRems = " <<  cbRems  <<  std::endl;

    if ( cbRems > 0 ) {
        retErr  = mmap.remapToFile(cbRead, cbRems);
        hash.updateHash(mmap.getAddress(), cbRems);
        cbRead  += cbRems;
    }
    showProgress(cbRead, posLast, fileLen, std::cerr)   <<  std::endl;

    if ( cbRead < fileLen ) {
        //  途中の場合は、その時点での内部状態を表示。  //
        std::cout   <<  hash.saveHash();
        std::cout   <<  "*"    <<  resInfo.targetFile  <<  std::endl;
        retErr  = ErrCode::PAUSED;
    } else {
        //  最後まで到達していたら終了処理を行う。  //
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
        std::cout   <<  buf;
        std::cout   <<  " *"    <<  resInfo.targetFile  <<  std::endl;
        retErr  = ErrCode::SUCCESS;
    }


    return ( retErr );
}

ErrCode
computeHash(
        const  std::string      &fileName,
        const  Common::AppOpts  &appOpts)
{
    Common::ResumeInfo  resInfo;

    resInfo.binaryMode  = appOpts.binaryMode;
    resInfo.resumeOffs  = 0;
    resInfo.processLen  = appOpts.pauseSize;
    resInfo.targetFile  = fileName;

    return  runCalcHash(resInfo, appOpts.bufferSize, appOpts);
}

int  main(int argc, char * argv[])
{
    Common::AppOpts     appOpts;
    Common::parseCommandLineArgs(appOpts, argc, argv);

    ErrCode     retErr  = ErrCode::SUCCESS;

    for ( size_t i = 0; i < appOpts.targetFiles.size(); ++ i ) {
        const  ErrCode  ec  = computeHash(appOpts.targetFiles[i], appOpts);
        if ( ec != ErrCode::SUCCESS ) {
            retErr  = ec;
        }
    }

    return ( static_cast<int>(retErr) );
}
