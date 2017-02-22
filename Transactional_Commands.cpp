//Transactional_Commands.cpp

#include "Transactional_Commands.hpp"
#include "Helper.hpp" // foward declaration


Transactional_Commands:: Transactional_Commands(){
    
    commandMap["Fact"] = factCommand;
    commandMap["Rule"] = ruleCommand;
    commandMap["Drop"] = dropCommand;
    commandMap["Inference"] = inferenceCommand;
    commandMap["Load"] = loadCommand;
    commandMap["Dump"] = dumpCommand;
    
    cout << "Transactional Command initialized\n";

}

// ===================================================================================
// 	LOAD
// ===================================================================================
// 	Load facts and rules, into the KB and the RB respectively from a file. 
//
//	Input: 
//		path [IN] - string containing the filename given from the transactional
//			command.
//
// ===================================================================================

void Transactional_Commands:: loadCommand(string path){
    const char* f = path.c_str();
    fstream file;
    // line
    string l;
	file.exceptions ( fstream::failbit | fstream::badbit );
  	try 
  	{
  		// open file
	    file.open (f, ios::in);
	    while ( getline(file, l) )
    	{
    		cout << l << endl;
    	}
	    // close file
	    file.close();
  	}
  	catch ( fstream::failure e ) {
    	cerr << "Failed to load file\n";
  	}
}

// ===================================================================================
// 	DUMP
// ===================================================================================
//	Save the facts and rules saved in the runtime KB and RB into a file in a format 
//	that can be loaded later.
//
//	Input: 
//		path [IN] - string containing the filename given from the transactional
//			command.
//
// ===================================================================================

void Transactional_Commands:: dumpCommand(string path)
{
	const char* f = path.c_str();
    fstream file;
	file.exceptions ( fstream::failbit | fstream::badbit );
  	try 
  	{
  		// open/create file
	    file.open (f, ios::out);
	    // prints to file, overrides old file
	    file << "Hello World!";
	    // close file
	    file.close();
  	}
  	catch (ifstream::failure e) {
    	cerr << "Failed to dump file\n";
  	}
}

void Transactional_Commands:: inferenceCommand(string command)
{
    
}

void Transactional_Commands:: dropCommand(string command)
{
    
}

void Transactional_Commands:: factCommand(string fact)
{
//    cout << "Fact method called\n";
//    cout <<"Fact is: " << fact << endl;
    
    Helper:: instance()->parseDefinition(fact);
    
}

void Transactional_Commands:: ruleCommand(string rule)
{
    
}

typedef void (*command_operations)(string);
map<string,command_operations> Transactional_Commands:: getMapCommand(){ return commandMap; }

vector<tuple<string,vector<string>>> Transactional_Commands:: getFact(){ return fact; }

