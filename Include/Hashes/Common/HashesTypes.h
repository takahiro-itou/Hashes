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

#include    <cstdint>
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

//----------------------------------------------------------------
/**
**    型安全なブール型。
**/

enum  Boolean
{
    BOOL_FALSE  =  0,       /**<  偽。  **/
    BOOL_TRUE   =  1        /**<  真。  **/
};

//----------------------------------------------------------------
/**
**    ファイルの長さを表す型。
**/

typedef     size_t              FileLength;

//----------------------------------------------------------------
/**
**    バッファサイズ（要素数）を表す型。
**/

typedef     size_t              BufferSize;


//----------------------------------------------------------------
/**
**    読み取り専用バッファ。
**/

typedef     const  void  *      LpcReadBuf;

//----------------------------------------------------------------
/**
**    読み書き両用バッファ。
**/

typedef     void  *             LpWriteBuf;

//----------------------------------------------------------------
/**
**    バイト型。
**/

typedef     unsigned char       BtByte;

/**
**    バイト型の読み取り専用バッファ。
**/

typedef     const  BtByte  *    LpcByteReadBuf;

/**
**    バイト型の読み書き両用バッファ。
**/

typedef     BtByte  *           LpByteWriteBuf;


//========================================================================
//
//    安全なポインタ型のキャスト。
//

template  <typename  T>
T  pointer_cast(void * const p)
{
    return  static_cast<T>(p);
}

template  <typename  T>
T  pointer_cast(const void * const p)
{
    return  static_cast<T>(p);
}

HASHES_NAMESPACE_END

#endif
