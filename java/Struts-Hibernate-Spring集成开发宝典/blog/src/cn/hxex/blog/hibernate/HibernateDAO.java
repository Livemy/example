package cn.hxex.blog.hibernate;

import java.util.List;

import org.hibernate.Session;

/**
 * ʹ��Hibernateʵ��DAO�Ļ�����
 * �����˳־û�������һЩ��������
 */
public class HibernateDAO {

	public Session getCurrentSession() {
		return HibernateUtil.getSessionFactory().getCurrentSession();
	}

	/**
	 * ���������Ϣ�����ݿ�
	 * @param obj ��Ҫ���г־û������Ķ���
	 */
	public void saveObject(Object obj) {
		getCurrentSession().save(obj);
	}

	/**
	 * ���³־û�����
	 * @param obj ��Ҫ���µĶ���
	 */
	public void updateObject(Object obj) {
		getCurrentSession().update(obj);
	}

	/**
	 * ʹ��HQL�����в�ѯ
	 * @param hsql ��ѯ���
	 * @return ���������Ķ��󼯺�
	 */
	public List getObjects(String hsql) {
		List result = getCurrentSession().createQuery(hsql).list();
		return result;
	}

	/**
	 * ʹ��HQL�����ж���Ĳ�ѯ
	 * @param hsql ��ѯ���
	 * @return ���������Ķ���
	 */
	public Object getObject(String hsql) {
		Object result = getCurrentSession().createQuery(hsql).uniqueResult();
		return result;
	}

	/**
	 * ����IDֵ�õ��־û��Ķ���
	 * @param cls ���������
	 * @param id IDֵ
	 * @return ָ��ID�Ķ���
	 */
	public Object getObject(Class cls, String id) {
		Object result = getCurrentSession().get(cls, id);
		return result;
	}

	/**
	 * ɾ��������Ϣ
	 * @param obj ��ɾ���Ķ���
	 */
	public void deleteObject(Object obj) {
		getCurrentSession().delete(obj);
	}

}
