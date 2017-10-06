package com.amaker.game.app;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.view.KeyEvent;
import android.view.View;

/**
 * 
 * @author ����־
 * ��Ϸ��ͼ��
 */
public class GameView extends View implements Runnable{
	// ���Bitmap
	private Bitmap playerBitmap;
	// �ӵ�Bitmap
	private Bitmap bulletBitmap;
	// ����Bitmap
	private Bitmap enemyBitmap;
	// ���
	private Player player;
	// �ӵ�
	private Bullet[] bullets = new Bullet[3];
	// ����
	private Enemy enemy;
	// Context
	private Context context;
	// ��Ļ����
	public int screenWidth,screenHeight;
	// ��ըͼƬ
	public Bitmap exploreBitmap;
	// �ж��Ƿ�ը
	private boolean isExplore;
	
	// ���췽��
	public GameView(Context context,int screenWidth,int screenHeight) {
		super(context);
		this.context = context;
		this.screenWidth = screenWidth;
		this.screenHeight = screenHeight;
		setFocusable(true);
	}
	// ���Ʒ���
	@Override
	public void draw(Canvas canvas) {
		// �����
		player.paint(canvas);
		// ���ӵ�
		for (int i = 0; i <bullets.length; i++) {
			bullets[i].draw(canvas);
		}
		// ���Ƶ���
		enemy.draw(canvas);
		
		if(isExplore){
			canvas.drawBitmap(exploreBitmap, enemy.getY(), enemy.getX(), null);
			isExplore = false;
			enemy.setAlive(false);
		}
		
		super.draw(canvas);
	}
	
	// �����¼�
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		switch (keyCode) {
		case KeyEvent.KEYCODE_DPAD_UP:
			player.move(Player.UP);
			break;
		case KeyEvent.KEYCODE_DPAD_DOWN:
			player.move(Player.DOWN);
			break;
		case KeyEvent.KEYCODE_DPAD_LEFT:
			player.move(Player.LEFT);
			break;
		case KeyEvent.KEYCODE_DPAD_RIGHT:
			player.move(Player.RIGHT);
			break;
		case KeyEvent.KEYCODE_DPAD_CENTER:
			for (int i = 0; i < bullets.length; i++) {
				if(bullets[i].getAlive()==false){
					bullets[i].setAlive(true, 
							player.getRefPixelX()-bullets[i].getWidth()/2,
							player.getRefPixelY()-player.getHeight());
					break;
				}
			}
			break;
		}
		return super.onKeyDown(keyCode, event);
	}

	// �̷߳���ʵ��
	public void run() {
		load();
		init();
		while(true){
			if(!enemy.isAlive()){
				enemy.setAlive();
			}
			tick();
			postInvalidate();
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
			}
		}
	}
	
	// ������Դ
	public void load(){
		// ������ͼƬ
		playerBitmap = GameHelper.getBitmap(context,R.drawable.player);
		// ʵ�������
		player = new Player(playerBitmap,playerBitmap.getWidth(),playerBitmap.getHeight());
		// ������Ļ��͸�
		player.setScreenSize(screenWidth, screenHeight);
		// ����ӵ�ͼƬ
		bulletBitmap = GameHelper.getBitmap(context,R.drawable.bullet);
		
		exploreBitmap = GameHelper.getBitmap(context,R.drawable.explored);
		for(int i=0;i<bullets.length;i++){
			// ʵ�����ӵ�
			bullets[i] = new Bullet(bulletBitmap,bulletBitmap.getWidth(),bulletBitmap.getHeight());
			// ������Ļ��͸�
			bullets[i].setScreenSize(screenWidth, screenHeight);
		}
		// ��õ���ͼƬ
		enemyBitmap = GameHelper.getBitmap(context, R.drawable.e6);
		// ʵ��������
		enemy = new Enemy(enemyBitmap,enemyBitmap.getWidth(),enemyBitmap.getHeight());
		// ������Ļ��͸�
		enemy.setScreenSize(screenWidth, screenHeight);
	}
	
	// ��ʼ��
	public void init(){
		// ��ʼ�����
		player.init();
		for (int i = 0; i < bullets.length; i++) {
			bullets[i].setAlive(false);
		}
	}
	
	// �����߳�
	public void start(){
		new Thread(this).start();
	}
	
	public void tick(){
		for (int i = 0; i < bullets.length; i++) {
			bullets[i].move();
			if(bullets[i].collidesWith(enemy, false)){
				isExplore = true;
			}
		}
		enemy.move();
		
	}
}
