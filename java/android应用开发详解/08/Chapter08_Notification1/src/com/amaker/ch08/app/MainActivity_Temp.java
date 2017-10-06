package com.amaker.ch08.app;

import com.amaker.ch08.app.R;

import android.app.Activity;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore.Audio;

public class MainActivity_Temp extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        String service = NOTIFICATION_SERVICE;
        NotificationManager nm = (NotificationManager)getSystemService(service);
        
        // ʵ����Notification
        Notification n = new Notification();
        // ������ʾͼ�꣬��ͼ�����״̬����ʾ
        int icon = n.icon = R.drawable.icon; 
        // ������ʾ��ʾ��Ϣ������ϢҲ����״̬����ʾ
        String tickerText = "Test Notification"; 
        // ��ʾʱ��
        long when = System.currentTimeMillis();
        n.icon = icon;
        n.tickerText = tickerText;
        n.when = when;
        
        // Ҳ����ͨ�����ֹ��췽��������
        Notification n1 = new Notification(icon, tickerText, when); 
        
        // ʵ����Intent
        Intent intent = new Intent(this, MainActivity_Temp.class); 
        // ���PendingIntent
        PendingIntent pi = PendingIntent.getActivity(this, 0, intent, 0); 
        // �����¼���Ϣ
        n.setLatestEventInfo(this, "My Title", "My Content", pi); 
        
        
        
        
        
        n.defaults |= Notification.DEFAULT_SOUND; 
        n.sound = Uri.parse("file:///sdcard/sound.mp3"); 
        n.sound = Uri.withAppendedPath(Audio.Media.INTERNAL_CONTENT_URI, "6"); 

        
        n.defaults |= Notification.DEFAULT_VIBRATE; 
        long[] vibrate = {0,50,100,150}; 
        n.vibrate = vibrate; 
        
        
        n.defaults |= Notification.DEFAULT_LIGHTS; 
        n.ledARGB = 0xff00ff00; 
        n.ledOnMS = 300; 
        n.ledOffMS = 1000; 
        n.flags |= Notification.FLAG_SHOW_LIGHTS; 


        
        
        
        
        
        // ��ʾ��֪ͨ��ID
        int ID = 1;
        // ����֪ͨ
        nm.notify(ID, n);
        
        
        
        
        
        
    }
}