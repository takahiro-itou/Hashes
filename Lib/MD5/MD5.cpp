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

}   //  End of namespace  MD5
HASHES_NAMESPACE_END
