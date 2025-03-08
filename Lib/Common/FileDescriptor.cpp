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
**      An Implementation of FileDescriptor class.
**
**      @file       Common/FileDescriptor.cpp
**/

#include    "Hashes/Common/FileDescriptor.h"

#include    <sys/stat.h>
#include    <unistd.h>


HASHES_NAMESPACE_BEGIN
namespace  Common  {

namespace  {

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    FileDescriptor  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。

FileDescriptor::FileDescriptor()
    : m_descriptor(-1),
      m_fileName(),
      m_cbFileSize(0)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

FileDescriptor::~FileDescriptor()
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

//----------------------------------------------------------------
//    ファイルを閉じる。
//

ErrCode
FileDescriptor::closeFile()
{
    if ( this->m_descriptor < 0 ) {
        //  ファイルが開かれていないので、何もすることが無い。  //
        return ( ErrCode::SUCCESS );
    }

    close(this->m_descriptor);
    this->m_descriptor  = -1;

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    ファイルを開く。
//

ErrCode
FileDescriptor::openFile(
        const  std::string  &fileName,
        const  int          mode)
{
    struct stat stbuf;

    //  現在開かれているファイルを閉じる。  //
    closeFile();

    //  指定されたファイルを開く。  //
    int fd  = open(fileName.c_str(), mode);
    if ( fd == -1 ) {
        return ( ErrCode::FILE_OPEN_ERROR );
    }

    //  ファイルサイズを取得しておく。  //
    if ( fstat(fd, &stbuf) == -1 ) {
    }
    this->m_cbFileSize  = stbuf.st_size;

    //  ファイルディスクリプタを記憶。  //
    this->m_descriptor  = fd;
    this->m_fileName    = fileName;
    this->m_oModeFlags  = mode;

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    最後に使ったファイルを開きなおす。
//

ErrCode
FileDescriptor::reopenFile()
{
    if ( this->m_fileName.empty() ) {
        return ( ErrCode::FILE_OPEN_ERROR );
    }

    return  openFile(this->m_fileName, this->m_oModeFlags);
}

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

}   //  End of namespace  Common
HASHES_NAMESPACE_END
