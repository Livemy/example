package com.amaker.test;
import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
/**
 * 
 * @author ����־
 * ѡ��˵�ʵ��
 */
public class MainActivity extends Activity {
	
	private static final int ITEM1 = Menu.FIRST;
	private static final int ITEM2 = Menu.FIRST+1;
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
    }

	/**
	 * ���Ǹ÷�����Ӳ˵���
	 */
	public boolean onCreateOptionsMenu(Menu menu) {
		menu.add(0, ITEM1, 0, "��ʼ");
		menu.add(0, ITEM2, 0, "�˳�");
		return true;
	}
    
    /**
     * ���Ǹ÷�������Ӧ�˵�ѡ������¼�
     */
    public boolean onOptionsItemSelected(MenuItem item) {
    	switch (item.getItemId()) {
		case ITEM1:
			setTitle("��ʼ��Ϸ��");
			break;
		case ITEM2:
			setTitle("�˳���");
			break;
		}
    	return true;
    }
}