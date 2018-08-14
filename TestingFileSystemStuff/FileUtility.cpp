#define NOMINMAX
#include "IOUtility.cpp"
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <windows.h>

namespace fs = std::experimental::filesystem;
class FileUtility
{

public:
	static std::vector<std::string> getDirectories(std::string filepath) {
		//hold directories
		std::vector<std::string> directories;
		//interate through each file in the folder (including dirs)
		for (auto & p : fs::directory_iterator(filepath)) {

			//get current filename
			std::string fileName = p.path().string();

			//add to vector if a folder
			if (fileName.find(".") == std::string::npos) {
				directories.push_back(fileName);
			}
		}
		//return the directories
		return directories;
	}

	//checks if file exists
	static bool fileExists(const string fileName)
	{
		//use ifstream to check if file exists
		std::ifstream infile(fileName);
		return infile.good();
	}

	static bool dirExists(const std::string& dirName_in)
	{
		DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
		if (ftyp == INVALID_FILE_ATTRIBUTES)
			return false;  //something is wrong with your path!

		if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
			return true;   // this is a directory!

		return false;    // this is not a directory!
	}

	static std::vector<std::string> getFilesMatchingType(std::string filetype, std::string directoryPath) {
		//hold directories
		std::vector<std::string> files;
		//interate through each file in the folder (including dirs)
		for (auto & p : fs::directory_iterator(directoryPath)) {

			//get current filename
			std::string fileName = p.path().string();

			if (fileName.substr(fileName.length() - filetype.length(), filetype.length()) == filetype) {
				files.push_back(fileName);
			}
		}
		return files;
	}

	//this will take a filepath and return the same path with the filename containing the parent directory name
	static std::string addContextToFile(std::string filePath) {
		//split the filepath on the slashes to get each directory
		std::vector<std::string> splitFilePath = StringUtility::splitString(filePath, '\\');
		//if the vector has at least 2 elements (dir and file)
		if (splitFilePath.size() > 1) {
			//build the new filename
			std::string filename = splitFilePath[splitFilePath.size() - 2] + '_' + splitFilePath[splitFilePath.size() - 1];
			
			//replace the original filename  with the new one
			splitFilePath[splitFilePath.size() - 1] = filename;

			//rebuild the filepath and return
			return StringUtility::combineString(splitFilePath, '\\');
		}
		//return the filepath if not 2 elements (can catch this later)
		else {
			return filePath;
		}
	}

	//copys file at file path to target directory path
	static bool copyFile(std::string sourceFileString, std::string targetDir) {
		fs::path sourceFile = sourceFileString;
		fs::path targetParent = targetDir;

		//builds the new filepath using the current filename and the target path
		auto target = targetParent / sourceFile.filename(); 

		//try copying
		try
		{
			fs::create_directories(targetParent); // Recursively create target directory if not existing.
			fs::copy_file(sourceFile, target, fs::copy_options::none);
			//return true if sucessfully copied
			return true;
		}
		//catch exception from existing file error
		catch (std::exception& e)
		{			
			StringUtility::print("Found duplicate of " + sourceFileString);
			//try resaving with context added to filename
			try {
				//get path with context
				std::string newContext = addContextToFile(sourceFileString);
				fs::path fileWithContext = newContext;
				StringUtility::print("Attempting save at " + newContext);
				auto target = targetParent / fileWithContext.filename();

				//retry save
				fs::create_directories(targetParent); 
				fs::copy_file(sourceFile, target, fs::copy_options::none);

				//return true if successful
				return true;
			}
			//if still error, print and return
			catch (std::exception& e2) {
				std::cout << e.what() << std::endl;
				return false;
			}
		}
	}
};

