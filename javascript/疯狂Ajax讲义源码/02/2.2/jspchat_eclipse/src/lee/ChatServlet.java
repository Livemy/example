package lee;

import javax.servlet.ServletException;
import javax.servlet.RequestDispatcher;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import java.io.IOException;

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
public class ChatServlet extends HttpServlet
{
	public void service(HttpServletRequest request,
		HttpServletResponse response)throws IOException,ServletException
	{
		//����ʹ��GBK�ַ����������������
		request.setCharacterEncoding("GBK");
		String msg = request.getParameter("chatMsg");
		if ( msg != null &&  !msg.equals(""))
		{
			//ȡ�õ�ǰ�û�
			String user = (String)request.getSession(true)
				.getAttribute("user");
			//����ChatService��addMsg�����������Ϣ
			ChatService.instance().addMsg(user , msg);
		}
		request.setAttribute("msg" , ChatService.instance().getMsg());
		//ת��������ҳ��
		forward("/chat.jsp" , request , response);
	}

	//ִ��ת������ķ���
	private void forward(String url , HttpServletRequest request,
		HttpServletResponse response)throws ServletException,IOException
	{
		//��ȡRequestDispatcher����
		RequestDispatcher rd = request.getRequestDispatcher(url);
		//ִ��ת��
		rd.forward(request,response);
	}
}