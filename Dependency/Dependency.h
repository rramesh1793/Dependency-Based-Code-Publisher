
#pragma once
/////////////////////////////////////////////////////////////////////
//	CSE 687 Project 3-  Dependency based CodePublisher			   //
//  Dependency.h -  Class analysing dependencies between Files     //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Macbook Pro, Windows 10   			           //
//  Application:   CodeAnalyzerEx                                  //
//  Author:        Rajesh Ramesh  SUID:416867192         		   //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module defines a control class class
whose functions match the type table keys and find out dependencies

Public Interface:
=================
doActivity -obtains and stores dependencies between files

Build Process:
==============
Required files
-TypeTable
-CppProperties
-Utilities
-Tokenizer
-NoSqlDatabaseApp

Maintenance History:
====================
ver 1.0 : 15 Mar 17
- first release
updated 
ver 2.0 : 07 Apr 17
*/

#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <ctime>
#include "../CppProperties/CppProperties.h"
#include "../Tokenizer/Tokenizer.h"
#include "../TypeTable/TypeTable.h"
#include "../Utilities/Utilities.h"
#include "../NoSqlDatabaseApp/NoSqlDatabaseApp.h"
#include "../CodePublisher/CodePublisher.h"

using Key = std::string;
using Keys = std::vector<Key>;
using File = std::string;
using Files = std::vector<File>;
using Pattern = std::string;
using Ext = std::string;
using FileMap = std::unordered_map<Pattern, Files>;


namespace CodeAnalysis
{
	class control // represents control flow to obtain the dependency
	{
	public:
		int doActivity(NoSqlDatabaseApp& db, Dependency& dbnew, Files allfiles);
	};
	int control::doActivity(NoSqlDatabaseApp& db, Dependency& dbnew, Files allfiles)
	{

		CodePublisher p;

		Keys keys = db.keys1();
		std::vector<ElementItem> veci;
		for (File fiall : allfiles)
		{
			ElementItem elitdep;

			try
			{
				std::string file = FileSystem::Path::getName(fiall);
				std::ifstream in(fiall);
				if (!in.good())
				{
					std::cout << "\n  unable to open " << file << "\n\n";
					return 1;
				}
				Scanner::Toker toker;
				toker.returnComments(false);
				toker.attach(&in);
				do
				{
					std::string token = toker.getTok();
					for (std::string key : keys)
					{
						if (key == token)
						{
							for (Element veckdep : db.value(key))
							{
								elitdep.childrenList.push_back(veckdep.filename);
								std::sort(elitdep.childrenList.begin(), elitdep.childrenList.end());
								elitdep.childrenList.erase(std::unique(elitdep.childrenList.begin(), elitdep.childrenList.end()), elitdep.childrenList.end());
							}

						}
					}


				} while (in.good());

				dbnew.save(fiall, elitdep);

				

			}
			catch (std::logic_error& excepti)
			{
				std::cout << "\n  " << excepti.what();
			}
		}


		return 0;
	}
}










