<%--
author  yeeku.H.lee kongyeeku@163.com
version  1.0
Copyright (C), 2008-2010, yeeku.H.Lee
This program is protected by copyright laws.
Program Name:sdfsd
Date: 
--%>

<%@ page contentType="text/html; charset=GBK" language="java" errorPage="" %>
<%@ page import="javax.naming.*,java.sql.*,javax.sql.*"%>

<html>
<head>
	<title> </title>
</head>
<body>
<%
//��ʼ��Context��ʹ��InitialContext��ʼ��Context
Context ctx=new InitialContext(); 
/*
ͨ��JNDI��������Դ����JNDIΪjava:comp/env/jdbc/dstest���ֳ���������
java:comp/env��Tomcat�̶��ģ�Tomcat�ṩ��JNDI�󶨶�����Ӹ�ǰ׺
jdbc/dstest�Ƕ�������Դʱ������Դ��
*/
DataSource ds=(DataSource)ctx.lookup("java:comp/env/jdbc/dstest");
//��ȡ���ݿ�����
Connection conn=ds.getConnection();
//��ȡStatement
Statement stmt=conn.createStatement();
//ִ�в�ѯ������ResulteSet����
ResultSet rs=stmt.executeQuery("select * from newsinf");
while(rs.next())
{
	out.println(rs.getString(2) + "<br/>");
}
%>
</body>
</html>