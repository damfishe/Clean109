//
//  Helper.hpp
//  CS109_SRI_CommandLine
//
//  Created by Kory Brown on 2/16/17.
//  Copyright © 2017 Kory Brown. All rights reserved.
//

#ifndef Helper_hpp
#define Helper_hpp

#include "Common.h"


class Helper{
    
public:
    static void storeBase(vector<map<string,string>> base, string def);
    static void getBase(vector<map<string,string>> base, string def);
    static void dropBase(vector<map<string,string>> base, string def);
    static void andBase(vector<map<string,string>> base);
    static void orBase(vector<map<string,string>> base);
    static void parse(string Command);
    
};

#endif /* Helper_hpp */
