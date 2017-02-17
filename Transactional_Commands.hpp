#ifndef Transactional_Commands_hpp
#define Transactional_Commands_hpp

#include "Common.hpp"


class Transactional_Commands {
    
    typedef void (Transactional_Commands:: *command_operations)(string);
    
private:
    map<string,command_operations> command;
    
public:
    Transactional_Commands();
    
    void loadCommand(string);
    void dumpCommand(string);
    void inferenceCommand(string);
    void dropCommand(string);
    void factCommand(string);
    void ruleCommand(string);
};

#endif /* Transactional_Commands_hpp */
