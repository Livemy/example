package cn.hxex.blog.hibernate;

import javax.naming.InitialContext;
import javax.naming.NamingException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Interceptor;
import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;
import org.hibernate.cfg.Environment;


/**
 * ������Hibernate�����࣬����Hibernate�����ú�������
 * <p>
 * ͨ����̬�ĳ�ʼ����������ȡHibernate��������������ʼ��
 * <tt>Configuration</tt>��<tt>SessionFactory</tt>����
 * <p>
 *
 * @author galaxy
 */
public class HibernateUtil 
{

    private static Log log = LogFactory.getLog(HibernateUtil.class);

    // ָ������������������
    private static final String INTERCEPTOR_CLASS = "hibernate.util.interceptor_class";

    // ��̬Configuration��SessionFactory�����ʵ����ȫ��Ψһ�ģ�
    private static Configuration configuration;
    private static SessionFactory sessionFactory;

    static 
    {
        // ��ȱʡ�������ļ�����SessionFactory
        try 
        {
        	// ����Ĭ�ϵ�Configuration�����ʵ��
        	// ����㲻ʹ��JDK 5.0����ע����ʹ��new Configuration()
        	// ������Configuration()�����ʵ��
            configuration = new Configuration();

            // ��ȡhibernate.properties����hibernate.cfg.xml�ļ�
            configuration.configure();

            // ����������ļ�������������������ô�������õ�configuration������
            String interceptorName = configuration.getProperty(INTERCEPTOR_CLASS);
            if (interceptorName != null) 
            {
                Class interceptorClass =
                        HibernateUtil.class.getClassLoader().loadClass(interceptorName);
                Interceptor interceptor = (Interceptor)interceptorClass.newInstance();
                configuration.setInterceptor(interceptor);
            }

            if (configuration.getProperty(Environment.SESSION_FACTORY_NAME) != null) 
            {
                // ��Hibernate��SessionFacory�󶨵�JNDI
                configuration.buildSessionFactory();
            } 
            else 
            {
                // ʹ�þ�̬����������SessioFactory�����ʵ��
                sessionFactory = configuration.buildSessionFactory();
            }

        } 
        catch (Throwable ex) 
        {
            // ����쳣��Ϣ
            log.error("Building SessionFactory failed.", ex);
            ex.printStackTrace();
            throw new ExceptionInInitializerError(ex);
        }
    }

    /**
     * ����ԭʼ��Configuration�����ʵ��
     *
     * @return Configuration
     */
    public static Configuration getConfiguration() 
    {
        return configuration;
    }

    /**
     * ����ȫ�ֵ�SessionFactory�����ʵ��
     *
     * @return SessionFactory
     */
    public static SessionFactory getSessionFactory() 
    {
        SessionFactory sf = null;
        String sfName = configuration.getProperty(Environment.SESSION_FACTORY_NAME);
        if ( sfName != null) 
        {
            log.debug("Looking up SessionFactory in JNDI.");
            try 
            {
                sf = (SessionFactory) new InitialContext().lookup(sfName);
            } 
            catch (NamingException ex) 
            {
                throw new RuntimeException(ex);
            }
        } 
        else 
        {
            sf = sessionFactory;
        }
        if (sf == null)
            throw new IllegalStateException( "SessionFactory not available." );
        return sf;
    }

    /**
     * �رյ�ǰ��SessionFactory�����ͷ����е���Դ
     */
    public static void shutdown() 
    {
        log.debug("Shutting down Hibernate.");
        // Close caches and connection pools
        getSessionFactory().close();

        // Clear static variables
        configuration = null;
        sessionFactory = null;
    }


    /**
     * ʹ�þ�̬��Configuration���������¹���SessionFactory��
     */
     public static void rebuildSessionFactory() 
     {
        log.debug("Using current Configuration for rebuild.");
        rebuildSessionFactory(configuration);
     }

    /**
     * ʹ��ָ����Configuration���������¹���SessionFactory����
     *
     * @param cfg
     */
     public static void rebuildSessionFactory(Configuration cfg) 
     {
        log.debug("Rebuilding the SessionFactory from given Configuration.");
        synchronized(sessionFactory) 
        {
            if (sessionFactory != null && !sessionFactory.isClosed())
                sessionFactory.close();
            if (cfg.getProperty(Environment.SESSION_FACTORY_NAME) != null)
                cfg.buildSessionFactory();
            else
                sessionFactory = cfg.buildSessionFactory();
            configuration = cfg;
        }
     }

    /**
     * �ڵ�ǰSessionFactory��ע��һ��������
     */
    public static SessionFactory registerInterceptorAndRebuild(Interceptor interceptor) 
    {
        log.debug("Setting new global Hibernate interceptor and restarting.");
        configuration.setInterceptor(interceptor);
        rebuildSessionFactory();
        return getSessionFactory();
    }

    /**
     * �������������
     * 
     * @return Interceptor
     */
    public static Interceptor getInterceptor() 
    {
        return configuration.getInterceptor();
    }

    /**
     * �ύ��ǰ���񣬲���ʼһ���µ�����
     */
    public static void commitAndBeginTransaction()
    {
    	sessionFactory.getCurrentSession().getTransaction().commit();
    	sessionFactory.getCurrentSession().beginTransaction();
    }
}

