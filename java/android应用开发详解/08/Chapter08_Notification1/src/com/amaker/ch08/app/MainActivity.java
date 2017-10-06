package com.amaker.ch08.app;

import com.amaker.ch08.app.R;

import android.app.Activity;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

/**
 * @author ����־
 * ����֪ͨ
 */

public class MainActivity extends Activity {
	// ������ť
	private Button sendBtn,cancelBtn;
	// ����Notification
	private Notification n ;
	// ����NotificationManager
	private NotificationManager nm;
	// Notification��ʾID
	private static final int ID = 1;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        // ʵ������ť
        sendBtn = (Button)findViewById(R.id.sendButton01);
        cancelBtn = (Button)findViewById(R.id.cancelButton02);
        
        // ���NotificationManagerʵ��
        String service = NOTIFICATION_SERVICE;
        nm = (NotificationManager)getSystemService(service);
        
        // ʵ����Notification
        n = new Notification();
        // ������ʾͼ�꣬��ͼ�����״̬����ʾ
        int icon = n.icon = R.drawable.happy; 
        // ������ʾ��ʾ��Ϣ������ϢҲ����״̬����ʾ
        String tickerText = "Test Notification"; 
        // ��ʾʱ��
        long when = System.currentTimeMillis();
        n.icon = icon;
        n.tickerText = tickerText;
        n.when = when;
        // Ϊ��ť��Ӽ�����
        sendBtn.setOnClickListener(sendListener);
        cancelBtn.setOnClickListener(cancelListener);
        
    }
    // ����֪ͨ������
    private OnClickListener sendListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
	        // ʵ����Intent
	        Intent intent = new Intent(MainActivity.this, MainActivity.class); 
	        // ���PendingIntent
	        PendingIntent pi = PendingIntent.getActivity(MainActivity.this, 0, intent, 0); 
	        // �����¼���Ϣ
	        n.setLatestEventInfo(MainActivity.this, "My Title", "My Content", pi); 
	        // ����֪ͨ
	        nm.notify(ID, n);
		}
	};
	// ȡ��֪ͨ������
	 private OnClickListener cancelListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			// ȡ��֪ͨ
			nm.cancel(ID);
		}
	};
}