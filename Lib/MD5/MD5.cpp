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

#define     SIN_20  0xF61E2562
#define     SIN_21  0xC040B340
#define     SIN_22  0x265E5A51
#define     SIN_23  0xE9B6C7AA
#define     SIN_24  0xD62F105D
#define     SIN_25  0x02441453
#define     SIN_26  0xD8A1E681
#define     SIN_27  0xE7D3FBC8
#define     SIN_28  0x21E1CDE6
#define     SIN_29  0xC44707D6
#define     SIN_2A  0xF4D50D87
#define     SIN_2B  0x455A14ED
#define     SIN_2C  0xA9E3E905
#define     SIN_2D  0xFCEFA3F8
#define     SIN_2E  0x676F02D9
#define     SIN_2F  0x8D2A4C8A

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
    uint32_t    table[64] = {
        SIN_10, SIN_11, SIN_12, SIN_13, SIN_14, SIN_15, SIN_16, SIN_17,
        SIN_18, SIN_19, SIN_1A, SIN_1B, SIN_1C, SIN_1D, SIN_1E, SIN_1F,
        SIN_20, SIN_21, SIN_22, SIN_23, SIN_24, SIN_25, SIN_26, SIN_27,
        SIN_28, SIN_29, SIN_2A, SIN_2B, SIN_2C, SIN_2D, SIN_2E, SIN_2F,
    };

    for ( int i = 0; i < 64; ++ i ) {
        buf[i]  = table[i];
    }

    return;
}

}   //  End of namespace  MD5
HASHES_NAMESPACE_END
