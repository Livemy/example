package org.crazyjava.inputtip.servlet;

import javax.servlet.ServletException;
import javax.servlet.ServletContext;
import javax.servlet.RequestDispatcher;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import java.io.PrintWriter;
import java.io.IOException;

import org.crazyjava.inputtip.service.*;

import org.springframework.web.context.support.WebApplicationContextUtils;

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
public class GetDetailServlet extends HttpServlet 
{
	public void service(HttpServletRequest request,
		HttpServletResponse response)
		throws ServletException, java.io.IOException
	{
		//ͨ��WebApplicationContextUtils��������Spring������
		//ͨ��Spring�������������е�ҵ���߼����
		TipService ts = (TipService)WebApplicationContextUtils
			.getWebApplicationContext(getServletContext())
			.getBean("tipService");
		//���ý����õ��ַ�����Ajax��POST���󶼲���UTF-8�ı��뼯
		request.setCharacterEncoding("utf-8");
		//��ȡ�������
		String model = request.getParameter("model");
		response.setContentType("text/html;charset=GBK");
		PrintWriter out =  response.getWriter();
		//�����Ӧ
		out.println(ts.getDescByModel(model));
	}
}