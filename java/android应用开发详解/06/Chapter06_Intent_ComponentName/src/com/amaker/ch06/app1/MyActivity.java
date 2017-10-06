package com.amaker.ch06.app1;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

import com.amaker.ch06.app.R;

/**
 * @author ����־
 * ����Intent��ComponentName����
 */
public class MyActivity extends Activity {
	// ����TextView
	private TextView tv;
    @Override
    public void onCreate(Bundle savedInstanceState) {
    	// ������ͼ����
        super.onCreate(savedInstanceState);
        setContentView(R.layout.my_layout);
        // ���Intent
        Intent intent = this.getIntent();
        // ���������ƶ���
        ComponentName cn = intent.getComponent();
        // ��ð�����
        String packageName = cn.getPackageName();
        // ���������
        String className = cn.getClassName();
        // ʵ����TextView
        tv = (TextView)findViewById(R.id.TextView01);
        // ��ʾ
        tv.setText("��������ƣ�"+packageName+"\n"+"��������ƣ�"+className);
    }
}