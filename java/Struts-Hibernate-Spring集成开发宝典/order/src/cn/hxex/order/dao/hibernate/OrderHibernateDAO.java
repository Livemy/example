package cn.hxex.order.dao.hibernate;

import java.sql.SQLException;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.springframework.orm.hibernate3.HibernateCallback;
import org.springframework.orm.hibernate3.support.HibernateDaoSupport;

import cn.hxex.order.bo.Order;
import cn.hxex.order.dao.IOrderDAO;

/**
 * ����DAO��Hibernateʵ�֣����������ݴ����߼�
 * 
 * @author galaxy
 *
 */
public class OrderHibernateDAO
	extends HibernateDaoSupport
	implements IOrderDAO {

	/**
	 * ͨ��ID���õ���������Ϣ
	 *
	 * @param id ������ID
	 * @return Order ������Ϣ
	 */
	public Order findOrderById(final int id) {

		Order order =
			(Order) getHibernateTemplate().load(Order.class, new Integer(id));
			
		return order;

	}

	/**
	 * ͨ���¶������û��õ���������Ϣ
	 *
	 * @param placedBy �¶������û���
	 * @return List ������Ϣ�б�
	 */
	public List findOrdersPlaceByUser(final String placedBy) {

		return getHibernateTemplate().executeFind(new HibernateCallback() {
			public Object doInHibernate(Session session)
				throws HibernateException, SQLException {

				StringBuffer sb = new StringBuffer(100);
				sb.append("select distinct order ");
				sb.append("from Order order ");
				sb.append("join order.lineItems lineItems ");
				sb.append("where order.placedBy = :placedBy");

				sb.append("order by order.id");

				Query query = session.createQuery(sb.toString());
				query.setString("placedBy", placedBy);

				List list = query.list();

				return list;

			}
		});
	}

	/**
	 * ����һ��������Ϣ
	 *
	 * @param order ������Ϣ
	 */
	public Order saveOrder(Order order) {

		getHibernateTemplate().save(order);

		return order;
	}

}