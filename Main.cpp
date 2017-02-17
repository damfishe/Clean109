//
//  main.cpp
//  CS109_SRI_CommandLine
//
//  Created by Kory Brown on 2/16/17.
//  Copyright © 2017 Kory Brown. All rights reserved.
//

#include "Common.hpp"
#include "Helper.hpp"

int main() {
    
    Helper:: parse("Rule GrandMother($X,$Y):- AND Mother($X,$Z) Mother($Z,$Y)");
    
    return 0;
}
