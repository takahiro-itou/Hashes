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

#include    "HashesSettings.h"

#include    <string>


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

//========================================================================
//
//    Public Member Functions.
//

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

//========================================================================
//
//    Member Variables.
//
private:

    /**   ファイルディスクリプタ。  **/
    int             m_descriptor;

    /**   ファイル名。  **/
    std::string     m_fileName;

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
