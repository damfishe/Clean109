//Interface.cpp

#include "Interface.hpp"


void Interface:: run()
{
    
    
    Helper::instance()->parseCommand("Fact Father(Roger,John)");
    Helper::instance()->parseCommand("Fact Father(Roger,Albert)");
    Helper::instance()->parseCommand("Fact Father(Allen,Margret)");
//    Helper::instance()->parse("Rule GrandMother($X,$Y):- AND Mother($X,$Z) Mother($Z,$Y)");
    
    Helper::instance()->parseCommand("Inference Father($X,$Y)");


    
}
