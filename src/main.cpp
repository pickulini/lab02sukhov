#include <iostream>
#include "16g.h"

int main() {
    Hex a("A1B2");
    Hex b("123");
    
    std::cout << a.toString() << " + " << b.toString() << " = " 
              << a.add(b).toString() << std::endl;
    
    return 0;
}
