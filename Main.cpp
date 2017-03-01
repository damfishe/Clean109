//Main.cpp

#include "Common.hpp"
#include "Interface.hpp"
#include "Transactional_Commands.hpp"

int main() {
    
    Interface i;
    
    Transactional_Commands t;
    //Tester for the dump command
    t.loadCommand("output.txt");
    
    i.run();
    t.dumpCommand("output2.txt");
    
//    vector<tuple<string,vector<string>>> v; // vector that holds a tuple
//   
//    // ===================================================
//    // Process to store relational data
//    tuple<string,vector<string>> a; // tuple that has a key(fact) and vector holding relationship
//    vector<string> b;
//    
//    get<0>(a) = "Father";
//    b.push_back("Roger");
//    b.push_back("John");
//    
//    get<1>(a) = b;
//    v.push_back(a);
//    
//    // ===================================================
//    
//    tuple<string,vector<string>> a1;
//    vector<string> b1;
//    
//    get<0>(a1) = "Father";
//    b1.push_back("Roger");
//    b1.push_back("Albert");
//    
//    get<1>(a1) = b1;
//    v.push_back(a1);
//    
//    // ===================================================
//    // Process to retrive relational data
//    for_each(v.begin(), v.end(),[](decltype(*v.begin()) it) -> void // used to retrive reoccuring key(fact)
//    {
//        if (get<0>(it) == "Father")
//        {
//                for(auto i:  get<1>(it))
//                    cout << i << endl;
//        }
//    });
//    // ===================================================

    
    return 0;
}
