package com.amaker.ch08.app;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
/**
 * @author ����־
 */
public class MyReceiver extends BroadcastReceiver{
	@Override
	public void onReceive(Context context, Intent intent) {
		// ʵ����Intent
		Intent i = new Intent();
		// ���µ�����������Activity
		i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		// ����Intent�������������
		i.setClass(context, DisplayActivity.class);
		// ����Activity��ʾ֪ͨ
		context.startActivity(i);
	}

}
