#pragma once
/////////////////////////////////////////////////////////////////////
//	CSE 687 Project 2- Type-based Depanal Analysis			   //
//  Strong Component.h -  Analyses the Strong Components           //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Macbook Pro, Windows 10   			           //
//  Application:   CodeAnalyzerEx                                  //
//  Author:        Rajesh Ramesh SUID:416867192          		   //
/////////////////////////////////////////////////////////////////////

/*
Module Operations:
==================
A control class is defined in this module where 
the functions defined in this control class match the Depanal keys
to find out the strong components

Public Interface:
=================
StrongComp;
SCC;

Maintenance History:
====================
ver 1.0 : 15 Mar 17
- first release
*/
#include<iostream>
#include <list>
#include <stack>
#include<math.h>
#include<algorithm>
#include<vector>
#include <unordered_map>
#define NIL -1
using namespace std;

/////////////////////////////////////////////////////////////////////
// The graph class stores the Depanal files as a graph         //
// and finds the strong Component class                          //
// ///////////////////////////////////////////////////////////////
class Graph
{
	int V;    
	list<int> *adj;    
	void StrongComp(int u, int disc[], int low[],
	stack<int> *st, bool stackMember[]);
	std::vector<std::vector<int>> bigvec;
public:
	Graph(int V);   
	void addEdge(int v, int w);   
	std::vector<std::vector<int>>  SCC(); };

Graph::Graph(int V)
{ this->V = V;
 adj = new list<int>[V];}

void Graph::addEdge(int v, int w)
{ adj[v].push_back(w);}

////////////////////////////////////////////////
//StrongComp stores the strong component values //
//////////////////////////////////////////////
void Graph::StrongComp(int u, int disc[], int low[], stack<int> *st,bool stackMember[])
{ std::vector<int> vector;
 static int time = 0;
 disc[u] = low[u] = ++time;
 st->push(u);
 stackMember[u] = true;
 list<int>::iterator it;
 for (it = adj[u].begin(); it != adj[u].end(); ++it)
{ int v = *it;  
 if (disc[v] == -1)
{ StrongComp(v, disc, low, st, stackMember);
 low[u] = min(low[u], low[v]);}
else if (stackMember[v] == true)
low[u] = min(low[u], disc[v]);}
int w = 0;  
vector.erase(vector.begin(), vector.end());
if (low[u] == disc[u])
{ while (st->top() != u)
{ w = (int)st->top();
//cout << w << " ";
vector.push_back(w);
stackMember[w] = false;
st->pop();}
w = (int)st->top();
//cout << w << "\n";
vector.push_back(w);
stackMember[w] = false;
st->pop();}
bigvec.push_back(vector);}
//Function to call SCC Utilities
std::vector<std::vector<int>> Graph::SCC()
{
    int *disc = new int[V];
	int *low = new int[V];
	bool *stackMember = new bool[V];
	stack<int> *st = new stack<int>();
	for (int i = 0; i < V; i++)
	{   disc[i] = NIL;
		low[i] = NIL;
		stackMember[i] = false;}
	for (int i = 0; i < V; i++)
		if (disc[i] == NIL)
		StrongComp(i, disc, low, st, stackMember);
	return bigvec;
}

