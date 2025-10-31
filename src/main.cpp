#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << unitbuf;
    
    string input;
    if(getline(cin, input)) {
        cout << input << endl;
    }
    
    return 0;
}
