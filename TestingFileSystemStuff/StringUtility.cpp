#include <string>
#include <iostream>
#include <vector>
#include <sstream>

class StringUtility
{

public:

	//print out string
	static void print(std::string string) {
		std::cout << string << std::endl;
	}

	//will accept a string and delimter and spit the string based on the delimiter and return a vector<string> of those values
	static std::vector<std::string> splitString(std::string stringToSplit, char delimiter) {

		std::stringstream test(stringToSplit);
		std::string segment;
		std::vector<std::string> seglist;

		//loop through segments and build the vector
		while (std::getline(test, segment, delimiter))
		{
			seglist.push_back(segment);
		}
		return seglist;
	}

	//will accept vector<string> and delimiter and return built string
	static std::string combineString(std::vector<std::string> splitString, char delimiter) {

		//if the vector has elements
		if (splitString.size() > 0) {
			std::string combinedString = "";

			//add each sement with the delmiter to the string
			for (std::string sement : splitString) {
				combinedString += (sement + delimiter);
			}
			//removed last delimiter and return
			combinedString = combinedString.substr(0, combinedString.length() - 1);
			return combinedString;
		}
		//if vector was empty return empty string
		else {
			return "";
		}
	}

	//will accept two vectors checking the first for the second
	static bool checkVectorForVector(std::vector<std::string> &containing, std::vector<std::string> &contained) {

		//check the vectors have a size
		if (contained.size() > 0 && containing.size() > 0) {
			try {
				//if the first vector contains both the first and last element of second vector, return true
				if (std::find(containing.begin(), containing.end(), contained[0]) != containing.end() && std::find(containing.begin(), containing.end(), contained[contained.size() - 1]) != containing.end()) {
					return true;
				}
				//if not return false
				else {
					return false;
				}
			}
			//if errors return false
			catch (...) {
				return false;
			}
		}
		//if empty return false
		else {
			return false;
		}


	}
};
