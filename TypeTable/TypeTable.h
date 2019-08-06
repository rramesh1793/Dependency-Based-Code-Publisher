#pragma once
/////////////////////////////////////////////////////////////////////
//  CSE 687 Project 3-  Dependency based CodePublisher              //
//  TypeTable.h -  Type Analysis and typletable design             //
//  ver 1.0                                                        //                                                            //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      MacbookPro, Windows 10    			           //
//  Application:   CodeAnalyzerEx                                  //
//  Author:        Rajesh Ramesh            SUID:416867192		   //
/////////////////////////////////////////////////////////////////////

/*
Module Operations:
==================
This module defines 2 classes TypeAnalysis class and Element class
--> TypeAnalysis class is a key/value pair in-memory database        
Its function is to store and retrieve elements from the AST Node
-The functions defined in this class are used for Type Analysis and buidling a typetable
----------------------------------------------------------------
--> Class Element corressponds to a data record in the NoSql database  
* filename,typename,using namespace are required to be stored    
Public Interface:
=================
doActivity
Build Process:
==============
Required files
-Parser
-CppProperties
-Tokenizer
Maintenance History:
====================
ver 1.0 : 15 Mar 17
- first release
*/

#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <functional>
#include<stack>
#include <iostream>
#include "../CppProperties/CppProperties.h"
#include "../Parser/ActionsAndRules.h"
#include "../Logger/Logger.h"
#include <iostream>

#pragma warning (disable : 4101)  // disable warning re unused variable x, below
namespace CodeAnalysis
{ class Element
	{
	public:
		using Type = std::string;
		using Namespace = std::string;
		using Filename = std::string;
		//////////////////////////////////////////////
		//Type, Namespace and Filename are Metadata//
		////////////////////////////////////////////
		Property<Type> type_name;         
		Property<Namespace> name_space;   
		Property<Filename> filename;    
		std::string showchildren(); //// Displays the children
	};


	std::string Element::showchildren()
	{
		std::ostringstream out;
		out.setf(std::ios::adjustfield, std::ios::left);
		out << "\n";
		out << "    " << std::setw(10) << "Type Name"<<"\n";
		out << "    " << std::setw(10) << type_name << "\n";
		out << "    " << std::setw(10) << "_*-*-*-_*-*-*-_*-*-*-" << "\n";
		out << "    " << std::setw(10) << "Using NameSpace" << "\n";
		out << "    " << std::setw(10) << name_space << "\n"; 
	    out << "    " << std::setw(10) << "_*-*-*-_*-*-*-_*-*-*-" << "\n";
		out << "    " << std::setw(10) << "File Name" << "\n";
		out << "    " << std::setw(10) << filename << "\n";
		out << "    " << std::setw(10) << "_*-*-*-_*-*-*-_*-*-*-" << "\n\n";
		return out.str();
	}
	class NoSqlDatabaseApp
	{
	public:
		using Key = std::string;
		using Keys = std::vector<Key>;
		bool saveele(Key key, Element elem); //saveele() - saves the new element to the Database
		std::vector<Element> NoSqlDatabaseApp::value(Key key); //value(Key key) - Returns the Element of a certain key in the Database 
		Keys keys1(); //keys1() - function to return the keys of the DataBase
		void NoSqlDatabaseApp::keydisp(Keys list); //keydisp()-Displays all keys in the Database
		size_t count(); //count() - Returns count of the DataBase
	private:
		using Item = std::pair<Key, std::vector<Element>>;
		std::unordered_map<Key, std::vector<Element>> store;
	};


	std::vector<Element> NoSqlDatabaseApp::value(Key key)
	{
		std::vector<Element> vect;
		if (store.find(key) == store.end())
		{	return vect;}
		return store[key];}

	bool NoSqlDatabaseApp::saveele(Key key, Element elem)
	{  std::vector<Element> vec;
		vec.push_back(elem);
		if (store.find(key) != store.end())
			return false;
		store[key] = vec;
		return true;}

	
	typename NoSqlDatabaseApp::Keys NoSqlDatabaseApp::keys1()
	{   Keys keysdb;
		for (Item itval : store)
		{ keysdb.push_back(itval.first); }
		return keysdb; }

	size_t NoSqlDatabaseApp::count()
	{return store.size();}
	void NoSqlDatabaseApp::keydisp(Keys list)
	{   for (Key k : list)
		{std::cout << "\t" << k << "\n";}
		return;}
	class TypeAnalysis
	{
	public:
		using SPtr = std::shared_ptr<ASTNode*>;
		std::stack<std::string> stack;
		TypeAnalysis();
		void doTypeAnalysis(NoSqlDatabaseApp& db);
	private:
		void dfs(ASTNode* pNode, NoSqlDatabaseApp& db);
		AbstrSynTree& ASTref_;
		ScopeStack<ASTNode*> scopeStack_;
		Scanner::Toker& toker_;};

	//////////////////////////////////////////////////////////////////////////////////
	//TypeAnalysis() - Gets the instances of the ScopeStack,Toker and the AST Node //   
	////////////////////////////////////////////////////////////////////////////////
	inline TypeAnalysis::TypeAnalysis() :
		ASTref_(Repository::getInstance()->AST()),
		scopeStack_(Repository::getInstance()->scopeStack()),
		toker_(*(Repository::getInstance()->Toker()))
	{std::function<void()> test = [] { int x; };}

	inline bool doDisp(ASTNode* pNode)
	{	static std::string toDisplay[] = {
	   "lambda", "class", "struct", "enum", "alias", "typedef", };
		for (std::string type : toDisplay)
		{	if (pNode->type_ == type)
				return true;}
		return false;}
	inline void TypeAnalysis::dfs(ASTNode* pNode, NoSqlDatabaseApp& db)
	{	std::vector<std::string> vec;
		Element typanalele1;
		static std::string path = "";
		if (pNode->path_ != path)
		{ path = pNode->path_;}
		if (pNode->type_ == "namespace")
		{	stack.push(pNode->name_);}
		if (doDisp(pNode))
		{  typanalele1.type_name = pNode->type_;
			typanalele1.filename = pNode->package_;
			if (stack.size() == 0)
			{ typanalele1.name_space = "rajesh";}
			else
			{	typanalele1.name_space = stack.top();}
			db.saveele(pNode->name_, typanalele1);}
		if (pNode->type_ == "namespace"  && pNode->name_ == "Global Namespace")
		{	for (auto pchild : pNode->children_)
			{ if (pchild->type_ == "function" && pchild->name_ != "main")
				{	typanalele1.type_name = pchild->type_;
					typanalele1.filename = pchild->package_;
					typanalele1.name_space = pNode->name_;
					db.saveele(pchild->name_, typanalele1);}}}
		for (auto pChild : pNode->children_)
		{	if (pChild->parentType_ == "namespace")
		{		stack.push(pNode->name_);	}
		dfs(pChild, db);
		if (pChild->parentType_ == "namespace")
		{	stack.pop();}}}

	///////////////////////////////////////////
	//doTypeAnalysis  performs TypeAnalysis //
	/////////////////////////////////////////
	inline void TypeAnalysis::doTypeAnalysis(NoSqlDatabaseApp& db)
	{	ASTNode* pRoot = ASTref_.root();
		dfs(pRoot,db);
	}}




