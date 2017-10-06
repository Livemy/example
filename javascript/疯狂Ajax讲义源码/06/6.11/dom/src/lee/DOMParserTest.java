package lee;

import org.w3c.dom.*;
import java.io.*;
import java.util.*;
import  org.apache.xerces.parsers.DOMParser;

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
public class DOMParserTest
{
	public static void main(String[] args)
	{
		DOMParserTest tp = new DOMParserTest();
		tp.parseXMLFile("student.xml");
	}
	/**
	 * �����ĵ�
	 * @param fileName
	 */
	public void parseXMLFile(String fileName)
	{
		try
		{
			//����DOM��������ʵ��
			DOMParser parser = new DOMParser();
			//��ʼ�����ĵ�����XML�ļ�ת����DOM�������ڴ档
			parser.parse(fileName);
			//getDocument()��ȡDocument����
			Document doc = parser.getDocument();
			//��ȡroot�ڵ�
			Element elmtInfo = doc.getDocumentElement();
			//getElementsByTagName()���ݱ�ǩ����ȡ�ӽڵ��б�
			NodeList nlStudent = elmtInfo
				.getElementsByTagName("student");
			System.out.println("XML�ļ���ʼ����");
			//ѭ�����ÿһ��ѧ���ɼ�            
			for (int i = 0; i < nlStudent.getLength(); i++)
			{                
				//��ǰstudentԪ��
				Element elmtStudent = (Element) nlStudent.item(i);
				//���ø��ӹ�ϵ��ȡ�ӽڵ�
				NodeList nlCurrent = elmtStudent
					.getElementsByTagName("name");
				//��ȡ�������ڵ��ֵ
				System.out.println("����:" + nlCurrent.item(0)
					.getFirstChild().getNodeValue());
				//���ø��ӹ�ϵ��ȡ�ӽڵ�
				nlCurrent = elmtStudent.getElementsByTagName("sex");
				//��ȡ���Ա�ڵ��ֵ
				System.out.println("�Ա�:" + nlCurrent.item(0)
					.getFirstChild().getNodeValue());
				//�ٴλ�ȡ����γ̽ڵ�
				nlCurrent = elmtStudent.getElementsByTagName("lesson");
				//����ÿ���γ̽ڵ㡣
				for (int j = 0; j < nlCurrent.getLength(); j++)
				{
					//��ȡ��i���γ̽ڵ�
					Element elmtLesson = (Element) nlCurrent.item(j);
					//��ȡlessonName�ڵ��ֵ
					NodeList nlLesson = elmtLesson
						.getElementsByTagName("lessonName");
					System.out.print(nlLesson.item(0)
						.getFirstChild().getNodeValue());
					System.out.print(":");
					//��ȡlessonScore�ڵ��ֵ
					nlLesson = elmtLesson
						.getElementsByTagName("lessonScore");
					System.out.print(nlLesson.item(0)
						.getFirstChild().getNodeValue());
					System.out.println();
				}
				System.out.println("---------------------");
			}
			System.out.println("XML�ļ���������");
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
}