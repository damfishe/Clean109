//Transactional_Commands.hpp


#ifndef Transactional_Commands_hpp
#define Transactional_Commands_hpp

#include "Common.hpp"

typedef void (*command_operations)(string);

class Transactional_Commands {
    
private:
    map<string,command_operations> commandMap;
    
public:
    Transactional_Commands();
    
    map<string,command_operations> getMapCommand();
    
    static void loadCommand(string);
    static void dumpCommand(string);
    static void inferenceCommand(string);
    static void dropCommand(string);
    static void factCommand(string);
    static void ruleCommand(string);
};

#endif /* Transactional_Commands_hpp */
