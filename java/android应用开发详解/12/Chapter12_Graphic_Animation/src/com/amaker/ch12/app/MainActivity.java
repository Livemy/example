package com.amaker.ch12.app;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.RotateAnimation;
import android.view.animation.ScaleAnimation;
import android.view.animation.TranslateAnimation;
import android.widget.Button;
import android.widget.ImageView;

public class MainActivity extends Activity {
	// ����ʹ�õ���Button��ͼ���
	private Button b1, b2, b3, b4;
	// ����ʹ�õ���ImageView���
	private ImageView girlImage;
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		// ���õ�ǰ��ͼ����
		setContentView(R.layout.main);
		// ʵ������ͼ���
		girlImage = (ImageView) findViewById(R.id.ImageView01);
		b1 = (Button) findViewById(R.id.Button01);
		b2 = (Button) findViewById(R.id.Button02);
		b3 = (Button) findViewById(R.id.Button03);
		b4 = (Button) findViewById(R.id.Button04);
		
		// Ϊ��ť��Ӽ����¼�
		b1.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				// ����Sacle(�ߴ�)�仯����
				Animation scaleAnimation = new ScaleAnimation(0f, 1f, 0f, 1f,
						Animation.RELATIVE_TO_SELF, 0.5f,
						Animation.RELATIVE_TO_SELF, 0.5f);
				// ���ö�������ʱ��
				scaleAnimation.setDuration(3000);
				// ��ʼ����
				girlImage.startAnimation(scaleAnimation);
			}
		});
		// Ϊ��ť��Ӽ����¼�
		b2.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				// ����Alpha(����)����
				Animation alphaAnimation = new AlphaAnimation(0.1f, 1.0f);
				// ���ö�������ʱ��
				alphaAnimation.setDuration(3000);
				// ��ʼ����
				girlImage.startAnimation(alphaAnimation);
			}
		});
		// Ϊ��ť��Ӽ����¼�
		b3.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				// ����translate(λ�ñ仯)����
				Animation translateAnimation = new TranslateAnimation(10, 100,
						10, 100);
				// ���ö�������ʱ��
				translateAnimation.setDuration(3000);
				// ��ʼ����
				girlImage.startAnimation(translateAnimation);
			}
		});
		// Ϊ��ť��Ӽ����¼�
		b4.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				// ����rotate(��ת)����
				Animation rotateAnimation = new RotateAnimation(0f, +360f,
						Animation.RELATIVE_TO_SELF, 0.5f,
						Animation.RELATIVE_TO_SELF, 0.5f);
				// ���ö�������ʱ��
				rotateAnimation.setDuration(3000);
				// ��ʼ����
				girlImage.startAnimation(rotateAnimation);
			}
		});
		

	}
}