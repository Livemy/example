/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: E:\\android\\workspace\\workspace\\Chapter08_Service_02\\src\\com\\amaker\\ch08\\app\\IPerson.aidl
 */
package com.amaker.ch07.app;

import java.lang.String;
import android.os.RemoteException;
import android.os.IBinder;
import android.os.IInterface;
import android.os.Binder;
import android.os.Parcel;

// AIDL �ļ����ɵ�Java�ӿ�ʵ����
public interface IPerson extends android.os.IInterface {
	/** Local-side IPC implementation stub class. */
	
	// ����࣬���ø����asInterface����Ŀ��ӿ�
	public static abstract class Stub extends android.os.Binder implements
			com.amaker.ch07.app.IPerson {
		private static final java.lang.String DESCRIPTOR = "com.amaker.ch08.app.IPerson";

		/** Construct the stub at attach it to the interface. */
		public Stub() {
			this.attachInterface(this, DESCRIPTOR);
		}

		/**
		 * Cast an IBinder object into an IPerson interface, generating a proxy
		 * if needed.
		 */
		public static com.amaker.ch07.app.IPerson asInterface(
				android.os.IBinder obj) {
			if ((obj == null)) {
				return null;
			}
			android.os.IInterface iin = (android.os.IInterface) obj
					.queryLocalInterface(DESCRIPTOR);
			if (((iin != null) && (iin instanceof com.amaker.ch07.app.IPerson))) {
				return ((com.amaker.ch07.app.IPerson) iin);
			}
			// ���ô�����ʵ��
			return new com.amaker.ch07.app.IPerson.Stub.Proxy(obj);
		}

		public android.os.IBinder asBinder() {
			return this;
		}

		public boolean onTransact(int code, android.os.Parcel data,
				android.os.Parcel reply, int flags)
				throws android.os.RemoteException {
			switch (code) {
			case INTERFACE_TRANSACTION: {
				reply.writeString(DESCRIPTOR);
				return true;
			}
			case TRANSACTION_setAge: {
				data.enforceInterface(DESCRIPTOR);
				int _arg0;
				_arg0 = data.readInt();
				this.setAge(_arg0);
				reply.writeNoException();
				return true;
			}
			case TRANSACTION_setName: {
				data.enforceInterface(DESCRIPTOR);
				java.lang.String _arg0;
				_arg0 = data.readString();
				this.setName(_arg0);
				reply.writeNoException();
				return true;
			}
			case TRANSACTION_display: {
				data.enforceInterface(DESCRIPTOR);
				java.lang.String _result = this.display();
				reply.writeNoException();
				reply.writeString(_result);
				return true;
			}
			}
			return super.onTransact(code, data, reply, flags);
		}

		private static class Proxy implements com.amaker.ch07.app.IPerson {
			private android.os.IBinder mRemote;

			Proxy(android.os.IBinder remote) {
				mRemote = remote;
			}

			public android.os.IBinder asBinder() {
				return mRemote;
			}

			public java.lang.String getInterfaceDescriptor() {
				return DESCRIPTOR;
			}

			public void setAge(int age) throws android.os.RemoteException {
				android.os.Parcel _data = android.os.Parcel.obtain();
				android.os.Parcel _reply = android.os.Parcel.obtain();
				try {
					_data.writeInterfaceToken(DESCRIPTOR);
					_data.writeInt(age);
					mRemote.transact(Stub.TRANSACTION_setAge, _data, _reply, 0);
					_reply.readException();
				} finally {
					_reply.recycle();
					_data.recycle();
				}
			}

			public void setName(java.lang.String name)
					throws android.os.RemoteException {
				android.os.Parcel _data = android.os.Parcel.obtain();
				android.os.Parcel _reply = android.os.Parcel.obtain();
				try {
					_data.writeInterfaceToken(DESCRIPTOR);
					_data.writeString(name);
					mRemote
							.transact(Stub.TRANSACTION_setName, _data, _reply,
									0);
					_reply.readException();
				} finally {
					_reply.recycle();
					_data.recycle();
				}
			}

			public java.lang.String display() throws android.os.RemoteException {
				android.os.Parcel _data = android.os.Parcel.obtain();
				android.os.Parcel _reply = android.os.Parcel.obtain();
				java.lang.String _result;
				try {
					_data.writeInterfaceToken(DESCRIPTOR);
					mRemote
							.transact(Stub.TRANSACTION_display, _data, _reply,
									0);
					_reply.readException();
					_result = _reply.readString();
				} finally {
					_reply.recycle();
					_data.recycle();
				}
				return _result;
			}
		}

		static final int TRANSACTION_setAge = (IBinder.FIRST_CALL_TRANSACTION + 0);
		static final int TRANSACTION_setName = (IBinder.FIRST_CALL_TRANSACTION + 1);
		static final int TRANSACTION_display = (IBinder.FIRST_CALL_TRANSACTION + 2);
	}

	public void setAge(int age) throws android.os.RemoteException;

	public void setName(java.lang.String name)
			throws android.os.RemoteException;

	public java.lang.String display() throws android.os.RemoteException;
}
