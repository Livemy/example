package com.amaker.ch11.app;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import android.app.Activity;
import android.graphics.PixelFormat;
import android.hardware.Camera;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.view.KeyEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class MainActivity extends Activity {
	// �������ս������SurfaceView
	private SurfaceView surfaceView;
	// ��������������SurfaceHolder
	private SurfaceHolder surfaceHolder;
	// ���������
	private Camera camera;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        // ʵ�������ս������
        surfaceView = (SurfaceView)findViewById(R.id.preview);
        // ��SurfaceView�л��SurfaceHolder
        surfaceHolder = surfaceView.getHolder();
        // ΪSurfaceHolder ��ӻص�
        surfaceHolder.addCallback(surfaceCallback);
        surfaceHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
    }
    
    // ��Ӧ�����¼�
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
    	if(keyCode==KeyEvent.KEYCODE_CAMERA||keyCode==KeyEvent.KEYCODE_SEARCH){
    		takePic();
    		return true;
    	}
    	return super.onKeyDown(keyCode, event);
    }
    // ���շ���
    private void takePic(){
    	// ֹͣԤ��
    	camera.stopPreview();
    	// ����
    	camera.takePicture(null,null, pictureCallback);
    }
    // ��Ƭ�ص�
    Camera.PictureCallback pictureCallback = new Camera.PictureCallback() {
		@Override
		public void onPictureTaken(byte[] data, Camera camera) {
			new SavePictureTask().execute(data);
			camera.startPreview();
		}
	};
	
	// ������Ƭ������
	class SavePictureTask extends AsyncTask<byte[],String,String>{
		@Override
		protected String doInBackground(byte[]... params) {
			// �����ļ�
			File picture = new File(Environment.getExternalStorageDirectory(),"picture.jpg");
			// ����ļ�����ɾ����
			if(picture.exists())picture.delete();
			try {
				// ����ļ������
				FileOutputStream  fos = new FileOutputStream(picture.getPath());
				// д�����ļ�
				fos.write(params[0]);
				// �ر��ļ���
				fos.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
			return null;
		}
	}
    // SurfaceHodler �ص��������������ر�����Լ���Ƭ�ߴ�ĸı�
    SurfaceHolder.Callback surfaceCallback = new SurfaceHolder.Callback() {
		@Override
		public void surfaceCreated(SurfaceHolder holder) {
			// �����
			camera = Camera.open();
			try {
				// ����Ԥ��
				camera.setPreviewDisplay(holder);
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		
		@Override
		public void surfaceChanged(SurfaceHolder holder, int format, int width,
				int height) {
			// ����������
			Camera.Parameters parameters = camera.getParameters();
			// ������Ƭ��С
			parameters.setPreviewSize(width, height);
			// ������Ƭ��ʽ
			parameters.setPictureFormat(PixelFormat.JPEG);
			// �����������
			camera.setParameters(parameters);
			// ��ʼԤ��
			camera.startPreview();
		}
		
		@Override
		public void surfaceDestroyed(SurfaceHolder holder) {
			// ֹͣԤ��
			camera.stopPreview();
			// �ͷ������Դ
			camera.release();
			camera = null;
		}
	};
}