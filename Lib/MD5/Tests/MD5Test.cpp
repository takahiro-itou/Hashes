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
    CPPUNIT_TEST(testUpdateHash);

    CPPUNIT_TEST(testHashValue1);
    CPPUNIT_TEST(testHashValue2);
    CPPUNIT_TEST(testHashValue3);
    CPPUNIT_TEST(testHashValue4);
    CPPUNIT_TEST(testHashValue5);
    CPPUNIT_TEST(testHashValue6);

    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testMD5();

    void  testFinalizeHash();
    void  testInitializeHash();
    void  testUpdateHash();

    void  testHashValue1();
    void  testHashValue2();
    void  testHashValue3();
    void  testHashValue4();
    void  testHashValue5();
    void  testHashValue6();

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

    //  初期化直後は以下の通り  RFC1321 Page4 (Little Endian)
    //  word A: 01 23 45 67 = 0x67452301
    //  word B: 89 ab cd ef = 0xefcdab89
    //  word C: fe dc ba 98 = 0x98badcfe
    //  word D: 76 54 32 10 = 0x10325476
    CPPUNIT_ASSERT_EQUAL(0x67452301U, testee.m_context.regs[0]);
    CPPUNIT_ASSERT_EQUAL(0xEFCDAB89U, testee.m_context.regs[1]);
    CPPUNIT_ASSERT_EQUAL(0x98BADCFEU, testee.m_context.regs[2]);
    CPPUNIT_ASSERT_EQUAL(0x10325476U, testee.m_context.regs[3]);

    return;
}

void  MD5Test::testUpdateHash()
{
    TestTarget  testee;
    TestTarget::MDCode  out;

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.initializeHash());
    CPPUNIT_ASSERT_EQUAL(
            ErrCode::SUCCESS, testee.updateHash("message ", 8));
    CPPUNIT_ASSERT_EQUAL(
            ErrCode::SUCCESS, testee.updateHash("digest", 6));

    out = testee.finalizeHash();

    //  MD5 test suite
    //  MD5("message digest") = f96b697d7cb7938d525a2f31aaf161d0
    //  1st: f9 6b 69 7d = 0x7d696bf9
    //  2nd: 7c b7 93 8d = 0x8d93b77c
    //  3rd: 52 5a 2f 31 = 0x312f5a52
    //  4th: aa f1 61 d0 = 0xd061f1aa
    CPPUNIT_ASSERT_EQUAL(0x7D696BF9U, out.words[0]);
    CPPUNIT_ASSERT_EQUAL(0x8D93B77CU, out.words[1]);
    CPPUNIT_ASSERT_EQUAL(0x312F5A52U, out.words[2]);
    CPPUNIT_ASSERT_EQUAL(0xD061F1AAU, out.words[3]);

    return;
}

void  MD5Test::testHashValue1()
{
    TestTarget  testee;
    TestTarget::MDCode  out;

    CPPUNIT_ASSERT_EQUAL(ErrCode::SUCCESS, testee.initializeHash());
    CPPUNIT_ASSERT_EQUAL(
            ErrCode::SUCCESS, testee.updateHash("a", 1));
    out = testee.finalizeHash();

    //  MD5 test suite
    //  MD5("a") = 0cc175b9c0f1b6a831c399e269772661
    //  1st: 0c c1 75 b9 = 0xb975c10c
    //  2nd: c0 f1 b6 a8 = 0xa8b6f1c0
    //  3rd: 31 c3 99 e2 = 0xe299c331
    //  4th: 69 77 26 61 = 0x61267769
    CPPUNIT_ASSERT_EQUAL(0xB975C10CU, out.words[0]);
    CPPUNIT_ASSERT_EQUAL(0xA8B6F1C0U, out.words[1]);
    CPPUNIT_ASSERT_EQUAL(0xE299C331U, out.words[2]);
    CPPUNIT_ASSERT_EQUAL(0x61267769U, out.words[3]);

    return;
}

void  MD5Test::testHashValue2()
{
}

void  MD5Test::testHashValue3()
{
}

void  MD5Test::testHashValue4()
{
}

void  MD5Test::testHashValue5()
{
}

void  MD5Test::testHashValue6()
{
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
