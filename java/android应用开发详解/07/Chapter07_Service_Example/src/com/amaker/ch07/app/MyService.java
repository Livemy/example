package com.amaker.ch07.app;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;
import android.widget.Toast;

/**
 * @author ����־
 * ����Service
 */
public class MyService extends Service{
	
	// ���Է���null��ͨ������һ����aidl����Ľӿ�
	public IBinder onBind(Intent intent) {
		Log.i("SERVICE", "onBind..............");
		Toast.makeText(MyService.this, "onBind..............", Toast.LENGTH_LONG).show();
		return null;
	}
	// Service����ʱ����
	public void onCreate() {
		Log.i("SERVICE", "onCreate..............");
		Toast.makeText(MyService.this, "onCreate..............", Toast.LENGTH_LONG).show();
	}
	// ���ͻ��˵���startService()��������Serviceʱ���÷���������
	public void onStart(Intent intent, int startId) {
		Log.i("SERVICE", "onStart..............");
		Toast.makeText(MyService.this, "onStart..............", Toast.LENGTH_LONG).show();
	}
	// ��Service����ʹ��ʱ����
	public void onDestroy() {
		Log.i("SERVICE", "onDestroy..............");
		Toast.makeText(MyService.this, "onDestroy..............", Toast.LENGTH_LONG).show();
	}
}
