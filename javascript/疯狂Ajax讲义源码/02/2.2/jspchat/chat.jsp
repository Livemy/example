<%--
��վ: <a href="http://www.crazyjava.org">���Java����</a>
author  yeeku.H.lee kongyeeku@163.com
version  1.0
Copyright (C), 2001-2010, yeeku.H.Lee
This program is protected by copyright laws.
Program Name:
Date: 
--%>
<%@ page contentType="text/html;charset=GBK" errorPage="error.jsp"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=GBK"/>
<title>����ҳ��</title>
</head>
<body>
<table width="780" border="1" align="center">
<tr>
<td><p align="center">����ҳ��</p>
<p align="center">
  <textarea name="textarea" cols="100" rows="30" readonly="readonly">
	${requestScope.msg}</textarea> 
</p>
<form name="form1" method="post" action="chat.do" >
  <div align="center">
    <input name="chatMsg" type="text" size="90" onclick="document.form1.submit;"/>
    <input type="submit" name="Submit" value="����"/>
  </div>
</form>
<p>&nbsp; </p>
</td>
</tr>
</table>
<script>
	var input = document.getElementById("chatMsg");
	input.focus();

	function check()
	{
		if (input.value == null || input.value == "")
		{
			alert("������������Ϣ����Ҫ���Ϳ���Ϣ!");
			return false;
		}
	}

	function submitChat()
	{
		document.getElementById("form1").onsubmit();
	}

	document.getElementById("form1").onsubmit = check;
</script>
</body>
</html>
