package cn.hxex.springcore.beanwrapper;

import org.springframework.beans.BeanWrapper;
import org.springframework.beans.BeanWrapperImpl;

public class BeanWrapperMain {

	public static void main(String[] args) {
		
		Company c = new Company();
		BeanWrapper bwComp = new BeanWrapperImpl(c);
		
		// �����ַ�����ֵ
		bwComp.setPropertyValue( "name", "Surecomp China" );
		// ���������������Ե�ֵ
		bwComp.setPropertyValue( "addresses[0]", "Address0" );
		bwComp.setPropertyValue( "addresses[1]", "Address1" );
		bwComp.setPropertyValue( "addresses[2]", "Address2" );
		
		bwComp.setPropertyValue( "managingDirector", new Employee() );
		
		// ����HashMap��ֵ
		bwComp.setPropertyValue( "managingDirector.telephones[home]", "11111111" );
		bwComp.setPropertyValue( "managingDirector.telephones[mobile]", "22222222" );

		// ��������ֵ
		bwComp.setPropertyValue( "managingDirector.salary", "80000.00" );

		System.out.println( c.toString() );
	}

}
