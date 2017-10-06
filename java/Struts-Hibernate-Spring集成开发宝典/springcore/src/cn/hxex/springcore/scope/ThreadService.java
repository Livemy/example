package cn.hxex.springcore.scope;

/**
 * ���̵߳�ҵ�����
 */
public class ThreadService extends Thread {

	public void run() {

		for( int i=0; i<5; i++ ) {
			
			// ���Bean��ʵ��
			ThreadBean bean = (ThreadBean)ThreadMain.factory.getBean( "threadBean" );
			// �޸�Bean��״̬
			bean.setStatus( bean.getStatus() + 10 );
			// ��ʾBean����Ϣ
			bean.display();
			
			// �������ʱ���ͣ������ʹ�ò�ͬ����ÿ�δ����ʱ�䲻ͬ
			long interval = (long)( Math.random() * 100 );
			try {
				sleep( interval );
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
