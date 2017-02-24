//Helper.hpp

#ifndef Helper_hpp
#define Helper_hpp

#include "Common.hpp"

class Transactional_Commands; // forward declaration

// Singleton Class
class Helper{
    
private:
    Helper(); // constructor is private to no instances of class can be created (Singleton)
    
    Transactional_Commands* tCommands;
    static Helper * h_instance;
    
public:
    static Helper * instance();
    
    void DumpHelp(string);
    void LoadHelp(string);
    void storeBase(vector<tuple<string,vector<string>>>&,vector<string>&,string);
    void getBase(vector<tuple<string,vector<string>>>&,string);
    void dropBase(string);
    void andBase();
    void orBase();
    void parseCommand(string);
    void parseDefinition(char,string);
    void retrieveBaseData(vector<tuple<string,vector<string>>>&, string);
    
};

#endif /* Helper_hpp */
