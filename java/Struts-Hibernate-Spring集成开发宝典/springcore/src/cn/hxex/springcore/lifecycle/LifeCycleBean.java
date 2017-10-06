package cn.hxex.springcore.lifecycle;

/**
 * ���Գ�ʼ�����������ٷ�����Bean
 */
public class LifeCycleBean {

	private String message;

	public String getMessage() {
		return message;
	}

	public void setMessage(String message) {
		this.message = message;
	}
	
	/**
	 * ��ʼ������
	 */
	public void initialize() {
		System.out.println( "Initialize method..." );
		System.out.println( getMessage() );
	}
	
	/**
	 * ���ٷ���
	 */
	public void cleanup() {
		System.out.println( "Destroy method..." );
	}

}
