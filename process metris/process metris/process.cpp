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
MYSQL_RES *result;//����ṹ�������е�һ����ѯ�����
char query[150]; //��ѯ���
MYSQL_ROW column; //һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���

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

string IntToString2(int a[])//int ����תstring�ڶ����֣�ֱ�ӵ������
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

//�������ݿ�
bool ConnectDatabase(MYSQL & myCont){
	mysql_init(& myCont);
	//int i = CR_CONN_HOST_ERROR;
	if (0 == mysql_options(& myCont, MYSQL_SET_CHARSET_NAME, "gbk"))//�����ַ���
	{
		cout << "�����ַ����ɹ�" << endl;
	}
	if (0 == mysql_options(& myCont, MYSQL_OPT_RECONNECT, &my_true))
	{
		cout << "���ÿ������ɹ�" << endl;
    }

	if (!mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, CLIENT_MULTI_STATEMENTS))//�������ݿ�
	{
		cout << "�������ӵ����ݿ�" << endl;
		fprintf(stderr, "Failed to connect to database: Error: %s", mysql_error(& myCont));
		return false;
	}
	cout << "�������ݿ�ɹ�" << endl;
	return true;
}

//�ͷ���Դ
void FreeConnect()
{
	//�ͷ���Դ
	if (result != NULL) mysql_free_result(result);//�ͷŽ����Դ*/
	mysql_close(& myCont);
}



/***************************���ݿ����***********************************/
//��ʵ���е����ݿ����������д��sql��䣬Ȼ����mysql_query(&mysql,query)����ɣ������������ݿ�����ɾ�Ĳ�
//��������
bool InsertData(MYSQL & myCont, const string a, const int b, const string c, const string d, const string e, const string h, const int g = 0)
{
	xx = "insert into test_1 values('"+a+"','"+to_string(b)+"','','"+d+"','','"+to_string(g) +"','" +h +"','0','0','0"+"');";
	
	strncpy_s(query, xx.c_str(), xx.length());
	
	//sprintf_s(query, "insert into test_1 values(" + a + "," + to_string(b) +  "," + c +  "," + d +  "," + e + ");");  //������취ʵ���ֶ��ڿ���̨�ֶ�����ָ��
	cout << query << endl;
	if (mysql_query(&myCont, query))        //ִ��SQL���
	{
		printf("Query failed (%s)\n", mysql_error(&myCont));
	}
	else
	{
		printf("Insert success\n");
		return false;
	}
	//�ͷ�SQL���
	do
	{
		auto result = mysql_store_result(&myCont);
		mysql_free_result(result);
	} while (!mysql_next_result(&myCont));
	return true;
}


//��ѯ����
bool QueryDatabase1()
{
    sprintf_s(query, "select * from test_1"); //ִ�в�ѯ��䣬�����ǲ�ѯ���У�test_1�Ǳ��������ü����ţ���strcpyҲ����
	mysql_query(& myCont, "set names gbk"); //���ñ����ʽ��SET NAMES GBKҲ�У�������cmd����������
//����0 ��ѯ�ɹ�������1��ѯʧ��
	if (mysql_query(&myCont, query))        //ִ��SQL���
{
	printf("Query failed (%s)\n", mysql_error(& myCont));
    return false;
}
else
{
printf("query success\n");
}
//��ȡ�����
	if (!(result = mysql_store_result(&myCont)))    //���sql�������󷵻صĽ����
{
		printf("Couldn't get result from %s\n", mysql_error(& myCont));
        return false;
}

    //��ӡ��������
	printf("number of dataline returned: %d\n", mysql_affected_rows(&myCont)); //mysql_affected_rows���ر����µ�UPDATE, DELETE��INSERT��ѯӰ���������
	//�ͷ�SQL���
	

//��ȡ�ֶε���Ϣ
char *str_field[32];  //����һ���ַ�������洢�ֶ���Ϣ
for (int i = 0; i<6; i++)   //����֪�ֶ�����������»�ȡ�ֶ���
{
	str_field[i] = mysql_fetch_field(result)->name; //mysql_fetch_fields() ����һ�������ֶνṹ�����顣���ڽ��������������MYSQL_FIELD�ṹ�����顣ÿ���ṹ�ṩ�˽������1�е��ֶζ��塣���ڽ���������е�MYSQL_FIELD�ṹ�����顣
}
for (int i = 0; i<6; i++)   //��ӡ�ֶ�
printf("%10s\t", str_field[i]);
printf("\n");
//��ӡ��ȡ������
while (column = mysql_fetch_row(result))   //����֪�ֶ���������£���ȡ����ӡ��һ��
{
	printf("%10s\t%10s\t%10s%10s\t%10s\t%10s\t\n", column[0], column[1], column[2], column[3], column[4], column[5]);  //column��������
}
do
{
	result = mysql_store_result(&myCont);
	mysql_free_result(result);
} while (!mysql_next_result(&myCont));//������ڶ����ѯ�����mysql_next_result()����ȡ��һ����ѯ���������״̬���ظ�Ӧ�ó������ǰ��Ĳ�ѯ�����˽����������Ϊ�����mysql_free_result()��
//�������Ϊ��Ļ����ͻ��ظ�do...while���ѭ��, ֱ��while()Ϊ��,���ڶ����ѯ������˳�ѭ����0��ʾ�ж�����
return true;
}

bool QueryDatabase()
{
	mysql_query(&myCont, "set names gbk");
	//����0 ��ѯ�ɹ�������1��ѯʧ��
	if (mysql_query(&myCont, "select * from test_1"))        //ִ��SQL���
	{
		printf("Query failed (%s)\n", mysql_error(&myCont));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	result = mysql_store_result(&myCont);
	//��ӡ��������
	printf("number of dataline returned: %d\n", mysql_affected_rows(&myCont));
	for (int i = 0; fd = mysql_fetch_field(result); i++)  //��ȡ�ֶ���
		strcpy_s(field[i], fd->name);
	int j = mysql_num_fields(result);  // ��ȡ����
	for (int i = 0; i<j; i++)  //��ӡ�ֶ�
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

//�޸���־����
bool ModifyData(MYSQL & myCont,const string e, const int g)
{
	string temp("update test_1 set log = '" + e + "' where id ="+to_string(g)+";"); 
	strncpy_s(query, temp.c_str(), temp.length());  //������취ʵ���ֶ��ڿ���̨�ֶ�����ָ��
	//cout << query << endl;
	if (mysql_query(&myCont, query))        //ִ��SQL���
	{
		printf("Modify failed (%s)\n", mysql_error(&myCont));
		return false;
	}
	else
	{
		printf("Modify Data success\n");
	}
	//�ͷ�SQL���
	do
	{
		auto result = mysql_store_result(&myCont);
		mysql_free_result(result);
	} while (!mysql_next_result(&myCont));
	return true;
}

//�޸���������
bool ModifyData_author(MYSQL & myCont, const string c, const int g)
{
	string temp("update test_1 set author = '" + c + "' where id =" + to_string(g) + ";");
	strncpy_s(query, temp.c_str(), temp.length());  //������취ʵ���ֶ��ڿ���̨�ֶ�����ָ��
	//cout << query << endl;
	if (mysql_query(&myCont, query))        //ִ��SQL���
	{
		printf("Modify failed (%s)\n", mysql_error(&myCont));
		return false;
	}
	else
	{
		printf("Modify Data success\n");
	}
	//�ͷ�SQL���
	do
	{
		auto result = mysql_store_result(&myCont);
		mysql_free_result(result);
	} while (!mysql_next_result(&myCont));
	return true;
}


//�޸Ĵ���ı��������
bool ModifyData1(MYSQL & myCont, const string a, const string b, const string c, const int g)
{
	string temp("update test_1 set file_change = " + a +", insertion =" + b + ", deletion = " + c + " where id =" + to_string(g) + ";");
	//++
	strncpy_s(query, temp.c_str(), temp.length());  //������취ʵ���ֶ��ڿ���̨�ֶ�����ָ��
	cout << query << endl;
	if (mysql_query(&myCont, query))        //ִ��SQL���
	{
		printf("Modify failed (%s)\n", mysql_error(&myCont));
		return false;
	}
	else
	{
		printf("Modify Data success\n");
	}
	//�ͷ�SQL���
	do
	{
		auto result = mysql_store_result(&myCont);
		mysql_free_result(result);
	} while (!mysql_next_result(&myCont));
	return true;
}

//ɾ������
bool DeleteData()
{
	sprintf_s(query, "TRUNCATE TABLE test_1");
	//char query[100];
	//printf("please input the sql:\n");
	//gets_s(query);  //�����ֶ�����sql���
	if (mysql_query(&myCont, query))        //ִ��SQL���
	{
		printf("Delete Data failed (%s)\n", mysql_error(&myCont));
		return false;
	}
	else
	{
		printf("Delete Data success\n");
	}
	//�ͷ�SQL���
	do
	{
		auto result = mysql_store_result(&myCont);
		mysql_free_result(result);
	} while (!mysql_next_result(&myCont));
	return true;
}

