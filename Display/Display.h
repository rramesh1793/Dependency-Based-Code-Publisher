#pragma once
/////////////////////////////////////////////////////////////////////
//  CSE 687 Project 3-  Dependency based CodePublisher             //
//  Display.h -  File to print Type table, and Dependency Table    //
//                                                                 //
//  version 1.0                                                    //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Macbook Pro, Windows 10   			           //
//  Application:   CodeAnalyzerEx                                  //
//  Author:        Rajesh Ramesh   SU ID:416867192	         	   //
/////////////////////////////////////////////////////////////////////

/*
Module Operations:
==================
This module defines three display functions:
Display_Type_Analysis - Displays the Type Table
Display_StrConnComp - Displays the Strongly Connected Components
Display_Dependency_Table - Displays the Dependency Table

Public Interface:
=================
Display_Type_Analysis - displays the Type table
Display_StrConnComp - displays the strongly connected components
Display_Dependency_Table - displays the dependency table

Build Process:
==============
Required files to execute this are:
-Dependency
-TypeTable
-StrongComponenent
-Utilities

Maintenance History:
====================
ver 2.0 : 07 Apr 17

*/

#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <functional>
#include <map>
#include <unordered_map>
#include <exception>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include "../FileSystem/FileSystem.h"
#include "../FileMgr/FileMgr.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"
#include "../AbstractSyntaxTree/AbstrSynTree.h"
#include "../Logger/Logger.h"
#include "../Utilities/Utilities.h"
#include "../Analyzer/Executive.h"
#include "../Parser/Parser.h"
#include "../TypeTable/TypeTable.h"
#include "../Dependency/Dependency.h"
#include "../StrongComponent/StrongComponent.h"
#include "../StrongComponent/StrongComponent.h"
#include "../Persistance/Persistance.h"

using Key = std::string;
using Keys = std::vector<Key>;
using Rslt = Logging::StaticLogger<0>;  
using Demo = Logging::StaticLogger<1>;  
using Dbug = Logging::StaticLogger<2>; 
using Path = std::string;
using File = std::string;
using Files = std::vector<File>;
using Pattern = std::string;
using Ext = std::string;
using FileMap = std::unordered_map<Pattern, Files>;
using namespace CodeAnalysis;

//Displays the Type Table
void Display_Type_Analysis(NoSqlDatabaseApp db)
{   TypeAnalysis tanal;
	tanal.doTypeAnalysis(db);
    Keys keys1 = db.keys1();
	for (std::string kchtanal : keys1)
{ for (Element elem : db.value(kchtanal))
 { std::cout << "\n  " << kchtanal << ":   ";
   std::cout << elem.showchildren();}}}
//Displays strong components
void Display_StrConnComp(std::vector<vector<int>> rfMap, std::unordered_map<int, File> rev)
{ for (std::vector<int> rscc : rfMap)
 { for (int scc : rscc)
   {	cout << " " << rev[scc];	}
		cout << "\n";} }

//Displays Dependency Table
void Display_Dependency_Table(Dependency dbnew)
{ Keys key1 = dbnew.keys();
  for (std::string key : key1)
{	for (auto elem : dbnew.value(key))
  {	std::cout << "\n  " << key << ":   ";
    std::cout << elem.showelement();}}}




