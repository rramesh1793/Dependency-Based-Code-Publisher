#pragma once
/////////////////////////////////////////////////////////////////////
//	CSE 687 Project 3-  Dependency based CodePublisher			   //
//  CodePublisher.h -  Class to generate htm pages                 //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Macbook Pro, Windows 10   			           //
//  Application:   CodeAnalyzerEx                                  //
//  Author:        Rajesh Ramesh  SUID:416867192         		   //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module defines a publisher class
whose functions is to generate htm pages containing links to dependent packages and contains buttons 

Public Interface:
=================
Publisher class- Generates HTM pages consisting of dependencies of packages

Build Process:
==============
Required files
-TypeTable
-Utilities
-Publisher

Maintenance History:
====================
ver 1.0 : 07 Apr 17
- first release
*/

#include<fstream>
#include<iostream>
#include<vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <ctime>
#include "../Tokenizer/Tokenizer.h"
#include "../NoSqlDataBaseApp/NoSqlDatabaseApp.h"
#include "../TypeTable/TypeTable.h"
#include "../Utilities/Utilities.h"
#include "../CodePublisher/CodePublisher.h"

using Key = std::string;
using Keys = std::vector<std::string>;
using File = std::string;
using Files = std::vector<File>;
using Pattern = std::string;
using Ext = std::string;
using FileMap = std::unordered_map<Pattern, Files>;
using Helper = Utilities::StringHelper;

//Class CodePublisher - Class that contains functions to generate htm pages that contain dependencies
class CodePublisher
{
public:
	void publish(File file, ElementItem elem, std::ofstream& ofjs);
	void getfile(ElementItem elem, std::ofstream& out);
};
//Function to generate htm pages
void CodePublisher::publish(File file1, ElementItem elem, std::ofstream& ofjs)
{   std::string path = FileSystem::Path::getPath(file1);
	std::string file = FileSystem::Path::getName(file1);
	File filepub = "../PublishedList/"+file + ".htm";
	std::ofstream out(filepub);
	std::ifstream in(file1);
	if (!in.is_open())
	{
		std::cout << "Failed - unable to open file";
	}
	else
	{	out << "<html><head> <link rel = \"" << "stylesheet\"" << " type = \"text/css\"" << "  href=\"" << "cssstyle.css\"/></head><body>";
	    out << "<head><script type=\"text/javascript\" src = \"jsscript.js\"></script></head>";
		char c;
		out << "<pre><br><br><br>";
		getfile(elem, out);
		out << "<br><br>";
		int counter = 1;
		while (in.get(c))
		{   if (in.eof())
				break;
			else if (c == '<')
				out << "&lt;";
			else if (c == '>')
				out << "&gt;";
			else if (c == '}')
			{
				out << "}";
				out << "</div>";
			}
			else if (c == '{')
			{   out << "{";
				out << "<button onclick = \"myFunc" << counter << "()\">+</button>";
				out << "<div id = \"mydiv" << counter << "\">";
				ofjs << "function myFunc" << counter << "() {var x = document.getElementById('mydiv" << counter << "');if(x.style.display == 'none') {x.style.display = 'block';}else {x.style.display = 'none';}} \n";
				counter++;
			}
			else out << c;
		}
		out << "\n</pre></body></html>";
		in.close();
		out.close();
		return;
	}}

//Function to print dependencies
void CodePublisher:: getfile(ElementItem elem, std::ofstream& out)
{
	for (File filename : elem.childrenList)
	{
		std::string half = FileSystem::Path::getPath(filename);
		std::string fname = FileSystem::Path::getName(filename);
		std::string endpath = fname + ".htm";
		out << "<a href = \""; out << endpath; out << "\"";
		out << ">"; out << fname; out << " - "; out << endpath;
		out << "</a><br>";
	}
}