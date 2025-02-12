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
**      An Implementation of Test Case 'MD5'.
**
**      @file       MD5/Tests/MD5Test.cpp
**/

#include    "TestDriver.h"
#include    "Hashes/MD5/MD5.h"


HASHES_NAMESPACE_BEGIN
namespace  MD5  {

//========================================================================
//
//    MD5Test  class.
//
/**
**    クラス MD5  の単体テスト。
**/

class  MD5Test : public  TestFixture
{
    CPPUNIT_TEST_SUITE(MD5Test);
    CPPUNIT_TEST(testMD5);
    CPPUNIT_TEST(testInitializeHash);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testMD5();

    void  testInitializeHash();

    typedef     MD5     TestTarget;
};

CPPUNIT_TEST_SUITE_REGISTRATION( MD5Test );

//========================================================================
//
//    Tests.
//

void  MD5Test::testMD5()
{
    TestTarget  testee;
    return;
}

void  MD5Test::testInitializeHash()
{
    TestTarget  testee;

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.initializeHash());
    return;
}

}   //  End of namespace  MD5
HASHES_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
