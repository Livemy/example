package com.amaker.ch14.app01;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.location.LocationManager;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity {
	// Intent Action ����
	private static String PROXIMITY_ALERT_ACTION_NAME = "com.amaker.ch14.ProximityAlert";
	// ������ťButtonʵ��
	private Button btn;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // ���õ�ǰActivity�Ľ��沼��
        setContentView(R.layout.main);
        // ͨ��findViewById�������Buttonʵ��
        btn = (Button)findViewById(R.id.Button01);
        btn.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				// �趨
				set();
			}
		});
    }
    
    // ������ʾ����
    private void set() {
    	// ��λ������
	    String locService = Context.LOCATION_SERVICE;
	    // ��λ���������ʵ��
	    LocationManager locationManager;
	    // ͨ��getSystemService�������LocationManagerʵ��
	    locationManager = (LocationManager)getSystemService(locService);
	    // ��������
	    double lat = 37.4;
	    // ����γ��
	    double lng = 55.0;
	    // �����뾶(��λ��)
	    float radius = 200f;
	    // ������
	    long expiration = -1; 
	    // ����Intent
	    Intent intent = new Intent(PROXIMITY_ALERT_ACTION_NAME);
	    // ����PendingIntent
	    PendingIntent pi = 
	    	PendingIntent.getBroadcast(this, -1,intent,0);
	    // �����������
	    locationManager.addProximityAlert(lat, lng, radius, expiration,pi);
    }
}