#include "process.h"
#include <sstream>  
#include <stdlib.h>
#include <iostream>

const char* user = "root";         //username
const char* pswd = "604351";         //password
const char* host = "localhost";    //or"127.0.0.1"
const char* table = "test";        //database
unsigned int port = 3306;           //server port      
bool my_true = true;
MYSQL myCont;
MYSQL_ROW sql_row;
MYSQL_FIELD *fd;
char field[32][32];
MYSQL_RES *result;//这个结构代表返回行的一个查询结果集
char query[150]; //查询语句
MYSQL_ROW column; //一个行数据的类型安全(type-safe)的表示，表示数据行的列

string project;
int id;
string author;
string date;
string logg;
int bug;
string xx;

string IntToString1(int & i)
{
	string s;
	stringstream ss(s);
	ss << i;
	return ss.str();
}

string IntToString2(int a[])//int 数组转string第二部分：直接调用这个
{

	int arrayLength = sizeof(a) / sizeof(a[0]);

	string strs;

	for (int i = 0; i<arrayLength; i++)
	{
		int &temp = a[i];
		strs += IntToString1(temp);
	}
	return(strs);
}

//连接数据库
bool ConnectDatabase(MYSQL & myCont){
	mysql_init(& myCont);
	//int i = CR_CONN_HOST_ERROR;
	if (0 == mysql_options(& myCont, MYSQL_SET_CHARSET_NAME, "gbk"))//设置字符集
	{
		cout << "设置字符集成功" << endl;
	}
	if (0 == mysql_options(& myCont, MYSQL_OPT_RECONNECT, &my_true))
	{
		cout << "设置可重连成功" << endl;
    }

	if (!mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, CLIENT_MULTI_STATEMENTS))//连接数据库
	{
		cout << "不能连接到数据库" << endl;
		fprintf(stderr, "Failed to connect to database: Error: %s", mysql_error(& myCont));
		return false;
	}
	cout << "连接数据库成功" << endl;
	return true;
}

//释放资源
void FreeConnect()
{
	//释放资源
	if (result != NULL) mysql_free_result(result);//释放结果资源*/
	mysql_close(& myCont);
}



/***************************数据库操作***********************************/
//其实所有的数据库操作都是先写个sql语句，然后用mysql_query(&mysql,query)来完成，包括创建数据库或表，增删改查
//插入数据
bool InsertData(MYSQL & myCont, const string a, const int b, const string c, const string d, const string e, const string h, const int g = 0)
{
	xx = "insert into test_1 values('"+a+"','"+to_string(b)+"','','"+d+"','','"+to_string(g) +"','" +h +"','0','0','0"+"');";
	
	strncpy_s(query, xx.c_str(), xx.length());
	
	//sprintf_s(query, "insert into test_1 values(" + a + "," + to_string(b) +  "," + c +  "," + d +  "," + e + ");");  //可以想办法实现手动在控制台手动输入指令
	cout << query << endl;
	if (mysql_query(&myCont, query))        //执行SQL语句
	{
		printf("Query failed (%s)\n", mysql_error(&myCont));
	}
	else
	{
		printf("Insert success\n");
		return false;
	}
	//释放SQL语句
	do
	{
		auto result = mysql_store_result(&myCont);
		mysql_free_result(result);
	} while (!mysql_next_result(&myCont));
	return true;
}


//查询数据
bool QueryDatabase1()
{
    sprintf_s(query, "select * from test_1"); //执行查询语句，这里是查询所有，test_1是表名，不用加引号，用strcpy也可以
	mysql_query(& myCont, "set names gbk"); //设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
//返回0 查询成功，返回1查询失败
	if (mysql_query(&myCont, query))        //执行SQL语句
{
	printf("Query failed (%s)\n", mysql_error(& myCont));
    return false;
}
else
{
printf("query success\n");
}
//获取结果集
	if (!(result = mysql_store_result(&myCont)))    //获得sql语句结束后返回的结果集
{
		printf("Couldn't get result from %s\n", mysql_error(& myCont));
        return false;
}

    //打印数据行数
	printf("number of dataline returned: %d\n", mysql_affected_rows(&myCont)); //mysql_affected_rows返回被最新的UPDATE, DELETE或INSERT查询影响的行数。
	//释放SQL语句
	

//获取字段的信息
char *str_field[32];  //定义一个字符串数组存储字段信息
for (int i = 0; i<6; i++)   //在已知字段数量的情况下获取字段名
{
	str_field[i] = mysql_fetch_field(result)->name; //mysql_fetch_fields() 返回一个所有字段结构的数组。对于结果集，返回所有MYSQL_FIELD结构的数组。每个结构提供了结果集中1列的字段定义。关于结果集所有列的MYSQL_FIELD结构的数组。
}
for (int i = 0; i<6; i++)   //打印字段
printf("%10s\t", str_field[i]);
printf("\n");
//打印获取的数据
while (column = mysql_fetch_row(result))   //在已知字段数量情况下，获取并打印下一行
{
	printf("%10s\t%10s\t%10s%10s\t%10s\t%10s\t\n", column[0], column[1], column[2], column[3], column[4], column[5]);  //column是列数组
}
do
{
	result = mysql_store_result(&myCont);
	mysql_free_result(result);
} while (!mysql_next_result(&myCont));//如果存在多个查询结果，mysql_next_result()将读取下一个查询结果，并将状态返回给应用程序。如果前面的查询返回了结果集，必须为其调用mysql_free_result()。
//如果条件为真的话，就会重复do...while这个循环, 直至while()为假,存在多个查询结果，退出循环；0表示有多个结果
return true;
}

bool QueryDatabase()
{
	mysql_query(&myCont, "set names gbk");
	//返回0 查询成功，返回1查询失败
	if (mysql_query(&myCont, "select * from test_1"))        //执行SQL语句
	{
		printf("Query failed (%s)\n", mysql_error(&myCont));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	result = mysql_store_result(&myCont);
	//打印数据行数
	printf("number of dataline returned: %d\n", mysql_affected_rows(&myCont));
	for (int i = 0; fd = mysql_fetch_field(result); i++)  //获取字段名
		strcpy_s(field[i], fd->name);
	int j = mysql_num_fields(result);  // 获取列数
	for (int i = 0; i<j; i++)  //打印字段
		printf("%10s   ", field[i]);
	    printf("\n");
	while (column = mysql_fetch_row(result))
	{
		for (int i = 0; i<j; i++)
			printf("%10s   ", column[i]);
		printf("\n");
	}
	do
	{
		result = mysql_store_result(&myCont);
		mysql_free_result(result);
	} while (!mysql_next_result(&myCont));
	return true;
}

//修改日志数据
bool ModifyData(MYSQL & myCont,const string e, const int g)
{
	string temp("update test_1 set log = '" + e + "' where id ="+to_string(g)+";"); 
	strncpy_s(query, temp.c_str(), temp.length());  //可以想办法实现手动在控制台手动输入指令
	//cout << query << endl;
	if (mysql_query(&myCont, query))        //执行SQL语句
	{
		printf("Modify failed (%s)\n", mysql_error(&myCont));
		return false;
	}
	else
	{
		printf("Modify Data success\n");
	}
	//释放SQL语句
	do
	{
		auto result = mysql_store_result(&myCont);
		mysql_free_result(result);
	} while (!mysql_next_result(&myCont));
	return true;
}

//修改作者数据
bool ModifyData_author(MYSQL & myCont, const string c, const int g)
{
	string temp("update test_1 set author = '" + c + "' where id =" + to_string(g) + ";");
	strncpy_s(query, temp.c_str(), temp.length());  //可以想办法实现手动在控制台手动输入指令
	//cout << query << endl;
	if (mysql_query(&myCont, query))        //执行SQL语句
	{
		printf("Modify failed (%s)\n", mysql_error(&myCont));
		return false;
	}
	else
	{
		printf("Modify Data success\n");
	}
	//释放SQL语句
	do
	{
		auto result = mysql_store_result(&myCont);
		mysql_free_result(result);
	} while (!mysql_next_result(&myCont));
	return true;
}


//修改代码改变情况数据
bool ModifyData1(MYSQL & myCont, const string a, const string b, const string c, const int g)
{
	string temp("update test_1 set file_change = " + a +", insertion =" + b + ", deletion = " + c + " where id =" + to_string(g) + ";");
	//++
	strncpy_s(query, temp.c_str(), temp.length());  //可以想办法实现手动在控制台手动输入指令
	cout << query << endl;
	if (mysql_query(&myCont, query))        //执行SQL语句
	{
		printf("Modify failed (%s)\n", mysql_error(&myCont));
		return false;
	}
	else
	{
		printf("Modify Data success\n");
	}
	//释放SQL语句
	do
	{
		auto result = mysql_store_result(&myCont);
		mysql_free_result(result);
	} while (!mysql_next_result(&myCont));
	return true;
}

//删除数据
bool DeleteData()
{
	sprintf_s(query, "TRUNCATE TABLE test_1");
	//char query[100];
	//printf("please input the sql:\n");
	//gets_s(query);  //这里手动输入sql语句
	if (mysql_query(&myCont, query))        //执行SQL语句
	{
		printf("Delete Data failed (%s)\n", mysql_error(&myCont));
		return false;
	}
	else
	{
		printf("Delete Data success\n");
	}
	//释放SQL语句
	do
	{
		auto result = mysql_store_result(&myCont);
		mysql_free_result(result);
	} while (!mysql_next_result(&myCont));
	return true;
}

