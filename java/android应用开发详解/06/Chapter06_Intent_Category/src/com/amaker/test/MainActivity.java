package com.amaker.test;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

/**
 * @author ����־
 * ����Intent �� Category����
 */
public class MainActivity extends Activity {
	// ���� Button
	private Button b1;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // ���õ�ǰ����
        setContentView(R.layout.main);
        // ʵ���� Button
        b1 = (Button)findViewById(R.id.Button01);
        // ΪButton ��Ӽ�����
        b1.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				// ʵ����Intent
		        Intent i = new Intent();
		        // ���Action����
		        i.setAction(Intent.ACTION_MAIN);
		        // ���Category����
		        i.addCategory(Intent.CATEGORY_HOME);
		        // ����Activity
		        startActivity(i);
			}
		});
    }
}