//
//  Transactional_Commands.hpp
//  CS109_SRI_CommandLine
//
//  Created by Kory Brown on 2/16/17.
//  Copyright © 2017 Kory Brown. All rights reserved.
//

#ifndef Transactional_Commands_hpp
#define Transactional_Commands_hpp

#include "Common.h"

class Transactional_Commands {
private:
    
public:
    void load();
    void dump();
    void inference(string command);
    void drop(string command);
    void fact(string fact);
    void rule(string rule);
};

#endif /* Transactional_Commands_hpp */
