package com.amaker.ch08.app;

import com.amaker.ch08.app.R;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
/**
 * @author ����־
 * ���Թ㲥��֪ͨ
 */
public class MainActivity extends Activity {
	// ����Button
	private Button btn;
	// ����Broadcast Receiver action
	private static final String MY_ACTION = "com.amaker.ch08.app.MY_ACTION";
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // ���õ�ǰ������ͼ
        setContentView(R.layout.main);
        // ʵ����Button
        btn = (Button)findViewById(R.id.Button01);
        // ����¼�������
        btn.setOnClickListener(listener);
    }
    // �����¼�������
    private OnClickListener listener = new OnClickListener() {
		@Override
		public void onClick(View v) {
			// ʵ����Intent
			Intent intent = new Intent();
			// ����Intent action����
			intent.setAction(MY_ACTION);
			// ����㲥
			sendBroadcast(intent);
		}
	};
}