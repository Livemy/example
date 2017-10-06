package com.amaker.ch06.app;

import com.amaker.ch06.app.R;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
/**
 * 
 * @author ����־
 * Intent Filter ����
 */
public class MainActivity extends Activity {
	// ����Button
	private Button btn;
	private static final String ACTION1 = "com.amaker.ch06.app.TEST_ACTION1";
	private static final String ACTION2 = "com.amaker.ch06.app.TEST_ACTION2";
	private static final String ACTION3 = "com.amaker.ch06.app.TEST_ACTION3";
	
	private static final String CATEGORY1 = "com.amaker.ch06.app.CATEGORY1";
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // �������ݲ���
        setContentView(R.layout.main);
        //ʵ������ť
        btn = (Button)findViewById(R.id.Button01);
        
        String a = Intent.ACTION_VIEW;
        // ��ӵ���������
        btn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View view) {
				  Intent intent = new Intent();
				  //intent.setAction(ACTION1);
				  //Uri data = Uri.parse("content://com.amaker.ch07.app/abc");
				  //intent.setData(data);
				  
				  intent.addCategory(CATEGORY1);
				  
				  intent.setAction("android.intent.action.VIEW");
				  intent.setData(Uri.parse("http://www.google.com"));
				  
			      startActivity(intent);
			}
		});
    }
}