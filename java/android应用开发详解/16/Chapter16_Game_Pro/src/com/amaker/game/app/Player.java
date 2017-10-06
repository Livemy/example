package com.amaker.game.app;

import android.graphics.Bitmap;
import com.amaker.game.Sprite;

/**
 * 
 * @author ����־
 * ���ʵ����
 */
public class Player extends Sprite{
	// ������Ļ��͸�
	private int screenWidth,screenHeight;
	// ������ҿ�͸�
	private int frameWidth,frameHeight;
	// ��������Ƿ����
	private boolean isAlive = false;
	// �����ƶ����������ϡ��¡�����
	public static final int UP = 1;
	public static final int DOWN = 2;
	public static final int LEFT = 3;
	public static final int RIGHT = 4;
	// �����ƶ��ٶ�
	public static int SPEED = 4;
	
	// ���췽��
	public Player(Bitmap Bitmap,int frameWidth,int frameHeight) {
		super(Bitmap);
		this.frameWidth = frameWidth;
		this.frameHeight = frameHeight;
		defineReferencePixel(frameWidth/2, frameHeight/2);
	}
	// ������Ļ�ߴ�
	public void setScreenSize(int screenWidth,int screenHeight){
		this.screenHeight = screenHeight;
		this.screenWidth = screenWidth;
	}
	// �������
	public void setAlive(boolean isAlive){
		this.isAlive = isAlive;
		setPosition(screenWidth/2, screenHeight/2);
	}
	// �����Ҵ��״̬
	public boolean getAlive(){
		return this.isAlive;
	}
	// �ƶ����
	public void move(int direction){
		// �����ƶ�
		if(direction==UP){
			move(0, -SPEED);
			if(getY()<0){
				setPosition(getX(), 0);
			}
		}
		// �����ƶ�
		if(direction==DOWN){
			move(0, SPEED);
			if(getY()>screenHeight-frameHeight){
				setPosition(getX(), screenHeight-frameHeight);
			}
		}
		
		// �����ƶ�
		if(direction==LEFT){
			move(-SPEED, 0);
			if(getX()<0){
				setPosition(0, getY());
			}
		}
		// �����ƶ�
		if(direction==RIGHT){
			move(SPEED, 0);
			if(getX()>screenWidth-frameWidth){
				setPosition(screenWidth-frameWidth,getY());
			}
		}
	}
	// ��ʼ�����
	public void init(){
		SPEED = 4;
		setAlive(true);
	}
}
