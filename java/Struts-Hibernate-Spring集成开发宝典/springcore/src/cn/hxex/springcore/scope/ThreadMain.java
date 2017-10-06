package cn.hxex.springcore.scope;

import org.springframework.beans.factory.BeanFactory;
import org.springframework.beans.factory.xml.XmlBeanFactory;
import org.springframework.core.io.ClassPathResource;

/**
 * �����Զ����������������
 */
public class ThreadMain {

	public static BeanFactory factory;

	static {
		// IoC�����ĳ�ʼ��
		ClassPathResource resource = new ClassPathResource("cn/hxex/springcore/scope/ThreadBeans.xml");
		factory = new XmlBeanFactory(resource);
		// ע���Զ����������
		((XmlBeanFactory)factory).registerScope( "thread", new ThreadScope() );
	}
	
	/**
	 * ��������������̵߳�ҵ�����
	 */
	public static void main(String[] args) {

		for( int i=0; i<5; i++ ) {
			ThreadService service = new ThreadService();
			service.start();
		}

	}

}
