package com.amaker.ch17.app;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

/**
 * @author ����־
 * ��ʱ���ѹ㲥
 */
public class TaskReceiver extends BroadcastReceiver{
	@Override
	public void onReceive(Context context, Intent intent) {
		
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		
		intent.setClass(context, AlarmActivity.class);
		
		context.startActivity(intent);
		
	}
}
