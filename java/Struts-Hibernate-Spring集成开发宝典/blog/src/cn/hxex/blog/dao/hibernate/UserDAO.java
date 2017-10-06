package cn.hxex.blog.dao.hibernate;

import cn.hxex.blog.dao.IUserDAO;
import cn.hxex.blog.exception.BlogDAOException;
import cn.hxex.blog.hibernate.HibernateDAO;
import cn.hxex.blog.model.User;

/**
 * IUserDAO�ӿڵ�Hibernateʵ��
 */
public class UserDAO extends HibernateDAO implements IUserDAO {

	/**
	 * �����û���Ϣ�����ݿ�
	 * @param user ��������û�����
	 */
	public void saveUser(User user)
	{
		if (user == null)
			return;

		User u = getUser(user.getName());
		if (u != null)
			throw new BlogDAOException("�û����Ѿ����ڣ���ʹ�������û�����");

		saveObject(user);
	}

	/**
	 * �õ��û�����
	 * @param username �û��ĵ�¼��
	 * @return ָ����¼�����û�����
	 */
	public User getUser(String username)
	{
		User u = (User) getObject("from User u where u.name = '" + username
				+ "'");
		return u;
	}

	/**
	 * �õ��û��������Ϣ
	 * @param id �û���IDֵ
	 * @return ָ�����û���Ϣ
	 */
	public User getUserById(String id)
	{
		return (User) getObject(User.class, id);
	}

}
