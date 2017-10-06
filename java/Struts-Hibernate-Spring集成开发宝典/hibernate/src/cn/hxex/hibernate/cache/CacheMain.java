package cn.hxex.hibernate.cache;

import java.net.URL;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;

public class CacheMain extends Thread{

    private static Log log = LogFactory.getLog( CacheMain.class );

    // ��̬Configuration��SessionFactory�����ʵ����ȫ��Ψһ�ģ�
    private static Configuration configuration;
    private static SessionFactory sessionFactory;

    static 
    {
        // ��ȱʡ�������ļ�����SessionFactory
        try 
        {
        	URL configURL = ClassLoader.getSystemResource( "cn/hxex/hibernate/cache/hibernate.cfg.xml" );
        	// ����Ĭ�ϵ�Configuration�����ʵ��
            configuration = new Configuration();

            // ��ȡhibernate.properties����hibernate.cfg.xml�ļ�
            configuration.configure( configURL );

            // ʹ�þ�̬����������SessioFactory�����ʵ��
            sessionFactory = configuration.buildSessionFactory();
        } 
        catch (Throwable ex) 
        {
            // ����쳣��Ϣ
            log.error("Building SessionFactory failed.", ex);
            ex.printStackTrace();
            throw new ExceptionInInitializerError(ex);
        }
    }
	
    public static SessionFactory getSessionFactory() {
    	return sessionFactory;
    }
    
    public void run() {
    	SessionFactory sf = CacheMain.getSessionFactory();
    	Session session = sf.getCurrentSession();
    	
    	session.beginTransaction();
    	
    	User user = (User)session.get( User.class, "1" );
    	System.out.println( user );
    	
    	session.getTransaction().commit();

    }
    
	public static void main(String[] args) {
		
		CacheMain main1 = new CacheMain();
		main1.start();

		CacheMain main2 = new CacheMain();
		main2.start();
	}
}
