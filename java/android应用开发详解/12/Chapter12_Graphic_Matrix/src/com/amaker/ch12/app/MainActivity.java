package com.amaker.ch12.app;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;

public class MainActivity extends Activity {
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		MyView myView = new MyView(MainActivity.this);
		// ���õ�ǰ��ͼ����
		setContentView(myView);
	}
	// �Զ�����ͼ��
	class MyView extends View {
		// λͼʵ��
		private Bitmap bm;
		// Matrix ʵ��
		private Matrix matrix = new Matrix();
		// ��ת�Ƕ�
		private float angle = 0.0f;
		// λͼ��͸�
		private int w, h;
		// ���ű���
		private float scale = 1.0f;
		// �ж����Ż�����ת
		private boolean isScale = false;
		
		// ���췽��
		public MyView(Context context) {
			super(context);
			// ���λͼ
			bm = BitmapFactory.decodeResource(this.getResources(),
					R.drawable.girl);
			// ���λͼ��
			w = bm.getWidth();
			// ���λͼ��
			h = bm.getHeight();
			// ʹ��ǰ��ͼ��ý���
			this.setFocusable(true);
		}

		@Override
		protected void onDraw(Canvas canvas) {
			super.onDraw(canvas);
			// ����Matrix
			matrix.reset();
			if (!isScale) {
				// ��תMatrix
				matrix.setRotate(angle);
			} else {
				// ����Matrix
				matrix.setScale(scale, scale);
			}
			// ����ԭʼλͼ��Matrix��������ͼ
			Bitmap bm2 = Bitmap.createBitmap(bm, 0, 0, w, h, matrix, true);
			// ��������ͼ
			canvas.drawBitmap(bm2, matrix, null);
		}

		@Override
		public boolean onKeyDown(int keyCode, KeyEvent event) {
			// ������ת
			if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT) {
				isScale = false;
				angle++;
				postInvalidate();
			}
			// ������ת
			if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT) {
				isScale = false;
				angle--;
				postInvalidate();
			}
			// �Ŵ�
			if (keyCode == KeyEvent.KEYCODE_DPAD_UP) {
				isScale = true;
				if (scale < 2.0)
					scale += 0.1;
				postInvalidate();
			}
			// ��С
			if (keyCode == KeyEvent.KEYCODE_DPAD_DOWN) {
				isScale = true;
				if (scale > 0.5)
					scale -= 0.1;
				postInvalidate();
			}

			return super.onKeyDown(keyCode, event);
		}
	}
}