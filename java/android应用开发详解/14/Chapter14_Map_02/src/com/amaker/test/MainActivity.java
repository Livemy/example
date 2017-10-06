package com.amaker.test;

import android.app.Activity;
import android.content.Context;
import android.location.Location;
import android.location.LocationManager;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends Activity {
	private LocationManager locationManager;
	private TextView tv;

	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		locationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
		tv = (TextView) findViewById(R.id.myTextView01);

		Location location = locationManager
				.getLastKnownLocation(LocationManager.GPS_PROVIDER);
		printMsg(location);

	}

	private void printMsg(Location l) {
		StringBuilder builder = new StringBuilder("�����õ�providers:");
		
		if (l != null) {
			double lat = l.getLatitude();
			double lng = l.getLongitude();
			builder.append("(");
			builder.append(lat);
			builder.append(",");
			builder.append(lng);
			builder.append(")");
			
			if(l.hasAccuracy()){
				builder.append("\n���ȣ�");
				builder.append(l.getAccuracy());
			}
			
			if(l.hasAltitude()){
				builder.append("\n�߶ȣ�");
				builder.append(l.getAltitude());
			}
			
			if(l.hasBearing()){
				builder.append("\n����");
				builder.append(l.getBearing());
			}
			
			if(l.hasSpeed()){
				builder.append("\n�ٶȣ�");
				builder.append(l.getSpeed());
			}

		} else {
			builder.append("û��λ����Ϣ");
		}
		tv.setText(builder);
	}

}