package com.amaker.ch08.app;

import com.amaker.ch08.app.R;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
/**
 * 
 * @author ����־
 * �����㲥
 */
public class MainActivity extends Activity {
	// ����һ��Action����
	private static final String MY_ACTION = "com.amaker.ch08.action.MY_ACTION";
	// ����һ��Button����
	private Button btn;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // ���õ�ǰ������ͼ
        setContentView(R.layout.main);
        btn = (Button)findViewById(R.id.Button01);
        // Ϊ��ť���õ���������
        btn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				// ʵ����Intent����
		        Intent intent = new Intent();
		        // ����Intent action����
		        intent.setAction(MY_ACTION);
		        // ΪIntent��Ӹ�����Ϣ
		        intent.putExtra("msg", "�عϵعϣ������������յ���ظ����յ���ظ���");
		        // �����㲥
		        sendBroadcast(intent);
			}
		});
    }
}