package com.amaker.test;
import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ContextMenu.ContextMenuInfo;
import android.widget.TextView;

/**
 * 
 * @author ����־ ���������Ĳ˵����ı䱳��ɫ
 */
public class MainActivity extends Activity {
	private static final int ITME1 = Menu.FIRST;
	private static final int ITME2 = Menu.FIRST+1;
	private static final int ITME3 = Menu.FIRST+2;
	private TextView myTV;
	
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		myTV = (TextView)findViewById(R.id.TextView01);
		registerForContextMenu(myTV);
	}

	@Override
	public void onCreateContextMenu(ContextMenu menu, View v,
			ContextMenuInfo menuInfo) {
		menu.add(0, ITME1, 0, "��ɫ����");
		menu.add(0, ITME2, 0, "��ɫ����");
		menu.add(0, ITME3, 0, "��ɫ����");
	}
	
	@Override
	public boolean onContextItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case ITME1:
			myTV.setBackgroundColor(Color.RED);
			break;
		case ITME2:
			myTV.setBackgroundColor(Color.GREEN);
			break;
		case ITME3:
			myTV.setBackgroundColor(Color.WHITE);
			break;
		}
		return true;
	}
}