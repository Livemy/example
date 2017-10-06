package cn.hxex.hibernate.lock;

import java.net.URL;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.LockMode;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;

public class LockMain extends Thread{

    private static Log log = LogFactory.getLog( LockMain.class );

    // ��̬Configuration��SessionFactory�����ʵ����ȫ��Ψһ�ģ�
    private static Configuration configuration;
    private static SessionFactory sessionFactory;

    static 
    {
        // ��Ĭ�ϵ������ļ�����SessionFactory
        try 
        {
        	URL configURL = ClassLoader.getSystemResource( "cn/hxex/hibernate/lock/hibernate.cfg.xml" );
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
    
    public void testPessimisticLock() {

		SessionFactory sf = LockMain.getSessionFactory();
		Session session = sf.getCurrentSession();
		session.beginTransaction();
		
		Query query = session.createQuery("from User user");
		query.setLockMode("user", LockMode.UPGRADE);
		List users = query.list();
		for( int i=0; i<users.size(); i++ ) {
			System.out.println( users.get( i ) );
		}
		session.getTransaction().commit();
    }
    
    public void testOptimisticLock() {

    	SessionFactory sf = LockMain.getSessionFactory();
    	Session session = sf.openSession();
 
    	Transaction tx = session.beginTransaction();
    	
    	User userV1 = (User)session.load( User.class, "1" );
    	
    	// �ȵڶ�������ִ��
    	try {
			sleep( 3000 );
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
    	
    	userV1.setAge(new Integer(32));
    	tx.commit();

    	session.close();
    }
    
    public void run() {
    	testOptimisticLock();
    }
    
	public static void main(String[] args) {
		
//		LockMain main = new LockMain();
//		main.testPessimisticLock();
		
		LockMain main1 = new LockMain();
		main1.start();
		LockMain main2 = new LockMain();
		main2.start();
	}
}
