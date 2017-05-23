#include "process.h"
#include "Text.h"
#include "stat.h"
int main(){
	
	//project = "hive1";
	//author = "ljx1";
	//date = "two week ago1";
	//logg = "son of bitch1";
	//id = 5201;
     ConnectDatabase(myCont);
	//InsertData(myCont, project, id, author, date, logg , bug);
	//QueryDatabase1();
	//ModifyData();
	//DeleteData();
	//QueryDatabase();
	//cout << "****" << endl;*/
	Text Hive("test.txt");
	//QueryDatabase();
	Hive.insertDatabase(myCont);
	Stat Stat("stat.txt");
	Stat.modifyDatabase(myCont);
	//DeleteData();
	FreeConnect();
	system("pause");
	return 0;
}
