/****************************************************
*@brief:mysqlhelper demo
*@autor:lvlv
*@date:2016.06.12
*@MySQL version:MySQL Community Server 5.6.30 (GPL)
****************************************************/

#include <string.h>
#include <iostream>
#include <string>
using namespace std;

#include "mysqlHelper.h"
using namespace mysqlhelper;


int main(int argc, char* argv[]){

	//��ʼ��mysql���󲢽�������
	MysqlHelper mysqlHelper;
	mysqlHelper.init("119.29.184.114", "root", "123456", "StudentCourse");
	try{
		mysqlHelper.connect();
	}
	catch (MysqlHelper_Exception& excep){
		cout << excep.errorInfo;
		return -1;
	}

	//����һ��ѧ����¼
	//ʾ���������
	//string sql="insert into student values("201421031060","����","��������ѧ","2014","�������",1)";

	MysqlHelper::RECORD_DATA record;
	record.insert(make_pair("studentNo", make_pair(MysqlHelper::DB_STR, "201421031060")));
	record.insert(make_pair("name", make_pair(MysqlHelper::DB_STR, "����")));
	record.insert(make_pair("school", make_pair(MysqlHelper::DB_STR, "������ҽҩ��ѧ")));
	record.insert(make_pair("grade", make_pair(MysqlHelper::DB_STR, "2014")));
	record.insert(make_pair("major", make_pair(MysqlHelper::DB_STR, "�������ѧ�뼼��")));
	record.insert(make_pair("gender", make_pair(MysqlHelper::DB_INT, "1")));
	int res = 0;
	try{
		res = mysqlHelper.insertRecord("student", record);
	}
	catch (MysqlHelper_Exception& excep){
		cout << excep.errorInfo;
		return -1;
	}
	cout << "res:" << res << " insert successfully " << endl;

	//ɾ��һ��ѧ����¼��ѧ��Ϊ201421031059
	try{
		res = mysqlHelper.deleteRecord("student", "where studentNo=\"201421031059\"");
	}
	catch (MysqlHelper_Exception& excep){
		cout << excep.errorInfo;
		return -1;
	}
	cout << "res:" << res << " delete successfully " << endl;

	//����ѧ��Ϊ201421031059��ѧ��ѡ������пγ�����
	MysqlHelper::MysqlData dataSet;
	string querySQL = "select courseName from course co where co.courseNo in (select courseNo from courseSelection where studentNo=\"201421031060\")";
	try{
		dataSet = mysqlHelper.queryRecord(querySQL);
	}
	catch (MysqlHelper_Exception& excep){
		cout << excep.errorInfo;
		return -1;
	}
	cout << "query successfully" << endl;
	for (size_t i = 0; i<dataSet.size(); ++i){
		cout << dataSet[i]["courseName"] << endl;
	}

	//�޸�ѧ��Ϊ201421031060��ѧ��רҵ
	MysqlHelper::RECORD_DATA recordChange;
	recordChange.insert(make_pair("major", make_pair(MysqlHelper::DB_STR, "�������")));
	try{
		res = mysqlHelper.updateRecord("student", recordChange, "where studentNo=\"201421031060\"");
	}
	catch (MysqlHelper_Exception& excep){
		cout << excep.errorInfo;
		return -1;
	}
	cout << "res:" << res << " update successfully" << endl;
	system("pause");
	return 0;
}