package cn.hxex.order.bo;

import java.util.HashSet;
import java.util.Set;

/**
 * ����ʵ�����
 */
public class Order {

	// ����
	private int id;

	// �����ܼ�Ǯ
	private double total;

	// �����������û���
	private String userName;

	// ������Ŀ
	private Set orderLineItems = new HashSet();

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public Set getOrderLineItems() {
		return orderLineItems;
	}

	public void setOrderLineItems(Set orderLineItems) {
		this.orderLineItems = orderLineItems;
	}

	public double getTotal() {
		return total;
	}

	public void setTotal(double total) {
		this.total = total;
	}

	public String getUserName() {
		return userName;
	}

	public void setUserName(String userName) {
		this.userName = userName;
	}

}
