#pragma once
//////////////////////////////////////////////////////////////////////////////////////
// 	CSE 687 Project 3-  Dependency based CodePublisher	                           //
//  NoSqlDatabaseApp.h -  Class designed for operating on the dependency table    //
//  ver 1.0                                                                      //
//  Language:      Visual C++ 2008, SP1                                         //
//  Platform:      Macbook Pro, Windows 10			                           //
//  Application:   CodeAnalyzerEx                                             //
//  Author:        Rajesh Ramesh            SUID:416867192		             //
//////////////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module defines a Dependency class where its functions 
are designed to store dependency relationships

Public Interface:
=================
Element Class-ElementItem represents a data record in the NoSql database   
which needs to store the data of the child
Dependency Class
Build Process:
==============
Required files
-Tokenizer
-TypeTable
-CppProperties

Maintenance History:
====================
ver 1.0 : 15 Mar 17
- first release
*/
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include <ctime>
#include "../Tokenizer/Tokenizer.h"
#include "../TypeTable/TypeTable.h"
#include "../CppProperties/CppProperties.h"
#include "../Utilities/Utilities.h"
using Key = std::string;
using Keys = std::vector<Key>;
using File = std::string;
using Files = std::vector<File>;
using Pattern = std::string;
using Ext = std::string;
using FileMap = std::unordered_map<Pattern, Files>;
using Helper = Utilities::StringHelper;
using namespace Utilities;


class ElementItem
{ public:
	using Name = std::string;
	std::vector<std::string> childrenList;
	std::string showelement();};

/////////////////////////////////////////////////////////////////////
// NoSqlDatabaseApp class represents a key/value pair in-memory database   //
// which stores and retrieves elements                           //
//////////////////////////////////////////////////////////////////

class Dependency
{
public:
	using Key = std::string;
	using Keys = std::vector<Key>;
	Keys keys(); //keys() - returns the keys of the database
	bool save(Key key, ElementItem elem); //save(Key key) - Saves new element item to the Database
	std::vector<ElementItem> value(Key key); //value(Key key) - returns the ElementItem of a certain key in the Database
	size_t count(); //count() - Returns count of the DataBase
	void Dependency::keydisp(Keys list); //keydisp() -displays all keys in the Database
private:
	using Item = std::pair<Key,std::vector<ElementItem>>;
	std::unordered_map<Key,std::vector<ElementItem>> store;
};

typename Dependency::Keys Dependency::keys()
{   Keys keys;
	for (Item item : store)
	{keys.push_back(item.first);}
	return keys;}
size_t Dependency::count()
{return store.size();}


std::string ElementItem::showelement() //showelement() - prints the files
{
	std::ostringstream out;
	out.setf(std::ios::adjustfield, std::ios::left);
	out <<"--->"<< " Children are   " << " : ";
	std::vector<std::string> c = childrenList;
	for (Key kelemitem : c)
	{ out << "  "; out << kelemitem; }
      out << "\n";
	return out.str();}

void Dependency::keydisp(Keys list)
{ for (Key k1 : list)
	{std::cout << "\t" << k1 << "\n";}
	return;}

bool Dependency::save(Key key, ElementItem elem)
{
	std::vector<ElementItem> vec;
	vec.push_back(elem);
	if (store.find(key) != store.end())
		return false;
	store[key] = vec;
	return true;}

std::vector<ElementItem> Dependency::value(Key key)
{   ElementItem elem;
	std::vector<ElementItem> vec;
	if (store.find(key) == store.end())
	{return vec;}
	return store[key];}






