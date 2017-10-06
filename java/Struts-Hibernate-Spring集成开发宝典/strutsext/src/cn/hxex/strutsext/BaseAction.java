package cn.hxex.strutsext;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

public abstract class BaseAction extends Action {

	public final ActionForward execute(ActionMapping mapping, 
			ActionForm form,
			HttpServletRequest request, 
			HttpServletResponse response)
			throws Exception {
		try {
			return doExecute( mapping, form, request, response );
		} catch ( Exception ex ) {
			return doException( ex, mapping, form, request, response );
		}
	}

	/**
	 * �쳣������
	 */
	public ActionForward doException(Exception ex,
			ActionMapping mapping, 
			ActionForm form,
			HttpServletRequest request, 
			HttpServletResponse response) {
		// ���쳣���д���
		
		return null;  // ����ҳ��
	}

	/**
	 * Action������
	 */
	public abstract ActionForward doExecute(ActionMapping mapping, 
			ActionForm form,
			HttpServletRequest request, 
			HttpServletResponse response)
			throws Exception;
}
