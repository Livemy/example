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
 */
public class DisplayActivity extends Activity {
	// ������ť
	private Button cancelBtn;
	// ����Notification
	private Notification n ;
	// ����NotificationManager
	private NotificationManager nm;
	// Notification��ʾID
	private static final int ID = 1;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main2);
        // ʵ������ť
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
        
        // ʵ����Intent
        Intent intent = new Intent(this, MainActivity.class); 
        // ���PendingIntent
        PendingIntent pi = PendingIntent.getActivity(this, 0, intent, 0); 
        // �����¼���Ϣ
        n.setLatestEventInfo(this, "My Title", "My Content", pi); 
        // ����֪ͨ
        nm.notify(ID, n);
        
        // Ϊ��ť��Ӽ�����
        cancelBtn.setOnClickListener(cancelListener);
    }
    
	// ȡ��֪ͨ������
	 private OnClickListener cancelListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			// ȡ��֪ͨ
			nm.cancel(ID);
		}
	};
}