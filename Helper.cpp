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
    
    tCommands->getMapCommand()[command](rest); //calls the proper function in transactional commands
    
    
    
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

string Helper:: parseKey(string &input)
{
    
    string delimiter = "(";
    size_t pos = 0; // position of delimiter
    string key = ""; // holds the key or fact name
    
    pos = input.find(delimiter);
    key = input.substr(0, pos); // assings string from given input up to delimiter
    //    input.erase(0, pos + delimiter.length()); // erases delimiter and any character before it
    
    return key;
    
}

vector<string> Helper:: parseParams(string &input)
{
    int count = 0;
    string delimiter = "(";
    string delimiter2 = ",";
    size_t pos = 0; // position of delimiter
    
    vector<string> parameters; // holds each parameter
    
    pos = input.find(delimiter); // find the
    
    string temp = input.substr(0, pos);
    cout << "Input key: " << input.substr(0, pos) << endl;
    pos++; // eats delimiter;
    
    string parsedInput = input.substr(pos, input.length());
    
    while ((pos = parsedInput.find(delimiter2)) != string::npos)  // will loop through as many parameters except the last one
    {
        parameters.push_back(parsedInput.substr(0, pos));
        cout << "Parameter(" << count++ << "): " << parameters[parameters.size()-1] << endl;
        //        input.erase(0, pos + delimiter.length());
        pos++; // eats delimiter
        parsedInput = parsedInput.substr(pos, input.length());
        
    }
    
    // if loop breaks theres always going to be one parameter left to store
    delimiter = ")";
    pos = parsedInput.find(delimiter);
    parameters.push_back(parsedInput.substr(0, pos));
    cout << "Parameter(" << count << "): " << parameters[parameters.size()-1] << endl;
    
    
    return parameters;
    
}

void Helper:: parseDefinition(char function, string def)
{
    if (function=='f' | function=='i')
    {
        string key = parseKey(def);
        cout << "Key: " << key << endl;
        vector<string> parameters = parseParams(def);
        
        
        if(function=='f')
            storeBase(tCommands->getFact(), parameters, key);
        else if(function=='i')
        {
            retrieveRule(parameters,key);
        }
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
        
        
        vector<string> params;
        delimiter = ",";
        while ((pos = def.find(delimiter)) != string::npos) // will loop through as many parameters except the last one
        {
            params.push_back(def.substr(0, pos));
            cout << "Parameter(" << count++ << "): " << params[params.size()-1] << endl;
            def.erase(0, pos + delimiter.length());
            //            cout << def << endl;
            if (def.at(2) == ')')
                break;
        }
        
        delimiter = ")";
        pos = def.find(delimiter);
        params.push_back(def.substr(0, pos));
        def.erase(0, pos + delimiter.length());
        cout << "Parameter(" << count << "): " << params[params.size()-1] << endl;
        
        delimiter = ":-";
        pos = def.find(delimiter);
        def.erase(0, pos + delimiter.length()); // eats up delimiter
        //        cout << def << endl;
        
        count = 1;
        vector<string> params2;
        delimiter = " ";
        pos = def.find(delimiter);
        def.erase(0, pos + delimiter.length()); // eats up delimiter
        while ((pos = def.find(delimiter)) != string::npos)  // will loop through as many parameters except the last one
        {
            params2.push_back(def.substr(0, pos));
            cout << "Parameter(" << count++ << "): " << params2[params2.size()-1] << endl;
            def.erase(0, pos + delimiter.length());
        }
        
        delimiter = "\n";
        pos = def.find(delimiter);
        params2.push_back(def.substr(0, pos));
        def.erase(0, pos + delimiter.length());
        cout << "Parameter(" << count << "): " << params2[params2.size()-1] << endl;
        
        storeBase(tCommands->getRule(), params2, key);
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
void Helper:: storeBase(vector< tuple< string,vector<string> > > &base, vector<string> &params, string key)
{
    tuple<string,vector<string>> fact; // tuple that has a key(fact) and vector holding relationship
    get<0>(fact) = key;
    get<1>(fact) = params;
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
vector<vector<string>> Helper:: retrieveFact(string key)
{
    vector<string> params;
    vector<vector<string>> relationalData;
     cout << key << " Fact: ";
    // & in [] of lambda functions allows lambda function to acess local variables
    for_each(tCommands->getFact().begin(), tCommands->getFact().end(),[&](decltype(*tCommands->getFact().begin()) it) -> void // iterates through vector
             {
                 if (get<0>(it) == key) // checks tuple if key matches
                 {
                     for(int i=0; i < get<1>(it).size(); i++) // iterates through vector inside tuple
                     {
                         if (i != get<1>(it).size()-1) // printing purpose: used to add commas
                         {
                             params.push_back(get<1>(it)[i]);
                             cout << get<1>(it)[i] << ","; // prints an index in vector
                         }
                         else
                         {
                             params.push_back(get<1>(it)[i]);
                             cout << get<1>(it)[i] << " | "; // prints an index in vector
                         }
                     }
                     //                    for(auto i:  get<1>(it))
                     //                        cout << i << " ";
                     relationalData.push_back(params);
                     params.clear();
                 }
             });
    
    return relationalData;
}

void Helper:: retrieveRule(vector<string> params, string key)
{
    vector<string> query;
    string logicalOperater;
    
    cout << key << " Rule" << ": ";
    // & in [] of lambda functions allows lambda function to acess local variables
    for_each(tCommands->getRule().begin(), tCommands->getRule().end(),[&](decltype(*tCommands->getRule().begin()) it) -> void // iterates through vector
             {
                 
                 if (get<0>(it) == key)
                 {
                     for(int i=0; i < get<1>(it).size(); i++)
                     {
                         if (i==0){
                             cout << get<1>(it)[i] << ", ";
                             logicalOperater = get<1>(it)[i]; // holds the operator
                             
                         }
                         else if(i <= get<1>(it).size()-2)
                         {
                             cout << get<1>(it)[i] << ", ";
                             decltype(get<1>(it)[i]) fact = get<1>(it)[i]; // variable holding a fact inside rule
                             // need to parse fact name from params
                             query.push_back(fact);
                             
                             //
                             //                             cout << "Inference call in retrive function" << endl;
                             //                             tCommands->inferenceCommand(fact);
                             
                             
                             // need a function that will grab parameters from fact in order to determine if its a genaric inference or specific
                             
                             // need a function to pass each part of the rule for processing
                             
                             
                             
                             
                         }
                         else
                         {
                             
                             cout << get<1>(it)[i] << endl;
                             decltype(get<1>(it)[i]) fact = get<1>(it)[i]; // variable holding a fact inside rule
                             // need to parse fact name from params
                             query.push_back(fact);
                         }
                     }
                     //                    for(auto i:  get<1>(it))
                     //                        cout << i << " ";
                 }
             });
    
    if(logicalOperater=="AND")
        andBase(query, key);
    else if (logicalOperater=="OR")
        orBase(query, key);
}

void Helper:: andBase(vector<string> query, string key)
{
    
    vector<vector<string>> relationalData = retrieveFact(parseKey(query[0])); // holds data from fact from each individual query in rule ie. Grandmother():- Mother() Mother()
    vector<vector<string>> paramData; // holds parameters from each individual querey ie. Mother($x,$z) Mother($z,$y)
    
    for(int i=0; i < query.size(); i++)
            paramData.push_back(parseParams(query[i]));
    
    for(int i=0; i < relationalData.size(); i++) // the size of vectors are be the same
    { //
         for(int j=0; j < paramData.size(); j++) // the size of vectors are the same
         {
             relationalData[i][j]; paramData[i][j];
         }
    }
    
    
    //    for(int i=0; i < query.size(); i++)
    //    temp.push_back(retrieveFact(parseKey(query[0])));
    
    
    
    
    
    
    //    for(int i=0; i < temp.size(); i++)
    //    {
    //        for(int j=0; j < query.size(); j++){
    //
    //            temp[i][j]
    //
    //        }
    //    }
    
//    for_each(temp.begin(), temp.end(),[&](decltype(*temp.begin()) array) -> void // iterates through vector
//             {
//                 for_each(array.begin(), array.end(),[&](decltype(*array.begin()) data) -> void // iterates through vector
//                          {
//                              cout << "AND: " << data << endl;
//                              
//                          });
//                 
//             });
//    
    cout << endl;
    
}

void Helper:: orBase(vector<string> query, string key)
{
    
}
