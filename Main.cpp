#include "Common.hpp"
#include "Helper.hpp"

int main() {
    
    Helper:: parse("Rule GrandMother($X,$Y):- AND Mother($X,$Z) Mother($Z,$Y)");
    
    return 0;
}
