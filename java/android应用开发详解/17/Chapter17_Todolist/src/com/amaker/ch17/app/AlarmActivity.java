package com.amaker.ch17.app;

import android.app.Activity;
import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

/**
 * @author ����־
 * �����û�
 */
public class AlarmActivity extends Activity {
	public static final int ID = 1;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.alarm);
		// ���Button��TextViewʵ��
		Button btn = (Button) findViewById(R.id.cancelButton01);
		TextView tv = (TextView)findViewById(R.id.msgTextView01);
		
		// ���NotificationManagerʵ��
		String service = Context.NOTIFICATION_SERVICE;
		final NotificationManager nm = (NotificationManager)getSystemService(service);
		// ʵ����Notification
		Notification n = new Notification();
		// ������ʾ��ʾ��Ϣ������ϢҲ����״̬����ʾ
		String msg = getIntent().getStringExtra("msg");
		// ��ʾʱ��
		n.tickerText = msg;
		tv.setText(msg);
		
		// ����������ʾ
		n.sound = Uri.parse("file:///sdcard/fallbackring.ogg");
		// ����֪ͨ
		nm.notify(ID, n);
		// ȡ��֪ͨ
		btn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				nm.cancel(ID);
				finish();
			}
		});
	}
}
