<%--
��վ: <a href="http://www.crazyjava.org">���Java����</a>
author  yeeku.H.lee kongyeeku@163.com
version  1.0
Copyright (C), 2001-2010, yeeku.H.Lee
This program is protected by copyright laws.
Program Name:
Date: 
--%>
<%@ page contentType="text/html; charset=GBK" language="java" %>
<%
//��ȡ�������
String user = request.getParameter("user");
String[] books = request.getParameterValues("books");
//����HTML�ַ�����Ӧ
out.println(user + ",���ã�����ʱ����:" + new java.util.Date());
out.println("<br />��ϲ����ͼ�����£�");
out.println("<ol>");
for(int i = 0 ; i < books.length ; i++)
{
	out.println("<li>" + books[i] + "</li>");
}
out.println("</ol>");
%>