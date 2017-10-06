package cn.hxex.blog.dao;

import cn.hxex.blog.model.User;

/**
 * ����User�����DAO�ӿ�
 */
public interface IUserDAO {
	// �����û�����
	public void saveUser( User user );
	// �����û����õ��û���Ϣ
	public User getUser( String username );
	// �����û�����õ��û���Ϣ
	public User getUserById( String id );
}
