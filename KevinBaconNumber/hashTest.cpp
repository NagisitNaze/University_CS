#include <iostream>
#include <string>
#include "HashList.h"

int main() 
{
    std::cout << "Testing HashList: ";
    HashList myList(503);
    myList.insert("ok");
    myList.insert("this");
    myList.insert("not this");

    std::cout << "finding: ok, this:\n";
    std::cout << myList.find("ok") << std::endl;
    std::cout << myList.find("this") << std::endl;
    std::cout << "viewing hash for: not this, test, temp:\n";
    std::cout << myList.showHash("not this") << std::endl;
    std::cout << myList.showHash("test") << std::endl;
    std::cout << myList.showHash("temp") << std::endl;
    return 0; 
}
