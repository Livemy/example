package org.crazyjava.inputtip.dao;

import java.util.List;
import org.crazyjava.inputtip.model.*;

/**
 * Description:
 * <br/>��վ: <a href="http://www.crazyjava.org">���Java����</a> 
 * <br/>Copyright (C), 2001-2010, crazyjava.inputtip.H.Lee
 * <br/>This program is protected by copyright laws.
 * <br/>Program Name:
 * <br/>Date:
 * @author  crazyjava.inputtip.H.Lee kongcrazyjava.inputtip@163.com
 * @version  1.0
 */
public interface BrandDao  
{
	/**
	 * ����id����Ʒ��
	 * @param id ��Ҫ���ҵ�Ʒ��id
	 */
	Brand get(Integer id);
	
	/**
	 * ����Ʒ��
	 * @param Brand ��Ҫ���ӵ�Ʒ��
	 */
	void save(Brand Brand);

	/**
	 * �޸�Ʒ��
	 * @param Brand ��Ҫ�޸ĵ�Ʒ��
	 */
	void update(Brand Brand);

	/**
	 * ɾ��Ʒ��
	 * @param id ��Ҫɾ����Ʒ��id
	 */
	void delete(Integer id);

	/**
	 * ɾ��Ʒ��
	 * @param Brand ��Ҫɾ����Ʒ��
	 */
	void delete(Brand Brand);

	/**
	 * ��ѯȫ��Ʒ��
	 * @return ȫ��Ʒ��
	 */
	List<Brand> findAll();
}