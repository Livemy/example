package cn.hxex.order.bo;

/**
 * ������Ŀ����
 */
public class OrderLineItem {

	// ����
	private int id;

	// �۸�
	private double lineItemPrice;

	// ������Ŀ������Ϣ
	private String description;

	// ��������
	private Order order;

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public double getLineItemPrice() {
		return lineItemPrice;
	}

	public void setLineItemPrice(double lineItemPrice) {
		this.lineItemPrice = lineItemPrice;
	}

	public Order getOrder() {
		return order;
	}

	public void setOrder(Order order) {
		this.order = order;
	}

	
}
