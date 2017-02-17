//
//  Transactional_Commands.hpp
//  CS109_SRI_CommandLine
//
//  Created by Kory Brown on 2/16/17.
//  Copyright © 2017 Kory Brown. All rights reserved.
//

#ifndef Transactional_Commands_hpp
#define Transactional_Commands_hpp

#include "Common.hpp"

class Transactional_Commands {
private:
    vector<map<string,string> > fact;
    vector<map<string,string> > rule;
    
public:
    void loadCommand();
    void dumpCommand();
    void inferenceCommand(string command);
    void dropCommand(string command);
    void factCommand(string fact);
    void ruleCommand(string rule);
};

#endif /* Transactional_Commands_hpp */
