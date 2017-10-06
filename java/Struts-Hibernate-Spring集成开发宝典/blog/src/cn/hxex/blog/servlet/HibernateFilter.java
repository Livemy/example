package cn.hxex.blog.servlet;

import java.io.IOException;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.SessionFactory;

import cn.hxex.blog.hibernate.HibernateUtil;


/**
 * ���ڽ���Hibernate�������Servlet������
 *
 * @author galaxy
 */
public class HibernateFilter implements Filter {

    private static Log log = LogFactory.getLog(HibernateFilter.class);

    /**
     * ����������Ҫ����
     * ����ʵ��Hibernate����Ŀ�ʼ���ύ
     */
    public void doFilter(ServletRequest request,
                         ServletResponse response,
                         FilterChain chain)
            throws IOException, ServletException 
    {
    	// �õ�SessionFactory�����ʵ��
    	SessionFactory sf = HibernateUtil.getSessionFactory();

        try 
        {
        	// ��ʼһ���µ�����
            log.debug("Starting a database transaction");
            sf.getCurrentSession().beginTransaction();

            log.debug( "Request Path:\t" + ((HttpServletRequest)request).getServletPath() );
            // Call the next filter (continue request processing)
            chain.doFilter(request, response);

            // �ύ����
            log.debug("Committing the database transaction");
            sf.getCurrentSession().getTransaction().commit();

        } 
        catch (Throwable ex) 
        {
        	ex.printStackTrace();
            try 
            {
            	// �ع�����
                log.debug("Trying to rollback database transaction after exception");
                sf.getCurrentSession().getTransaction().rollback();
            } 
            catch (Throwable rbEx) 
            {
                log.error("Could not rollback transaction after exception!", rbEx);
            }

            // �׳��쳣
            throw new ServletException(ex);
        }
    }

    /**
     * Servlet�������ĳ�ʼ������
     * ���Զ�ȡ�����ļ������õ����ò���
     */
    public void init(FilterConfig filterConfig) throws ServletException {}

    /**
     * Servlet�����ٷ���
     * �����ͷŹ��������������Դ
     */
    public void destroy() {}

}