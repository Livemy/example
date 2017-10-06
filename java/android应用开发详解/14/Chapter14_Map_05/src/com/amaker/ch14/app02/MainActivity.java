package com.amaker.ch14.app02;

import java.io.IOException;
import java.util.List;
import java.util.Locale;

import android.app.Activity;
import android.content.Context;
import android.location.Address;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationManager;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {
	// ����TextView
	private TextView tv;
	// ����Button
	private Button b1,b2;
    // ��λ���������ʵ��
    private LocationManager locationManager;
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
    	// ���õ�ǰActivity�Ľ��沼��
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
      	// ��λ������
	    String locService = Context.LOCATION_SERVICE;
	    // ͨ��getSystemService�������LocationManagerʵ��
	    locationManager = (LocationManager)getSystemService(locService);
	    // ͨ��findViewById�������TextViewʵ��
	    tv = (TextView) findViewById(R.id.TextView01);
	    
	    // ͨ��findViewById�������Buttonʵ��
	    b1 = (Button) findViewById(R.id.Button01);
	    // ͨ��findViewById�������Buttonʵ��
	    b2 = (Button) findViewById(R.id.Button02);
	    // Ϊ��ť��ӵ����¼�������
	    b1.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				// �������
				forward();
			}
		});
	    
	    // Ϊ��ť��ӵ����¼�������
	    b2.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				// �������
				reverse();
			}
		});
    }
    
    // �������
    private void forward() {
    	// ʵ����Geocoder
    	Geocoder gc = new Geocoder(this, Locale.getDefault());
    	// ��ַ
    	String address = "�����찲��";
    	// λ���б�
    	List<Address> locations = null;
    	try {
    		// ���λ�����
    		locations = gc.getFromLocationName(address, 10);
    		// ���Locations��Ϊ��
    		if(locations.size()>0){
    			// ���Addressʵ��
    			Address a = locations.get(0);
    			// ��þ�γ��
    			double lat = a.getLatitude();
    			double lng = a.getLongitude();
    			// ��ʾ��Ϣ
    			tv.setText(lat+":"+lng);
    		}
    	} catch (IOException e) {}
    }
    
    
    // �������
    private void reverse() {
    	// ����
    	double lng = 116.46;
    	// γ��
    	double lat = 39.92;
    	// ʵ����Geocoder
    	Geocoder gc = new Geocoder(this, Locale.getDefault());
    	// ������ַ�б�
    	List<Address> addresses = null;
    	try {
    		// ���Addressʵ���б�
    		addresses = gc.getFromLocation(lat, lng, 10);
    		// ����StringBuilder������λ����Ϣ
    		StringBuilder sb = new StringBuilder();
    		// �ж�addresses�Ƿ�Ϊ��
    		if(addresses.size()>0){
    			// ���Address
    			Address a = addresses.get(0);
    			for (int i = 0; i < a.getMaxAddressLineIndex(); i++){
    				// ��ַ
    				sb.append(a.getAddressLine(i)).append("\n");
    				// �ص�
    				sb.append(a.getLocality()).append("\n");
    				// �ʱ�
    				sb.append(a.getPostalCode()).append("\n");
    				// ��������
    				sb.append(a.getCountryName());
    			}
    			tv.setText(sb.toString());
    		}
    	} catch (IOException e) {}
    }
}