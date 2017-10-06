package cn.hxex.basic.exercise;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;
import org.hibernate.cfg.Configuration;

import cn.hxex.basic.model.User;

public class LifeCycle
{

	public static final SessionFactory sessionFactory;
	
	static
	{
		sessionFactory = new Configuration().configure().buildSessionFactory();
	}
	
	public static void main(String[] args)
	{
		LifeCycle.lifecycle();
	}
	
	public static void lifecycle()
	{
		// ��������̬ʵ�����User
		User user = new User();
		user.setName( "abc" + String.valueOf( Math.random() ) );
		// Ϊ�˱����������е��û����ظ������������������
		user.setPassword( "def" );
		// user��Ȼ��������̬

		Session session = sessionFactory.openSession();
		Transaction tx = session.beginTransaction();
		// ��ʱuser������Ȼ��Transient״̬
		session.save( user );
		// ��ʱ��user�����Ѿ���������Hibernate��ʵ����������У���ת��ΪPersistent״̬
		System.out.println( "User 1:" + user );
		// ��ʱ��id�Ѿ���ֵ�ˡ�
		get( user.getId() );
		// ����δ������ִ�����ݿ�Ĳ����������޷��õ������ֵ
		tx.commit();
		// �����ύ�󣬽������ݿ���û����в���һ����¼
		System.out.println( "Transaction 1 commit!" );
		get( user.getId() );
		// ��ʱ���������ݿ��еõ��ղŲ����user�����ˡ�
		
		Transaction tx2 = session.beginTransaction();
		user.setPassword( "mmmmmmmmmmmmm" );
		tx2.commit();
		// ��Ȼ��������в�û�е���Session��save()����������user����
		// ������user������Persistent״̬�����Զ�user�����������κ��޸Ķ������־û������ݿ���
		// ��ô���ݿ��е��û�����ҲӦ�ñ�Ϊ��def��
		System.out.println( "Transaction 2 commit!" );
		session.close();

		get( user.getId() );
		// ��ʱ�����Ѿ���Ϊ�µ�ֵ��
	}
	
	public static User get( String id )
	{
		Session session = sessionFactory.openSession();
		Transaction tx = session.beginTransaction();
		
		User user = (User)session.get( User.class, id );
		// Hibernate�ڷ���User����֮��Ὣ�����뵽Hibernate��ʵ�����������
		// ���ԣ���ʱ��user������Persistent״̬��
		display( user );
		
		tx.commit();
		session.close();
		
		return user;
	}
	
	public static void display( Object obj )
	{
		System.out.println( obj );
	}
}
