/*
 * 
 * Created on: Apr 14, 2019
 * Author: Bingyao Li
 * Description:mydb.cpp
 * Copyright (C) 2017 NAOC-TJUCS
 *
 */


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <list>
#include "mysql.h"
#include "struct.h"

MYSQL *connection = NULL;
MYSQL mysql;

void init_db()
{
	mysql_init(&mysql);
}

int conn_db(const char *hostname, const char *username, const char *password, const char *dbname)
{
	if(connection)
		mysql_close(connection);

	connection = mysql_real_connect(&mysql, hostname, username, password, dbname, 0, 0, 0);

	if(connection == NULL)
	{
		printf("%s\n", mysql_error(&mysql));
		return -1;
	}

	printf("success connect to mysql\n");
	return 0;
}


void disconn_db()
{
	if (connection)
	{
		mysql_close(connection);
		connection = NULL;
	}
}

string getValue(const char *SQL)
{
	int state = mysql_query(connection, SQL);				//执行SQL语句
	if(state != 0)
	{
		printf("%s\n", mysql_error(connection));
		return "";
	}

	MYSQL_RES *result = mysql_store_result(connection);

	if(result == (MYSQL_RES *) NULL)
	{
		printf("%s\n", mysql_error(connection));
		return "";
	}
	else
	{
		MYSQL_FIELD *sqlField;
		int iFieldCount = 0;

		//循环遍历所有字段
		while (1)
		{
			sqlField = mysql_fetch_field(result);
			if(sqlField == NULL)
				break;
			iFieldCount++;
		}
		MYSQL_ROW sqlRow;
		//循环到每一行
		while (1)
		{
			sqlRow = mysql_fetch_row(result);
			if(sqlRow == NULL)
				break;
			//循环得到每一行中的每个字段
			for(int i = 0; i < iFieldCount; i++)
			{
				if(sqlRow[i] == NULL)
					return "";
				else
					return sqlRow[i];
			}
		}
		mysql_free_result(result);
	}

	return "";
}

int getCount(const char *SQL)
{
	int state = mysql_query(connection, SQL);				//执行SQL语句
	if(state != 0)
	{
		printf("%s\n", mysql_error(connection));
		return -1;
	}

	MYSQL_RES *result = mysql_store_result(connection);	//得到查询结果

	if(result == (MYSQL_RES *) NULL)
	{
		printf("%s\n", mysql_error(connection));
		return -1;
	}
	else
	{
		MYSQL_FIELD *sqlField;
		int iFieldCount = 0;

		//循环遍历所有字段
		while (1)
		{
			sqlField = mysql_fetch_field(result);
			if(sqlField == NULL)
				break;
			iFieldCount++;
		}

		MYSQL_ROW sqlRow;
		//循环到每一行
		while (1)
		{
			sqlRow = mysql_fetch_row(result);
			if(sqlRow == NULL)
				break;

			//循环得到每一行中的每个字段
			for(int i = 0; i < iFieldCount; i++)
			{
				if(sqlRow[i] == NULL)
					return -1;
				else
					return atoi(sqlRow[i]);
			}
		}
		mysql_free_result(result);
	}

	return -1;
}

int updateInfo(const char *SQL)
{
	int state = mysql_query(connection, SQL);					//执行SQL语句
	if (state != 0)
	{
		printf("%s\n", mysql_error(connection));
		return -1;
	}
	return 0;
}

