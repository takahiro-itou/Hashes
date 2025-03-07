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
**      An Interface of MD5 class.
**
**      @file       MD5/MD5.h
**/

#if !defined( HASHES_MD5_INCLUDED_MD5_H )
#    define   HASHES_MD5_INCLUDED_MD5_H

#include    "Hashes/Common/HashesTypes.h"


HASHES_NAMESPACE_BEGIN
namespace  MD5  {

//========================================================================
//
//    MD5  class.
//

class  MD5
{

//========================================================================
//
//    Internal Type Definitions.
//

public:

    enum  {
        BLOCK_BYTES         = 64,
        PROC_BYTES_MASK     = 0x3F,
        NUM_WORD_REGS       = 4,
        SIN_TABLE_SIZE      = 64,
    };

    /**   ワード型は 32 ビット。    **/
    typedef     uint32_t        MDWordType;

    /**   ハッシュ値を格納する型。  **/
    struct  MDCode  {
        MDWordType  words[NUM_WORD_REGS];
    };

private:

    typedef     uint64_t        LengthType;

    typedef     uint8_t         BtByte;

    typedef     BtByte          BufferType[64];

    /**   計算用バッファの型。  **/
    struct  ContextRegister
    {
        MDWordType  regs[NUM_WORD_REGS];
        LengthType  numByte;
        BtByte      buffer[BLOCK_BYTES];
    };

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    MD5();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~MD5();

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
public:

    //----------------------------------------------------------------
    /**   ハッシュ値の計算バッファを初期化する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    initializeHash();

    //----------------------------------------------------------------
    /**   ハッシュ値の計算バッファを更新する。
    **
    **  @param [in] inBuf   入力データのアドレス。
    **  @param [in] cbBuf   入力データのバイト数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    updateHash(
            const   LpcReadBuf  inBuf,
            const   FileLength  cbBuf);

    //----------------------------------------------------------------
    /**   ハッシュ値の計算を完了する。
    **
    **    計算した値はキャッシュに保存しておく。
    **
    **  @return    計算した値を返す。
    **/
    MDCode
    finalizeHash();

    //----------------------------------------------------------------
    /**   計算したハッシュ値を取得する。
    **
    **  @return   計算した値をキャッシュから返す。
    **/
    MDCode
    getHashValue()  const;

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
private:

    //----------------------------------------------------------------
    /**   定数テーブルの内容をコピーする。
    **
    **    単体テストクラスにテーブルの値を渡して
    **  内容をチェックしてもらうための関数。
    **/
    static  void
    copySinTable(uint32_t (&buf)[SIN_TABLE_SIZE]);

    //----------------------------------------------------------------
    /**   指定した 16 ワードブロックを処理する。
    **
    **  @param [in]     inBuf
    **  @param [in,out] regs
    **  @return     void.
    **/
    static  inline  void
    processBlock(
            const   LpcByteReadBuf  inBuf,
            MDWordType              regs[NUM_WORD_REGS]);

//========================================================================
//
//    Member Variables.
//
private:

    /**   計算用バッファ。  **/
    ContextRegister     m_context;

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   MD5Test;
};

}   //  End of namespace  MD5
HASHES_NAMESPACE_END

#endif
