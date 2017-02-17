//
//  Interface.hpp
//  CS109_SRI_CommandLine
//
//  Created by Kory Brown on 2/16/17.
//  Copyright © 2017 Kory Brown. All rights reserved.
//

#ifndef Interface_hpp
#define Interface_hpp

#include "Common.hpp"
#include "Transactional_Commands.hpp"

class Interface{
    
private:
    vector <Transactional_Commands*> transactionalCommands;
    bool keepRunning;
    
public:
    Interface();
    void run();
    ~Interface();
    
};

#endif /* Interface_hpp */
