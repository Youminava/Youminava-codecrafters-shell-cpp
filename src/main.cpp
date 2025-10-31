#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << unitbuf;
    
    string input;
    while(getline(cin, input)) {
     if(input == "\\q") {return 0;}
   cout << input << endl;
 }
}
