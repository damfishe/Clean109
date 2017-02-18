#include "Helper.hpp"


Helper* Helper:: h_instance = nullptr; // used to initialized pointer

//Helper.cpp

Helper:: Helper(){
    
    tCommands = new Transactional_Commands;
}

Helper* Helper:: instance(){
    
    if(!h_instance)
        h_instance = new Helper;
    return h_instance;
}

void Helper::parse(string user_input)
{
    stringstream line(user_input);
    // "Fact Father(Rodger, John)
    
    string command = "";
    getline(line, command,' ');
    size_t ch = user_input.find(" ");
    ch++; //increment size_t to eat away the extra sapce.
    string rest = user_input.substr (ch);
//    cout << command << endl;
//    cout << rest << endl;
    
    tCommands->getMapCommand()[command](rest);
    
   
    
    
    // used for parsing Rule
//    stringstream line2(rest);
//    string command2 = "";
//    getline(line2, command2, ':'); //only one character for the third argurment.
//    size_t ch2 = rest.find(":");
//    ch2++;
//    ch2++;
//    ch2++;
//    string rest2 = rest.substr (ch2);
//    cout << command2 << endl;
//    cout << rest2 << endl;
    
    
    
    
    // if check to see if there is any character left if so then procceed

    
    
    
    
    
    
}
