package cn.hxex.blog.config;

import java.util.Hashtable;

import org.apache.commons.lang.builder.ReflectionToStringBuilder;

import cn.hxex.blog.exception.BlogException;

/**
 * ϵͳ������Ϣ��
 */
public class BlogConfig {

	public static Hashtable beans;

	/**
	 * ���캯��
	 */
	public BlogConfig()
	{
		beans = new Hashtable();
	}

	/**
	 * ����һ��BeanConfig����
	 * @param bean
	 */
	public void addDao(DaoConfig bean)
	{
		beans.put(bean.getId(), bean);
	}

	/**
	 * �õ�һ��DAO�ӿڶ����ʵ��
	 * @param name DAO�ӿڶ��������
	 * @return ָ��DAO�ӿڵ�ʵ�����ʵ��
	 */
	public Object getDao(String name)
	{
		DaoConfig config = (DaoConfig) beans.get(name);

		if (config == null)
		{
			throw new BlogException("Couldn't find the dao: " + name);
		}

		return config.getInstance();
	}

	public String toString()
	{
		return ReflectionToStringBuilder.toString(this);
	}
}
