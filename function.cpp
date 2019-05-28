#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int funcCountRec (string str, string orig )
{
   int count = 0;	
    
   while(str.find(orig) != str.npos){
     ++count;
     str.erase(str.find(orig),orig.length());
   }       
   return count;       
}
 
