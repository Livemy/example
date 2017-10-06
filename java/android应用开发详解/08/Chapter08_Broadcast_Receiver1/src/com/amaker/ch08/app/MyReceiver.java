package com.amaker.ch08.app;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

/**
 * @author ����־
 * ���չ㲥
 */
public class MyReceiver extends BroadcastReceiver{
	
	@Override
	public void onReceive(Context cxt, Intent intent) {
		// ��Intent�л����Ϣ
		String msg = intent.getStringExtra("msg");
		// ʹ��Toast��ʾ
		Toast.makeText(cxt, msg, Toast.LENGTH_LONG).show();
	}
}
