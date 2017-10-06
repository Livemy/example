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
public class ModelDaoHibernate 
	extends HibernateDaoSupport implements ModelDao
{
	/**
	 * ����id�����ͺ�
	 * @param id ��Ҫ���ҵ��ͺ�id
	 */
	public Model get(Integer id)
	{
		return (Model)getHibernateTemplate()
			.get(Model.class , id);
	}
	/**
	 * �����ͺ�
	 * @param model ��Ҫ���ӵ��ͺ�
	 */
	public void save(Model model)
	{
		getHibernateTemplate().save(model);
	}

	/**
	 * �޸��ͺ�
	 * @param model ��Ҫ�޸ĵ��ͺ�
	 */
	public void update(Model model)
	{
		getHibernateTemplate().saveOrUpdate(model);
	}

	/**
	 * ɾ���ͺ�
	 * @param id ��Ҫɾ�����ͺ�id
	 */
	public void delete(Integer id)
	{
		getHibernateTemplate().delete(get(id));
	}

	/**
	 * ɾ���ͺ�
	 * @param model ��Ҫɾ�����ͺ�
	 */
	public void delete(Model model)
	{
		getHibernateTemplate().delete(model);
	}

	/**
	 * ��ѯȫ���ͺ�
	 * @return ����ȫ���ͺ�
	 */
	public List<Model> findAll()
	{
		return (List<Model>)getHibernateTemplate()
			.find("from Model");
	}

	/**
	 * ����Ʒ�Ʋ�ѯ�ͺ�
	 * @param brand ��Ҫ��ѯ��Ʒ��
	 * @return ��Ʒ�ƶ�Ӧ��ȫ�����ͺ�
	 */
	public List<Model> findByBrand(String brand)
	{
		return (List<Model>)getHibernateTemplate()
			.find("from Model as m where m.brand.name=?" , brand);
	}

	/**
	 * �����ͺ�����ѯ�ͺ�
	 * @param model ��Ҫ��ѯ���ͺ���
	 * @return ���ͺ�����Ӧ���ͺ�
	 */
	public Model findByModel(String model)
	{
		List<Model> ml = (List<Model>)getHibernateTemplate()
			.find("from Model as m where m.name=?" , model);
		if (ml != null && ml.size() >= 0)
		{
			return ml.get(0);
		}
		return null;
	}
}
