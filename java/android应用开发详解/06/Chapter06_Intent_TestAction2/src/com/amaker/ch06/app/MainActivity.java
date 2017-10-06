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
	// ����Button
	private Button btn;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // ���õ�ǰ������ͼ
        setContentView(R.layout.main);
        // ʵ����Button
        btn = (Button)findViewById(R.id.Button01);
        btn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
		        // ����Intent
		        Intent intent = new Intent();
		        // ����Intent Action����
		        intent.setAction(Intent.ACTION_GET_CONTENT);
		        // ����Intent Type ����
		        intent.setType("vnd.android.cursor.item/phone");
		        // ����Activity
		        startActivity(intent);
			}
		});
    }
}