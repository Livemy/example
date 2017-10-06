/******************************************************************************
		     (c) COPYRIGHT 2000-2008 by Harbour Networks System, Ltd.
                              All rights reserved.

     This software is confidential and proprietary to Harbour Networks
     System, Ltd. No part of this software may be reproduced, stored,
     transmitted, disclosed or used in any form or by any means other
     than as expressly provided by the written license agreement between
     Harbour Networks System and its licensee.
===============================================================================
�ļ���   : testcomplex2.cpp
�ļ����� : 
��ʷ��¼ : 
  ����              ����            �汾                �޶�˵��
huangmeng1698     2004-03-15         V1.0                  ����
******************************************************************************/
#include "testcomplex2.h"


CppUnit::Test* CTestComplex2::suite()
{
    typedef void (CTestComplex2::* TestMethod)();
    TestMethod p;

    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "ComplexTest" );
    
    p = &CTestComplex2::testEqual;
    suiteOfTests->addTest(new CppUnit::TestCaller<CTestComplex2>("testEqual", p));

    p = &CTestComplex2::testUnequal;
    suiteOfTests->addTest(new CppUnit::TestCaller<CTestComplex2>("testUnequal", p));
    return suiteOfTests;
}

void CTestComplex2::setUp()
{

}

void CTestComplex2::tearDown()
{

}

void CTestComplex2::testEqual()
{
    CPPUNIT_ASSERT(false);
}

void CTestComplex2::testUnequal()
{

}






