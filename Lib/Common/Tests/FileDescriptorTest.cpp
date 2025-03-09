﻿//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
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
**      An Implementation of Test Case 'FileDescriptor'.
**
**      @file       Common/Tests/FileDescriptorTest.cpp
**/

#include    "TestDriver.h"
#include    "Hashes/Common/FileDescriptor.h"

#include    <stdio.h>


HASHES_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    FileDescriptorTest  class.
//
/**
**    クラス FileDescriptor の単体テスト。
**/

class  FileDescriptorTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(FileDescriptorTest);
    CPPUNIT_TEST(testGetFileSize);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testGetFileSize();
};

CPPUNIT_TEST_SUITE_REGISTRATION( FileDescriptorTest );

//========================================================================
//
//    Tests.
//

void  FileDescriptorTest::testGetFileSize()
{
    char    buf[1024] = { 0 };

    FILE *  fp  = fopen("dummy.bin", "wb");

    fwrite(buf, 1, sizeof(buf), fp);
    fwrite(buf, 1, sizeof(buf), fp);
    fwrite(buf, 1, 123, fp);
    fclose(fp);

    FileDescriptor  fd;
    fd.openFile("dummy.bin");
    CPPUNIT_ASSERT_EQUAL(2171UL, fd.getFileSize());

    return;
}

}   //  End of namespace  Common
HASHES_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
