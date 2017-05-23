#include "stat.h"
#include <regex>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

bool isAllDigit(const string& str)
{
	int i;
	if (str.empty())
		return false;
	for (i = 0; i != str.length(); i++)
	{
		if (!isdigit(str[i]))
		{
			return false;
		}
	}
	return true;
}

void Stat::modifyDatabase(MYSQL & myCont){
	ifstream input(stat_file);
	string temp;
	int id = 0;

	//string pattern("^[\d+$]");
	//pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
	//regex r(pattern);

	while (getline(input, temp)){
		vector<string> Line{" ", " ", " " };
		string word;
		string temp1;
		string temp2;
		istringstream line(temp);
		//取得一次作者的时间信息
		 line >> word;
		 temp1 = word;
		 if (isAllDigit(word)){
			 //cout << temp << id << endl;
			 while (line >> word){
				 if (word == "files" || word == "file")
					 Line[0] = temp1;
				 if (word == "insertions(+)," || word == "insertions(+)" || word == "insertion(+)")
					 Line[1] = temp2;
				 if (word == "deletions(-)" || word == "deletion(-)")
					 Line[2] = temp2;
				 temp2 = word;
				
			 }  
			 id++;
			 ModifyData1(myCont,Line[0], Line[1], Line[2], id);
			 //cout << Line[0] << " " << Line[1] << " " << Line[2] << "" << endl;
		 }
		
		
	}
	
}
			
		
