#include "Helper.hpp"
#include "Transactional_Commands.hpp" // forward declaration


Helper* Helper:: h_instance = nullptr; // used to initialized pointer

Helper:: Helper()
{
    
    tCommands = new Transactional_Commands;
}

Helper:: ~Helper()
{
    
    delete tCommands;
}

// ===================================================================================
// Instance
// ===================================================================================
// 	Used to access functionality of Helper class. Allows only one instance(object) to 
//  be created.
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
}

// ===================================================================================
// Parse Key
// ===================================================================================
// 	Used to parse rest of string passed from parseCommand and other functions.
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
    //char acts as a tag for our function so that def can go through the proper conditional branch.
    // def represents the entire string without the command.  Example being Father(Roger, John)
    if (function=='f') //
    {
        string key = parseKey(def); //parse the key part of def.  Example being Father.
        cout << "Key: " << key << endl;
        vector<string> parameters = parseParams(def); //obtain the perameters of our string.  Example being (Roger, John).
        
        
        storeBase(tCommands->getFact(), parameters, key); //send the parameters and the key to be sto
    }
    else if (function=='r') // if our tagged string is a rule
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
// RetrieveFact
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

tuple<string,string,vector<string>,vector<vector<string>>> Helper:: retrieveRule(vector<string> params, string key)
{
    vector<vector<string>> rule;
    vector<string> ruleTemp;
    string logicalOp;
    
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
                             logicalOp = get<1>(it)[i]; // holds the operator
                             
                         }
                         else if(i <= get<1>(it).size()-2)
                         {
                             cout << get<1>(it)[i] << ", ";
                             decltype(get<1>(it)[i]) fact = get<1>(it)[i]; // variable holding a fact inside rule
                             // need to parse fact name from params
                             ruleTemp.push_back(fact);
                             
                             // need a function that will grab parameters from fact in order to determine if its a genaric inference or specific
                             
                             // need a function to pass each part of the rule for processing
                             
                         }
                         else
                         {
                             
                             cout << get<1>(it)[i] << endl;
                             decltype(get<1>(it)[i]) fact = get<1>(it)[i]; // variable holding a fact inside rule
                             // need to parse fact name from params
                             ruleTemp.push_back(fact);
                             
                             rule.push_back(ruleTemp);
                             ruleTemp.clear();
                         }
                     }
                 }
             });
    return make_tuple(logicalOp, key, params,rule);
}

// ===================================================================================
//  op
// ===================================================================================
//  Calls the "andOperator" or "orOperator" depending on the condition. 
//
//  Created so that we can recursively call the 'and' and 'or' rules.
//
//
//
// ===================================================================================

vector<vector<vector<string>>> Helper:: op(string logicalOp, string key,vector<string> keyParams,vector<vector<string>> rule)
{
    vector<vector<vector<string>>> data;
    for(int i=0; i < rule.size(); i++)
    {
        if(logicalOp=="AND")
            data.push_back(andOperator(key, keyParams, rule[i]));
        else if (logicalOp=="OR")
            data.push_back(orOperator(key, keyParams, rule[i]));
    }
    return data;
}

// ===================================================================================
//  vectorCondense
// ===================================================================================
//  Condenses the vector from a vector<vector<vector<string>>> to a 
//  vector<vector<string>> for 'andOperator' and 'orOperator' return types.
//
//
//
// ===================================================================================

vector<vector<string>> Helper:: vectorCondense(vector<vector<vector<string>>> v)
{
    vector<vector<string>> result;
    for(int i = 0; i < v.size(); i++)
    {
        for(int param = 0; param < v[i].size(); param++)
        {
            result.push_back(v[i][param]);
        }
    }
    
    return result;
}

// ===================================================================================
//  singleVecCondense
// ===================================================================================
//  Condenses the vector from a vector<vector<string>> to a 
//  vector<string> for parseQuery method.
//
//
//
// ===================================================================================

vector<string> Helper:: singleVecCondense(vector<vector<string>> v)
{
    vector<string> result;
    for(int i = 0; i < v.size(); i++)
    {
        for(int param = 0; param < v[i].size(); param++)
        {
            result.push_back(v[i][param]);
        }
    }
    
    return result;
}

// ===================================================================================
// AND Operator
// ===================================================================================
//
//
//
//
//
//
// ===================================================================================

vector<vector<string>> Helper:: andOperator(string key, vector<string> keyParams, vector<string> rule)
{
    vector<vector<string>> paramData; // holds parameters from each individual querey ie. Mother($x,$z) Mother($z,$y)
    vector<bool> paramCheck;
    vector<tuple<int,int,int,int>> paramIndex; // tuple<vectorIndex1,param,vectorIndex2,param>
    vector<vector<string>> inferData; // holds the data to be returned
    
    for(int i=0; i < rule.size(); i++)
        paramData.push_back(parseParams(rule[i]));
    
    vector<vector<string>> temp;
    vector<vector<string>> factData;
    
    auto tempTup = retrieveRule(keyParams, parseKey(rule[0]));
    if((temp = get<3>(tempTup)).size() == 0) // if rule is not defined
    {
//         holds data from fact from left parememter
                if (paramData[0][0] == keyParams[0] && paramData[0][1] == keyParams[1]) // both parameters are generic
                {
                    factData = retrieveFact(parseKey(rule[0]),paramData[0][0],paramData[0][1]);
                }
                else  if (paramData[0][0] != keyParams[0] && paramData[0][1] == keyParams[1]) // the left parameter is specific
                {
                     factData = retrieveFact(parseKey(rule[0]),keyParams[0],paramData[0][1]);
                }
                else  if (paramData[0][0] == keyParams[0] && paramData[0][1] != keyParams[1]) // the right paremeter is specific
                {
                  factData = retrieveFact(parseKey(rule[0]), paramData[0][0],keyParams[1]);
                }
    }
    else // if rule is defined
    {
//        holds data from fact from left parememter
        if (paramData[0][0] == keyParams[0] && paramData[0][1] == keyParams[1]) // both parameters are generic
        {
            auto temp = op(get<0>(tempTup), get<1>(tempTup), get<2>(tempTup), get<3>(tempTup));
            factData = vectorCondense(temp);
        }
        else  if (paramData[0][0] != keyParams[0] && paramData[0][1] == keyParams[1]) // the left parameter is specific
        {
            vector<string> param;
            param.push_back(keyParams[0]);
            param.push_back(paramData[0][1]);
            auto temp = op(get<0>(tempTup), get<1>(tempTup), param, get<3>(tempTup));
            factData = vectorCondense(temp);        }
        else  if (paramData[0][0] == keyParams[0] && paramData[0][1] != keyParams[1]) // the right paremeter is specific
        {
            vector<string> param;
            param.push_back(paramData[0][0]);
            param.push_back(keyParams[1]);
            auto temp = op(get<0>(tempTup), get<1>(tempTup), param, get<3>(tempTup));
            factData = vectorCondense(temp);
        }
    }
    
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
        // this holds the corelation fact data from the rule target based on parameters
        vector<vector<vector<string>>> relationalData;
        vector<vector<string>> match;
        
        for (int i=0; i<factData.size(); i++)
        {
            tempTup = retrieveRule(keyParams, parseKey(rule[1]));
            if((temp = get<3>(tempTup)).size() == 0) // if rule is not defined
            {
                // there should only be one vector contained so use index 0 to pull index to vector that has data
                // this pulls the data based on the correlation between rule targetfrom fact from each individual query in rule ie. Grandmother():- Mother() Mother()
                relationalData.push_back(retrieveFact(parseKey(rule[1]), factData[i][get<1>(paramIndex[0])], paramData[1][1]));
            }
            else // if rule is defined
            {
                relationalData = op(get<0>(tempTup), get<1>(tempTup), get<2>(tempTup), get<3>(tempTup));
                break;
            }
        }
        // this is where the logical operator logic happens
        for(int i=0; i < relationalData.size(); i++) // iterates through data that has been returned from correlations of rule target
        { // used to iterate through relationalData and factData; there size is ALWAYS going to be equal
            if(relationalData[i].size() != 0) // if empty break
            {
                vector<string> matchTemp; // temporary holds matches of current iterated vector
                vector<string>inferDataTemp; // temporary holds inference data of current iterated vector
                
                // loop through vectors one by one finding if theres a match if theres not then that means thats the data we want
                for(int k = 0; k < relationalData[i].size(); k++)  // iterates through vectors inside of relationalData (vector<vector<string>)
                {
                    for(int j=0; j < relationalData[i][k].size(); j++) // iterates through vector's data inside of relationalData vector (string)
                    { // factData is the only variable using j index
                        for(int param = 0; param < paramData[j].size(); param++) // iterate through parameters (string)
                        {
                            // this code looks at parameter at a time comparing it to the results of inferData
                            // if the current parameter matches inferData then we dont want it ie. GrandMother($X,$Y):- Mother($X,$Z) Mother($Z,$Y)
                            // we dont want the $Z parameter so this code will leave you with $X, $Y
                            // the data only prints for now; and needs to be made more generic ie. nothing hard coded
                            if (factData[i][j].compare(relationalData[i][k][param]) == 0)
                            {
                                matchTemp.push_back(relationalData[i][k][param]);
                                break;
                            }
                            if (param == relationalData[i][k].size()-1)
                            {
                                inferDataTemp.push_back(factData[i][j]);
                            }
                        }// end for
                    }// end for
                    
                    match.push_back(matchTemp);
                    inferData.push_back(inferDataTemp);
                    matchTemp.clear();
                    inferDataTemp.clear();
                }// end for
                
            } // end if
        }// end for
        // at the end of for loop match will have all the matching data to be eliminated from saved vector to be returned
        
        // looks for duplicates and only output the correlated data
        for(auto v: relationalData) // loops through outer vector: v is the actual vector
            for(int i=0; i<v.size(); i++)  // loops through inner vector: vv is the actual vector
                for(int k=0; k < match[i].size(); k++) // iterates through match's inner vector
                    for(int j=0; j<v[i].size(); j++) // loops through data in relationalData
                    { // doing it this way eliminate v[x][i]; just another way of looping
                        if (match[i][k].compare(v[i][j]) != 0)
                        {
                            inferData[i].push_back(v[i][j]);
                            
                        }
                    }
    }// end if
    cout << endl << endl;
    return inferData;
    
}

// ===================================================================================
// OR Operator
// ===================================================================================
//
//
//
//
//
//
// ===================================================================================

vector<vector<string>> Helper:: orOperator(string key, vector<string> keyParams, vector<string> query)
{
    
    vector<vector<string>> paramData; // holds parameters from each individual querey ie. Mother($x,$z) Mother($z,$y)
    vector<bool> paramCheck;
    vector<tuple<int,int,int,int>> paramIndex; // tuple<vectorIndex1,param,vectorIndex2,param>
    vector<vector<string>> result;
    
    vector<vector<vector<string>>> relationalData;
    for(int i=0; i < query.size(); i++)
    {
        paramData.push_back(parseParams(query[i]));
        if (paramData[i][0] == keyParams[0] && paramData[i][1] == keyParams[1]) // both parameters are generic
        relationalData.push_back(retrieveFact(parseKey(query[i]),paramData[i][0],paramData[i][1])); // holds data from fact from each individual query in rule ie. Parent():- Father() Mother()
        else  if (paramData[i][0] != keyParams[0] && paramData[i][1] == keyParams[1]) // the left parameter is specific
            relationalData.push_back(retrieveFact(parseKey(query[i]),keyParams[0],paramData[i][1])); // holds data from fact from each individual query in rule ie. GParent():- Father() Mother()
        else  if (paramData[i][0] == keyParams[0] && paramData[i][1] != keyParams[1]) // the right paremeter is specific
            relationalData.push_back(retrieveFact(parseKey(query[i]),paramData[i][0],keyParams[1])); // holds data from fact from each individual query in rule ie. Parent():- Father() Mother()
    }
    
    
    // check parameters for correlation between rule targets
    for(int i=0; i < paramData.size()-1; i++) // controls the leftmost rule target  Mother($x,$z)<-leftmost Mother($z,$y)
        for(int param = 0; param < paramData[i].size(); param++) // iterates the leftmost rule target parameters
            for(int param = 0; param < paramData[i].size(); param++)
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
    // result.push_back(retrieveRule(keyParams, parseKey(query[j])));
    // grabs data from Fact based on parameters
    if (paramCheck.size() != paramData[0].size()) // checks to see if all parameters match, if they dont proceed
    {
        // this is where the logical operator logic happens
        vector<vector<vector<string>>> match;
        vector<vector<vector<string>>> tempResult;
        
        // loop through each query
        for(int i=0; i < query.size(); i++)
        { 
            tempResult.push_back(retrieveFact(parseKey(query[i]), keyParams[1], keyParams[1]));
            // example code of how to use the new return type of retrieveRule
            match.push_back(retrieveFact(parseKey(query[i]),keyParams[0],keyParams[1]));
        }
        result = vectorCondense(tempResult);
    }
    return result;
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
            for_each(Factbase.begin(), Factbase.end()-1,[&](decltype(*Factbase.begin()) it) -> void // iterates through vector
                     {
                         string temp = "FACT ";
                         temp.append(get<0>(it));
                         temp.append("(");
                         for(int i=0; i < get<1>(it).size(); i++)
                         {
                             if (i != get<1>(it).size()-1){
                                 temp.append(get<1>(it)[i]);
                                 temp.append(",");
                             }else{
                                 temp.append(get<1>(it)[i]);
                                 temp.append(")");
                             }
                         }
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
    cout << "How do you make this project in a week and a half?" << endl;
    try
    {
        // open file
        file.open (f, ios::in);
        cout << "Trying to open file" << endl;
        
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
        }
        // close file
        file.close();
    }
    catch ( fstream::failure e ) {
        cerr << "Failed to load file\n";
    }
    
}

// ===================================================================================
// dropBase
// ===================================================================================
//
//  dropBase drops the command from the fact or rule database
//
//
//
//
// ===================================================================================

void Helper::dropBase(string command)
{
    int count = 0;
    vector<int> factIndex;

    // first evaluates the fact database, deleting any instances of the command
    // find all indexes in the fact vector
    for(vector<tuple<string,vector<string>>>::iterator i = tCommands->getFact().begin(); i != tCommands->getFact().end(); i++) // iterates through vector
    {
        // look for target facts
        if ( command.compare(get<0>(*i)) == 0 )
        {
            factIndex.push_back(count);
        }
        count++;
    }
    
    // iterate backwards through the vector deleting instances of the fact from the fact vector
	for (int i = factIndex.size() - 1; i >= 0; --i)
    {
        count = factIndex[i];
        tCommands->getFact().erase(tCommands->getFact().begin() + count);
    }    
	
    // then evaluates the rule database, deleting any instances of the command
    vector<int> ruleIndex;
    count = 0;
    // find all indexes in the rule vector
    for(vector<tuple<string,vector<string>>>::iterator i = tCommands->getRule().begin(); i != tCommands->getRule().end(); i++) // iterates through vector
    {
        // look for target rules
        if ( command.compare(get<0>(*i)) == 0 )
        {
            ruleIndex.push_back(count);
        }
        count++;
    }
    // iterate backwards through the vector deleting instances of the rule from the rule vector
    for(int i = ruleIndex.size()-1; i>=0; --i)
    {
		count = ruleIndex[i];
        tCommands->getRule().erase(tCommands->getRule().begin() + count);
    }
	
}

// ===================================================================================
//  ParseQuery
// ===================================================================================
//
//  If the user specifies a name for a query, this function will deal with parsing and 
//  saving it.
//
//
//
// ===================================================================================

void Helper:: ParseQuery(string rest)
{
    vector<vector<string>> tempFacts;
    string key;
    cout << "in Parse Query" << endl;
    string empty_string = "";
    string temp = "";
    size_t ch = rest.find(")"); // find the location of the space in our string
    temp = rest;
    
    ch++;
    rest.erase(0, ch);
    vector<string> parameters;
    cout << "This is rest after the erase " << endl;
    if (rest.compare(empty_string) == 0){
        //call the inference part where we only need to print
        parameters = parseParams(temp);
        cout << "This is the basic inference case" << endl;
        key = parseKey(temp);
        cout << "this is the key: " << key << endl;
        auto opParams = retrieveRule(parameters,key);
        vector<vector<string>> rule = get<3>(opParams);
        
        if (rule.size() == 0)
            tempFacts = retrieveFact(key, get<2>(opParams)[0], get<2>(opParams)[1]);
        else
        tempFacts = vectorCondense(op(get<0>(opParams), get<1>(opParams), get<2>(opParams), get<3>(opParams)));
    } else {
        cout << "This is the other inference case" << endl;
        //there is an extra part of the string for inference.
        string key2 = parseKey(temp); //parses our full string saved in temp to get key2 as Grandmother.
        parameters = parseParams(temp);
        size_t space = rest.find(" ");
        space++;
        key = rest.substr (space); //Obtain the acronym (GF) as our key and save it for when we store the results in the fact vector.
        cout << "This is the key" << endl;
        cout << key << endl;
        
        auto opParams = retrieveRule(parameters,key2);
        vector<vector<string>> rule = get<3>(opParams);
        
        if (rule.size() == 0)
            tempFacts = retrieveFact(key, get<2>(opParams)[0], get<2>(opParams)[1]);
        else
            tempFacts = vectorCondense(op(get<0>(opParams), get<1>(opParams), get<2>(opParams), get<3>(opParams)));
    }
    //cout << ch << " This is the position of the space"
    
    //cout << temp << endl;
    
    vector<string> fact = singleVecCondense(tempFacts);
    storeBase(tCommands->getFact(), fact, key);
    
    cout << endl << key << " Inference: ";
    for(auto b: fact)
        cout << b << " ";
    cout << endl;
}






