package com.amaker.test;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

// �̳�Activity
public class MainActivity extends Activity {
	// ����Ҫʹ�õ����
	private TextView myTextView;
	private Button myButton;
    // ����onCreate����
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // ���õ�ǰ��ͼ
        setContentView(R.layout.main);
        // ͨ��findViewById()������ʵ�������
        myTextView = (TextView) findViewById(R.id.TextView01);
        myButton = (Button) findViewById(R.id.Button01);
    }
}