package com.amaker.test.app;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BitmapShader;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.ComposeShader;
import android.graphics.LinearGradient;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.RadialGradient;
import android.graphics.Shader;
import android.graphics.SweepGradient;
import android.graphics.Shader.TileMode;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;

public class MainActivity extends Activity {
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		MyView v = new MyView(this);
		setContentView(v);
	}
	// �Զ�����ͼ��
	class MyView extends View{
		// ����Bitmap����
		private Bitmap bm ;
		// ����λͼ��Ⱦ����
		private Shader bitmapShader;
		// ����������Ⱦ����
		private Shader linearGradient;
		// ����������Ⱦ����
		private Shader radialGradient;
		// �����ݶ���Ⱦ����
		private Shader sweepGradient;
		// ���������Ⱦ����
		private Shader composeShader;
		// ��������
		private Paint paint;
		// ������ɫ����
		private int[] colors;
		private boolean isFirst = true;
		
		public MyView(Context context) {
			super(context);
			// ���Bitmapʵ��
			bm = BitmapFactory.decodeResource(getResources(), R.drawable.girl);
			// ʵ��������
			paint = new Paint();
			colors = new int[]{Color.RED,Color.GREEN,Color.BLUE};
			// ʵ����λͼ��Ⱦ����,x���귽���ظ�ͼ�Σ�y���귽����ͼ��
			bitmapShader = new BitmapShader(bm, TileMode.REPEAT, TileMode.MIRROR);
			// ʵ����������Ⱦ
			linearGradient = new LinearGradient(0, 0, 100, 100,
					colors, null,  TileMode.REPEAT);
			// ʵ����������Ⱦ
			radialGradient = new RadialGradient(100, 100, 80, 
					colors, null,  TileMode.REPEAT);
			// ʵ�����ݶ���Ⱦ
			sweepGradient =  new SweepGradient(200, 200, colors, null);
			
			// ʵ���������Ⱦ
			composeShader = new ComposeShader(linearGradient, radialGradient,PorterDuff.Mode.DARKEN);
			// ʹ���ý���
			setFocusable(true);
		}
		@Override
		protected void onDraw(Canvas canvas) {
			super.onDraw(canvas);
			if(isFirst){
				//д�֣�������ʾ�û�����
				String content = "����/��/��/��/�м�����ԣ�";
				paint.setColor(Color.BLUE);
				canvas.drawText(content, 0, content.length()-1, 20, 20, paint);
			}else{
				// ȫ��������
				canvas.drawRect(0, 0, getWidth(), getHeight(), paint);
			}
		}
		
		@Override
		public boolean onKeyDown(int keyCode, KeyEvent event) {
			isFirst = false;
			if(keyCode==KeyEvent.KEYCODE_DPAD_UP){
				// ��������Ⱦ����Ϊλͼ��Ⱦ
				paint.setShader(bitmapShader);
			}
			if(keyCode==KeyEvent.KEYCODE_DPAD_DOWN){
				// ��������Ⱦ����Ϊ������Ⱦ
				paint.setShader(linearGradient);
			}
			if(keyCode==KeyEvent.KEYCODE_DPAD_LEFT){
				// ��������Ⱦ����Ϊ������Ⱦ
				paint.setShader(radialGradient);
			}
			if(keyCode==KeyEvent.KEYCODE_DPAD_RIGHT){
				// ��������Ⱦ����Ϊ�ݶ���Ⱦ
				paint.setShader(sweepGradient);
			}
			if(keyCode==KeyEvent.KEYCODE_DPAD_CENTER){
				// ��������Ⱦ����Ϊ�����Ⱦ
				paint.setShader(composeShader);
			}
			// �ػ����
			postInvalidate();
			return super.onKeyDown(keyCode, event);
		}
	}
}