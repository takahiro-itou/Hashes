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
    LpcByteReadBuf  lpInput = static_cast<LpcByteReadBuf>(inBuf);
    LpByteWriteBuf  buffer  = this->m_context.buffer;

    FileLength  bufPos  = ((this->m_context.numByte) & 0x3F);
    this->m_context.numByte += cbBuf;

    size_t      cbCopy  = BLOCK_BYTES - bufPos;
    FileLength  remLen  = cbBuf;
    if ( cbCopy <= cbBuf ) {
        memcpy(buffer + bufPos, lpInput, cbCopy);
        lpInput += cbCopy;
        remLen  -= cbCopy;
        bufPos  = 0;
        processBlock(buffer, this->m_context.regs);
    }

    for ( ; remLen >= BLOCK_BYTES ;
            lpInput += BLOCK_BYTES, remLen -= BLOCK_BYTES )
    {
        processBlock(lpInput, this->m_context.regs);
    }

    memcpy(buffer + bufPos, lpInput, remLen);
    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    ハッシュ値の計算を完了する。
//

MD5::MDCode
MD5::finalizeHash()
{
    BtByte  bits[8];

    FileLength  cbByte  = (this->m_context.numByte);
    const   FileLength  cbBits  = (cbByte << 3);

    bits[0] = ((cbBits      ) & 0xFF);
    bits[1] = ((cbBits >>  8) & 0xFF);
    bits[2] = ((cbBits >> 16) & 0xFF);
    bits[3] = ((cbBits >> 24) & 0xFF);
    bits[4] = ((cbBits >> 32) & 0xFF);
    bits[5] = ((cbBits >> 40) & 0xFF);
    bits[6] = ((cbBits >> 48) & 0xFF);
    bits[7] = ((cbBits >> 56) & 0xFF);

    //  パディングを実施。  //
    cbByte  &= 0x3F;
    const   FileLength  padLen  = (120 - cbByte) & 0x3F;
    updateHash(s_tblPadding, padLen);

    //  パディング前のビット数を追加。  //
    updateHash(bits, sizeof(bits));

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
    (A) += OPE((B), (C), (D)) + (xk) + static_cast<MDWordType>(sin);    \
    (A) = ROTATE_LEFT((A), (s));                                        \
    (A) += (B);                                                         \
}

#define     ROUND1(A, B, C, D, X, k, s, sin)    \
    ROUND_OPERATION(A, B, C, D, F, X[k], s, sin)

#define     ROUND2(A, B, C, D, X, k, s, sin)    \
    ROUND_OPERATION(A, B, C, D, G, X[k], s, sin)

#define     ROUND3(A, B, C, D, X, k, s, sin)    \
    ROUND_OPERATION(A, B, C, D, H, X[k], s, sin)

#define     ROUND4(A, B, C, D, X, k, s, sin)    \
    ROUND_OPERATION(A, B, C, D, I, X[k], s, sin)

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

    //  ROUND1  //
    ROUND1(a, b, c, d, x,  0,  7, SIN_10);
    ROUND1(d, a, b, c, x,  1, 12, SIN_11);
    ROUND1(c, d, a, b, x,  2, 17, SIN_12);
    ROUND1(b, c, d, a, x,  3, 22, SIN_13);

    ROUND1(a, b, c, d, x,  4,  7, SIN_14);
    ROUND1(d, a, b, c, x,  5, 12, SIN_15);
    ROUND1(c, d, a, b, x,  6, 17, SIN_16);
    ROUND1(b, c, d, a, x,  7, 22, SIN_17);

    ROUND1(a, b, c, d, x,  8,  7, SIN_18);
    ROUND1(d, a, b, c, x,  9, 12, SIN_19);
    ROUND1(c, d, a, b, x, 10, 17, SIN_1A);
    ROUND1(b, c, d, a, x, 11, 22, SIN_1B);

    ROUND1(a, b, c, d, x, 12,  7, SIN_1C);
    ROUND1(d, a, b, c, x, 13, 12, SIN_1D);
    ROUND1(c, d, a, b, x, 14, 17, SIN_1E);
    ROUND1(b, c, d, a, x, 15, 22, SIN_1F);

    //  ROUND2  //
    ROUND2(a, b, c, d, x,  1,  5, SIN_20);
    ROUND2(d, a, b, c, x,  6,  9, SIN_21);
    ROUND2(c, d, a, b, x, 11, 14, SIN_22);
    ROUND2(b, c, d, a, x,  0, 20, SIN_23);

    ROUND2(a, b, c, d, x,  5,  5, SIN_24);
    ROUND2(d, a, b, c, x, 10,  9, SIN_25);
    ROUND2(c, d, a, b, x, 15, 14, SIN_26);
    ROUND2(b, c, d, a, x,  4, 20, SIN_27);

    ROUND2(a, b, c, d, x,  9,  5, SIN_28);
    ROUND2(d, a, b, c, x, 14,  9, SIN_29);
    ROUND2(c, d, a, b, x,  3, 14, SIN_2A);
    ROUND2(b, c, d, a, x,  8, 20, SIN_2B);

    ROUND2(a, b, c, d, x, 13,  5, SIN_2C);
    ROUND2(d, a, b, c, x,  2,  9, SIN_2D);
    ROUND2(c, d, a, b, x,  7, 14, SIN_2E);
    ROUND2(b, c, d, a, x, 12, 20, SIN_2F);

    //  ROUND3  //
    ROUND3(a, b, c, d, x,  5,  4, SIN_30);
    ROUND3(d, a, b, c, x,  8, 11, SIN_31);
    ROUND3(c, d, a, b, x, 11, 16, SIN_32);
    ROUND3(b, c, d, a, x, 14, 23, SIN_33);

    ROUND3(a, b, c, d, x,  1,  4, SIN_34);
    ROUND3(d, a, b, c, x,  4, 11, SIN_35);
    ROUND3(c, d, a, b, x,  7, 16, SIN_36);
    ROUND3(b, c, d, a, x, 10, 23, SIN_37);

    ROUND3(a, b, c, d, x, 13,  4, SIN_38);
    ROUND3(d, a, b, c, x,  0, 11, SIN_39);
    ROUND3(c, d, a, b, x,  3, 16, SIN_3A);
    ROUND3(b, c, d, a, x,  6, 23, SIN_3B);

    ROUND3(a, b, c, d, x,  9,  4, SIN_3C);
    ROUND3(d, a, b, c, x, 12, 11, SIN_3D);
    ROUND3(c, d, a, b, x, 15, 16, SIN_3E);
    ROUND3(b, c, d, a, x,  2, 23, SIN_3F);

    //  ROUND4  //
    ROUND4(a, b, c, d, x,  0,  6, SIN_40);
    ROUND4(d, a, b, c, x,  7, 10, SIN_41);
    ROUND4(c, d, a, b, x, 14, 15, SIN_42);
    ROUND4(b, c, d, a, x,  5, 21, SIN_43);

    ROUND4(a, b, c, d, x, 12,  6, SIN_44);
    ROUND4(d, a, b, c, x,  3, 10, SIN_45);
    ROUND4(c, d, a, b, x, 10, 15, SIN_46);
    ROUND4(b, c, d, a, x,  1, 21, SIN_47);

    ROUND4(a, b, c, d, x,  8,  6, SIN_48);
    ROUND4(d, a, b, c, x, 15, 10, SIN_49);
    ROUND4(c, d, a, b, x,  6, 15, SIN_4A);
    ROUND4(b, c, d, a, x, 13, 21, SIN_4B);

    ROUND4(a, b, c, d, x,  4,  6, SIN_4C);
    ROUND4(d, a, b, c, x, 11, 10, SIN_4D);
    ROUND4(c, d, a, b, x,  2, 15, SIN_4E);
    ROUND4(b, c, d, a, x,  9, 21, SIN_4F);

    //  このブロックの結果を引数 regs に加える  //
    regs[0] += a;
    regs[1] += b;
    regs[2] += c;
    regs[3] += d;
    return;
}

}   //  End of namespace  MD5
HASHES_NAMESPACE_END
