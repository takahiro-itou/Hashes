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
#include    <sys/mman.h>
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
      m_mapLen(0),
      m_mapOffs(0),
      m_ptrHead(nullptr),
      m_pgSize(sysconf(_SC_PAGE_SIZE))
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
    //  境界をページサイズに合わせる。  //
    const   FileLength  pgSize  = (this->m_pgSize);
    const   FileLength  pgOffs  = (offset / pgSize) * pgSize;
    const   FileLength  trgOffs = (offset - pgOffs);
    const   FileLength  pgByte  = (cbSize + trgOffs);

    void *  ptr = mmap( nullptr, pgByte, PROT_READ, MAP_PRIVATE,
                        this->m_fd.getFileDescriptor(), pgOffs);
    if ( ptr == MAP_FAILED ) {
        return ( ErrCode::FAILURE );
    }

    //  マップが完了したらディスクリプタは閉じてよい。  //
    //fd.closeFile();

    this->m_ptrBuf  = ptr;
    this->m_mapLen  = pgByte;
    this->m_mapOffs = trgOffs;
    this->m_ptrHead = static_cast<LpByteWriteBuf>(ptr) + trgOffs;

    return ( ErrCode::SUCCESS );
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

//----------------------------------------------------------------
//    ファイルに対してマップの準備をする。
//

ErrCode
MmapUtils::setupMappingToFile(
        const  std::string  &fileName)
{
    ErrCode     retErr  = ErrCode::FAILURE;

    retErr  = this->m_fd.openFile(fileName);
    if ( retErr != ErrCode::SUCCESS ) {
        return ( retErr );
    }

    //  ファイルは一旦閉じておく。  //
    retErr  =  this->m_fd.closeFile();
    return ( retErr );
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
