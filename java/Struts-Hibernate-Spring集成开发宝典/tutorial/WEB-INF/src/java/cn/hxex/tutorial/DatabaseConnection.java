package cn.hxex.tutorial;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * ���ݿ⸨��������
 * 
 * @author galaxy
 */
public class DatabaseConnection {

	public static String url = "jdbc:oracle:thin:@192.168.10.121:1521:HiFinance";
	public static String user = "scott";
	public static String password = "tiger";
	public static String driver = "oracle.jdbc.driver.OracleDriver";
	
	/**
	 * ������ݿ������
	 * @return ���ݿ������
	 */
	public static Connection getConnection()
	{
		try {
			Class.forName( driver );
			return DriverManager.getConnection( url, user, password );
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		} catch (ClassNotFoundException ex) {
			ex.printStackTrace();
			return null;
		}
	}
	
	/**
	 * �ر������ݵ����ӣ����ͷ���Ӧ����Դ
	 */
	public static void releaseConnection( Connection conn, Statement st, ResultSet rs )
	{
		if( rs!=null )
		{
			try {
				rs.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		
		if( st!=null )
		{
			try {
				st.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		
		if( conn!=null )
		{
			try {
				conn.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}
}
