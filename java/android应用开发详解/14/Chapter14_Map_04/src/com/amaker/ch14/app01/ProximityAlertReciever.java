package com.amaker.ch14.app01;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.location.LocationManager;
import android.widget.Toast;

public class ProximityAlertReciever extends BroadcastReceiver{
	@Override
	public void onReceive(Context context, Intent intent) {
		// �����ؼ���
		String key = LocationManager.KEY_PROXIMITY_ENTERING;
		// ��Intent��ö�����Ϣ���ж��Ƿ������������
		Boolean isEnter = intent.getBooleanExtra(key, false);
		if(isEnter){
			Toast.makeText(context, "���Ѿ����뺣������", Toast.LENGTH_LONG);
		}
	}
}
