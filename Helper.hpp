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
    ~Helper();
    static Helper * instance();
    
    void DumpHelp(string);
    void LoadHelp(string);
    void ParseQuery(string);
    void storeBase(vector<tuple<string,vector<string>>>&,vector<string>&,string);
    //void getBase(vector<tuple<string,vector<string>>>&,string);
    void dropBase(string);
    vector<string> andOperator(string,vector<string>,vector<string>);
    vector<string> orOperator(string,vector<string>,vector<string>);
    void parseCommand(string);
    void parseDefinition(char,string);
    vector<string> parseRule(string);
    string parseKey(string &input);
    vector<vector<string>> retrieveFact(string,string&,string&);
    vector<string> retrieveRule(vector<string>,string);
    vector<string> parseParams(string &input);
	//void print();
    
};

#endif
 /* 
Helper_hpp 
*/
