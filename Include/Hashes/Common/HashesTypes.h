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
**      Type Definitions.
**
**      @file       Common/HashesTypes.h
**/

#if !defined( HASHES_COMMON_INCLUDED_HASHES_TYPES_H )
#    define   HASHES_COMMON_INCLUDED_HASHES_TYPES_H

#include    "HashesSettings.h"

#include    <stddef.h>


HASHES_NAMESPACE_BEGIN

//========================================================================
//
//    Type Definitions.
//

//----------------------------------------------------------------
/**
**    エラーコード。
**/

enum class  ErrCode
{
    /**   正常終了。    **/
    SUCCESS             = 0,

    /**   異常終了。エラーの理由は不明または報告なし。  **/
    FAILURE             = 1,

    /**   ファイルオープンエラー。  **/
    FILE_OPEN_ERROR     = 2,

    /**   ファイル入出力エラー。    **/
    FILE_IO_ERROR       = 3,
};

HASHES_NAMESPACE_END

#endif
