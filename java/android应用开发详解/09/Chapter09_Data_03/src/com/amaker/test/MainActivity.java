package com.amaker.test;

import android.app.Activity;
import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;

public class MainActivity extends Activity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        SQLiteDatabase db = createDatabase();
        //createTable(db);
        //insert(db);
        //insert2(db);
        //update(db);
       // update2(db);
       // delete(db);
        delete2(db);
        query(db);
        db.close();
        
    }
    // �������ݿ⣬ע������Ҫָ��ȫ·��
    private SQLiteDatabase createDatabase(){
    	return SQLiteDatabase.openOrCreateDatabase("/data/data/com.amaker.test/databases/temp2.db", null);
    }
    // ������
    private void createTable(SQLiteDatabase db){
    	String sql = " create table UserTbl(_id integer primary key autoincrement,username text,password text)";
    	db.execSQL(sql);
    }
    // ��������
    private void insert(SQLiteDatabase db){
    	String sql = " insert into UserTbl(username,password) values('amaker','123') ";
    	db.execSQL(sql);
    }
    // ����2 
   private void insert2(SQLiteDatabase db){
	   ContentValues cv =new ContentValues();
	   cv.put("username","ghz");
	   cv.put("password", "456");
	   db.insert("UserTbl", null, cv);
   }
    // ��ѯ
    private void query(SQLiteDatabase db){
    	Cursor c = db.query("UserTbl", null, null, null, null, null, null);
    	if(c.moveToFirst()){
    		for (int i = 0; i < c.getCount(); i++) {
				c.move(i);
				int id = c.getInt(0);
				String username = c.getString(1);
				String password = c.getString(2);
				System.out.println(id+":"+username+":"+password);
			}
    	}
    }
    // �޸�
    private void update(SQLiteDatabase db){
    	String sql = " update UserTbl set password=888 where _id=1 ";
    	db.execSQL(sql);
    }
    // �޸�2
    private void update2(SQLiteDatabase db){
    	ContentValues values = new ContentValues();
    	values.put("password", "999");
    	String whereClause = "_id=?";
    	String[] whereArgs = {String.valueOf(1)};
    	db.update("UserTbl", values, whereClause, whereArgs);
    }
    
    // ɾ��
    private void delete(SQLiteDatabase db){
    	String sql = " delete from UserTbl where _id=2 ";
    	db.execSQL(sql);
    }
    // ɾ��2
    private void delete2(SQLiteDatabase db){
    	String whereClause = "_id=?";
    	String[] whereArgs = {String.valueOf(1)};
    	db.delete("UserTbl", whereClause, whereArgs);
    }
    
    
}