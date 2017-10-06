package com.amaker.ch06.app;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
/**
 * 
 * @author ����־
 * ����Intent Action ����
 */
public class MainActivity extends Activity {
	// ����Action ���Գ���
	public static final String MY_ACTION="com.amaker.ch07.app.MY_ACTION";
	// ����Button
	private Button btn;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // ���ò�����ͼ
        setContentView(R.layout.main);
        // ʵ����Button
        btn = (Button)findViewById(R.id.Button01);
        btn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				 // ʵ����Intent
		        Intent intent = new Intent();
		        // ΪIntent����Action����
		        intent.setAction(MY_ACTION);
		        // ����Activity
		        startActivity(intent);
			}
		});
    }
}