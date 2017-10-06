/******************************************************************************
		     (c) COPYRIGHT 2000-2008 by Harbour Networks System, Ltd.
                              All rights reserved.

     This software is confidential and proprietary to Harbour Networks
     System, Ltd. No part of this software may be reproduced, stored,
     transmitted, disclosed or used in any form or by any means other
     than as expressly provided by the written license agreement between
     Harbour Networks System and its licensee.
===============================================================================
�ļ���   : testcomplex2.h
�ļ����� : 
��ʷ��¼ : 
  ����              ����            �汾                �޶�˵��
huangmeng1698     2004-03-15         V1.0                  ����
******************************************************************************/
#ifndef _TEST_COMPLEX2_H_
#define _TEST_COMPLEX2_H_

#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"
#include "../complex.h"

class CTestComplex2 : public CppUnit::TestFixture 
{ 
private:
    CComplex *m_p1;
    CComplex *m_p2;
    
public: 
    CTestComplex2() : m_p1(NULL), m_p2(NULL){}
    
    CppUnit::Test* suite();
    
    void setUp();
    void tearDown();

    void testEqual();
    void testUnequal();
};

#endif/*_TEST_COMPLEX2_H_*/
