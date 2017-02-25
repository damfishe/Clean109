//Interface.cpp

#include "Interface.hpp"


void Interface:: run()
{
    
    
    Helper::instance()->parseCommand("Fact Father(Roger,John)");
    Helper::instance()->parseCommand("Fact Father(Roger,Albert)");
    Helper::instance()->parseCommand("Fact Father(Allen,Margret, Alliosn, Joe, Jim)");
    //Helper::instance()->parseCommand("Inference Father($X,$Y)");
    //Helper::instance()->parseCommand("Dump output.txt");
    
    
//    Helper::instance()->parseCommand("Rule GrandMother($X,$Y):- AND Mother($X,$Z) Mother($Z,$Y)");
//    Helper::instance()->parseCommand("Inference GrandMother($X,$Y)");

    
    
   


    
}
