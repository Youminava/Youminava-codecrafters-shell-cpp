#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    cout << unitbuf;    
    string input;
   
    const char* home_dir = getenv("HOME");
    string history_file;
   
    if(home_dir !=nullptr) {
    history_file = string(home_dir) + "/kubsh_history";
    }
    else history_file = "/kubsh_history";

    while(true) {
    cout << "$ ";
    if(!getline(cin, input)) break; 
    if(!input.empty()) {
      bool isValid = false;
      if(input == "\\q" || input == "history") isValid = true;
      else if(input.find("echo ") == 0 || input == "echo") isValid = true;

      if(!isValid) {
        cout << "Unknown command: " << input << endl;
        continue;
      }
    }

    if(!input.empty() && input != "\\q" && input != "history") {
    ofstream file(history_file, ios::app);
    file << input << endl;
    }
    if(input == "\\q") {
    return 0;
    }
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
