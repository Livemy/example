<%@ page contentType="text/xml; charset=GBK"%>
<%
//����������Ӧ�ı��뷽ʽ
response.setContentType("text/xml; charset=UTF-8");
response.setHeader("Cache-Control","no-cache");
//���XML�ĵ��ĸ�Ԫ��
out.println("<citylist>");
int id = Integer.parseInt(request.getParameter("id"));
//�Բ�ͬ�Ĳ��������ɲ�ͬ��XML�ĵ�
switch(id)
{
	case 1:
%>
<city>�Ϻ�</city>
<city>����</city>
<city>����</city>
<%
	break;
	case 2:
%>
<city>��ʢ��</city>
<city>ŦԼ</city>
<city>����</city>
<%
	break;
	case 3:
%>
<city>����</city>
<city>����</city>
<city>����</city>
<%
	break;
}
%>
</citylist>
