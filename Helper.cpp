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
    
    if(!h_instance) // same as if(h_instance == NULL)
        h_instance = new Helper; // create a new object
    return h_instance;
} // this allows only ONE object to be created of this class

// ===================================================================================
// Parse Command
// ===================================================================================
// 	Used to retrieve a Fact or Rule
//
//
//
//
//
// ===================================================================================
void Helper::parseCommand(string user_input)
{
    //string dump_string = "Dump";
    stringstream line(user_input);  //takes the contents of user_input and copies it to a string object
    // "Fact Father(Rodger, John)
    //cout << line << endl;
    string rule_check = ":"; //creates a string with : to see if a rule is being inputted.
    
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
// Parse Definition
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

// ===================================================================================
// Parse Params
// ===================================================================================
//
//
//
//
//
//
// ==================================================================================

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

// ===================================================================================
// Parse Rule
// ===================================================================================
//
//
//
//
//
//
// ==================================================================================

vector<string> Helper:: parseRule(string input)
{
    vector<string> param;
    string delimiter = ":-";
    size_t pos = input.find(delimiter);
    pos++; // eats up delimiter :
    pos++; // eats up delimiter -
    
    int count = 1;
    delimiter = " ";
    pos++; // eats up delimiter ' '(space)
    
    
    string parsedInput = input.substr(pos, input.length());
    
    while ((pos = parsedInput.find(delimiter)) != string::npos)  // will loop through as many parameters except the last one
    {
        param.push_back(parsedInput.substr(0, pos));
        cout << "Parameter(" << count++ << "): " << param[param.size()-1] << endl;
        pos++; // eats delimiter
        parsedInput = parsedInput.substr(pos, input.length());
    }
    
    delimiter = "\n";
    pos = parsedInput.find(delimiter);
    param.push_back(parsedInput.substr(0, pos));
    cout << "Parameter(" << count << "): " << param[param.size()-1] << endl;
    return param;
}

// ===================================================================================
// Parse Definition
// ===================================================================================
//
//
//
//
//
//
// ==================================================================================

void Helper:: parseDefinition(char function, string def)
{
    
    if (function=='f' || function=='i')
    {
        string key = parseKey(def);
        cout << "Key: " << key << endl;
        vector<string> parameters = parseParams(def);
        
        
        if(function=='f')
            storeBase(tCommands->getFact(), parameters, key);
        else if(function=='i')
        {
//           vector<string> blah = retrieveRule(parameters,key);
            
            retrieveRule(parameters,key);
        }
    }
    else if (function=='r') // for rule
    {
        
        string key = parseKey(def);
        cout << "Key: " << key << endl;
        //        vector<string> keyParams = parseParams(def); unused may need later
        
        vector<string> params2 = parseRule(def);
        storeBase(tCommands->getRule(), params2, key);
    }
    
    cout << endl;
    
}



// ===================================================================================
// StoreBase
// ===================================================================================
//
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
// Retrieve Fact
// ===================================================================================
// 	Used to retrieve a Fact
//
//
//
//
//
// ===================================================================================
vector<vector<string>> Helper:: retrieveFact(string key, string &param1, string &param2)
{
    vector<string> params;
    vector<vector<string>> relationalData;
    cout << key << " Fact: ";
    char a;
    char b;
    // & in [] of lambda functions allows lambda function to acess local variables
    for_each(tCommands->getFact().begin(), tCommands->getFact().end(),[&](decltype(*tCommands->getFact().begin()) it) -> void // iterates through vector
             {
                 if (get<0>(it) == key) // checks tuple if key matches
                 {
                     a=param1[0];
                     b=param2[0];
                     if (param1[0] == '$' && param2[0] == '$') // if query is generic
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
                     else if (param1[0] != '$' && param2[0] == '$') // if the first parameter is specific
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
                         
                         if(param1.compare(params[0]) == 0)
                             relationalData.push_back(params);
                         params.clear();
                     }
                     else if (param1[0] == '$' && param2[0] != '$') // if the second parameters is specific
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
                         if(param2.compare(params[1]) == 0)
                             relationalData.push_back(params);
                         params.clear();
                     }
                 }
             });
    cout << endl;
    
    return relationalData;
}

// ===================================================================================
// Retrieve Rule
// ===================================================================================
// 	Used to retrieve a Rule
//
//
//
//
//
// ===================================================================================

vector<string> Helper:: retrieveRule(vector<string> params, string key)
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
                         if (i==0)
                         {
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
    
    vector<string> nothing;
    if(logicalOperater=="AND")
        return andOperator(key, params, query);
    else if (logicalOperater=="OR")
        orOperator(key, params, query);
    return nothing;
}

// ===================================================================================
// AND Base
// ===================================================================================
//
//
//
//
//
//
// ===================================================================================

vector<string> Helper:: andOperator(string key, vector<string> keyParams, vector<string> query)
{
    vector<vector<string>> paramData; // holds parameters from each individual querey ie. Mother($x,$z) Mother($z,$y)
    vector<bool> paramCheck;
    vector<tuple<int,int,int,int>> paramIndex; // tuple<vectorIndex1,param,vectorIndex2,param>
    vector<string> inferData; // holds the data to be returned
    
    
    for(int i=0; i < query.size(); i++)
        paramData.push_back(parseParams(query[i]));
    
     vector<vector<string>> factData = retrieveFact(parseKey(query[0]),paramData[0][0],paramData[0][1]); // holds data from fact from each individual query in rule ie. Grandmother():- Mother() Mother()
    //this variable pulls the facts for the first rule target only; the preceding rule target may used the first rule target which will be handeled later
    
    // check parameters for correlation between rule targets
    for(int i=0; i < paramData.size()-1; i++) // controls the leftmost rule target  Mother($x,$z)<-leftmost Mother($z,$y)
        for(int param = 0; param < paramData[i].size(); param++) // iterates the leftmost rule target parameters
                for(int j=0; j < paramData[i+1].size(); j++) // iterates rule target paremeters to the right of leftmost
                {
                    string a = paramData[i][param]; // used for testing
                    string b = paramData[i+1][j]; // used for testing
                    if (paramData[i][param].compare(paramData[i+1][j]) == 0) // checks to see if param match
                    {
                        paramCheck.push_back(true);
                        paramIndex.push_back(make_tuple(i,param,i+1,j)); // records index of the leftmost rule target and its param and the compared rule target index and its param
                    }
                    
                }
    
    // grabs data from Fact based on parameters
    if (paramCheck.size() != paramData[0].size()) // checks to see if all parameters match, if they dont proceed
    {
        vector<vector<string>> relationalData = retrieveFact(parseKey(query[1]), factData[get<0>(paramIndex[0])][get<1>(paramIndex[0])], paramData[1][1]); // there should only be one vector contained so use index 0 to pull index to vector that has data
        cout << endl << key << " Inference: ";
        
        // this is where the logical operator logic happens
        vector<string> match;
        // loop through vectors one by one finding if theres a match if theres not then that means thats the data we want
        for(int i=0; i < factData.size(); i++) // iterates through vector
            for(int param = 0; param < factData[i].size(); param++) // iterate throguh vector's data
                for(int j=0; j < paramData[i].size(); j++) // iterate through inferData
                {
                    // this code looks at parameter at a time comparing it to the results of inferData
                    // if the current parameter matches inferData then we dont want it ie. GrandMother($X,$Y):- Mother($X,$Z) Mother($Z,$Y)
                    // we dont want the $Z parameter so this code will leave you with $X, $Y
                    // the data only prints for now; and needs to be made more generic ie. nothing hard coded
                    if (factData[i][param].compare(relationalData[0][j]) == 0)
                    {
                        match.push_back(relationalData[0][j]);
                        break;
                    }
                    if (j == paramData[i].size()-1)
                    {
                        cout << factData[i][param] << " ";
                        inferData.push_back(factData[i][param]);
                    }
                }
        
        
        for(auto v: relationalData) // loops through vector: v is the actual vector
            for(int i=0; i<v.size(); i++) // loops through data in vector
            { // doing it this way eliminate v[x][i]; just another way of looping
                if (match[i].compare(v[i]) != 0)
                {
                    cout << v[i] << " ";
                    inferData.push_back(v[i]);

                }
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
    return inferData;
    
}

// ===================================================================================
// OR Base
// ===================================================================================
//
//
//
//
//
//
// ===================================================================================
void Helper:: orOperator(string key, vector<string> keyParams, vector<string> query)
{
//    vector<vector<string>> paramData; // holds parameters from each individual querey ie. Mother($x,$z) Mother($z,$y)
//    vector<bool> paramCheck;
//    vector<tuple<int,int,int,int>> paramIndex; // tuple<vectorIndex1,param,vectorIndex2,param>
//    
//    vector<vector<string>> relationalData;
//    for(int i=0; i < query.size(); i++)
//    {
//        paramData.push_back(parseParams(query[i]));
//        relationalData = retrieveFact(parseKey(query[i]),paramData[i][0],paramData[i][1]); // holds data from fact from each individual query in rule ie. Grandmother():- Mother() Mother()
//    }
//    
//    
//    // check parameters for correlation between rule targets
//    
//    for(int i=0; i < paramData.size()-1; i++) // controls the leftmost rule target  Mother($x,$z)<-leftmost Mother($z,$y)
//        for(int param = 0; param < paramData[i].size(); param++) // iterates the leftmost rule target parameters
//            for(int param = 0; param < paramData[i].size(); param++)
//                for(int j=0; j < paramData[i+1].size(); j++) // iterates rule target paremeters to the right of leftmost
//                {
//                    string a = paramData[i][param]; // used for testing
//                    string b = paramData[i+1][j]; // used for testing
//                    if (paramData[i][param].compare(paramData[i+1][j]) == 0) // checks to see if param match
//                    {
//                        paramCheck.push_back(true);
//                        paramIndex.push_back(make_tuple(i,param,i+1,j)); // records index of the leftmost rule target and its param and the compared rule target index and its param
//                    }
//                    
//                }
//    
//    // grabs data from Fact based on parameters
//    if (paramCheck.size() != paramData[0].size()) // checks to see if all parameters match, if they dont proceed
//    {
//        vector<vector<string>> inferData = retrieveFact(parseKey(query[1]), relationalData[get<0>(paramIndex[0])][get<1>(paramIndex[0])], paramData[1][1]); // there should only be one vector contained so use index 0 to pull index to vector that has data
//        cout << endl << key << " Inference: ";
//        
//        // this is where the logical operator logic happens
//        vector<string> match;
//        // loop through vectors one by one finding if theres a match if theres not then that means thats the data we want
//        for(int i=0; i < relationalData.size(); i++) // iterates through vector
//            for(int param = 0; param < relationalData[i].size(); param++) // iterate throguh vector's data
//                for(int j=0; j < paramData[i].size(); j++) // iterate through inferData
//                {
//                    // this code looks at parameter at a time comparing it to the results of inferData
//                    // if the current parameter matches inferData then we dont want it ie. GrandMother($X,$Y):- Mother($X,$Z) Mother($Z,$Y)
//                    // we dont want the $Z parameter so this code will leave you with $X, $Y
//                    // the data only prints for now; and needs to be made more generic ie. nothing hard coded
//                    if (relationalData[i][param].compare(inferData[0][j]) == 0)
//                    {
//                        match.push_back(inferData[0][j]);
//                        break;
//                    }
//                    if (j == paramData[i].size()-1)
//                        cout << relationalData[i][param] << " ";
//                }
//        
//        
//        for(auto v: inferData) // loops through vector: v is the actual vector
//            for(int i=0; i<v.size(); i++) // loops through data in vector
//            { // doing it this way eliminate v[x][i]; just another way of looping
//                if (match[i].compare(v[i]) != 0)
//                    cout << v[i] << " ";
//            }
//        cout << endl;
//    }
}


// ===================================================================================
// DumpHelp
// ===================================================================================
// 	Called from within the dump function of Transactional Commands.  Trying to handle
//  the dumping from within Transactional commands was not working; there would be an
//  error given you would try to call the fact vector from within dump function.  You cannot
//  a nonstatic vector from within the static dump funcion.  Making the fact vector static
//  and the getFact() function static would lead to having to create an object that would call
//  getFact() function.  Running this code would produce no errors until link time, in which
//  there would be a link error I would not entirely understand.  However, This fucntion
//  writes the contents of the fact vector to a file.  The format looks wrong on the file
//  preview, but is correct when you open the file all the way.
// ==================================================================================


//Only works for facts as of now
//Tip:  create a conditional that checks to see if the fact and rule vectors are empty.  If the vector is not empty output to a file, else do nothing.
void Helper:: DumpHelp(string path)
{
    
    const char* f = path.c_str();
    fstream file;
    file.exceptions ( fstream::failbit | fstream::badbit );
    vector<tuple<string,vector<string>>>& Factbase = tCommands->getFact();
    vector<tuple<string,vector<string>>>& Rulebase = tCommands->getRule();
    try
    {
        cout << "In the dump function" << endl;
        // open/create file
        file.open (f, ios::out);
        if(Factbase.size() != 0){
            for_each(Factbase.begin(), Factbase.end(),[&](decltype(*Factbase.begin()) it) -> void // iterates through vector
                     {
                         string temp = "FACT ";
                         temp.append(get<0>(it));
                         //cout << temp << endl;
                         temp.append("(");
                         //cout << temp << endl;
                         for(int i=0; i < get<1>(it).size(); i++)
                         {
                             if (i != get<1>(it).size()-1){
                                 temp.append(get<1>(it)[i]);
                                 temp.append(",");
                                 //cout << get<1>(it)[i] << ","; //prints out every parameter name except for last one
                             }else{
                                 temp.append(get<1>(it)[i]);
                                 temp.append(")");
                                 //cout << get<1>(it)[i] << endl; //prints out last parameter name
                             }
                         }
                         //                    for(auto i:  get<1>(it))
                         //                        cout << i << " ";
                         
                         //cout << temp << endl;
                         file << temp <<endl;
                     });
        } else {
            cout << "there are no facts to dump." << endl;
        }
        if(Rulebase.size() != 0){
            string logicalOperater;
            for_each(Rulebase.begin(), Rulebase.end(),[&](decltype(*Rulebase.begin()) it) -> void
                     {
                         string temp = "RULE ";
                         temp.append(get<0>(it));
                         cout << temp << endl;
                         temp.append("($X,$Y):- ");
                         cout << temp << endl;
                         for(int i=0; i < get<1>(it).size(); i++)
                         {
                             if (i==0){
                                 cout << "This is the logical operator " << get<1>(it)[i] << endl;
                                 logicalOperater = get<1>(it)[i]; // holds the operator
                                 temp.append(logicalOperater + " ");
                             } else if (i <= get<1>(it).size()-1){
                                 //cout << "What is this? " << get<1>(it)[i] << ", ";
                                 temp.append(get<1>(it)[i] + " ");
                                 cout << temp << endl;
                             }
                         }
                         
                         
                         file << temp << endl;
                     });
        }
        
        
        // open/create file
        // close file
        file.close();
    }
    catch (ifstream::failure e) {
        cerr << "Failed to dump file\n";
    }
    
}


void Helper:: LoadHelp(string path)
{
    cout << "in Load Help" << endl;
    const char* f = path.c_str();
    fstream file;
    // line
    string l;
    string fact_string = "FACT";
    string rule_string = "RULE";
    string inference_string = "INFERENCE";
    string drop_string = "DROP";
    string dump_string = "DUMP";
    file.exceptions ( fstream::badbit );
    try
    {
        // open file
        file.open (f, ios::in);
        while ( getline(file, l) )
        {
            cout << "right before string altering" << endl;
            cout << "this is l before alteration: " << l << endl;
            
            //this process is the same as ParseCommand; Later we will use the method instead.
            string delimeter = " ";
            size_t pos = 0;
            string command = "";
            pos = l.find(delimeter);
            command = l.substr(0, pos);
            l.erase(0, pos + delimeter.length());
            
            if(command.compare(fact_string) == 0){
                //Our string is in the example format: FACT Father(Rodger,John).
                //So we need to get the relation (Father) part of the string and set it to our key variable.
                string delimiter = "("; //Define space right after the relation (Father) ends.
                size_t pos2 = l.find("("); // Set the value of the
                string key = ""; // holds the key or fact name
                pos2 = l.find(delimiter); //set pos2 to the index where the ( is located in the string.
                key = parseKey(l); // saves the relaton part of the string as key, so it can be passed to storeBase later.
                cout << "this is l: " << l << endl;
                cout << "this is the key: " << key << endl;
                
                vector<string> parameters;
                
                //                l.erase(0, pos2 + delimiter.length()); // erases delimiter and any character before it
                //                delimiter = ",";
                //                while ((pos2 = l.find(delimiter)) != string::npos) { // will loop through as many parameters except the last one
                //                    parameters.push_back(l.substr(0, pos2));
                //                    l.erase(0, pos2 + delimiter.length());
                //                }
                //
                //                delimiter = ")";
                //                pos2 = l.find(delimiter);
                //                parameters.push_back(l.substr(0, pos2)); //push part of our string, string from the input file
                //                cout << "right before call to store Base." << endl;
                //                cout << l << endl;
                
                
                parameters = parseParams(l);
                storeBase(tCommands->getFact(), parameters, key);
                
            } else if (command.compare(rule_string) == 0) {
                string delimiter = "("; //Define space right after the relation (Father) ends.
                size_t pos2 = l.find("("); // Set the value of the
                string key = ""; // holds the key or fact name
                pos2 = l.find(delimiter); //set pos2 to the index where the ( is located in the string.
                key = parseKey(l); // saves the relaton part of the string as key, so it can be passed to storeBase later.
                cout << "this is l: " << l << endl;
                cout << "this is the key: " << key << endl;
                
                vector<string> params2 = parseRule(l);
                
                storeBase(tCommands->getRule(), params2, key);
                
            } else if (command.compare(inference_string) == 0) {
                //do the stuff for taking an inference out of a file.
                size_t ch = l.find(" ");
                ch++;
                string rest = l.substr (ch);
                tCommands->getMapCommand()[command](rest);
            } else if (command.compare(drop_string) == 0) {
                //do the stuff for taking a drop out of the file.
                size_t ch = l.find(" ");
                ch++;
                string rest = l.substr (ch);
                tCommands->getMapCommand()[command](rest);
            } else if (command.compare(dump_string) == 0){
                //do the stuff for taking a dump out of a file.
                size_t ch = l.find(" ");
                ch++;
                string rest = l.substr (ch);
                tCommands->getMapCommand()[command](rest);
            }
            
            //cout << l << endl;
        }
        // close file
        file.close();
    }
    catch ( fstream::failure e ) {
        cerr << "Failed to load file\n";
    }
    
}


void Helper::dropBase(string command)
{
    int count = 0; // iterates through the for loops
    vector<int> factIndex;
    for(vector<tuple<string,vector<string>>>::iterator i = tCommands->getFact().begin(); i != tCommands->getFact().end(); i++) // iterates through vector
    {
        cout << "count = " << count << endl;
        if ( command.compare(get<0>(*i)) == 0 )
        {
            cout << "deleting at j = " << count << endl;
            factIndex.push_back(count);
        }
        count++;
    }
    
    for(vector<int>::iterator i = factIndex.end() -1; i != factIndex.begin() - 1; i--)
    {
        cout << "index = " << *i << endl;
        count = *i;
        tCommands->getFact().erase(tCommands->getFact().begin() + count);
    }
    
    vector<int> ruleIndex;
    count = 0;
    for(vector<tuple<string,vector<string>>>::iterator i = tCommands->getRule().begin(); i != tCommands->getRule().end(); i++) // iterates through vector
    {
        cout << "count = " << count << endl;
        if ( command.compare(get<0>(*i)) == 0 )
        {
            cout << "deleting at j = " << count << endl;
            ruleIndex.push_back(count);
        }
        count++;
    }
    
    for(vector<int>::iterator i = ruleIndex.end() -1; i != ruleIndex.begin() - 1; i--)
    {
        cout << "index = " << *i << endl;
        count = *i;
        tCommands->getRule().erase(tCommands->getRule().begin() + count);
    }
}

void Helper:: ParseQuery(string rest){
    cout << "in Parse Query" << endl;
    string empty_string = "";
    string temp = "";
    size_t ch = rest.find(")"); // find the location of the space in our string
    temp = rest;
    ch++;
    rest.erase(0, ch);
    cout << "This is rest after the erase:" << rest << endl;
    if (rest.compare(empty_string) == 0){
        //call the inference part where we only need to print
        cout << "This is the basic inference case" << endl;
        size_t delim = temp.find("(");
        string key = temp.substr(0, delim);
        cout << "this is the key" << endl;
        cout << key << endl;
    } else {
        cout << "This is the other inference case" << endl;
        //there is an extra part of the string for inference.
        size_t space = rest.find(" ");
        space++;
        string key = rest.substr (space);
        cout << "This is the key" << endl;
        cout << key << endl;
    }
    //cout << ch << " This is the position of the space"
    cout << "this is the temp:" << endl;
    cout << temp << endl;
}






