package cn.hxex.blog.struts.ext;

import javax.servlet.http.HttpServletRequest;

import org.apache.struts.Globals;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;

public class BaseAction extends Action {

	/**
	 * ���Ӵ�����ʾ����Ϣ
	 * 
	 * @param request HttpServletRequestʵ��
	 * @param key ��Դ��Keyֵ
	 * @param values ��Դ�Ĳ���ֵ
	 */
	public void addMessage(HttpServletRequest request, String key,
			String[] values)
	{
		// �õ�ActionMessages�����ʵ��
		ActionMessages messages = (ActionMessages) request
				.getAttribute(Globals.ERROR_KEY);
		if (messages == null)
			messages = new ActionMessages();

		// ����ActionMessage�����ʵ���������ӵ�ActionMessages�����ʵ����
		if (values != null && values.length > 0)
			messages.add(Globals.ERROR_KEY, new ActionMessage(key, values));
		else
			messages.add(Globals.ERROR_KEY, new ActionMessage(key));
		
		// ��ActionMessages�����ʵ���󶨵�request��
		request.setAttribute(Globals.ERROR_KEY, messages);
	}

	/**
	 * ���Ӵ�����ʾ����Ϣ
	 * 
	 * @param request HttpServletRequestʵ��
	 * @param key ��Դ��Keyֵ
	 */
	public void addMessage(HttpServletRequest request, String key)
	{
		addMessage(request, key, null);
	}
	
}
