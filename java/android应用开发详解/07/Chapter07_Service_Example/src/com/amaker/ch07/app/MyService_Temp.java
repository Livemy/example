package com.amaker.ch07.app;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

/**
 * @author ����־
 * ����Service
 */
public class MyService_Temp extends Service{
	
	// ���Է���null��ͨ������һ����aidl����Ľӿ�
	public IBinder onBind(Intent intent) {
		return null;
	}
	// Service����ʱ����
	public void onCreate() {
		super.onCreate();
	}
	// ���ͻ��˵���startService()��������Serviceʱ���÷���������
	public void onStart(Intent intent, int startId) {
		super.onStart(intent, startId);
	}
	// ��Service����ʹ��ʱ����
	public void onDestroy() {
		super.onDestroy();
	}
}
