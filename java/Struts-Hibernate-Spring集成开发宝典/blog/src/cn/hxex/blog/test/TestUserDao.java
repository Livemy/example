package cn.hxex.blog.test;

import junit.framework.TestCase;
import cn.hxex.blog.dao.DaoFactory;
import cn.hxex.blog.dao.IUserDAO;
import cn.hxex.blog.exception.BlogDAOException;
import cn.hxex.blog.hibernate.HibernateUtil;
import cn.hxex.blog.model.User;

/**
 * UserDAO���Զ���
 */
public class TestUserDao extends TestCase {

	IUserDAO userDAO;
	static String username = "test" + (int)(Math.random() * 100000);
	static String userid;
	
	protected void setUp() throws Exception 
	{
		super.setUp();
		userDAO = (IUserDAO)DaoFactory.getDao( "userDao" );
		assertNotNull( "User DAO is NULL!", userDAO );
		HibernateUtil.getSessionFactory().getCurrentSession().beginTransaction();
	}

	protected void tearDown() throws Exception 
	{
		super.tearDown();
		HibernateUtil.getSessionFactory().getCurrentSession().getTransaction().commit();
	}

	// ����saveUser()����
	public void testSaveUser()
	{
		// ���������ı���
		User user = new User();
		user.setName( username );
		user.setPassword( "test" );
		userDAO.saveUser( user );

		assertNotNull( "Save User Success!", user.getId() );
		userid = user.getId();
		
		// ����ͬ���ı���
		User u3 = new User();
		u3.setName( username );
		u3.setPassword( "ttt" );
		boolean result = false;
		try
		{
			userDAO.saveUser( u3 );
		}
		catch( BlogDAOException ex )
		{
			result = true;
		}
		assertTrue( "The user Not Exists!", result );
	}
	
	// ����getUser()����
	public void testGetUser()
	{
		User user = userDAO.getUser( username );
		assertNotNull( "Get User Success!", user );
	}
	
	// ����getUserById()����
	public void testGetUserById()
	{
		User u = userDAO.getUserById( userid );
		assertNotNull( "Get(By Id) User Success!", u );		
	}

}
