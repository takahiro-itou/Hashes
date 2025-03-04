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
#    include    "HashesSettings.h"
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

//========================================================================
//
//    Type Definitions.
//

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

HASHES_NAMESPACE_END

#endif
