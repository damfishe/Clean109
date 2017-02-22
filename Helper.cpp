#include "Helper.hpp"
#include "Transactional_Commands.hpp" // forward declaration


Helper* Helper:: h_instance = nullptr; // used to initialized pointer

Helper:: Helper()
{
    
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
Helper* Helper:: instance()
{
    
    if(!h_instance) // if(h_instance == NULL)
        h_instance = new Helper; // create a new object
    return h_instance;
} // this allows only ONE object to be created of this class


void Helper::parseCommand(string user_input)
{
    stringstream line(user_input);  //takes the contents of user_input and copies it to a string object
    // "Fact Father(Rodger, John)
    //cout << line << endl;
    string rule_check = ":"; //creates a string with : to see if a rule is being inputted.
    size_t colon_index = user_input.find(rule_check); //find the location of rule_check string in user_input
    
    
    string command = ""; //creating an empty string to hold the parsed out command
    getline(line, command,' ');  //take the contects of the input before the space (the command) and assign it to the command string.
    
    size_t ch = user_input.find(" ");  // find the location of the space in our string
    //    cout << ch << endl; //The index of the space in our stirng
    ch++; //increment size_t to account for the extra sapce.
    string rest = user_input.substr (ch);
    
    //prints out command and the rest of the string just for simplicity.
    cout << "The command is: " << command << endl;
    cout << "The contents are: " << rest << endl;
    
    
    if (colon_index==string::npos) //string::npos retruns -1, so if we did not find a : in the inputted sting by the user, colon_index will be -1 and we do not have a rule.
    {
        tCommands->getMapCommand()[command](rest); //calls the proper function in transactional commands
    }
    else
    {
//        cout << "This is a Rule" << endl;  //output to know we have a rule.
         tCommands->getMapCommand()[command](rest);
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

// ===================================================================================
// ParseDefinition
// ===================================================================================
// 	Used to parse rest of string passed from parseCommand
//
//
//
//
//
// ===================================================================================
void Helper:: parseDefinition(char function, string def)
{
    if (function=='f' | function=='i')
    {
        int count = 1;
        string delimiter = "(";
        size_t pos = 0; // position of delimiter
        string key = ""; // holds the key or fact name
        
        pos = def.find(delimiter);
        key = def.substr(0, pos); // assings string from given input up to delimiter
        def.erase(0, pos + delimiter.length()); // erases delimiter and any character before it
        cout << "Key: " << key << endl;
        
        
        vector<string> parameters;
        delimiter = ",";
        while ((pos = def.find(delimiter)) != string::npos) { // will loop through as many parameters except the last one
            parameters.push_back(def.substr(0, pos));
            cout << "Parameter(" << count++ << "): " << parameters[parameters.size()-1] << endl;
            def.erase(0, pos + delimiter.length());
        }
        
        delimiter = ")";
        pos = def.find(delimiter);
        parameters.push_back(def.substr(0, pos));
        cout << "Parameter(" << count << "): " << parameters[parameters.size()-1] << endl;
        
        if(function=='f')
            storeBase(tCommands->getFact(), parameters, key);
        else if(function=='i')
            retrieveBaseData(tCommands->getFact(), key);
    }
    else if (function=='r')
    {
        int count = 1;
        string delimiter = "(";
        size_t pos = 0; // position of delimiter
        string key = ""; // holds the key or fact name
        
        pos = def.find(delimiter);
        key = def.substr(0, pos); // assings string from given input up to delimiter
        def.erase(0, pos + delimiter.length()); // erases delimiter and any character before it
        cout << "Key: " << key << endl;
        
        
        vector<string> parameters;
        delimiter = ",";
        while ((pos = def.find(delimiter)) != string::npos) // will loop through as many parameters except the last one
        {
            parameters.push_back(def.substr(0, pos));
            cout << "Parameter(" << count++ << "): " << parameters[parameters.size()-1] << endl;
            def.erase(0, pos + delimiter.length());
//            cout << def << endl;
            if (def.at(2) == ')')
                break;
        }
        
        delimiter = ")";
        pos = def.find(delimiter);
        parameters.push_back(def.substr(0, pos));
        def.erase(0, pos + delimiter.length());
        cout << "Parameter(" << count << "): " << parameters[parameters.size()-1] << endl;
        
        delimiter = ":-";
        pos = def.find(delimiter);
        def.erase(0, pos + delimiter.length()); // eats up delimiter
//        cout << def << endl;
        
        count = 1;
        vector<string> parameters2;
        delimiter = " ";
        pos = def.find(delimiter);
        def.erase(0, pos + delimiter.length()); // eats up delimiter
        while ((pos = def.find(delimiter)) != string::npos)  // will loop through as many parameters except the last one
        {
            parameters.push_back(def.substr(0, pos));
            cout << "Parameter(" << count++ << "): " << parameters[parameters.size()-1] << endl;
            def.erase(0, pos + delimiter.length());
        }
        
        delimiter = "\n";
        pos = def.find(delimiter);
        parameters.push_back(def.substr(0, pos));
        def.erase(0, pos + delimiter.length());
        cout << "Parameter(" << count << "): " << parameters[parameters.size()-1] << endl;
        
        storeBase(tCommands->getFact(), parameters2, key);
    }
    
    cout << endl;
    
}



// ===================================================================================
// StoreBase
// ===================================================================================
// 	Used to store a Fact or Rule
//
//
//
//
//
// ==================================================================================
void Helper:: storeBase(vector<tuple<string,vector<string>>>& base, vector<string>& relation, string key)
{
    tuple<string,vector<string>> fact; // tuple that has a key(fact) and vector holding relationship
    get<0>(fact) = key;
    get<1>(fact) = relation;
    base.push_back(fact);
}

// ===================================================================================
// RetrieveBaseData
// ===================================================================================
// 	Used to retrieve a Fact or Rule
//
//
//
//
//
// ===================================================================================
void Helper:: retrieveBaseData(vector<tuple<string,vector<string>>>& base, string key)
{
    // used to retrive reoccuring key(fact)
    for_each(base.begin(), base.end(),[&key](decltype(*base.begin()) it) -> void // iterates through vector
             {
                 cout << key << ": ";
                 if (get<0>(it) == key)
                 {
                     for(int i=0; i < get<1>(it).size(); i++)
                     {
                         if (i != get<1>(it).size()-1)
                             cout << get<1>(it)[i] << ",";
                         else
                             cout << get<1>(it)[i] << endl;
                     }
                     //                    for(auto i:  get<1>(it))
                     //                        cout << i << " ";
                 }
             });
}
