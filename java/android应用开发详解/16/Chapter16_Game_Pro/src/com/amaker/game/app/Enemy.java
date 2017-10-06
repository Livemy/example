package com.amaker.game.app;

import java.util.Random;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import com.amaker.game.Sprite;
/**
 * @author ����־
 * ����ͼ����
 */
public class Enemy extends Sprite {
	// ������˿�͸�
	private int frameWidth,frameHeight;
	// ������Ļ��͸�
	private int screenWidth,screenHeight;
	// �жϵ����Ƿ���
	private boolean isAlive;
	// �����
	Random r;
	public Enemy(Bitmap Bitmap, int frameWidth, int frameHeight) {
		super(Bitmap, frameWidth, frameHeight);
		this.frameWidth = frameWidth;
		this.frameHeight = frameHeight;
		defineReferencePixel(frameWidth / 2, frameHeight / 2);
		r = new Random();
	}
	// ������Ļ�Ŀ�͸�
	public void setScreenSize(int screenWidth,int screenHeight){
		this.screenHeight = screenHeight;
		this.screenWidth = screenWidth;
	}
	
	// ���õ��˴��
	public void setAlive(){
		isAlive = true;
		int x = (r.nextInt() & 0x7fffffff)%(screenWidth-frameWidth);
		setPosition(x,0);
	}
	
	public void setAlive(boolean alive){
		this.isAlive = alive;
	}
	// �ƶ�
	public void move(){
		if(isAlive){
			move(0, 3);
			if(getY()>screenHeight){
				isAlive=false;
			}
		}
	}
	
	public boolean isAlive(){
		return isAlive;
	}
	// ���Ƶ���
	public void draw(Canvas canvas){
		if(isAlive){
			paint(canvas);
		}
	}

}
