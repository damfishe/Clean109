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
    Helper:: instance()->LoadHelp(path);
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
    Helper:: instance()->DumpHelp(path);
}

// ===================================================================================
// 	INFERERNCE
// ===================================================================================
//	Issue a query.
//
//	Input: 
//		command [IN] - string containing the transactional command.
//
// ===================================================================================

void Transactional_Commands:: inferenceCommand(string command)
{
	Helper:: instance()->parseDefinition('i',command);
	Helper:: instance()->ParseQuery(command);
}

// ===================================================================================
// 	DROP
// ===================================================================================
//	Drop facts or a rule.
//
//	Input: 
//		command [IN] - string containing the transactional command.
//
// ===================================================================================

void Transactional_Commands:: dropCommand(string command)
{
    Helper:: instance()->dropBase(command);
}

// ===================================================================================
// 	FACT
// ===================================================================================
//	Define a fact.
//
//	Input: 
//		fact [IN] - string containing the fact.
//
// ===================================================================================

void Transactional_Commands:: factCommand(string fact)
{
    Helper:: instance()->parseDefinition('f',fact);
    
}

// ===================================================================================
// 	RULE
// ===================================================================================
//	Define a rule.
//
//	Input: 
//		rule [IN] - string containing the rule.
//
// ===================================================================================

void Transactional_Commands:: ruleCommand(string rule)
{
    Helper:: instance()->parseDefinition('r',rule);
}

typedef void (*command_operations)(string);
map<string,command_operations>& Transactional_Commands:: getMapCommand(){ return commandMap; }

vector<tuple<string,vector<string>>>& Transactional_Commands:: getFact(){ return fact; }

vector<tuple<string,vector<string>>>& Transactional_Commands:: getRule(){ return rule; }

/* For testing purposes
void Transactional_Commands::print(){
	auto j = 0;
	cout << "FACT" << endl;
	for_each(fact.begin(), fact.end(), [&](decltype(*fact.begin()) it) -> void // iterates through vector
	{

		for (int i = 0; i < get<1>(it).size(); i++) // iterates through vector inside tuple
		{
			cout << j << "   " << get<0>(it) << "   " << get<1>(it)[i] << endl; // prints an index in vector
		}
		j++;
	});    cout << "RULE" << endl;
	for_each(rule.begin(), rule.end(), [&](decltype(*rule.begin()) it) -> void // iterates through vector
	{
		for (int i = 0; i < get<1>(it).size(); i++) // iterates through vector inside tuple
		{
			cout << get<0>(it) << "   " << get<1>(it)[i] << endl; // prints an index in vector
		}
	});
}
*/