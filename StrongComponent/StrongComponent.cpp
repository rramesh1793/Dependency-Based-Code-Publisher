//Implementation of StrongComponent.h

#ifdef StrongComponent

#include "StrongComponent.h"
int main()
{	std::vector<std::vector<int>> revfileMap;
	cout << "\n Stronly connected components in first graph \n";
	Graph g1(5);
	g1.addEdge(1, 0);
	g1.addEdge(0, 2);
	g1.addEdge(2, 1);
	g1.addEdge(0, 3);
	g1.addEdge(3, 4);
    revfileMap = g1.SCC();
	cout << "\n\n";
    for (std::vector<int> r : revfileMap)
	{ for (int a : r)
	{cout << " " << a;}
	cout << "\n";}
	return 0;}

#endif

