#ifndef MY_H_FILE
#define MY_H_FILE
#include <WinSock2.h>
#include <mysql.h> 
#include <string>  
using namespace std;

extern bool my_true;
extern MYSQL myCont;
extern MYSQL_ROW sql_row;
extern MYSQL_FIELD *fd;
extern char field[32][32];
extern MYSQL_RES *result;//����ṹ�������е�һ����ѯ�����
extern char query[150]; //��ѯ���
extern MYSQL_ROW column; //һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���
extern string project;
extern int id;
extern string author;
extern string date;
extern string logg;
extern int bug;
extern string xx;


bool ConnectDatabase(MYSQL & myCont);
void FreeConnect();
bool InsertData(MYSQL & myCont, const string a, const int b, const string c, const string d, const string e, const string h, const int g);
bool QueryDatabase1();
bool ModifyData(MYSQL & myCont, const string e, const int g);
bool ModifyData1(MYSQL & myCont, const string a, const string b, const string c, const int g);
bool ModifyData_author(MYSQL & myCont, const string c, const int g);
bool DeleteData();
bool QueryDatabase();
string IntToString(int & i);
string IntToString2(int a[]);
#endif