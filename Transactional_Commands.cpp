//Transactional_Commands.cpp

#include "Transactional_Commands.hpp"
#include "Helper.hpp" // foward declaration


Transactional_Commands:: Transactional_Commands(){
    
    commandMap["FACT"] = factCommand;
    commandMap["RULE"] = ruleCommand;
    commandMap["DROP"] = dropCommand;
    commandMap["INFERENCE"] = inferenceCommand;
    commandMap["LOAD"] = loadCommand;
    commandMap["DUMP"] = dumpCommand;
    
    
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
    cout << "start of load function." << endl;
    Helper:: instance()->LoadHelp(path);
    cout << "end of load function." << endl;
//    const char* f = path.c_str();
//    fstream file;
//    // line
//    string l;
//	file.exceptions ( fstream::badbit );
//  	try 
//  	{
//  		// open file
//	    file.open (f, ios::in);
//	    while ( getline(file, l) )
//    	{
//    		cout << l << endl;
//    	}
//	    // close file
//	    file.close();
//  	}
//  	catch ( fstream::failure e ) {
//    	cerr << "Failed to load file\n";
//  	}
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

void Transactional_Commands:: dumpCommand(string path) //vector<tuple<string,vector<string>>>& base)
{
    cout << "start of dump function" << endl;
    cout << path << endl;
    Helper:: instance()->DumpHelp(path);
    cout << "end of dump function" << endl;
}



void Transactional_Commands:: inferenceCommand(string command)
{
   Helper:: instance()->ParseQuery(command);
   Helper:: instance()->parseDefinition('i',command);
}

void Transactional_Commands:: dropCommand(string command)
{
    Helper:: instance()->dropBase(command);
}

void Transactional_Commands:: factCommand(string fact)
{
//    cout << "Fact method called\n";
//    cout <<"Fact is: " << fact << endl;
    
    Helper:: instance()->parseDefinition('f',fact);
    
}

void Transactional_Commands:: ruleCommand(string rule)
{
    Helper:: instance()->parseDefinition('r',rule);
}

typedef void (*command_operations)(string);
map<string,command_operations>& Transactional_Commands:: getMapCommand(){ return commandMap; }

vector<tuple<string,vector<string>>>& Transactional_Commands:: getFact(){ return fact; }

vector<tuple<string,vector<string>>>& Transactional_Commands:: getRule(){ return rule; }

