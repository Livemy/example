<%@ page contentType="text/html; charset=GBK" language="java" %>
<%
//�ӷ�������ȡid����
int id = Integer.parseInt(request.getParameter("id"));
//����id��ֵ��ȷ����Ҫ���ظ��ͻ��˵���Ϣ�����ؿͻ��˵ĳ�����Ϣ��$���Ÿ���
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
