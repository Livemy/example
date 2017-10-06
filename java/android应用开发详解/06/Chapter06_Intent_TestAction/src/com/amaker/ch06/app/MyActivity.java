package com.amaker.ch06.app;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;
/**
 * @author ����־
 * ����Intent Action ����
 */
public class MyActivity extends Activity {
	// ����TextView
	private TextView tv;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // ������ͼ����
        setContentView(R.layout.my_layout);
        // ���Intent����
        Intent intent = getIntent();
        // ���Action
        String action = intent.getAction();
        // ���TextView
        tv = (TextView)findViewById(R.id.TextView01);
        // ��������
        tv.setText(action);
    }
}