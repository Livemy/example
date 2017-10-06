package com.amaker.ch12.app;

import android.app.Activity;
import android.graphics.drawable.AnimationDrawable;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;

public class MainActivity extends Activity {
	// ����ʹ�õ���Button��ͼ���
	private Button b1, b2;
	// ����ʹ�õ���ImageView���
	private ImageView myImage;
	// ����AnimationDrawable
	private AnimationDrawable danceAnimation;
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		// ���õ�ǰ��ͼ����
		setContentView(R.layout.main);
		// ʵ������ͼ���
		myImage = (ImageView) findViewById(R.id.ImageView01);
		b1 = (Button) findViewById(R.id.Button01);
		b2 = (Button) findViewById(R.id.Button02);
		
		// ��ñ���ɫ����ת��ΪAnimationDrawable����
		danceAnimation = (AnimationDrawable) myImage.getBackground();
		
		// Ϊ��ť��Ӽ����¼�
		b1.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				// ��ʼ����
				danceAnimation.start();
			}
		});
		// Ϊ��ť��Ӽ����¼�
		b2.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				// ֹͣ����
				danceAnimation.stop();
			}
		});

	}
}