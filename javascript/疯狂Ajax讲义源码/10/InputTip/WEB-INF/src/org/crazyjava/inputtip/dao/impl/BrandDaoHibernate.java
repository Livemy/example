package org.crazyjava.inputtip.dao.impl;

import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

import org.springframework.orm.hibernate3.support.HibernateDaoSupport;

import org.crazyjava.inputtip.model.*;
import org.crazyjava.inputtip.dao.*;
/**
 * Description:
 * <br/>��վ: <a href="http://www.crazyjava.org">���Java����</a> 
 * <br/>Copyright (C), 2001-2010, Yeeku.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  Yeeku.H.Lee kongyeeku@163.com
 * @version  1.0
 */
public class BrandDaoHibernate 
	extends HibernateDaoSupport implements BrandDao
{
	/**
	 * ����id����Ʒ��
	 * @param id ��Ҫ���ҵ�Ʒ��id
	 */
	public Brand get(Integer id)
	{
		//������HibernateTemplate��get���������ض�������Ӧ��¼
		return (Brand)getHibernateTemplate()
			.get(Brand.class , id);
	}
	/**
	 * ����Ʒ��
	 * @param brand ��Ҫ���ӵ�Ʒ��
	 */
	public void save(Brand brand)
	{
		//������HibernateTemplate��save�������Ӽ�¼
		getHibernateTemplate().save(brand);
	}

	/**
	 * �޸�Ʒ��
	 * @param brand ��Ҫ�޸ĵ�Ʒ��
	 */
	public void update(Brand brand)
	{
		//������HibernateTemplate��saveOrUpdate���¼�¼
		getHibernateTemplate().saveOrUpdate(brand);
	}

	/**
	 * ɾ��Ʒ��
	 * @param id ��Ҫɾ����Ʒ��id
	 */
	public void delete(Integer id)
	{
		//������HibernateTemplate��delete����ɾ���ض�������Ӧ��¼
		getHibernateTemplate().delete(get(id));
	}

	/**
	 * ɾ��Ʒ��
	 * @param brand ��Ҫɾ����Ʒ��
	 */
	public void delete(Brand brand)
	{
		//������HibernateTemplate��delete����ɾ��ָ��ʵ��
		getHibernateTemplate().delete(brand);
	}

	/**
	 * ����ǰ׺��ѯƷ��
	 * @param prefix ǰ׺
	 * @return ��ǰ׺��Ӧ��Ʒ��
	 */
	public List<Brand> findAll()
	{
		//������HibernateTemplate��find()������ѯ��¼
		return (List<Brand>)getHibernateTemplate()
			.find("from Brand");
	}
}
