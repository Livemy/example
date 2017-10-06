package com.amaker.ch10.app;

import android.app.Activity;
import android.content.ContentUris;
import android.content.ContentValues;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;

import com.amaker.ch10.app.Employees.Employee;

public class MainActivity extends Activity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        // ���
        insert();
        // ��ѯ
        query();
        // ����
        update();
        // ��ѯ
        query();
        // ɾ��
        del();
        // ��ѯ
        query();
    }
    // ɾ������
    private void del(){
    	// ɾ��IDΪ1�ļ�¼
    	Uri uri = ContentUris.withAppendedId(Employee.CONTENT_URI, 1);
    	// ���ContentResolver����ɾ��
    	getContentResolver().delete(uri, null, null);
    }
    // ����
    private void update(){
    	// ����IDΪ1�ļ�¼
    	Uri uri = ContentUris.withAppendedId(Employee.CONTENT_URI, 1);
    	ContentValues values = new ContentValues();
    	// ���Ա����Ϣ
    	values.put(Employee.NAME, "hz.guo");
    	values.put(Employee.GENDER, "male");
    	values.put(Employee.AGE,31);
    	// ���ContentResolver��������
		getContentResolver().update(uri, values, null, null);
    }
    // ��ѯ
    private void query(){
    	// ��ѯ������
    	   String[] PROJECTION = new String[] { 
    			   Employee._ID, 		// 0
    			   Employee.NAME, 		// 1
    			   Employee.GENDER, 	// 2
    			   Employee.AGE 		// 3
    	};
    	// ��ѯ���б���¼��Ϣ
		Cursor c = managedQuery(Employee.CONTENT_URI, PROJECTION, null,
				null, Employee.DEFAULT_SORT_ORDER);
		// �ж��α��Ƿ�Ϊ��
		if (c.moveToFirst()) {
			// �����α�
			for (int i = 0; i < c.getCount(); i++) {
				c.moveToPosition(i);
				// �������
				String name = c.getString(1);
				String gender = c.getString(2);
				int age = c.getInt(3);
				// �����־
				Log.i("emp", name+":"+gender+":"+age);
			}
		}
    }
    // ����
    private void insert(){
    	// ����Uri
    	Uri uri = Employee.CONTENT_URI;
    	// ʵ����ContentValues
    	ContentValues values = new ContentValues();
    	// ���Ա����Ϣ
    	values.put(Employee.NAME, "amaker");
    	values.put(Employee.GENDER, "male");
    	values.put(Employee.AGE,30);
    	// ���ContentResolver��������
    	getContentResolver().insert(uri, values);
    }
}