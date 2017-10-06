var objXMLHttp;
function createXMLHttpRequest()
{
	//����Mozilla��Firefox��Opera�������
	if (window.XMLHttpRequest)
	{
		objXMLHttp = new XMLHttpRequest();
	}
	//����Internet Explorer�����
	else
	{
		var MSXML = ['MSXML2.XMLHTTP.5.0', 'MSXML2.XMLHTTP.4.0',
			'MSXML2.XMLHTTP.3.0', 'MSXML2.XMLHTTP', 'Microsoft.XMLHTTP'];
		for(var n = 0; n < MSXML.length; n ++)
		{
			try
			{
				//����XMLHttpRequest����
				objXMLHttp = new ActiveXObject(MSXML[n]);        
				break;
			}
			catch(e)
			{
			}
		}
	}
}
createXMLHttpRequest();
//Ϊtest��ť���¼�������
document.getElementById("test").onclick=sendRequest;
function sendRequest()
{
	var url = "data";
	objXMLHttp.open("POST", url, true);
	//ָ����Ӧ����
	objXMLHttp.onreadystatechange = process;
	//��������
	objXMLHttp.send(null);
}
//process()�ǿ���������
function process()
{
	//�����������Ӧ����
	if (objXMLHttp.readyState == 4 && 
		(objXMLHttp.status == 200 || objXMLHttp.status == 304))
	{
		//������ͼ���������ط�������Ӧ
		show(objXMLHttp.responseText);
	}
}
function show(content)
{
	//����ģ�ͷ��ص�����
	document.getElementById("show").innerHTML=content;
}