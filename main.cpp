#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "function.cpp"
#include <dirent.h>
using namespace std;

int funcCountRec(string str, string orig );
 
struct listfiles
{
   string name;
   float relev;
};

int main(int argc, char* argv[])
{
    string req = "";
    int countfiles = 0;
	string scountinfo;
    int countinfo; 
    const char namedir[] = "E:\\Programming\\Rgz\\files\\"; 
    
    DIR *dir;
	struct dirent *ent;
	
	if ((dir = opendir (namedir)) != NULL) {
	  while ((ent = readdir (dir)) != NULL) {
	    if (strlen(ent->d_name) > 2)
        countfiles++;
	  }
	  closedir (dir);
	} else {
	  perror ("");
      cout << "Read directory error!" << endl;
	  return EXIT_FAILURE;
	}
    
    if (countfiles == 0){
      cout << "In the directory 0 files!" << endl;
	  return EXIT_FAILURE;
    }
    
    string str,onefile;
    int i = 0;
    
    listfiles* arrlist = new listfiles[countfiles];
    dir = opendir (namedir);	
    while ((ent = readdir (dir)) != NULL) {
     if (strlen(ent->d_name) > 2){
    	std::string dname = ent->d_name;
        onefile = namedir+dname;
        // ��������� ������ ����
		ifstream fone(onefile.c_str());
	    if (!fone.is_open()) {
	      cout << "Read file error!" << onefile << endl;
	      //system("pause");
	      //return 0;
		}
		else {
 		    arrlist[i].name = onefile;	// �������� ��� �����
            fone.close();
		}
	    i++;
     }
   }
   closedir (dir);
    
     cout << "Enter request : " ;
     getline(cin, req);
	
	//���������� ���� � �������
    countinfo=atoi(scountinfo.c_str());
    string orig = req;
    req = req+" ";
    int countword = 0;
    string tmpreq = req; 
    while(tmpreq.find(" ") != tmpreq.npos){
      ++countword;
      tmpreq.erase(tmpreq.find(" "),1);
    }              
    
  // ������� � ��������� ������ ���� �������  
    string* arrword = new string[countword];
    tmpreq = req; 
	string search = " ";
	int spacePos;
	int currPos = 0;
	int k = 0;
	int prevPos = 0;
    do
    {
      spacePos = req.find(search,currPos);
	    if(spacePos >= 0)
	    {
	        currPos = spacePos;
	        arrword[k] = req.substr(prevPos, currPos - prevPos);
	        currPos++;
	        prevPos = currPos;
	        k++;
	    }
   } while(spacePos >= 0);    
    
    for (int i = 0; i < countfiles; i++) 
    {
        onefile = arrlist[i].name;
        // ��������� ������ ����
		ifstream fone((onefile.c_str()));
		size_t words_counter = 0;
		string buffer;
		string sfile = ""; //�������� ���� � ������
		while(fone >> buffer) {
			++words_counter;
			sfile = sfile+buffer+" ";
		}
	
		int countw = 0;
		float countr = 0;
		float allcountr = 0;
		float koefvz = 0;  // ���������� ����������� 
		int countPossible = 0;
        for (int w = 0; w < countword; w++) // ���������� ��� �������� � 1, ������, �������� � �.�. ����
        {
          koefvz = ((w+1)*10)/countword; // ��� ������ ���� ��� ���� ����������� �����������
          countPossible = words_counter/(w+1); //���������� ��������� ���������

          for (int z = 0; z < countword; z++) 
          {
            string scheck = "";
            bool flgchk = true;
		    for (int x = 0; x <= w; x++) // ��������� 1-�� ����, ������ � �.�. ����
			{
		      if (z+x < countword)
			  { 
		   	    scheck = scheck + arrword[z+x]+" ";
                flgchk = true;
			  }
		   	  else
			  { 
	            flgchk = false;
              }
			}        	
			if (flgchk){  // ��������� ����� ������ ���������� ���������� ����
          	  countr = funcCountRec(sfile,scheck); //������� ���������� ���������
          	  countr = countr/countPossible; //��������� ������ (������� ���������� � ����������)
          	  countr = countr*koefvz; //���������� ������
          	  allcountr = allcountr + countr; 
            }  
          }
        }
        arrlist[i].relev = allcountr;  
        fone.close();
    }
    
    for (int x = 0; x < countfiles ; x++)
     {    
       cout << " Name = " << arrlist[x].name << endl;
       cout << " Relevance = " << arrlist[x].relev << endl ;
       cout << " ------------" << endl ;
	 }

	delete[]arrlist;
	delete[]arrword;
	
    system("pause");
    return 0;
}

