#ifndef MY_S_FILE
#define MY_S_FILE
#include "process.h "

class Stat{
public:
	Stat(string s) : stat_file(s){ }
	void modifyDatabase(MYSQL & myCont);
private:
	string stat_file;
};

#endif