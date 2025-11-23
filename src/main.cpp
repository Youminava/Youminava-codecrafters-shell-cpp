#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
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
    if (isatty(STDIN_FILENO)) {
        cout << "$ ";
    }
    if(!getline(cin, input)) break; 
    if(!input.empty()) {
      bool isValid = false;
      string cmdName = input;
      size_t spacePos = input.find(' ');
      if(spacePos != string::npos) {
        cmdName = input.substr(0, spacePos);
      }

      if(cmdName == "\\q" || cmdName == "history" || cmdName == "help" || 
         cmdName == "exit" || cmdName == "type" || cmdName == "pwd" || 
         cmdName == "cd" || cmdName == "echo" || cmdName == "debug" || cmdName == "\\e") {
        isValid = true;
      }

      if(!isValid) {
        cout << input << ": command not found" << endl;
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
    
    // Parse input to handle quotes for echo and debug
    vector<string> args;
    string current_arg;
    bool in_quotes = false;
    for(char c : input) {
        if(c == '\'') {
            in_quotes = !in_quotes;
        } else if(c == ' ' && !in_quotes) {
            if(!current_arg.empty()) {
                args.push_back(current_arg);
                current_arg.clear();
            }
        } else {
            current_arg += c;
        }
    }
    if(!current_arg.empty()) args.push_back(current_arg);

    if(!args.empty() && (args[0] == "echo" || args[0] == "debug")) {
        for(size_t i = 1; i < args.size(); ++i) {
            cout << args[i] << (i == args.size() - 1 ? "" : " ");
        }
        cout << endl;
    } 
    else if(!args.empty() && args[0] == "\\e") {
        if (args.size() > 1) {
            string var = args[1];
            if (var.size() > 0 && var[0] == '$') {
                var = var.substr(1);
            }
            const char* env_val = getenv(var.c_str());
            if (env_val) {
                string val = env_val;
                size_t start = 0;
                size_t end = val.find(':');
                while (end != string::npos) {
                    cout << val.substr(start, end - start) << endl;
                    start = end + 1;
                    end = val.find(':', start);
                }
                cout << val.substr(start) << endl;
            }
        }
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
