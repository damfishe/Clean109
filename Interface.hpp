//Interface.hpp

#ifndef Interface_hpp
#define Interface_hpp

#include "Common.hpp"
#include "Transactional_Commands.hpp"
#include "Helper.hpp"

class Interface{
    
private:
    bool keepRunning;
    string pathToFile;
    
public:
    //Interface();
    //~Interface();
    void run();
    
};

#endif /* Interface_hpp */
