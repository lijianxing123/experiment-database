#ifndef MY_T_FILE
#define MY_T_FILE
#include "process.h "
#include <fstream>
#include <iostream>
#include <sstream>
class Text{
public:
	Text(string s) : file(s){ }
	void insertDatabase(MYSQL & myCont);
private:
	string file;
};
#endif