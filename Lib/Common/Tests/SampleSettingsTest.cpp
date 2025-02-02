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
**      An Implementation of Test Case 'SampleSettings'.
**
**      @file       Common/Tests/SampleSettingsTest.cpp
**/

#include    "TestDriver.h"
#include    "Hashes/Common/SampleSettings.h"


HASHES_NAMESPACE_BEGIN

//========================================================================
//
//    SampleSettingsTest  class.
//
/**
**    クラス SampleSettings の単体テスト。
**/

class  SampleSettingsTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(SampleSettingsTest);
    CPPUNIT_TEST(testNameSpace);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testNameSpace();
};

CPPUNIT_TEST_SUITE_REGISTRATION( SampleSettingsTest );

//========================================================================
//
//    Tests.
//

void  SampleSettingsTest::testNameSpace()
{
    return;
}

HASHES_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
