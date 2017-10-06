package com.amaker.game.app;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import com.amaker.game.Sprite;
/**
 * @author ����־
 * �ӵ���
 */
public class Bullet extends Sprite{
	// ֡��͸�
	private int frameWidth,frameHeight;
	// ��Ļ��͸�
	private int screenWidth,screenHeight;
	// �Ƿ���
	private boolean isAlive;
	public Bullet(Bitmap Bitmap, int frameWidth, int frameHeight) {
		super(Bitmap, frameWidth, frameHeight);
		this.frameHeight = frameHeight;
		this.frameWidth = frameWidth;
		defineReferencePixel(frameWidth/2, frameHeight/2);
	}
	// ������Ļ�ߴ�
	public void setScreenSize(int screenWidth,int screenHeight){
		this.screenHeight = screenHeight;
		this.screenWidth = screenWidth;
	}
	// �������
	public void setAlive(boolean isAlive,int x,int y){
		this.isAlive = isAlive;
		setPosition(x,y);
	}
	
	// �������
	public void setAlive(boolean alive){
		this.isAlive = alive;
	}
	// �����Ҵ��״̬
	public boolean getAlive(){
		return this.isAlive;
	}
	// �ƶ��ӵ�
	public void move(){
		if(isAlive){
			move(0,-3);
		}
		if(getY()<0){
			isAlive = false;
		}
	}
	// �����ӵ�
	public void draw(Canvas c){
		if(isAlive)
		paint(c);
	}
	
}
