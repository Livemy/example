package cn.hxex.springcore.scope;

/*
 * �Զ���������Ĳ���Bean
 */
public class ThreadBean {

	// ״̬����
	private int status = 0;
	
	public int getStatus() {
		return status;
	}

	public void setStatus(int status) {
		this.status = status;
	}

	public void display() {

		StringBuffer buf = new StringBuffer();
		buf.append( "Thread " ).append( Thread.currentThread().getId() );
		buf.append( " Status:\t" ).append( getStatus() );
		System.out.println( buf.toString() );
	
	}
}
