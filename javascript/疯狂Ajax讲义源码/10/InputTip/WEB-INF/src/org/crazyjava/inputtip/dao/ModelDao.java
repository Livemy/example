package org.crazyjava.inputtip.dao;

import java.util.List;

import org.crazyjava.inputtip.model.*;

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
public interface ModelDao  
{
	/**
	 * ����id�����ͺ�
	 * @param id ��Ҫ���ҵ��ͺ�id
	 */
	 Model get(Integer id);
	
	/**
	 * �����ͺ�
	 * @param Model ��Ҫ���ӵ��ͺ�
	 */
	void save(Model model);

	/**
	 * �޸��ͺ�
	 * @param Model ��Ҫ�޸ĵ��ͺ�
	 */
	void update(Model model);

	/**
	 * ɾ���ͺ�
	 * @param id ��Ҫɾ�����ͺ�id
	 */
	void delete(Integer id);

	/**
	 * ɾ���ͺ�
	 * @param Model ��Ҫɾ�����ͺ�
	 */
	void delete(Model model);

	/**
	 * ��ѯȫ���ͺ�
	 * @return ȫ���ͺ�
	 */
	List<Model> findAll();

	/**
	 * ����Ʒ�Ʋ�ѯ�ͺ�
	 * @param brand ��Ҫ��ѯ��Ʒ��
	 * @return ��Ʒ�ƶ�Ӧ��ȫ�����ͺ�
	 */
	List<Model> findByBrand(String brand);

	/**
	 * �����ͺŲ�ѯ�ͺ�
	 * @param model ��Ҫ��ѯ���ͺ�
	 * @return ���ͺŶ�Ӧ��ȫ�����ͺ�
	 */
	Model findByModel(String model);
}