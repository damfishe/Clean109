//Interface.cpp

#include "Interface.hpp"

bool Valid_FACT_Input(string fact_defenition, bool& user_mess_up)//Checks to see if the fact has the opening and closing parentheses, that's
//the ONLY check it does, for the synthax  of the fact, not the content
{
	stack <char> syntax_check; //pushes the open parentheses and closed parentheses onto the stack, cause there should be only two
	//one pair of parantheses in a fact

	int i = 0;

	while (fact_defenition[i] != '(')//Check before the parentheses that the relationship name is only captial or lowercase letters,
		//no whitespaces or symbols
	{
		if (isalpha(fact_defenition[i]) == 0)
		{
			cout << "Your input for -> " + fact_defenition + " is incorrect" << endl;
			cout << "The relationship name must be only alphabets, no spaces or symbols, followed by a open parantheses" << endl;
			cout << "Example: 'Father('" << endl << endl;
			user_mess_up = true;
			return false;
		}
		++i;
	}

	for (char& c : fact_defenition)//loop through the string char by char, and only push when encoutering a parentheses
	{
		if (c == '(' || c == ')')
		{
			syntax_check.push(c);
		}
	}


	if (syntax_check.size() == 2 && syntax_check.top() == ')') //if the stack size is two, indiciating there are two parantheses, 
		//and the last thing to be pushed is the closing parentheses, that indicates the strings format was in the proper sythax
	{
		return true;
	}
	else
	{
		cout << "Your syntax -> "+ fact_defenition+ " is incorrect" << endl;
		cout << "Proper syntax: FACT [key](how many parameters you want seperated by commas)" << endl;
		cout << "Example: FACT Father(Roger,John,You)" << endl << endl;
		user_mess_up = true;
		return false;
	}
}

bool Valid_RULE_Input(string rule_defenition, bool& user_mess_up)//Makes sure the RULE sythax is correct
{
	stack<char> Rule_syntax; //Gonna be pushing '(' and '$', and they only get popped when there is a closed parentheses or the
	//proper rules for '$' were followed

	bool is_token_and_proper_operator_there = false;

	size_t looking_for_specific_char; //looks to see if the ":-" followed by the AND or OR logical operator is there

	int check_if_next_char_valid = 0; //keeps track of the '$' symbol, and if the next char after that token are valid
	int content_in_array = 0;//checks to see how many char are actually in the array

	for (char& c : rule_defenition)//counts how many char are in the array, until it hits the null char or new line char
	{
		++content_in_array;
	}

	int i = 0;

	while (rule_defenition[i] != '(')//Check before the parentheses that the relationship name is only captial or lowercase letters,
		//no whitespaces or symbols
	{
		if (isalpha(rule_defenition[i]) == 0)
		{
			cout << "Your input for -> " + rule_defenition + " is incorrect" << endl;
			cout << "The relationship name must be only alphabets, no spaces or symbols, followed by a open parentheses" << endl;
			cout << "Example: 'Father('" << endl << endl;
			user_mess_up = true;
			return false;
		}
		++i;
	}

	for (int j = 0; j < content_in_array; ++j)//goes through the array and pushes and pops the '(' and '$' char if certain criterias
		//are meet
	{
		if (rule_defenition[j] == '(') Rule_syntax.push(rule_defenition[j]);
		if (rule_defenition[j] == '$')
		{
			Rule_syntax.push(rule_defenition[j]);
			if (isupper(rule_defenition[j + 1]) != 0 && isalpha(rule_defenition[j + 1]) != 0)//if the next char after '$' is one 
				//alphabet and it is uppercase, it is a valid char to have after '$'
			{
				++check_if_next_char_valid;
			}
			else
			{
				cout << "Your syntax for -> " + rule_defenition + " is incorrect" << endl;
				cout << "All RULE parameters must  ONE uppercase character, and also have a $ symbol" << endl;
				cout << "Example: Parent($X,$Y)" << endl;
				user_mess_up = true;
				return false;
			}
		}

		if (check_if_next_char_valid != 0 && (rule_defenition[j + 2] == ',' || rule_defenition[j + 2] == ')'))
			//if the char after '$' is valid, and the next NEXT char after that is a comma or a closing parentheses, that indicates 
			//there is only one char after '$', that follows the proper criterias, so pop of the '$' and set the counter back to 0
		{
			--check_if_next_char_valid;
			Rule_syntax.pop();
		}

		if (rule_defenition[j] == ')')//if you see a closing parentheses, indicates that it closing the open parentheses that came 
			//before it, and the open parentheses is still in the stack, so pop it 
		{
			Rule_syntax.pop();
		}
	}

	looking_for_specific_char = rule_defenition.find(":- OR");//See if the user typed in ":- OR", if not, check for AND

	if (looking_for_specific_char != rule_defenition.npos)
	{
		is_token_and_proper_operator_there = true;
	}

	if (is_token_and_proper_operator_there == false)//If it can't find the OR one, look with AND with the same notation ":- AND"
	{
		looking_for_specific_char = rule_defenition.find(":- AND");

		if (looking_for_specific_char != rule_defenition.npos)
		{
			is_token_and_proper_operator_there = true;
		}
	}


	//If there's nothing in the stack, if the counter is zero and the token was properly typed, then the RULE sythax is passed 
	if (Rule_syntax.size() == 0 && check_if_next_char_valid == 0 && is_token_and_proper_operator_there == true)
	{
		return true;
	}
	else
	{
		cout << "Your syntax for -> " + rule_defenition + " is wrong" << endl;
		cout << "A proper example would be: RULE Parent($X,$Y) :- AND Father($X,$Y) Mother($X,$Y)" << endl;
		cout << "Please have a space before the ':-'  token, and after it followed by the logical operator (OR/AND), space, and the rest of the rule"
			<< endl << endl;
		user_mess_up = true;
		return false;
	}
}

bool Valid_INFERENCE_Input(string inference_defenition, bool& user_mess_up)
{
	stack<char> Rule_syntax; //Gonna be pushing '(' and '$', and they only get popped when there is a closed parentheses or the
	//proper rules for '$' were followed

	int check_if_next_char_valid = 0; //keeps track of the '$' symbol, and if the next char after that token are valid
	int content_in_array = 0;//checks to see how many char are actually in the array

	for (char& c : inference_defenition)//counts how many char are in the array, until it hits the null char or new line char
	{
		++content_in_array;
	}

	int i = 0;

	while (inference_defenition[i] != '(')//Check before the parentheses that the relationship name is only captial or lowercase letters,
		//no whitespaces or symbols
	{
		if (isalpha(inference_defenition[i]) == 0)
		{
			cout << "The relationship name must be only alphabets, no spaces or symbols, followed by a '('" << endl;
			cout << "Example: 'GrandFather('" << endl;
			cout << "Proceeding to the quit option" << endl << endl;
			user_mess_up = true;
			return false;
		}
		++i;
	}

	for (int j = 0; j < content_in_array; ++j)//goes through the array and pushes and pops the '(' and '$' char if certain criterias
		//are meet
	{
		if (inference_defenition[j] == '(') Rule_syntax.push(inference_defenition[j]);
		if (inference_defenition[j] == '$')
		{
			Rule_syntax.push(inference_defenition[j]);
			if (isupper(inference_defenition[j + 1]) != 0 && isalpha(inference_defenition[j + 1]) != 0)//if the next char after '$' is one 
				//alphabet and it is uppercase, it is a valid char to have after '$'
			{
				++check_if_next_char_valid;
			}
			else
			{
				cout << "All INFERENCE parameters must ONE uppercase character, and also have a $ symbol" << endl;
				cout << "Example: GrandFather($X,$Y) or GrandFather($X,$Y) GF" << endl;
				cout << "Proceeding to the quit option" << endl << endl;
				user_mess_up = true;
				return false;
			}
		}

		if (check_if_next_char_valid != 0 && (inference_defenition[j + 2] == ',' || inference_defenition[j + 2] == ')'))
			//if the char after '$' is valid, and the next NEXT char after that is a comma or a closing parentheses, that indicates 
			//there is only one char after '$', that follows the proper criterias, so pop of the '$' and set the counter back to 0
		{
			--check_if_next_char_valid;
			Rule_syntax.pop();
		}

		if (inference_defenition[j] == ')')//if you see a closing parentheses, indicates that it closing the open parentheses that came 
			//before it, and the open parentheses is still in the stack, so pop it 
		{
			Rule_syntax.pop();
		}
	}


	//If there's nothing in the stack, if the counter is zero and the token was properly typed, then the RULE sythax is passed 
	if (Rule_syntax.size() == 0 && check_if_next_char_valid == 0)
	{
		return true;
	}
	else
	{
		user_mess_up = true;
		return false;
	}
}

bool Valid_DROP_Input(string drop_defenition, bool& user_mess_up)
{

	for (char& c : drop_defenition)//loop through the string char by char, and only push when encoutering a parentheses
	{
		if (isalpha(c) == 0)
		{
			cout << "The DROP name must only be alphabets, no spaces or symbols before or after the name" << endl;
			cout << "Example: 'DROP Father' " << endl;
			cout << "Proceeding to the quit option" << endl << endl;
			user_mess_up = true;
			return false;
		}
	}

	return true;

}

bool Valid_DUMP_Input(string dump_defenition, bool& user_mess_up)
{

	size_t looking_for_specific_file_ending = dump_defenition.find(".sri"); //commented out for testing purpose, when ready
	//delete the line below, and uncomment this code 
	// size_t looking_for_specific_file_ending = dump_defenition.find(".txt");

	if (looking_for_specific_file_ending != dump_defenition.npos)
	{
		return true;
	}
	else
	{
		cout << "Name your file whatever you would like, however it must end with '.sri'" << endl;
		cout << "Example 'Output_file.sri'" << endl;
		cout << "Proceeding to the quit option" << endl<<endl;
		user_mess_up = true;
		return false;
	}
}

bool Valid_LOAD_Input(string path, bool& user_mess_up)
{
	int count = 0;
	bool syntax_correct = false;
	const char* f = path.c_str();
	fstream file;
	// line
	string line;
	file.exceptions(fstream::badbit);
	try
	{
		// open file
		file.open(f, ios::in);
		while (getline(file, line))
		{
			++count;

			string delimeter = " ";
			size_t pos = 0;
			string command = " ";
			pos = line.find(delimeter);
			command = line.substr(0, pos);
			line.erase(0, pos + delimeter.length());
			string rest = line;

			for (int i = 0; i < (int)command.size(); ++i) //captalizes all the words in the first part
			{
				command[i] = toupper(command[i]);
				cout << endl;
			}

			if (command == "FACT"){
				syntax_correct = Valid_FACT_Input(rest, user_mess_up);
			}
			else if (command == "RULE"){
				syntax_correct = Valid_RULE_Input(rest, user_mess_up);
			}
			else if (command == "DROP"){
				syntax_correct = Valid_DROP_Input(rest, user_mess_up);
			}
			else if (command == "INFERENCE"){
				syntax_correct = Valid_INFERENCE_Input(rest, user_mess_up);
			}
			else if (command == "DUMP"){
				syntax_correct = Valid_DUMP_Input(rest, user_mess_up);
			}

		
			if (syntax_correct == false){
				cout << "One of the lines wasn't typed properly, please go back and fix that line in that file" << endl;
				cout << "That line is :" << command + " " + rest << "at line: "<< count << endl << endl;
				return false;
			}
		}
	}
	catch (fstream::failure e) {
		cerr << "Failed to load file\n" << endl;
	}

	return true;
}

bool Quit_Session(char answer)//Ask the user if they want to end the program, if they say yes, ask if they have saved: Yes = Quit, No = DUMP, then quit
//if the user says no instead, ask them how many times they want the program to loop through until being asked to quit again
{
	cout << "Do you want to continue? Y for YES, N for NO: ";
	cin >> answer;
	cout << '\n';

	answer = toupper(answer); //Captilize the input incase they type a lowercase char

	if (answer == 'N')//if they say yes, check to make sure they saved before they exit
	{
		cout << "Have you saved your session? Y for yes, N for no: ";

		cin >> answer;
		cout << '\n';
		answer = toupper(answer);

		if (answer == 'Y')
		{
			return true;
		}
		else
		{
			Helper::instance()->parseCommand("DUMP quicksave.sri");
			cout << "Your session has been saved" << endl << "Goodbye" << endl;
			return true;
		}
	}

	return false;
}

void Interface::run()
{
	char UserInput[200];
	string string_version_UserInput;

	string first_part_of_command = " ";//Stores the first part of the command, the type of command itself
	string second_part_of_command;//Stores the second part of the command, the defenition of the command, can take in spaces
	int counter_of_char = 0; //counter to keep track of how many characters the user inputed into the array

	char endsession = '\0'; //Takes in if they want to quit the session or 
	bool error_commited = false;
	bool program_looping = true;
	string all_commands[6] = { "FACT", "RULE", "DROP", "INFERENCE", "LOAD", "DUMP" };//All the commands the user can type in

	cout << "Welcome to the Simple Rule-Base Inference Engine or SRI for short" << endl << endl; 

	while (program_looping == true)// This loop keeps the program running until the user indicates they want to exit out
	{

		bool first_half_error_commited = false;//Has the user commited an error by miscalling a certain command? 
		bool second_half_error_commited = false;//Has the user commited an error by having the wrong syntax

		cout << "Please enter one of the commands with their proper content=>" << endl << "	-FACT(store in a fact)"<< endl << "	-RULE(store in a rule)" 
			<< endl << "	-LOAD(load in a file)" << endl << "	-INFERENCE(issue a query)" << endl 
			<< "	-DUMP(download all facts and rule into a file)" << endl <<"	-DROP(remove a fact or rule)" << endl << "Enter here:";
		
		cin.get(UserInput, sizeof(UserInput) - 1, '\n');//get char for input stream until either the array is full
		//or the new line char is encountered
		cin.clear();
		cin.ignore(100, '\n');
		cout << endl;

		string_version_UserInput = UserInput;

		string delimeter = " ";
		size_t pos = 0;
		pos = string_version_UserInput.find(delimeter);
		first_part_of_command = string_version_UserInput.substr(0, pos);
		string_version_UserInput.erase(0, pos + delimeter.length());
		second_part_of_command = string_version_UserInput;

		for (int i = 0; i < (int)first_part_of_command.size(); ++i) //captalizes all the words in the first part
		{
			first_part_of_command[i] = toupper(first_part_of_command[i]);
		}

		for (int i = 0; i <= 6; ++i)//checks if the first word matches any command, if not, proceed to the quit menu
		{
			if (i == 6)//If you get to six, you are outside the size of the array
			{
				cout << "Error: You need to type in one of those six commands in all capital and proper spelling" << endl;
				cout << "Proceeding to the quit option" << endl;
				first_half_error_commited = true;
				error_commited = true;
				break;
			}

			if (first_part_of_command.compare(all_commands[i]) == 0)
			{
				break;
			}
		}

		
		if (first_part_of_command == "FACT")
		{
			if (Valid_FACT_Input(second_part_of_command, error_commited) == false)
			{
				second_half_error_commited = true;
			}
		}
		else if (first_part_of_command == "RULE")
		{
			if (Valid_RULE_Input(second_part_of_command, error_commited) == false)
			{
				second_half_error_commited = true;
			}
		}
		else if (first_part_of_command == "INFERENCE")
		{
			if (Valid_INFERENCE_Input(second_part_of_command, error_commited) == false)
			{
				second_half_error_commited = true;
			}
		}
		else if (first_part_of_command == "DROP")
		{
			if (Valid_DROP_Input(second_part_of_command, error_commited) == false)
			{
				second_half_error_commited = true;
			}
		}
		else if (first_part_of_command == "DUMP")
		{
			if (Valid_DUMP_Input(second_part_of_command, error_commited) == false)
			{
				second_half_error_commited = true;
			}
		}
		else if (first_part_of_command == "LOAD")
		{
			if (Valid_LOAD_Input(second_part_of_command, error_commited) == false)
			{
				second_half_error_commited = true;
			}
		}
		
		if (!first_half_error_commited && !second_half_error_commited)//If there are no errors in the input, pass it into the function
		{
			string total_command = first_part_of_command + " " + second_part_of_command;
			Helper::instance()->parseCommand(total_command);
		}

		if (error_commited == true)//Time to exit
		{
			if (Quit_Session(endsession))
			{
				program_looping = false;
			}
		}

		cin.clear();
		cin.ignore(1,'\n');
	}
}
