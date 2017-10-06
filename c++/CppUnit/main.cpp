#include <iostream>
#include "cppunit/TestCaller.h"
#include "cppunit/TestResult.h"
#include "cppunit/ui/text/TestRunner.h"
#include "unittest/testcomplex.h"
#include "unittest/testcomplex2.h"
#include "unittest/testcomplex3.h"
using namespace std;

int main(int argc, char *argv[])
{
    /*=======================��TestCase����====================*/
    /*CTestComplex a("test");
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(&a);
    runner.run();*/

    /*======================��TestFixture����===================*/
    /*CppUnit::TextUi::TestRunner runner;
    CTestComplex2 a;
    runner.addTest(a.suite());
    runner.run();*/

    /*=====================�ú����=============================*/
	CppUnit::TextUi::TestRunner runner;
	
	// ��ע���TestSuite�л�ȡ�ض���TestSuite, û�в�����ȡδ������TestSuite.
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

	// ������TestSuite��TestRunner��
	runner.addTest( registry.makeTest() );
	
    // ���в���
	runner.run();
    
    system("PAUSE");	
    return 0;
}