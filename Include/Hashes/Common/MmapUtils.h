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
**      An Interface of MmapUtils class.
**
**      @file       Common/MmapUtils.h
**/

#if !defined( HASHES_COMMON_INCLUDED_MMAP_UTILS_H )
#    define   HASHES_COMMON_INCLUDED_MMAP_UTILS_H

#if !defined( HASHES_COMMON_INCLUDED_FILE_DESCRIPTOR_H )
#    include    "FileDescriptor.h"
#endif

#if !defined( HASHES_SYS_INCLUDED_STRING )
#    include    <string>
#    define   HASHES_SYS_INCLUDED_STRING
#endif


HASHES_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //
class   FileDescriptor;

//========================================================================
//
//    MmapUtils  class.
//

class  MmapUtils
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

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
    MmapUtils();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~MmapUtils();

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
public:

    //----------------------------------------------------------------
    /**   ファイル名を指定してマップする。
    **
    **  @param [in] fileName    ファイル名。
    **  @param [in] offset      マップを開始する位置。
    **  @param [in] cbSize      マップするバイト数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    mapToFile(
            const  std::string  &fileName,
            const  FileLength   offset,
            const  FileLength   cbSize);

    //----------------------------------------------------------------
    /**   ファイルディスクリプタを指定してマップする。
    **
    **  @param [in] fd        ディスクリプタ
    **  @param [in] offset    マップを開始する位置。
    **  @param [in] cbSize    マップするバイト数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    mapToFile(
            const   FileDescriptor  &fd,
            const   FileLength      offset,
            const   FileLength      cbSize);

    //----------------------------------------------------------------
    /**   マップを解除する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    releaseMapping();

    //----------------------------------------------------------------
    /**   同じファイルに対して再度マップする。
    **
    **    同じファイルなのでファイル名は省略する。
    **  別のファイルに対してマップする時は mapToFile  を使う。
    **
    **  @param [in] offset
    **  @param [in] cbSize
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    remapToFile(
            const  FileLength   offset,
            const  FileLength   cbSize);

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   マップした領域の先頭を指すポインタを取得する。
    **
    **  @return     マップした領域の先頭アドレスを返す。
    **/
    LpWriteBuf
    getAddress()  const
    {
        return ( this->m_ptrHead );
    }

    //----------------------------------------------------------------
    /**   マップ対象のファイルサイズを取得する。
    **
    **  @return     ファイルサイズをバイト単位で返す。
    **/
    FileLength
    getFileSize()  const;

    //----------------------------------------------------------------
    /**   マップした領域の長さを取得する。
    **
    **  @return     マップした領域のサイズをバイト単位で返す。
    **/
    FileLength
    getMapSize()  const
    {
        return ( this->m_mapLen );
    }

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:

    /**   ファイルディスクリプタ。  **/
    FileDescriptor      m_fd;

    /**   マップした領域。          **/
    LpWriteBuf          m_ptrBuf;

    /**   マップした領域のサイズ。  **/
    FileLength          m_mapLen;

    FileLength          m_mapOffs;

    /**   オフセット込みの先頭。    **/
    LpWriteBuf          m_ptrHead;

    /**   ページサイズ。    **/
    long                m_pgSize;

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   MmapUtilsTest;
};

}   //  End of namespace  Common
HASHES_NAMESPACE_END

#endif
