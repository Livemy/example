@ECHO OFF
SET JAVA=java

REM ʹ�� Sun �� XML parser ��
SET PARSER=com.sun.xml.parser.Parser
REM ��Ҫʹ�� IBM xml4j 2.x ��
REM SET PARSER=com.ibm.xml.parsers.SAXParser
REM ��Ҳ�����ڴ��趨 CLASSPATH ��
REM SET CLASSPATH=%CLASSPATH%;/path/to/xml.jar;/path/to/xt.jar

%JAVA% -Dcom.jclark.xsl.sax.parser=%PARSER% com.jclark.xsl.sax.Driver %1 %2 %3
