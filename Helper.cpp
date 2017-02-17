#include "Helper.hpp"



void Helper::parse(string user_input)
{
    stringstream line(user_input);
    // "Fact Father(Rodger, John)
    
    string command = "";
    getline(line, command, ' ');
    size_t ch = user_input.find(" ");
    ch++; //increment size_t to eat away the extra sapce.
    string rest = user_input.substr (ch);
    cout << command << endl;
    cout << rest << endl;
    
    stringstream line2(rest);
    string command2 = "";
    getline(line2, command2, ':'); //only one character for the third argurment.
    size_t ch2 = rest.find(":");
    ch2++;
    ch2++;
    ch2++;
    string rest2 = rest.substr (ch2);
    cout << command2 << endl;
    cout << rest2 << endl;
    
    
    
    
    // if check to see if there is any character left if so then procceed

    
    
    
    
    
    
}
