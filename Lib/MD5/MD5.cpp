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

#include    "Sin.tbl"


HASHES_NAMESPACE_BEGIN
namespace  MD5  {

namespace  {

const   BtByte  s_tblPadding[64] = {
    0x80, 0, 0, 0,  0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0,
    0, 0, 0, 0,     0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0,
    0, 0, 0, 0,     0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0,
    0, 0, 0, 0,     0, 0, 0, 0,   0, 0, 0, 0,   0, 0, 0, 0
};

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
    this->m_context.regs[0] = 0x67452301;
    this->m_context.regs[1] = 0xEFCDAB89;
    this->m_context.regs[2] = 0x98BADCFE;
    this->m_context.regs[3] = 0x10325476;
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
    return  getHashValue();
}

//----------------------------------------------------------------
//    計算したハッシュ値を取得する。
//

MD5::MDCode
MD5::getHashValue()  const
{
    MDCode  output;

    output.words[0] = this->m_context.regs[0];
    output.words[1] = this->m_context.regs[1];
    output.words[2] = this->m_context.regs[2];
    output.words[3] = this->m_context.regs[3];

    return ( output );
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
        SIN_30, SIN_31, SIN_32, SIN_33, SIN_34, SIN_35, SIN_36, SIN_37,
        SIN_38, SIN_39, SIN_3A, SIN_3B, SIN_3C, SIN_3D, SIN_3E, SIN_3F,
        SIN_40, SIN_41, SIN_42, SIN_43, SIN_44, SIN_45, SIN_46, SIN_47,
        SIN_48, SIN_49, SIN_4A, SIN_4B, SIN_4C, SIN_4D, SIN_4E, SIN_4F,
    };

    for ( int i = 0; i < 64; ++ i ) {
        buf[i]  = table[i];
    }

    return;
}

//----------------------------------------------------------------
//    指定した 16 ワードブロックを処理する。
//

#define     F(x, y, z)  ( ((x) & (y)) | ((~(x)) & (z)) )
#define     G(x, y, z)  ( ((x) & (z)) | ((y) & (~(z))) )
#define     H(x, y, z)  ( (x) ^ (y) ^ (z) )
#define     I(x, y, z)  ( (y) ^ ((x) | (~(z))) )

#define     ROTATE_LEFT(x, n)   ( ((x) << (n)) | ((x) >> (32 - (n))) )

#define     ROUND_OPERATION(A, B, C, D, OPE, xk, s, sin)    {           \
    (A) += OPE((B), (C), (D)) + (xk) + static_cast<EDWordType>(sin);    \
    (A) = ROTATE_LEFT((A), (s));                                        \
    (A) += (B);                                                         \
}

inline  void
MD5::processBlock(
        const   LpcByteReadBuf  inBuf,
        MDWordType              regs[4])
{
    MDWordType  x[16];
    MDWordType  a = regs[0];
    MDWordType  b = regs[1];
    MDWordType  c = regs[2];
    MDWordType  d = regs[3];

    for ( int idx = 0, j = 0; idx < 16; ++ idx, j += 4 ) {
        x[idx]  = static_cast<MDWordType>(inBuf[j])
                        | (static_cast<MDWordType>(inBuf[j + 1]) <<  8)
                        | (static_cast<MDWordType>(inBuf[j + 2]) << 16)
                        | (static_cast<MDWordType>(inBuf[j + 3]) << 24);
    }

    //  このブロックの結果を引数 regs に加える  //
    regs[0] += a;
    regs[1] += b;
    regs[2] += c;
    regs[3] += d;
    return;
}

}   //  End of namespace  MD5
HASHES_NAMESPACE_END
