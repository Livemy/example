/******************************************************************************
		     (c) COPYRIGHT 2000-2008 by Harbour Networks System, Ltd.
                              All rights reserved.

     This software is confidential and proprietary to Harbour Networks
     System, Ltd. No part of this software may be reproduced, stored,
     transmitted, disclosed or used in any form or by any means other
     than as expressly provided by the written license agreement between
     Harbour Networks System and its licensee.
===============================================================================
�ļ���   : complex.cpp 
�ļ����� : 
��ʷ��¼ : 
  ����              ����            �汾                �޶�˵��
huangmeng1698     2004-03-15         V1.0                  ����
******************************************************************************/
#include "complex.h"

/******************************************************************************
�������� :  ==����������
������� :  a
            b
������� :  ��
�� �� ֵ :  bool
��    �� :  huangmeng1698
��    �� :  2004-03-15 19:45:06
******************************************************************************/
bool operator ==(const CComplex &a, const CComplex &b)
{ 
    int i;
    return true;
}

/******************************************************************************
�������� :  !=����������
������� :  a
            b
������� :  ��
�� �� ֵ :  bool
��    �� :  huangmeng1698
��    �� :  2004-03-15 19:45:06
******************************************************************************/
bool operator !=(const CComplex& a, const CComplex& b)
{
    return true;
}

bool CComplex::Test(int i)
{
    if (1 == i)
        return true;
    else
        return false;
}