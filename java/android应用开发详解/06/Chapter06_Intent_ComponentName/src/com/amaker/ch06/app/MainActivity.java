package com.amaker.ch06.app;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

/**
 * @author ����־
 * ����Intent��ComponentName����
 */
public class MainActivity extends Activity {
	private Button btn;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // ������ͼ����
        setContentView(R.layout.main);
        // ʵ����Button
        btn = (Button)findViewById(R.id.myButton01);
        // ��ӵ���������
        btn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				// ʵ�����������
				ComponentName cn = new ComponentName(MainActivity.this, "com.amaker.ch06.app1.MyActivity");
				// ʵ����Intent
		        Intent intent = new Intent();
		        // ΪIntent���������������
		        intent.setComponent(cn);
		        // ����Activity
		        startActivity(intent);
			}
		});
    }
}