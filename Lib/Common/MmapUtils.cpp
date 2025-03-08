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
**      An Implementation of MmapUtils class.
**
**      @file       Common/MmapUtils.cpp
**/

#include    "Hashes/Common/MmapUtils.h"

#include    <sys/stat.h>
#include    <unistd.h>


HASHES_NAMESPACE_BEGIN
namespace  Common  {

namespace  {

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    MmapUtils  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。

MmapUtils::MmapUtils()
    : m_fd(),
      m_ptrBuf(nullptr),
      m_mapLen(0)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

MmapUtils::~MmapUtils()
{
    releaseMapping();
    this->m_fd.closeFile();
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
//    ファイル名を指定してマップする。
//

ErrCode
MmapUtils::mapToFile(
        const  std::string  &fileName,
        const  FileLength   offset,
        const  FileLength   cbSize)
{
    ErrCode     retErr  = ErrCode::FAILURE;

    retErr  = this->m_fd.openFile(fileName);
    if ( retErr != ErrCode::SUCCESS ) {
        return ( retErr );
    }

    return  mapToFile(this->m_fd, offset, cbSize);
}

//----------------------------------------------------------------
//    ファイルディスクリプタを指定してマップする。
//

ErrCode
MmapUtils::mapToFile(
        const   FileDescriptor  &fd,
        const   FileLength      offset,
        const   FileLength      cbSize)
{
}

//----------------------------------------------------------------
//    マップを解除する。
//

ErrCode
MmapUtils::releaseMapping()
{
    if ( munmap(this->m_ptrBuf, this->m_mapLen) == -1 ) {
        perror("munmap");
    }

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    同じファイルに対して再度マップする。
//

ErrCode
MmapUtils::remapToFile(
        const  FileLength   offset,
        const  FileLength   cbSize)
{
    ErrCode     retErr  = ErrCode::FAILURE;

    retErr  = this->m_fd.reopenFile();
    if ( retErr != ErrCode::SUCCESS ) {
        return ( retErr );
    }

    return  mapToFile(this->m_fd, offset, cbSize);
}

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    マップ対象のファイルサイズを取得する。
//

FileLength
MmapUtils::getFileSize()  const
{
    return  this->m_fd.getFileSize();
}

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
