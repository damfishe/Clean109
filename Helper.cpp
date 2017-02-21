#include "Helper.hpp"


Helper* Helper:: h_instance = nullptr; // used to initialized pointer

//Helper.cpp

Helper:: Helper(){
    
    tCommands = new Transactional_Commands;
}

// ===================================================================================
// Instance
// ===================================================================================
// 	Used to access functionality of Helper class. Allows only one instance(object) to be
//  created
//
//  if theres not an object type Helper created
//	else return the object
//
// ===================================================================================

Helper* Helper:: instance(){
    
    if(!h_instance) // if(h_instance == NULL)
        h_instance = new Helper; // create a new object
    return h_instance;
} // this allows only ONE object to be created of this class

void Helper::parse(string user_input)
{
    stringstream line(user_input);  //takes the contents of user_input and copies it to a string object
    // "Fact Father(Rodger, John)
    //cout << line << endl;
    string rule_check = ":"; //creates a string with : to see if a rule is being inputted.
    size_t colon_index = user_input.find(rule_check); //find the location of rule_check string in user_input
    
    
    string command = ""; //creating an empty string to hold the parsed out command
    getline(line, command,' ');  //take the contects of the input before the space (the command) and assign it to the command string.
    
    size_t ch = user_input.find(" ");  // find the location of the space in our string
    cout << ch << endl; //The index of the space in our stirng
    ch++; //increment size_t to account for the extra sapce.
    string rest = user_input.substr (ch);
    
    //prints out command and the rest of the string just for simplicity.
    cout << "The command is: " << command << endl;
    cout << "The contents are: " << rest << endl;
    
    
    if (colon_index==string::npos){ //string::npos retruns -1, so if we did not find a : in the inputted sting by the user, colon_index will be -1 and we do not have a rule.
    tCommands->getMapCommand()[command](rest); //calls the proper function in transactional commands
    } else {
        cout << "This is a Rule" << endl;  //output to know we have a rule.
    }
   
    
    
// used for parsing Rule
//    stringstream line2(rest);
//    string command2 = "";
//    getline(line2, command2, ':'); //only one character for the third argument.
//    size_t ch2 = rest.find(":");
//    ch2++;  //incrementing the size_t account for the three extra characters; ":", "-", and " ".
//    ch2++;
//    ch2++;
//    string rest2 = rest.substr (ch2);
//    cout << command2 << endl;
//    cout << rest2 << endl;
    
    
    
    
    // if check to see if there is any character left if so then procceed

    
    
    
    
    
    
}
