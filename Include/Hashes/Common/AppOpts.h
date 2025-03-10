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
**      An Interface of AppOpts struct.
**
**      @file       Common/AppOpts.h
**/

#if !defined( HASHES_COMMON_INCLUDED_APP_OPTS_H )
#    define   HASHES_COMMON_INCLUDED_APP_OPTS_H

#if !defined( HASHES_COMMON_INCLUDED_HASHES_TYPES_H )
#    include    "HashesTypes.h"
#endif

#if !defined( HASHES_SYS_INCLUDED_STRING )
#    include    <string>
#    define   HASHES_SYS_INCLUDED_STRING
#endif

#if !defined( HASHES_SYS_INCLUDED_VECTOR )
#    include    <vector>
#    define   HASHES_SYS_INCLUDED_VECTOR
#endif


HASHES_NAMESPACE_BEGIN
namespace  Common  {


//========================================================================
//
//    Type Definitions.
//

typedef     std::vector<std::string>    StringArray;

struct  ResumeInfo  {
    Boolean     binaryMode;
    FileLength  resumeOffs;
    FileLength  processLen;
    std::string targetFile;

    ResumeInfo()
        : binaryMode(BOOL_TRUE),
          resumeOffs(0),
          processLen(0),
          targetFile( )
    { }
};

struct  AppOpts  {
    Boolean     binaryMode;
    Boolean     textMode;
    Boolean     checkMode;
    Boolean     flagIgnore;
    FileLength  bufferSize;
    FileLength  pauseSize;
    std::string resumeInfo;
    StringArray targetFiles;

    AppOpts()
        : binaryMode(BOOL_FALSE),
          textMode(BOOL_FALSE),
          checkMode(BOOL_FALSE),
          flagIgnore(BOOL_FALSE),
          bufferSize(8 * 1024 * 1024),
          pauseSize (0),
          resumeInfo(),
          targetFiles()
    { }
};

//========================================================================

//----------------------------------------------------------------
/**   コマンドライン引数を解析する。
**
**/

ErrCode
parseCommandLineArgs(
        AppOpts   & appOpts,
        const  int  argc,
        char *      argv[]);

}   //  End of namespace  Common
HASHES_NAMESPACE_END

#endif
