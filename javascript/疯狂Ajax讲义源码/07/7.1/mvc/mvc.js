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
		var MSXML = ['MSXML2.XMLHTTP.5.0', 'MSXML2.XMLHTTP.4.0', 'MSXML2.XMLHTTP.3.0', 'MSXML2.XMLHTTP', 'Microsoft.XMLHTTP'];
		for(var n = 0; n < MSXML.length; n ++)
		{
			try
			{
				objXMLHttp = new ActiveXObject(MSXML[n]);        
				break;
			}
			catch(e)
			{
				alert(e);
			}
		}
	}
}

createXMLHttpRequest();

function sendRequest()
{
	var url = "data";
	objXMLHttp.open("POST", url, true);
	objXMLHttp.onreadystatechange = show;//ָ����Ӧ����
	objXMLHttp.send(null);  // ��������
}

function show()
{
	if (objXMLHttp.readyState == 4 && (objXMLHttp.status == 200 || objXMLHttp.status == 304))
	{
		document.getElementById("show").innerHTML=objXMLHttp.responseText;
	}
}

document.getElementById("test").onclick=sendRequest;