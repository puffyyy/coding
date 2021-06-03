
create database netprogram;
use netprogram;


create table friends
(
	fid bigint auto_increment
		primary key,
	friend_id bigint not null,
	user_id bigint not null
);

create table `group`
(
	gid bigint auto_increment
		primary key,
	g_name varchar(255) null,
	g_createtime datetime null,
	g_avatar_path varchar(255) null
);

create table message
(
	mid bigint auto_increment
		primary key,
	message_text varchar(255) null,
	m_time datetime null,
	m_send_uid bigint not null,
	m_group bigint null,
	m_get_uid bigint null,
	m_type int null,
	m_get tinyint(1) null
);

create table notice
(
	nid bigint auto_increment
		primary key,
	send_uid bigint null,
	get_uid bigint null,
	time datetime null,
	content varchar(255) null,
	type int null
);

create table user
(
	uid bigint auto_increment
		primary key,
	username varchar(255) not null,
	password varchar(255) not null,
	sex varchar(5) null,
	avatar_path varchar(255) not null,
	phone_num varchar(255) null,
	constraint user_username_uindex
		unique (username)
);

create table user_in_group
(
	u_gid bigint auto_increment
		primary key,
	userid bigint not null,
	group_id bigint not null,
	user_name_in_group varchar(255) null
);

