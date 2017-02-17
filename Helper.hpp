#ifndef Helper_hpp
#define Helper_hpp

#include "Common.hpp"


class Helper{
    
public:
    static void storeBase(vector<string,string> base, string);
    static void getBase(vector<string,string>base, string);
    static void dropBase(vector<string,string> base, string);
    static void andBase(vector<string,string> base);
    static void orBase(vector<string,string>base);
    static void parse(string);
    
};

#endif /* Helper_hpp */
