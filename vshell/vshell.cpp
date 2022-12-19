
# include <iostream>
# include <string>
# include <filesystem>
# include <sstream>
# include <vector>
# include <sys/types.h>
# include <sys/stat.h>
# include <fstream>

namespace fs = std::filesystem;
using std::string;

string Homedir{ "Home" };
string CurrentDir{ "Home" };
string Command{};

enum StringCodes
{
	Pwd,	
	Ls, 
	Cat,
	Cd	 
};
StringCodes hashit(std::string const& GivenString)
{
	if (GivenString == "pwd") return Pwd;
	if (GivenString == "ls") return Ls;
	if (GivenString == "cat") return Cat;
	if (GivenString == "cd") return Cd;
	
}
void PwdExecute(string CurentDir);
void LsExecute(string CurentDir);
void CatExecute(string CurentDir);
void CdExecute(string Words);

void Split(string& Sentence, std::vector<string> &Words );

int main()
{
	
	while (true)
	{
title : std::vector<string> Words{};
		string Template{ CurrentDir + "/" + " " };
		std::cout << CurrentDir + "/" + " ";
		getline(std::cin, Command);
		Split(Command, Words);
		switch (hashit(Words[0]))
		{			   
		case Pwd:
			PwdExecute(CurrentDir);
			goto title;
		case Ls:
			LsExecute(CurrentDir);
			goto title;
		case Cat:
			CatExecute(Words[1]);
			goto title;
		case Cd:
			CdExecute(Words[1]);
			goto title;
		default:
			break;
		}
	}
}

void PwdExecute(string CurentDir)		 //check 1
{
	std::cout << "/"  << CurrentDir<< '\n';
};

void LsExecute(string CurentDir)			  //check 0.5
{
	for (const auto& Entry : std::filesystem ::directory_iterator(CurentDir))
		std::cout << Entry.path() << std::endl;
	std::cout << '\n';
};

void CatExecute(string Filename)	   //check
{
	string temp;
	std::ifstream File((CurrentDir + "/" + Filename), std::fstream::app);
	if (File.is_open())
	{
		while (!File.fail() && !File.eof())
		{
			File >> temp;
			std::cout << temp << ' ';
		}
	}
	else
	{
		std::cout << "File not exist" << '\n';
	}
	std::cout << '\n';
};

void Split(string& Sentence, std::vector<string> &Words)
{

	string result_word;

	for (size_t i = 0; i < Sentence.size(); ++i)
	{
		char character = Sentence[i];
		if (character == ' ' && result_word.size() != 0)
		{
			Words.push_back(result_word);
			result_word = "";
		}
		else
			result_word += character;
	}
	if (result_word != "")
		Words.push_back(result_word);
};

void CdExecute(string Words)
{
	unsigned int counter{ 0 };
	string Temp{"/"};
	std::stringstream ss(Words);
	for (size_t i{ 0 }; i < Words.size()-1; i++)
	{
		if (Words[i] == '/' && Words[i + 1] != '\0')
		{
			Words.insert(i, Temp);
		}

	}
	Temp = CurrentDir + '/' + Words;
	///*std::vector <string> Directories{};
	//if (getline(ss, Temp, '/'))
	//{
	//	while (getline(ss, Temp, '/')) {
	//		Directories.push_back(Temp);
	//		counter++;
	//	}
	///*}*/
	//else
	//	Directories.push_back(Words);*/
	//for (string i : Directories) //check
	//	std::cout << i << " ";

	if (std::filesystem::is_directory(Temp))
	{
		CurrentDir = Temp;
	}
	else 
	{
		std::cout << "No such directory";
	}
	//if (stat(c, &info) != 0)
	//	printf("cannot access %s\n", c);
	//else if (info.st_mode & S_IFDIR)  // S_ISDIR() doesn't exist on my windows 
	//{
	//	printf("%s is a directory\n", c);
	//	CurrentDir = Words;
	//}
	//else
	//{
	//	printf("%s is no directory\n", c);
	//}

	
};