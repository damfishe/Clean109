#include "Transactional_Commands.hpp"


Transactional_Commands:: Transactional_Commands(){
    
    command["fact"] = &Transactional_Commands::factCommand;
    command["rule"] = &Transactional_Commands::ruleCommand;
    command["drop"] = &Transactional_Commands::dropCommand;
    command["inference"] = &Transactional_Commands::inferenceCommand;
    command["load"] = &Transactional_Commands::loadCommand;
    command["dump"] = &Transactional_Commands::dumpCommand;

}

void Transactional_Commands:: loadCommand(string path){
    
}

void Transactional_Commands:: dumpCommand(string path){
    
}

void Transactional_Commands:: inferenceCommand(string command){
    
}

void Transactional_Commands:: dropCommand(string command){
    
}

void Transactional_Commands:: factCommand(string fact){
    
}

void Transactional_Commands:: ruleCommand(string rule){
    
}
