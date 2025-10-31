#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    cout << unitbuf;    
    string input;
   
    string history_file = "/home/govno/kubsh_history";

    while(true) {
     cout << "$ ";
    if(!getline(cin, input)) break; 
   
    if(!input.empty() && input != "\\q" && input != "history") {
    ofstream file(history_file, ios::app);
    file << input << endl;
    }

     if(input == "\\q") {return 0;}
     else if(input.find("echo ") == 0) {
     string message = input.substr(5);
     cout << message << endl;
   } 
    else if(input == "history") {
    ifstream read_file(history_file);
    string line;
    while(getline(read_file, line)) {
        cout << " " << line << endl;
      }
  }
 else cout << input << endl;
}
}
