package cn.hxex.blog.dao;

import java.util.List;

import cn.hxex.blog.model.Message;

/**
 * ����Message�����DAO�ӿ�
 */
public interface IMessageDAO {

	// ����������Ϣ
	public void saveMessage( Message message );
	// �޸�������Ϣ
	public void updateMessage( Message message );
	// �õ����е�������Ϣ
	public List getMessages( );
	// ɾ��������Ϣ
	public void deleteMessage( String id, String userId );
	// ����ID�õ����Ե���Ϣ
	public Message getMessage( String id );
	// ����IDɾ����־����
	public void deleteReplyMessage( String id, String userId );

}
