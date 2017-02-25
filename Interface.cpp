//Interface.cpp

#include "Interface.hpp"


void Interface:: run()
{
    
     Helper::instance()->parseCommand("RULE GrandMother($X,$Y):- AND Mother($X,$Z) Mother($Z,$Y)");
//    Helper::instance()->parseCommand("RULE Parent($X,$Y):- OR Father($X,$Y) Mother($X,$Y)");
    
    
//    Helper::instance()->parseCommand("FACT Father(Roger,John)");
//    Helper::instance()->parseCommand("FACT Father(Roger,Albert)");
//    Helper::instance()->parseCommand("FACT Father(Allen,Margret)");
//    Helper::instance()->parseCommand("INFERENCE Father($X,$Y)");
    
    
//    Helper::instance()->parseCommand("FACT Mother(Marry,John)");
//    Helper::instance()->parseCommand("FACT Mother(Marry,Albert)");
//    Helper::instance()->parseCommand("FACT Mother(Margret,Robert)");
    Helper::instance()->parseCommand("FACT Mother(Margret,Bob)");
    Helper::instance()->parseCommand("FACT Mother(Nancy,Margret)");
    Helper::instance()->parseCommand("INFERENCE GrandMother($X,$Y)");

    
    
   


    
}
