package cn.hxex.springcore.scope;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import org.springframework.beans.factory.ObjectFactory;
import org.springframework.beans.factory.config.Scope;

/**
 * �Զ�������������
 */
public class ThreadScope implements Scope {

	// ��������Beanʵ��������
	static Map container = Collections.synchronizedMap( new HashMap() );
	
	/**
	 * �õ�Bean��ʵ��
	 */
	public Object get(String name, ObjectFactory factory) {
		
		Map beans = (Map)container.get( getThreadId() );
		if( beans==null ) {
			beans = new HashMap();
			container.put( getThreadId(), beans );
		}
		
		Object obj = beans.get( name );
		if( obj==null ) {
			obj = factory.getObject();
			beans.put( name, obj );
		}
		
		return obj;
	}

	/**
	 * ɾ��Bean��ʵ��
	 */
	public Object remove(String name) {
		
		Map beans = (Map)container.get( getThreadId() );
		if( beans!=null ) {
			Object obj = beans.get( name );
			if( obj!=null ) {
				beans.remove( name );
				return obj;
			}
		}
		
		return null;
	}

	/**
	 * �õ���ǰ���̵�ID
	 */
	private Long getThreadId() {
		
		long id = Thread.currentThread().getId();
		return Long.valueOf( id );
		
	}
}
