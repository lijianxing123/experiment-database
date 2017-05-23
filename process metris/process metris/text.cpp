#include "Text.h"
#include <regex>



void Text::insertDatabase(MYSQL & myCont){
	string pattern("^[\(]");
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
	regex r(pattern);
	smatch results;

	string pattern1("[\)]$");
	pattern1 = "[[:alpha:]]*" + pattern1 + "[[:alpha:]]*";
	regex r1(pattern1);
	smatch results1;

	string project="HIVE";
    int id = 1;
	int bug=0;
	ifstream input(file);
	string temp;
	while (getline(input, temp)){
		//cout << temp << endl;
		string author("");
		string date("");
		string logg("");
		istringstream line(temp);
		string word("");
		string reviewer("");
		bool biaozhi=false;
		int j = 0;
		int k = 0;
		//取得一次作者的时间信息
		while (line >> word){
			if (word == "-"){
				line >> word;
				while (word != ","){
					author += word +" ";
					line >> word;
				}
			}
			//cout << author << endl;
			//取得一次日志的时间信息
			if (word == ","){
				line >> word;
				while (word != ":"){
					date += word + " ";
					line >> word;
				}
			}
			//cout << date << endl;

			//取得一次日志的内容信息
			if (word == ":"){
				while (line >> word){
					//cout << word << "\n";
					if (regex_search(word, results, r)){
						//cout << results.str() << endl;
						//cout << logg << endl;
						break;
					}
					logg += word + " ";
				}
			}

			//得到日志主内容
			for (int i = 0; i < logg.size(); i++){
				if (logg[i] == ':'){
					j = i;
					break;
					//cout << j << endl;
				}
			}
			//if (logg[i] == '\''){
			//	k= i;
				//cout << k << endl;
			//	break;
			//}}

			//logg = logg.substr ( j + 1 , 10 );

			//取得一次日志的reviewer信息
			if ( (word == "by") || (word == "via")){
				cout << id << "****" << endl;
				while (line >> word){
					reviewer += word + " ";
					biaozhi = regex_search(word, results1, r1);
					if (biaozhi){
						reviewer = reviewer.substr(0, reviewer.length() - 2);
						//cout << reviewer << endl;
						break;
					}
				}
			}
			if (biaozhi)
			  break;
		}

		InsertData(myCont, project, id, author, date, logg, reviewer, bug);
		int size = logg.length();
		/*if (k>j)
             ModifyData(myCont, logg.substr(j + 1, k - j - 1), id);
		else if (size > 110)
			ModifyData(myCont, logg.substr(j+1, 100), id);
		else
		    ModifyData(myCont, logg.substr(j+1, size - j), id);*/
		if (size > 110)
			ModifyData(myCont, logg.substr(j + 1, 100), id);
		else
			ModifyData(myCont, logg.substr(j + 1, size - j), id);

		    ModifyData_author(myCont , author , id);
		id++;
	}

	//string temp1 = "ahsdjaso jsado asodk adpoda sjdos ajod freind fteight";
	//string temp2 = "fteight ahsdjaso jsado asodk adpoda sjdos ajod freind ";
	//regex_search(temp1, results, r);
	//cout << results.str() << endl;
	//string pattern("[^c]ei");//^[\(]
	//pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
	//regex r(pattern);
	//smatch results;
	//regex_search(temp2, results, r);
	//cout << results.str() << endl;
}