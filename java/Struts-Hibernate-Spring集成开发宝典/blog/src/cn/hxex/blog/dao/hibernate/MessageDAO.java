package cn.hxex.blog.dao.hibernate;

import java.util.Iterator;
import java.util.List;

import cn.hxex.blog.dao.IMessageDAO;
import cn.hxex.blog.exception.BlogDAOException;
import cn.hxex.blog.hibernate.HibernateDAO;
import cn.hxex.blog.model.Message;
import cn.hxex.blog.model.ReplyMessage;
import cn.hxex.blog.model.User;

public class MessageDAO extends HibernateDAO implements IMessageDAO {

	/**
	 * ����������Ϣ
	 * 
	 * @param message
	 *            ����������Զ���
	 */
	public void saveMessage(Message message)
	{
		super.saveObject(message);
	}

	/**
	 * �õ����е�������Ϣ
	 * 
	 * @return �������е�������Ϣ
	 */
	public List getMessages()
	{
		String hsql = "from Message";
		return super.getObjects(hsql);
	}

	/**
	 * ɾ��������Ϣ
	 * 
	 * @param id
	 *            Ҫɾ����������Ϣ��IDֵ
	 * @param userId
	 *            ִ��ɾ���������û�ID
	 */
	public void deleteMessage(String id, String userId)
	{
		User user = (User)getObject( User.class, userId );
		if( user==null ) {
			throw new BlogDAOException( "Couldn't user!" );
		}
		
		Message m = null;
		
		Iterator it = user.getMessages().iterator();
		while( it.hasNext() ) {
			Message message = (Message)it.next();
			if( message.getId().equals( id ) ) {
				m = message;
			}
		}
		if( m!=null ) {
			deleteObject( m );
			user.getMessages().remove( m );
		}
	}

	/**
	 * �õ�������Ϣ
	 * 
	 * @param id
	 *            ���Ե�IDֵ
	 * @return ָ��IDֵ�����Զ���
	 */
	public Message getMessage(String id)
	{
		return (Message) getObject(Message.class, id);
	}

	/**
	 * ����������Ϣ
	 * 
	 * @param message
	 *            �����µ����Զ���
	 */
	public void updateMessage(Message message)
	{
		updateObject(message);
	}

	/**
	 * ɾ��������־������
	 * 
	 * @param id ���۵�IDֵ
	 * @param userId ɾ�����û�
	 */
	public void deleteReplyMessage(String id, String userId) {
		ReplyMessage reply = (ReplyMessage)getObject( ReplyMessage.class, id );
		if( reply==null ) {
			throw new BlogDAOException("�Ҳ�������Ҫɾ������־����!");
		}
		
		Message message = reply.getMessage();
		Iterator it = message.getReplies().iterator();
		while( it.hasNext() ) {
			ReplyMessage r = (ReplyMessage)it.next();
			if( r.getId().equals( id ) ) {
				message.getReplies().remove( r );
			}
		}
	}
}
