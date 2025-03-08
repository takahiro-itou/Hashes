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
**      An Interface of FileDescriptor class.
**
**      @file       Common/FileDescriptor.h
**/

#if !defined( HASHES_COMMON_INCLUDED_FILE_DESCRIPTOR_H )
#    define   HASHES_COMMON_INCLUDED_SAMPLE_DOCUMENT_H

#if !defined( HASHES_COMMON_INCLUDED_HASHES_TYPES_H )
#    include    "HashesTypes.h"
#endif

#if !defined( HASHED_SYS_INCLUDED_FCNTL_H )
#    include    <fcntl.h>
#    define   HASHED_SYS_INCLUDED_FCNTL_H
#endif

#if !defined( HASHES_SYS_INCLUDED_STRING )
#    include    <string>
#    define   HASHES_SYS_INCLUDED_STRING
#endif


HASHES_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    FileDescriptor  class.
//

class  FileDescriptor
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
    FileDescriptor();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~FileDescriptor();

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
    /**   ファイルを閉じる。
    **
    **/
    virtual  ErrCode
    closeFile();

    //----------------------------------------------------------------
    /**   ファイルを開く。
    **
    **  @param [in] fileName    ファイル名。
    **  @param [in] mode        オープンモード。
    **/
    virtual  ErrCode
    openFile(
            const  std::string  &fileName,
            const  int  mode = O_RDONLY);

    virtual  ErrCode
    reopenFile();


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
    /**   ファイルディスクリプタを取得する。
    **
    **/
    const   int
    getFileDescriptor()  const
    {
        return ( this->m_descriptor );
    }

    //----------------------------------------------------------------
    /**   ファイルサイズを取得する。
    **
    **/
    const   FileLength
    getFileSize()  const
    {
        return ( this->m_cbFileSize );
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
    int             m_descriptor;

    /**   ファイル名。  **/
    std::string     m_fileName;

    /**   ファイルオープンモード。  **/
    int             m_oModeFlags;

    /**   ファイルサイズ。  **/
    FileLength      m_cbFileSize;

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   FileDescriptorTest;
};

}   //  End of namespace  Common
HASHES_NAMESPACE_END

#endif
