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
    CPPUNIT_TEST(testFinalizeHash);
    CPPUNIT_TEST(testInitializeHash);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testMD5();

    void  testFinalizeHash();
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

void  MD5Test::testFinalizeHash()
{
    TestTarget  testee;
    TestTarget::MDCode  out;

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.initializeHash());
    out = testee.finalizeHash();

    //  MD5 test suite
    //  MD5("") = d41d8cd98f00b204e9800998ecf8427e
    //  1st: d4 1d 8c d9 = 0xd98c1dd4
    //  2nd: 8f 00 b2 04 = 0x04b2008f
    //  3rd: e9 80 09 98 = 0x980980e9
    //  4th: ec f8 42 7e = 0x7e42f8ec
    CPPUNIT_ASSERT_EQUAL(0xD98C1DD4U, out.words[0]);
    CPPUNIT_ASSERT_EQUAL(0x04B2008FU, out.words[1]);
    CPPUNIT_ASSERT_EQUAL(0x980980E9U, out.words[2]);
    CPPUNIT_ASSERT_EQUAL(0x7E42F8ECU, out.words[3]);

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
