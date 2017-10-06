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
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

/**
 * @author ����־
 * ����Service
 */

public class MainActivity extends Activity {
	// ����Button
	private Button startBtn,stopBtn,bindBtn,unbindBtn;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // ���õ�ǰ������ͼ
        setContentView(R.layout.main);
        // ʵ����Button
        startBtn = (Button)findViewById(R.id.startButton01);
        stopBtn = (Button)findViewById(R.id.stopButton02);
        bindBtn = (Button)findViewById(R.id.bindButton03);
        unbindBtn = (Button)findViewById(R.id.unbindButton04);
        
        // ��Ӽ�����
        startBtn.setOnClickListener(startListener);
        stopBtn.setOnClickListener(stopListener);
        bindBtn.setOnClickListener(bindListener);
        unbindBtn.setOnClickListener(unBindListener);
        
    }
    // ����Service������
    private OnClickListener startListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
	        // ����Intent
	        Intent intent = new Intent();
	        // ����Action����
	        intent.setAction("com.amaker.ch07.app.action.MY_SERVICE");
	        // ������Service
	        startService(intent);
		}
	};
	
    // ֹͣService������
    private OnClickListener stopListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
	        // ����Intent
	        Intent intent = new Intent();
	        // ����Action����
	        intent.setAction("com.amaker.ch07.app.action.MY_SERVICE");
	        // ������Service
	        stopService(intent);
		}
	};
	
   // ���Ӷ���
   private ServiceConnection conn = new ServiceConnection() {
    	@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			Log.i("SERVICE", "���ӳɹ���");
			Toast.makeText(MainActivity.this, "���ӳɹ���", Toast.LENGTH_LONG).show();
		}
		@Override
		public void onServiceDisconnected(ComponentName name) {
			Log.i("SERVICE", "�Ͽ����ӣ�");
			Toast.makeText(MainActivity.this, "�Ͽ����ӣ�", Toast.LENGTH_LONG).show();
		}
	};
	
    // ����Service������
    private OnClickListener bindListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
	        // ����Intent
	        Intent intent = new Intent();
	        // ����Action����
	        intent.setAction("com.amaker.ch07.app.action.MY_SERVICE");
	     
	        // ��Service
	        bindService(intent, conn, Service.BIND_AUTO_CREATE);
		}
	};
	
	
    // �����Service������
    private OnClickListener unBindListener = new OnClickListener() {
		@Override
		public void onClick(View v) {
	        // ����Intent
	        Intent intent = new Intent();
	        // ����Action����
	        intent.setAction("com.amaker.ch07.app.action.MY_SERVICE");
	        // �����Service
	        unbindService(conn);
		}
	};
	
}