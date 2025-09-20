#include <iostream>
#include <string>
int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
 while(true) { 
 std::cout << "$ ";
  std::string input
;
  if(!std::getline(std::cin, input)){
break;
}

if(!input.empty()){ std::cout << input <<  ": command not found" << std::endl;
    }
   }
return 0;

 }
