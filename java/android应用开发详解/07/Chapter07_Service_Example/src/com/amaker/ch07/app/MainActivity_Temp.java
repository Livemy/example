package com.amaker.ch07.app;

import com.amaker.ch07.app.R;

import android.app.Activity;
import android.app.Service;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;

public class MainActivity_Temp extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        // ����Intent
        Intent intent = new Intent();
        // ����Action����
        intent.setAction("com.amaker.ch08.app.action.MY_SERVICE");
        // ������Service
        startService(intent);
        // ֹͣһ��Service
        stopService(intent);
        
        
        // ���Ӷ���
        ServiceConnection conn = new ServiceConnection() {
        	@Override
			public void onServiceConnected(ComponentName name, IBinder service) {
				Log.i("SERVICE", "���ӳɹ���");
			}
        	
			@Override
			public void onServiceDisconnected(ComponentName name) {
				Log.i("SERVICE", "�Ͽ����ӣ�");
			}
		};
        // ��Service
        bindService(intent, conn, Service.BIND_AUTO_CREATE);
    }
}