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
        
        if(function=='f'){
            storeBase(tCommands->getFact(), parameters, key);
            //string fact_string = "FACT";
           // tCommands->dumpCommand1(tCommands->getFact(), fact_string, key);
            
            
        }else if(function=='i')
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
            parameters2.push_back(def.substr(0, pos));
            cout << "Parameter(" << count++ << "): " << parameters[parameters2.size()-1] << endl;
            def.erase(0, pos + delimiter.length());
        }
        
        delimiter = "\n";
        pos = def.find(delimiter);
        parameters2.push_back(def.substr(0, pos));
        def.erase(0, pos + delimiter.length());
        cout << "Parameter(" << count << "): " << parameters2[parameters2.size()-1] << endl;
        
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
void Helper:: storeBase(vector<tuple<string,vector<string>>>& base, vector<string>& parameters, string key)
{
    tuple<string,vector<string>> fact; // tuple that has a key(fact) and vector holding relationship
    get<0>(fact) = key;
    get<1>(fact) = parameters;
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
    cout << "Kory Sucks" << endl;
    // used to retrive reoccuring key(fact)
    for_each(base.begin(), base.end(),[&](decltype(*base.begin()) it) -> void // iterates through vector
             {
                 cout << key << ": ";
                 if (get<0>(it) == key)
                 {
                     for(int i=0; i < get<1>(it).size(); i++)
                     {
                         if (i != get<1>(it).size()-1)
                             cout << get<1>(it)[i] << ","; //prints out every parameter name except for last one
                         else
                             cout << get<1>(it)[i] << endl; //prints out last parameter name
                     }
                     //                    for(auto i:  get<1>(it))
                     //                        cout << i << " ";
                 }
             });
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
    vector<tuple<string,vector<string>>>& base = tCommands->getFact();
    try
    {
        cout << "In the dump function" << endl;
        // open/create file
        file.open (f, ios::out);
        
        
                for_each(base.begin(), base.end(),[&](decltype(*base.begin()) it) -> void // iterates through vector
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
    file.exceptions ( fstream::badbit );
    try
    {
        // open file
        file.open (f, ios::in);
        while ( getline(file, l) )
        {
            cout << "right before string altering" << endl;
            cout << l << endl;
            stringstream line(l);
            string command = "";
            getline(line, command,' ');
            if(command.compare(fact_string) == 0){
                //Our string is in the format example format: FACT Father(Rodger,John).
                //So we need to get the relation (Father) part of the string and set it to our key variable.
                string delimiter = "("; //Define space right after the relation (Father) ends.
                size_t pos2 = l.find("("); // Set the value of the
                string key = ""; // holds the key or fact name
                size_t pos1 = l.find(" "); // finds the index of the string where the " " is located.
                pos1++; //increment over the space to right before the relation.
                pos2 = l.find(delimiter); //set pos2 to the index where the ( is located in the string.
                key = l.substr(pos1, pos2); // saves the relaton part of the string as key, so it can be passed to storeBase later.
                cout << "this is the key: " << key << endl;
                l.erase(0, pos2 + delimiter.length()); // erases delimiter and any character before it
                vector<string> parameters;
                delimiter = ",";
                while ((pos2 = l.find(delimiter)) != string::npos) { // will loop through as many parameters except the last one
                    parameters.push_back(l.substr(0, pos2));
                    l.erase(0, pos2 + delimiter.length());
                }
                
                delimiter = ")";
                pos2 = l.find(delimiter);
                parameters.push_back(l.substr(0, pos2)); //push part of our string, string from the input file
                cout << "right before call to store Base." << endl;
                cout << l << endl;
                storeBase(tCommands->getFact(), parameters, key);
                
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









