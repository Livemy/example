<%-- ����ָ������JSPҳ������ݡ��ַ��� --%>
<%@ page contentType="text/html; charset=GBK" language="java" %>
<%
////����һ�����ַ�����
//String a = null;
////���������������ָ���쳣��
//out.println(a.length);
%>

<%
int id = Integer.parseInt(request.getParameter("id"));
System.out.println(id);
switch(id)
{
	case 1:
%>
�Ϻ�$����$����
<%
	break;
	case 2:
%>
��ʢ��$ŦԼ$����
<%
	break;
	case 3:
%>
����$���$����
<%
	break;
}
%>
