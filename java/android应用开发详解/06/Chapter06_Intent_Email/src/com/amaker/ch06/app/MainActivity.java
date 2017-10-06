package com.amaker.ch06.app;

import com.amaker.ch06.app.R;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

/**
 * @author ����־
 * ����Email
 */
public class MainActivity extends Activity {
	// ������ͼ���
	private EditText toEditText,subjectEditText,contentEditText;
	private Button sendBtn;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        // ʵ������ͼ���
        toEditText = (EditText)findViewById(R.id.toEditText01);
        subjectEditText = (EditText)findViewById(R.id.subjectEditText01);
        contentEditText = (EditText)findViewById(R.id.contentEditText01);
        
        sendBtn = (Button)findViewById(R.id.sendButton01);
        // Ϊ��ť��ӵ���������
        sendBtn.setOnClickListener(listener);
    }
    
    
    // ���Ͱ�ť����������
    private OnClickListener listener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			// ���������Ϣ
			String to = toEditText.getText().toString();
			String subject = subjectEditText.getText().toString();
			String content = contentEditText.getText().toString();
			// ����Intent
			Intent emailIntent = new Intent(android.content.Intent.ACTION_SEND);
			// ������������
			emailIntent.setType("plain/text");
			// ���ö�����Ϣ
			emailIntent.putExtra(android.content.Intent.EXTRA_EMAIL, new String[]{to});
			emailIntent.putExtra(android.content.Intent.EXTRA_SUBJECT, subject);
			emailIntent.putExtra(android.content.Intent.EXTRA_TEXT, content);
			
			startActivity(Intent.createChooser(emailIntent, "�����ʼ�..."));
			
		}
	};
}