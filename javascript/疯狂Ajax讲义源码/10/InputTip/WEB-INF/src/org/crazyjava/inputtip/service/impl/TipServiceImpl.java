package org.crazyjava.inputtip.service.impl;

import org.crazyjava.inputtip.dao.*;
import org.crazyjava.inputtip.model.*;
import org.crazyjava.inputtip.service.*;

import java.util.*;
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
public class TipServiceImpl implements TipService
{
	//ʵ��ҵ���߼�����������������DAO���
	private BrandDao bd;
	private ModelDao md;
	//����ע������DAO����������setter����
	public void setBrandDao(BrandDao bd)
	{
		this.bd = bd;
	}
	public void setModelDao(ModelDao md)
	{
		this.md = md;
	}
	////����Ʒ��ǰ׺���������Ը�ǰ׺��ʼ��������
	public List<String> getBrandsByPrefix(String prefix)
	{
		//�������е�Ʒ�Ƽ�¼
		List<Brand> brands = bd.findAll();
		List<String> result = new ArrayList<String>();
		//�������е�Ʒ�Ƽ�¼
		for (Brand brand : brands )
		{
			//���Ʒ�Ƽ�¼��ǰ׺��ʼ
			if (brand.getName().toUpperCase()
				.startsWith(prefix.toUpperCase()))
			{
				//����Ʒ����ӵ����������
				result.add(brand.getName());
			}
		}
		return result;
	}
	//����Ʒ�������ظ�Ʒ�Ƶ������ͺ�����
	public List<String> getModelsByBrand(String brand)
	{
		List<String> result = new ArrayList<String>();
		//����Ʒ�Ʒ������е��ͺ�ʵ��
		List<Model> mlist = md.findByBrand(brand);
		//�����ͺż��ϣ���ÿ���ͺŵ�������ӵ����������
		for (Model model : mlist )
		{
			result.add(model.getName());
		}
		return result;
	}
	//�����ͺ����������ͺ�����
	public String getDescByModel(String model)
	{
		//�����ͺ��������ض����ͺ�ʵ��
		Model m = md.findByModel(model);
		//����ͺŲ�Ϊ�գ��򷵻��ͺ�����
		if (m != null)
		{
			return m.getDesc();
		}
		return null;
	}
}