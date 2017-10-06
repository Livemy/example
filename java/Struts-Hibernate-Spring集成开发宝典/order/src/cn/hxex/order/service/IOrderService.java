package cn.hxex.order.service;

import java.util.List;

import cn.hxex.order.bo.Order;
import cn.hxex.order.dao.IOrderDAO;
import cn.hxex.order.exception.OrderException;
import cn.hxex.order.exception.OrderMinimumAmountException;

/**
 * ����ҵ��ӿ�
 * 
 * @author galaxy
 * 
 */
public interface IOrderService {

	/**
	 * ���涩������
	 * 
	 * @param order
	 *            ��Ҫ����Ķ�������
	 * @return �����Ķ�������
	 * @throws OrderException
	 * @throws OrderMinimumAmountException
	 */
	public abstract Order saveNewOrder(Order order) throws OrderException,
			OrderMinimumAmountException;

	/**
	 * ͨ�������û�������ѯ������Ϣ
	 * 
	 * @param user
	 *            �¶������û�
	 * @return Order
	 */
	public abstract List findOrderByUser(String user) throws OrderException;

	/**
	 * ͨ��ID����ѯ������Ϣ
	 * 
	 * @param id
	 *            ����ID
	 * @return Order ��������
	 */
	public abstract Order findOrderById(int id) throws OrderException;

	/**
	 * ����IOrderDAO�ӿڶ����ʵ��
	 * 
	 * @param orderDAO
	 *            IOrderDAO�ӿڵ�ʵ��
	 */
	public abstract void setOrderDAO(IOrderDAO orderDAO);
}
