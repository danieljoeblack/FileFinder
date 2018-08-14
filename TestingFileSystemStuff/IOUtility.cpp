#include <iomanip>
#include "StringUtility.cpp"
using namespace std;

class IOUtility
	/*Based of class notes*/
{

public:

	//ouputs the passed question and stores the response in the referenced variable
	static void get_input(const string &question, string &input)
	{
		cout << question << endl;
		getline(cin, input);
	}

	//get numeric input, repeat until a vaild answer is entered
	static void get_input(const string &question, int &input)
	{
		while (true)
		{
			cout << question << endl;

			string tmp;
			getline(cin, tmp);
			stringstream stream(tmp);

			if (stream >> input)
			{
				break;
			}

			cout << "Please enter a correct value." << endl;
		}
	}

	//write a message to the console with some formatting
	static void draw_message(const string message)
	{		
		string messageSeg="";

		cout << "\n" << endl;
		cout << setfill('=') << setw(100) << "\n";
		for (int i = 1; i < message.length(); i++) {
			if (i % 90 !=0) {
				messageSeg += message[i-1];
				if (i == message.length() - 1) {
					cout << messageSeg << "\n";					
					messageSeg = "";
				}
			}
			else {
				messageSeg += message[i - 1];
				cout << messageSeg << "\n";				
				messageSeg = "";
			}						
		}
		cout << setfill('=') << setw(100) << "\n";
		cout << endl;
	}

	//write out menu options and return choice
	static int draw_menu(const vector<string> &options)
	{
		int count = 1;
		for (string option : options)
		{
			cout << count << ") " << option << endl;
			count++;
		}

		cout << "\n" << endl;
		cout << setfill('=') << setw(30) << "\n";
		cout << endl;

		int choice;
		get_input("Please choose an option: ", choice);
		return choice;
	}
};