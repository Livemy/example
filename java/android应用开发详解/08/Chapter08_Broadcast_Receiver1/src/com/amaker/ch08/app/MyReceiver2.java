package com.amaker.ch08.app;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

/**
 * 
 * @author ����־
 * ��ʾϵͳ������ɹ㲥������
 */
public class MyReceiver2 extends BroadcastReceiver{

	@Override
	public void onReceive(Context context, Intent intent) {
		// ��ʾ�㲥��Ϣ
		Log.i("my_tag", "BOOT_COMPLETED~~~~~~~~~~~~~~~~");
	}

}
