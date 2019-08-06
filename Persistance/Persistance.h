/////////////////////////////////////////////////////////////////////
//  Persistance.h -  Package that supports XMl Parsing              //
//  ver 1.0                                                        //
//  CSE 687 Project 3-  Dependency based CodePublisher              //                                                 //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Macbook Pro, Windows 10		     	           //
//  Application:   NoSql Database                                  //
//  Author:       Rajesh Ramesh  SUID:416867192          		   //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module defines a Persistance class whose
functions populate the XML document and
then return the dataBase object
Public Interface:
=================
toXml
fromXml
Build Process:
==============
Required files
- convert.h
-CppProperties
-NoSQLDataBase
Maintenance History:
====================
ver 1.0 : 15 Mar 17
- first release
*/

#pragma once
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../Convert/Convert.h"
#include "../StrHelper.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include "../NoSQLDataBaseApp/NoSQLDataBaseApp.h"
#include "../Dependency/Dependency.h"
#include "../CppProperties/CppProperties.h"
#include<fstream>
using Key = std::string;
using Keys = std::vector<std::string>;
using namespace XmlProcessing;
using SPtr = std::shared_ptr<AbstractXmlElement>;
using Path = std::string;
using File = std::string;
using Files = std::vector<File>;
using Pattern = std::string;
using Ext = std::string;
using FileMap = std::unordered_map<Pattern, Files>;

/////////////////////////////////////////////////////////////////////////////////////////////////
//toXml() - returns a xml string and used to persist values in the XML Document for dependency//
///////////////////////////////////////////////////////////////////////////////////////////////
std::string toXml(Dependency depb)
{
    std::string xml;
	XmlDocument doc;
    Keys allkeys = depb.keys();
    SPtr pRoot = makeTaggedElement("DatabaseRec");
	doc.docElement() = pRoot;
    for (Key keyss : allkeys)
	{  SPtr pNameElem = makeTaggedElement("Record");
	   pRoot->addChild(pNameElem);
       SPtr elekey = makeTaggedElement("EleKey");
	   pNameElem->addChild(elekey);
	   SPtr tenamekey = makeTextElement(keyss);
	   elekey->addChild(tenamekey);
	  SPtr ele15 = makeTaggedElement("ChilKeys");
	  pNameElem->addChild(ele15);
      for (ElementItem k : depb.value(keyss))
	 {  for (std::string s : k.childrenList)
	  {		  SPtr techild = makeTaggedElement("Child");
			  ele15->addChild(techild);
			  SPtr childvalue = makeTextElement(s);
			  techild->addChild(childvalue);  } }}
	xml = doc.toString();
	try
	{std::ofstream xmlsam("../raj.xml");
	 xmlsam << xml;
	 xmlsam.close();}
	catch (const std::exception& excep)
	{std::cout << excep.what();}
    return xml;}


///////////////////////////////////////////////////////////////////////////////////////////////
//toxmlstrong - Returns a xml string and used to persist values in the XML Document for SCC //
/////////////////////////////////////////////////////////////////////////////////////////////
std::string toxmlstrong(std::vector<std::vector<int>>& db, std::unordered_map<int, File>& rev)
{
	std::string xml;
	XmlDocument doc;
	SPtr pRoot = makeTaggedElement("DBX");
	doc.docElement() = pRoot;
	for (std::vector<int> r : db)
	{	SPtr ele15 = makeTaggedElement("SCC_Component");
		pRoot->addChild(ele15);
		for  (int a : r)
		{	SPtr techild = makeTaggedElement("Child");
			ele15->addChild(techild);
			SPtr childvalue = makeTextElement(rev[a]);
			techild->addChild(childvalue);
			}}
	xml = doc.toString();
	try
	{ std::ofstream xmlsam("../rajesh.xml");
		xmlsam << xml;
		xmlsam.close();
	}
	catch (const std::exception& ex)
	{	std::cout << ex.what();}
	return xml;}





