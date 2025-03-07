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
    MD5::MD5    hash;

    hash.initializeHash();

    hash.finalizeHash();
}

int  main(int argc, char * argv[])
{
    Common::AppOpts     appOpts;
    Common::parseCommandLineArgs(appOpts, argc, argv);

    return ( 0 );
}
