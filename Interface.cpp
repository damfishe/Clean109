//Interface.cpp

#include "Interface.hpp"

//bool Valid_FACT_Input(string fact_defenition, int& counter)//Checks to see if the fact has the opening and closing parentheses, that's
////the ONLY check it does, for the synthax  of the fact, not the content
//{
//	stack <char> syntax_check; //pushes the open parentheses and closed parentheses onto the stack, cause there should be only two
//								//one pair of parantheses in a fact
//
//	int i = 0; 
//
//	while (fact_defenition[i] != '(')//Check before the parentheses that the relationship name is only captial or lowercase letters,
//		//no whitespaces or symbols
//	{
//		if (isalpha(fact_defenition[i]) == 0)
//		{
//			cout << "The relationship name must be only alphabets, no spaces or symbols, followed by a '('" << endl;
//			cout << "Example: 'Father('" << endl;
//			cout << "Proceeding to the quit option" << endl << endl;
//			counter = 0;
//			return false;
//		}
//		++i;
//	}
//
//	for (char& c : fact_defenition)//loop through the string char by char, and only push when encoutering a parentheses
//	{
//		if (c == '(' || c == ')') 
//		{
//			syntax_check.push(c);
//		}
//	}
//
//
//	if (syntax_check.size() == 2 && syntax_check.top() == ')') //if the stack size is two, indiciating there are two parantheses, 
//		//and the last thing to be pushed is the closing parentheses, that indicates the strings format was in the proper sythax
//	{
//		return true;
//	}
//	else
//	{
//		cout << "Your syntax for FACT is incorrect" << endl;
//		cout << "Proper syntax: FACT [key](how many parameters you want seperated by commas)" << endl;
//		cout << "Example: FACT Father(Roger,John)" << endl;
//		cout << "Proceeding to the quit option" << endl;
//		cout << '\n';
//		counter = 0;
//		return false;
//	}
//}
//
//bool Valid_RULE_Input(string rule_defenition, int& counter)//Makes sure the RULE sythax is correct
//{
//	stack<char> Rule_syntax; //Gonna be pushing '(' and '$', and they only get popped when there is a closed parentheses or the
//	//proper rules for '$' were followed
//	
//	bool is_token_and_proper_operator_there = false;
//	
//	size_t looking_for_specific_char; //looks to see if the ":-" followed by the AND or OR logical operator is there
//
//	int check_if_next_char_valid = 0; //keeps track of the '$' symbol, and if the next char after that token are valid
//	int content_in_array = 0;//checks to see how many char are actually in the array
//	
//	for (char& c : rule_defenition)//counts how many char are in the array, until it hits the null char or new line char
//	{
//		++content_in_array;
//	}
//
//	int i = 0;
//
//	while (rule_defenition[i] != '(')//Check before the parentheses that the relationship name is only captial or lowercase letters,
//		//no whitespaces or symbols
//	{
//		if (isalpha(rule_defenition[i]) == 0)
//		{
//			cout << "The relationship name must be only alphabets, no spaces or symbols, followed by a '('" << endl;
//			cout << "Example: 'Father('" << endl;
//			cout << "Proceeding to the quit option" << endl << endl;
//			counter = 0;
//			return false;
//		}
//		++i;
//	}
//
//	for (int j = 0; j < content_in_array; ++j)//goes through the array and pushes and pops the '(' and '$' char if certain criterias
//		//are meet
//	{
//		if (rule_defenition[j] == '(') Rule_syntax.push(rule_defenition[j]);
//		if (rule_defenition[j] == '$')
//		{
//			Rule_syntax.push(rule_defenition[j]);
//			if (isupper(rule_defenition[j + 1]) != 0 && isalpha(rule_defenition[j + 1]) != 0)//if the next char after '$' is one 
//				//alphabet and it is uppercase, it is a valid char to have after '$'
//			{
//				++check_if_next_char_valid;
//			}
//			else
//			{
//				cout << "All RULE parameters must  ONE uppercase character, and also have a $ symbol" << endl;
//				cout << "Example: Parent($X,$Y)" << endl;
//				cout << "Proceeding to the quit option" << endl << endl;
//				counter = 0;
//				return false;
//			}
//		}
//
//		if (check_if_next_char_valid != 0 && (rule_defenition[j + 2] == ',' || rule_defenition[j + 2] == ')'))
//			//if the char after '$' is valid, and the next NEXT char after that is a comma or a closing parentheses, that indicates 
//			//there is only one char after '$', that follows the proper criterias, so pop of the '$' and set the counter back to 0
//		{
//			--check_if_next_char_valid;
//			Rule_syntax.pop();
//		}
//
//		if (rule_defenition[j] == ')')//if you see a closing parentheses, indicates that it closing the open parentheses that came 
//			//before it, and the open parentheses is still in the stack, so pop it 
//		{
//			Rule_syntax.pop();
//		}
//	}
//
//	looking_for_specific_char = rule_defenition.find(":-OR");//See if the user typed in ":-OR" or ":- OR", if not, check for AND
//
//	if (looking_for_specific_char != rule_defenition.npos)
//	{
//		is_token_and_proper_operator_there = true;
//	}
//	else
//	{
//		looking_for_specific_char = rule_defenition.find(":- OR");
//
//		if (looking_for_specific_char != rule_defenition.npos)
//		{
//			is_token_and_proper_operator_there = true;
//		}
//	}
//
//	if (is_token_and_proper_operator_there == false)//If it can't find the OR one, look with AND with the same notation ":-AND" ":- AND"
//	{
//		looking_for_specific_char = rule_defenition.find(":-AND");
//
//		if (looking_for_specific_char != rule_defenition.npos)
//		{
//			is_token_and_proper_operator_there = true;
//		}
//		else
//		{
//			looking_for_specific_char = rule_defenition.find(":- AND");
//
//			if (looking_for_specific_char != rule_defenition.npos)
//			{
//				is_token_and_proper_operator_there = true;
//			}
//		}
//	}
//
//	//If there's nothing in the stack, if the counter is zero and the token was properly typed, then the RULE sythax is passed 
//	if (Rule_syntax.size() == 0 && check_if_next_char_valid==0 && is_token_and_proper_operator_there==true)
//	{
//		cout << "Worked so far" << endl << endl;
//		return true;
//	}
//	else
//	{
//		cout << "Returning a faliure" << endl << endl;
//		counter = 0;
//		return false;
//	}
//}
//
//bool Quit_Session(char answer)//Ask the user if they want to end the program, if they say yes, ask if they have saved: Yes = Quit, No = DUMP, then quit
////if the user says no instead, ask them how many times they want the program to loop through until being asked to quit again
//{
//	cout << "Would you like to exit out of the session? Y for yes, N for no: ";
//	cin >> answer;
//	cout << '\n';
//
//	answer = toupper(answer); //Captilize the input incase they type a lowercase char
//
//	if (answer == 'Y')//if they say yes, check to make sure they saved before they exit
//	{
//		cout << "Have you saved your session? Y for yes, N for no: ";
//
//		cin >> answer;
//		cout << '\n';
//		answer = toupper(answer);
//
//		if (answer == 'Y')
//		{
//			return true;
//		}
//		else
//		{
//			Helper::instance()->parseCommand("DUMP");
//			cout << "Your session has been saved" << endl << "Goodbye" << endl;
//			return true;
//		}
//	}
//
//	return false;		
//}
//
//void Interface:: run()
//{
//
//	string first_part_of_command = " ";//Stores the first part of the command, the type of command itself
//	char second_part_of_command[150];//Stores the second part of the command, the defenition of the command, can take in spaces
//	int counter_of_char = 0; //counter to keep track of how many characters the user inputed into the array
//
//	char endsession = '\0'; //Takes in if they want to quit the session or not
//	int counter_to_exit = 0; //Takes in how long they want the session to loop for until being asked to quit again
//
//	string all_commands[6] = { "FACT", "RULE", "DROP", "INFERENCE", "LOAD", "DUMP" };//All the commands the user can type in
//
//	cout << "Welcome to the Power Falcons recruiting center" << endl;
//
//	while (true)// This loop keeps the program running until the user indicates they want to exit out
//	{
//		if (counter_to_exit != 0) --counter_to_exit;
//
//		bool first_half_error_commited = false;//Has the user commited an error by miscalling a certain command? 
//		bool second_half_error_commited = false;//Has the user commited an error by having the wrong syntax
//
//		cout << "Please enter in one of the six commands you would like to do:" << endl << "	FACT"
//			<< endl << "	RULE" << endl << "	LOAD" << endl << "	INFERENCE" << endl << "	DUMP" << endl <<
//			"	DROP" << endl << "Enter here:";
//		cin >> first_part_of_command;
//		cin.clear();//Sets a new value for the stream's internal error state flags.
//		cin.ignore(100, '\n');//stop extracting when:(1) up to one hundred char are extracted and ignored or, (2) when you hit the newline char
//
//		cout << "Now, please enter the proper content, syntactically correct with no spaces, for " << first_part_of_command << endl
//			<< "Enter here:";
//
//		cin.get(second_part_of_command, sizeof(second_part_of_command) - 1, '\n');//get char for input stream until either the array is full
//		//or the new line char is encountered
//		cin.clear(); 
//		cin.ignore(100, '\n');
//
//		for (int i = 0; i < (int)first_part_of_command.size(); ++i) //captalizes all the words in the first part
//		{
//			first_part_of_command[i] = toupper(first_part_of_command[i]);
//			cout << first_part_of_command[i] << endl;
//		}
//
//		cout << "========================================================" << endl;
//
//		cout << first_part_of_command << endl;
//		cout << "========================================================" << endl;
//
//		cout << second_part_of_command << endl;
//		cout << "========================================================" << endl;
//
//		for (int i = 0; i <= 6; ++i)//checks if the first word matches any command, if not, proceed to the quit menu
//		{
//			if (i == 6)//If you get to six, you are outside the size of the array
//			{
//				cout << "Error: You need to type in one of those six commands in all capital and proper spelling" << endl;
//				cout << "Proceeding to the quit option" << endl;
//				first_half_error_commited = true;
//				counter_to_exit = 0;
//				break;
//			}
//
//			if (first_part_of_command.compare(all_commands[i]) == 0)
//			{
//				cout << "It matches" << endl;
//				break;
//			}
//		}
//
//		if (first_part_of_command == "FACT")
//		{
//			if (Valid_FACT_Input(second_part_of_command, counter_to_exit) == false)
//			{
//				second_half_error_commited = true;
//			}
//		}
//		else if (first_part_of_command == "RULE")
//		{
//			if (Valid_RULE_Input(second_part_of_command, counter_to_exit) == false)
//			{
//				second_half_error_commited = true;
//			}
//		}
//
//		if (!first_half_error_commited && !second_half_error_commited)//If there are no errors in the input, pass it into the function
//		{
//			cout << "it works" << endl;
//			cout << first_part_of_command + " " + second_part_of_command << endl;
//			string total_command = first_part_of_command + " " + second_part_of_command;
//			Helper::instance()->parseCommand(total_command);
//		}
//		
//		if (counter_to_exit == 0)//Time to exit
//		{
//			if (Quit_Session(endsession))
//			{
//				break;
//			}
//			else//Else, if they don't want to quit, they can indicate how many times they want to loop through before 
//				//being asked to quit again
//			{
//				cout << "How many more turns would you like to go before being asked again to quit? ";
//				cin >> counter_to_exit;
//
//			}
//		}
//	}
//}


void Interface:: run()
{
    
    
        Helper::instance()->parseCommand("FACT Father(Roger,John)");
    //    Helper::instance()->parseCommand("FACT Mother(Marry,John)");
    //    Helper::instance()->parseCommand("FACT Father(Roger,Albert)");
    //    Helper::instance()->parseCommand("FACT Mother(Marry,Albert)");
    //    Helper::instance()->parseCommand("FACT Mother(Margret,Robert)");
    //    Helper::instance()->parseCommand("FACT Mother(Marry,Albert)");
    Helper::instance()->parseCommand("FACT Mother(Nancy,Margret)");
    Helper::instance()->parseCommand("FACT Mother(Nancy,Roger)");
    Helper::instance()->parseCommand("FACT Mother(Margret,Bob)");
    
    
//    Helper::instance()->parseCommand("FACT Father(Roger,Albert)");
//    Helper::instance()->parseCommand("FACT Father(Allen,Margret, Alliosn, Joe, Jim)");
    //Helper::instance()->parseCommand("INFERENCE Father($X,$Y)");
//    Helper::instance()->parseCommand("LOAD output.txt");
//    Helper::instance()->parseCommand("DUMP output2.txt");
    
    
//    Helper::instance()->parseCommand("RULE Parent($X,$Y):- OR Father($X,$Y) Mother($X,$Y)");
    Helper::instance()->parseCommand("RULE GrandMother($X,$Y):- AND Mother($X,$Z) Mother($Z,$Y)");
    Helper::instance()->parseCommand("RULE GrandMother($X,$Y):- AND Mother($X,$Z) Father($Z,$Y)");
    Helper::instance()->parseCommand("INFERENCE GrandMother($X,$Y)");
//    Helper::instance()->parseCommand("INFERENCE Parent($X,$Y)");
    
}
