/////////////////////////////////////////////////////////////////////
//	CSE 687 Project 3-  Dependency based CodePublisher			   //
//  Test Executive.cpp - code to demonstrate requirements 1- 10     //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      MacBook Pro,Windows 10    			           //
//  Application:   CodeAnalyzerEx                                  //
//  Author:        Rajesh Ramesh  SU ID: 416867192                 //
/////////////////////////////////////////////////////////////////////

#include "../TypeTable/TypeTable.h"
#include "../Dependency/Dependency.h"
#include "../StrongComponent/StrongComponent.h"
#include "../StrongComponent/StrongComponent.h"
#include "../Persistance/Persistance.h"
#include "SourceFiles.h"
#include "../Parser/Parser.h"
#include "../FileSystem/FileSystem.h"
#include "../FileMgr/FileMgr.h"
#include "../Display/Display.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"
#include "../AbstractSyntaxTree/AbstrSynTree.h"
#include "../Logger/Logger.h"
#include "../Utilities/Utilities.h"
#include "../Analyzer/DepAnal.h"
#include "../Analyzer/Executive.h"
#include "../CodePublisher/CodePublisher.h"
#include <functional>
#include <chrono>
#include <ctime>
#include <exception>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using Key = std::string;
using Keys = std::vector<Key>;
using Rslt = Logging::StaticLogger<0>;  
using Demo = Logging::StaticLogger<1>;  
using Dbug = Logging::StaticLogger<2>;  
using File = std::string;
using Path = std::string;
using Files = std::vector<File>;
using Pattern = std::string;
using Ext = std::string;
using FileMap = std::unordered_map<Pattern, Files>;
using namespace CodeAnalysis;


////////////////////////////////////////////////////////////////////////////
//Used to create a TypeTable to store information for dependency analysis//
//////////////////////////////////////////////////////////////////////////
NoSqlDatabaseApp Type_Table()
{
	TypeAnalysis tanal;
	NoSqlDatabaseApp dbtypetab;
	tanal.doTypeAnalysis(dbtypetab);
	Display_Type_Analysis(dbtypetab);
	return dbtypetab;
}
/////////////////////////////////////////////
////Files are assigned respective numbers///
///////////////////////////////////////////

std::unordered_map<int, File> revCalc(Files allFiles)
{
	int counter = 0;
	std::unordered_map<File, int> fMap;
	std::unordered_map<int, File> revf;
	for (File file : allFiles)
	{ fMap[FileSystem::Path::getName(file)] = counter;
	counter++;
	}
	std::vector<vector<int>> rfMap;
	std::vector<File> kfkeys;
	kfkeys.reserve(fMap.size());
	std::vector<int> vals;
	for (auto kv : fMap)
	{ kfkeys.push_back(kv.first);
	  vals.push_back(kv.second);
   	 revf[kv.second] = kv.first;
	} return revf; }

///////////////////////////////////////
//Used to create a Dependency Table///
/////////////////////////////////////
Dependency Dependency_Table(NoSqlDatabaseApp db, Files allFiles)
{
	Dependency dbnew;
	control cont;
	cont.doActivity(db, dbnew, allFiles);
	Display_Dependency_Table(dbnew);
	return dbnew;
}
//////////////////////////////////////////////////////////////////////
// Searches to discover the strong components for file dependencies//
////////////////////////////////////////////////////////////////////

std::vector<vector<int>> SCCRequirement(Files allFiles,Dependency dbnew)
{
	std::vector<vector<int>> rfMap;
	int counter = 0;
	std::vector<int> vec;
	std::unordered_map<File, int> fMap;
	std::unordered_map<int, File> rev1;

	for (File file : allFiles)
	{ fMap[FileSystem::Path::getName(file)] = counter;
		counter++; }
	std::vector<File> kfkeys;
	kfkeys.reserve(fMap.size());
	std::vector<int> vals;
	vals.reserve(fMap.size());
	for (auto kv : fMap)
	{ kfkeys.push_back(kv.first);
		vals.push_back(kv.second);
		rev1[kv.second] = kv.first; }
    Graph g1(counter);
	Keys k = dbnew.keys();
	for (std::string key : k)
	{ for (ElementItem child : dbnew.value(key))
		{for (std::string c : child.childrenList)
		{ g1.addEdge(fMap[key], fMap[c]);}
		}}
    rfMap = g1.SCC();
	Display_StrConnComp(rfMap, rev1);
	return rfMap;
}

//Function that displays contents of index page 
void procindex(std::ofstream& outofindex, Keys dbkeys)
{
	outofindex << "<html><head><title>HTML Reference</title></head><body><pre><br><br>The Index of dependency files are as follows<br><br><br><br>";
	for (File filename : dbkeys)
	{
		std::string name = FileSystem::Path::getName(filename);
		std::string endpath = name + ".htm";
		outofindex << "<a href = \"";
		outofindex << endpath;
		outofindex << "\"";
		outofindex << ">";
		outofindex<< name;
		outofindex << "</a>";
		outofindex << "<br>";
		outofindex << "<br>";
		outofindex << "<br>";
		outofindex << "<br>";
	}
	outofindex << "<br>";
	outofindex << "<br>";
	outofindex << "</pre";
	outofindex << "</body>";
	outofindex << "</html>";
	outofindex.close();
	std::string path = "file:///" + FileSystem::Path::getFullFileSpec("../../PublishedList/index.htm");
	std::wstring spath = std::wstring(path.begin(), path.end());
	LPCWSTR swpath = spath.c_str();
	LPCWSTR a = L"open";
	LPCWSTR ie = L"iexplore.exe";
	ShellExecute(NULL, a, ie, swpath, NULL, SW_SHOWDEFAULT);
}

void callrequirements() //Function to display all requirments
{	std::cout << "\n Requirement 1 Demonstrated - Used Visual Studio 2015 and its C++ Windows Console Projects, as provided in the ECS computer labs \n";
	std::cout << "\n Requirement 2 Demonstrated - Used the C++ standard library's streams for all I/O and new and delete for all heap-based memory management\n";
	std::cout << "\n Requirement 3 Demonstrated - Provided a Publisher program that provides for creation of web pages each of which captures the content of a single C++ source code file, e.g., *.h or *.cpp.\n";
	std::cout << "\n Requirement 4 Demonstrated - Facility to expand or collapse class bodies, methods, and global functions using JavaScript and CSS properties \n";
	std::cout << "\n Requirement 5 Demonstrated - Provided a CSS style sheet that the Publisher uses to style its generated pages and a JavaScript file that provides functionality to hide and unhide sections of code for outlining, using mouse clicks \n";
	std::cout << "\n Requirement 6 Demonstrated - Embedded in each web page's <head> section links to the style sheet and JavaScript file \n\n";
	std::cout << "\n Requirement 7 Demonstrated - Embedded HTML5 links to dependent files with a label, at the top of the web page. Publisher uses functionality from my Project #2 to discover package dependencies within the published set of source files \n";
	std::cout << "\n Requirement 8 Demonstrated - Developed command line processing to define the files to publish by specifying path and file patterns \n";
	std::cout << "\n Requirement 9 Demonstrated - Demonstrated the CodePublisher functionality by publishing all the important packages in Project #3 \n";
	std::cout << "\n Requirement 10 Demonstrated - Included an automated unit test suite that demonstrates meeting of all the requirements of this project\n";
}

////////////////////////////////////
//Main function of Test Executive//
//////////////////////////////////
int main(int argc, char* argv[])
{
	CodeAnalysisExecutive codeanexec;
	try
	{
		bool succeeded = codeanexec.ProcessCommandLine(argc, argv);
		if (!succeeded)
		{
			return 1;
		}
		codeanexec.getSourceFiles();
		codeanexec.processSourceCode(true);
		std::ostringstream out;
		FileMap fileMapTemp = codeanexec.getFileMap();
		Files allFiles;
		using Pair = std::pair<Pattern, Files>;
		for (Pair pair : fileMapTemp)
		{
			for (File f : pair.second)
			{
				allFiles.push_back(f);
			}
		}  std::cout << setw(8) << "\n CSE 687 Project 3 - Dependency based CodePublisher \n";
		callrequirements();
		NoSqlDatabaseApp dbtype = Type_Table();
		Dependency dbnew = Dependency_Table(dbtype, allFiles);
		CodePublisher p; //Code publishing starts from here
        File index = "../PublishedList/index.htm";
		std::ofstream outofindex(index);
		File jsscript = "../PublishedList/jsscript.js";
		std::ofstream ofjs1(jsscript);
		File cssstyle = "../PublishedList/cssstyle.css";
		std::ofstream ofcss(cssstyle);
		ofcss << "body {background-color: #AFEEEE;}";
		ofcss << "font: 15px arial, sans-serif;";
		Keys dbkeys = dbnew.keys();
		for (Key key : dbkeys)
		{		for (ElementItem elem : dbnew.value(key))
			{
				p.publish(key, elem, ofjs1);	}
		}
		procindex(outofindex, dbkeys);
	}
catch (std::exception& excep)
{ codeanexec.flushLogger();
  std::cout << "\n\n  exception caught in Test Executive::main: " + std::string(excep.what()) + "\n\n";
  codeanexec.stopLogger();
  return 1;}
return 0; }

