//Helper.hpp

#ifndef Helper_hpp
#define Helper_hpp

#include "Common.hpp"
#include "Transactional_Commands.hpp"

// Singleton Class
class Helper{
    
private:
    Helper(); // constructor is private to no instances of class can be created (Singleton)
    
    Transactional_Commands* tCommands;
    static Helper * h_instance;
    
public:
    static Helper * instance();
    
    void storeBase(vector<string>,string);
    void getBase(vector<string>,string);
    void dropBase(vector<string>,string);
    void andBase(vector<string>);
    void orBase(vector<string>);
    void parse(string);
    
};

#endif /* Helper_hpp */
