package cn.hxex.order.dao;

import java.util.List;

import cn.hxex.order.bo.Order;

/**
 * ����������DAO�ӿ�
 * 
 * @author galaxy
 * 
 */
public interface IOrderDAO {

	/**
	 * ͨ������ID����ѯ��������Ϣ
	 * 
	 * @param id
	 *            ������ID
	 * @return Order ������Ϣ
	 */
	public abstract Order findOrderById(final int id);

	/**
	 * ͨ�������û������õ���������Ϣ
	 * 
	 * @param placedBy
	 *            �����������û�
	 * @return List ���û��Ķ�������
	 */
	public abstract List findOrdersPlaceByUser(final String placedBy);

	/**
	 * ���涩������
	 * 
	 * @param order ��������
	 */
	public abstract Order saveOrder(final Order order);

}
