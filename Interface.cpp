//Interface.cpp

#include "Interface.hpp"


<<<<<<< HEAD
void Interface:: run(){

	//should we make it a static variable?
	string userinput = " "; //Takes in what the user inputs
	char endsession = ' '; //Takes in if they want to quit the session or not
	int counter_to_exit = 0; //Takes in how long they want the session to loop for until being asked to quit again

	cout << "Welcome to the Power Falcons recruiting center" << endl;

	while (true)// This loop keeps the program running until the user indicates they want to exit out
	{
		if (counter_to_exit != 0) --counter_to_exit;

		cout << "Please enter in one of the six commands with their defentions following afterwards:" << endl << "	-FACT" 
			<< endl  << "	-RULE" << endl << "	-LOAD" << endl << "	-INFERENCE" << endl <<  "	-DUMP" << endl <<
			"	-DROP" << endl;

		Helper::instance()->parseCommand("Fact Father(Roger,John)"); 

		if (counter_to_exit == 0)//if it's time to exit the program
		{
			cout << "Would you like to exit out of the session? Y for yes, N for no: ";
			cin >> endsession;

			endsession = toupper(endsession); //Captilize the input incase they type a lowercase char

			if (endsession == 'Y')//if they say yes, check to make sure they saved before they exit
			{
				cout << "Have you saved your session? Y for yes, N for no: ";

				cin >> endsession;
				endsession = toupper(endsession);

				if (endsession == 'Y')
				{
					break;
				}
				else
				{
					Helper::instance()->parseCommand("Dump ");
					cout << "Your session has been saved" << endl << "Goodbye" << endl;
					break;
				}
			}
			else//Else, if they don't want to quit, they can indicate how many times they want to loop through before 
				//being asked to quit again
			{
				cout << "How many more turns would you like to go before being asked again to quit? ";
				cin >> counter_to_exit;
				cout << "The program will loop for " << counter_to_exit << " times before being asked to quit again" << endl;
			}
		}
	
	}
=======
void Interface:: run()
{
    
    
    //    Helper::instance()->parseCommand("FACT Father(Roger,John)");
    //    Helper::instance()->parseCommand("FACT Mother(Marry,John)");
    //    Helper::instance()->parseCommand("FACT Father(Roger,Albert)");
    //    Helper::instance()->parseCommand("FACT Mother(Marry,Albert)");
    //    Helper::instance()->parseCommand("FACT Mother(Margret,Robert)");
    //    Helper::instance()->parseCommand("FACT Mother(Marry,Albert)");
    Helper::instance()->parseCommand("FACT Mother(Nancy,Margret)");
    Helper::instance()->parseCommand("FACT Mother(Margret,Bob)");
    
    
//    Helper::instance()->parseCommand("FACT Father(Roger,Albert)");
//    Helper::instance()->parseCommand("FACT Father(Allen,Margret, Alliosn, Joe, Jim)");
    //Helper::instance()->parseCommand("INFERENCE Father($X,$Y)");
//    Helper::instance()->parseCommand("LOAD output.txt");
//    Helper::instance()->parseCommand("DUMP output2.txt");
    
    
    Helper::instance()->parseCommand("RULE GrandMother($X,$Y):- AND Mother($X,$Z) Mother($Z,$Y)");
    Helper::instance()->parseCommand("INFERENCE GrandMother($X,$Y)");
    
    
    
    
    
    
>>>>>>> e7f090ab5ddc50f9f50dbb82f5f3660b564a9a15
    
}
