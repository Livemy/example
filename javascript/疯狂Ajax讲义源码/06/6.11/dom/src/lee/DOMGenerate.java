package lee;

import java.io.StringWriter;
import java.io.*;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.apache.xml.serialize.OutputFormat;
import org.apache.xml.serialize.XMLSerializer;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 * Description:
 * <br/>��վ: <a href="http://www.crazyjava.org">���Java����</a> 
 * <br/>Copyright (C), 2001-2010, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class DOMGenerate
{
	//����������������
	public static void main( String[] args ) 
	{
		try 
		{
			//����DocumentFactory����
			DocumentBuilderFactory dbf = 
				DocumentBuilderFactory.newInstance();
			DocumentBuilder db = dbf.newDocumentBuilder();
			//����Document����
			Document doc = db.newDocument();
			//������Ԫ��
			Element root = doc.createElement("Student");
			//����nameԪ��
			Element item = doc.createElement("name"); 
			//ΪnameԪ�������ı��ӽڵ�
			item.appendChild(doc.createTextNode("����"));
			//��nameԪ����ӵ���Ԫ����
			root.appendChild(item);
			//����ageԪ��
			item = doc.createElement("age"); 
			//ΪageԪ�������ı���Ԫ��
			item.appendChild(doc.createTextNode("28" ));
			//��ageԪ����ӵ���Ԫ����
			root.appendChild(item);
			//����highԪ��
			item = doc.createElement("high");
			//ΪhighԪ������ı���Ԫ��
			item.appendChild(doc.createTextNode("1.72" ));
			//��highԪ����ӵ���Ԫ����
			root.appendChild(item);
			//����scoreԪ��
			item = doc.createElement("score");
			//����JavaԪ��
			Element lesson = doc.createElement("Java");
			//ΪJavaԪ������ı���Ԫ�ء�
			lesson.appendChild(doc.createTextNode("95"));
			//��JavaԪ����ӵ�scoreԪ��
			item.appendChild( lesson );
			//����StrutsԪ��
			lesson = doc.createElement("Struts");
			//ΪStrutsԪ������ı���Ԫ�ء�
			lesson.appendChild(doc.createTextNode("90"));
			//��StrutsԪ����ӵ�scoreԪ��
			item.appendChild( lesson );
			//����HibernateԪ��
			lesson = doc.createElement("Hibernate");
			//ΪHibernateԪ������ı���Ԫ�ء�
			lesson.appendChild(doc.createTextNode("90"));
			//��HibernateԪ����ӵ�scoreԪ��
			item.appendChild( lesson );
			//��scoreԪ����ӵ���Ԫ����
			root.appendChild( item ); 
			//Ϊ�ĵ�ָ����Ԫ��
			doc.appendChild( root );
			//ָ�������ʽ
			OutputFormat format = new OutputFormat(doc
				, "GBK" , true);
			StringWriter stringOut = new StringWriter();  
			XMLSerializer serial = new XMLSerializer( stringOut, format );
			//��DOM��ת�����ַ���
			serial.asDOMSerializer(); 
			serial.serialize(doc.getDocumentElement());
			//�����ļ������
			PrintStream ps = new PrintStream(new FileOutputStream("new.xml"));
			//���XML�ļ�
			ps.println(stringOut.toString());
		}
		catch (Exception ex)
		{
			ex.printStackTrace();
		}
	}
}