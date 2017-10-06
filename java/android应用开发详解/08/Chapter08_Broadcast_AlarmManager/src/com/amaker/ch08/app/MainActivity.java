package com.amaker.ch08.app;

import com.amaker.ch08.app.R;

import android.app.Activity;
import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

/**
 * 
 * @author ����־ 
 * ����AlarmManager
 */
public class MainActivity extends Activity {
	// ����Button
	private Button setBtn, cancelBtn;
	// ����㲥Action
	private static final String BC_ACTION = "com.amaker.ch08.app.action.BC_ACTION";

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		// ���õ�ǰ������ͼ
		setContentView(R.layout.main);
		
		// ʵ����Button
		setBtn = (Button) findViewById(R.id.Button01);
		cancelBtn = (Button) findViewById(R.id.Button02);
		
		// ���AlarmManagerʵ��
		final AlarmManager am = (AlarmManager) getSystemService(ALARM_SERVICE);
		
		// ʵ����Intent
		Intent intent = new Intent();
		// ����Intent action����
		intent.setAction(BC_ACTION);
		intent.putExtra("msg", "���ȥ��������");
		// ʵ����PendingIntent
		final PendingIntent pi = PendingIntent.getBroadcast(MainActivity.this, 0,
				intent, 0);
		// ���ϵͳʱ��
		final long time = System.currentTimeMillis();

		// ���ð�ť�����¼�
		setBtn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				// �ظ���ʾ���ӵ�ǰʱ�俪ʼ�����5��
				am.setRepeating(AlarmManager.RTC_WAKEUP, time,
						8 * 1000, pi);
			}
		});
		
		// ���ð�ť�����¼�
		cancelBtn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				am.cancel(pi);
			}
		});
	}
}