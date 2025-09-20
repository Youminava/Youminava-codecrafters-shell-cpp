#include <iostream>
#include <string>
int main() {
//setlocale(LC_ALL, "RU");
using namespace std;
  cout << std::unitbuf;
  cerr << std::unitbuf;
 while(true) { 
 cout << "$ ";
 string input;

  if(!getline(cin, input)){
break;
}



if (input  ==  "\\q") {
cout << "Exit"<< endl;
 break;
}

if(!input.empty()){ cout <<"Your entered string: " << input << endl;
    }
   }
return 0;

 }
