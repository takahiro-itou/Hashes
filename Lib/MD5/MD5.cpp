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
**      An Implementation of MD5 class.
**
**      @file       MD5/MD5.cpp
**/

#include    "Hashes/MD5/MD5.h"

#include    <memory.h>


#define     SIN_10  0xD76AA478
#define     SIN_11  0xE8C7B756
#define     SIN_12  0x242070DB
#define     SIN_13  0xC1BDCEEE
#define     SIN_14  0xF57C0FAF
#define     SIN_15  0x4787C62A
#define     SIN_16  0xA8304613
#define     SIN_17  0xFD469501
#define     SIN_18  0x698098D8
#define     SIN_19  0x8B44F7AF
#define     SIN_1A  0xFFFF5BB1
#define     SIN_1B  0x895CD7BE
#define     SIN_1C  0x6B901122
#define     SIN_1D  0xFD987193
#define     SIN_1E  0xA679438E
#define     SIN_1F  0x49B40821

HASHES_NAMESPACE_BEGIN
namespace  MD5  {

namespace  {

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    MD5  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

MD5::MD5()
    : m_context()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

MD5::~MD5()
{
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    ハッシュ値の計算バッファを初期化する。
//

ErrCode
MD5::initializeHash()
{
    this->m_context.regs[0] = 0;
    this->m_context.regs[1] = 0;
    this->m_context.regs[2] = 0;
    this->m_context.regs[3] = 0;
    this->m_context.numByte = 0;
    memset(this->m_context.buffer, 0, sizeof(this->m_context.buffer));

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    ハッシュ値の計算バッファを更新する。
//

ErrCode
MD5::updateHash(
        const   LpcReadBuf  inBuf,
        const   FileLength  cbBuf)
{
    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    ハッシュ値の計算を完了する。
//

MD5::MDCode
MD5::finalizeHash()
{
    MDCode  dummy = {};
    return ( dummy );
}

//----------------------------------------------------------------
//    計算したハッシュ値を取得する。
//

MD5::MDCode
MD5::getHashValue()  const
{
    MDCode  dummy = {};
    return ( dummy );
}

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    定数テーブルの内容をコピーする。
//
//    単体テストクラスにテーブルの値を渡して
//  内容をチェックしてもらうための関数。
//

void
MD5::copySinTable(uint32_t (&buf)[64])
{
    buf[ 0] = SIN_10; buf[ 1] = SIN_11; buf[ 2] = SIN_12; buf[ 3] = SIN_13;
    buf[ 4] = SIN_14; buf[ 5] = SIN_15; buf[ 6] = SIN_16; buf[ 7] = SIN_17;
    buf[ 8] = SIN_18; buf[ 9] = SIN_19; buf[10] = SIN_1A; buf[11] = SIN_1B;
    buf[12] = SIN_1C; buf[13] = SIN_1D; buf[14] = SIN_1E; buf[15] = SIN_1F;
}

}   //  End of namespace  MD5
HASHES_NAMESPACE_END
