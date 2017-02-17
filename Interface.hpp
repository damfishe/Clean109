#ifndef Interface_hpp
#define Interface_hpp

#include "Common.hpp"
#include "Transactional_Commands.hpp"

class Interface{
    
private:
    vector <Transactional_Commands*> transactionalCommands;
    bool keepRunning;
    string pathToFile;
    
public:
    Interface();
    void run();
    ~Interface();
    
};

#endif /* Interface_hpp */
