#include "FileUtility.cpp"

using namespace std;


int main()
{
	//path to start search
	string searchPath;

	//path to save
	string targetPath;
	
	//to store filetype
	string selectedFileType;
	int selectedFileTypeIndex;

	//to store filetype selections
	vector<string> fileTypes{"pdf","txt","doc","docx","csv","xlsx","other..."};

	//greeting
	IOUtility::draw_message("Welcome to File Finder. This program allows you to specify a search folder, a filetype,anda target directory. Using this information any files matching the criteria will be found and copied to the target destination.");

	//get the search folder
	//todo:validate input
	IOUtility::get_input("Where do you want to search?\nPlease enter the full path. (ex. 'C:\\Users\\Dan\\Documents')\n",searchPath);
	
	bool valid = FileUtility::dirExists(searchPath);;
	while (!valid) {
		valid = FileUtility::dirExists(searchPath);
		if (!valid) {
			IOUtility::get_input("Please enter a valid path for the search. Ensure it looks like 'C:\\Users\\Dan\\Documents'. ", searchPath);
		}
	}

	//get the filetype to search for
	IOUtility::draw_message("What type of file do you want to search for?");
	selectedFileTypeIndex = IOUtility::draw_menu(fileTypes);
	if (selectedFileTypeIndex != 7) {
		selectedFileType = fileTypes[selectedFileTypeIndex-1];
	}
	else {
		IOUtility::get_input("Please enter the filetype, with only its characters, that you wish to search for.", selectedFileType);
	}

	//get the target location
	//get the search folder
	IOUtility::get_input("Where do you want to save the files found (does not need to exist prior to run)?\nPlease enter the full path. (ex. 'C:\\Users\\Dan\\Documents')\n", targetPath);


	//hold directories
	vector<string> directories;
	vector<string> files;
	vector<string> badFiles;


	//get the inital directories
	directories = FileUtility::getDirectories(searchPath);
	
	//set the while flag
	bool changed = true;
	int counter = 0;
	int copied = 0;

	//start indexing search folder
	StringUtility::print("Indexing Filesystem...");
	while (changed) {
		//set changed to false to stop while if nothing new
		changed = false;

		//loop through the directories, looking at only dirs matching the depths of the loop
		vector<string> curDirs;
		for (string dir : directories) {
			if (std::count(dir.begin(), dir.end(), '\\') > counter) {
				//for each directory get the containing directories
				vector<string> loopDirs = FileUtility::getDirectories(dir);
				//add them to the currrent drectories
				curDirs.insert(curDirs.end(), loopDirs.begin(), loopDirs.end());
			}										
		}
		//if the current directores are not already in the vector, add them. Also set the changed terminator to cause another loop (one layer deeper).
		if (curDirs.size() > 0) {
			if (!StringUtility::checkVectorForVector(directories, curDirs)) {
				directories.insert(directories.end(), curDirs.begin(), curDirs.end());
				changed = true;
			}
		}
		//increase layer
		counter++;
		StringUtility::print("Layer: "+to_string(counter));
		StringUtility::print("Folder Count: "+to_string(directories.size()));
	}
	
	cout << "Folders Found: " << directories.size() << "\n" << endl;

	StringUtility::print("Finding Files...");

	//get all matching files
	for (string dir : directories) {
		vector<string> curFiles = FileUtility::getFilesMatchingType(selectedFileType, dir);
		files.insert(files.end(), curFiles.begin(), curFiles.end());
	}

	//copy all matching files
	for (string file : files) {
		StringUtility::print(file);
		if (FileUtility::copyFile(file, targetPath))
			copied++;
		else
			badFiles.push_back(file);
	}

	StringUtility::print("Files Found:" + to_string(files.size()));
	StringUtility::print("Files Copied: " + to_string(copied));	

	//if any error files, tell the user
	if (badFiles.size() > 0) {
		StringUtility::print("Unable to copy the following files: ");
		for (string file : badFiles) {
			StringUtility::print("\t" + file);
		}
	}	

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
	std::cin.get();
}