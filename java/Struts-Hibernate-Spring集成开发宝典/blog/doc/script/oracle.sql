-- ������ռ�
CREATE TABLESPACE blog
DATAFILE '/opt/oracle/oradata/test/blog01.dbf' size 200M
EXTENT MANAGEMENT local;

-- �����û�
CREATE USER blog IDENTIFIED BY blog
DEFAULT TABLESPACE blog;

-- ����Ȩ��
GRANT connect, resource TO blog;

-- ʹ��blog�û��������ݿ�
CONNECT blog/blog;

-- ����������Ϣ��
CREATE TABLE userinfo (
	id		VARCHAR2(32) NOT NULL,
	name		VARCHAR2(32) NOT NULL,
	password	VARCHAR2(32) NOT NULL,
	CONSTRAINT userinfo_pk PRIMARY KEY (id),
	CONSTRAINT userinfo_unique_name UNIQUE ( name )
);

-- ����������־��
CREATE TABLE message (
	id			VARCHAR2(32) NOT NULL,
	title			VARCHAR2(32) NOT NULL,
	content		VARCHAR2(2000),
	user_id		VARCHAR2(32),
	CONSTRAINT message_pk PRIMARY KEY (id),
	CONSTRAINT message_user FOREIGN KEY (user_id) REFERENCES userinfo(id) 
);

-- ��������������Ϣ��
CREATE TABLE replymessage (
	id			VARCHAR2(32) NOT NULL,
	username	VARCHAR2(64) NOT NULL,
	title		VARCHAR2(32) NOT NULL,
	content		VARCHAR2(2000),
	message_id	VARCHAR2(32) NOT NULL,
	CONSTRAINT replymessage_pk PRIMARY KEY (id),
	CONSTRAINT replymessage_message FOREIGN KEY (message_id) REFERENCES message(id)
);