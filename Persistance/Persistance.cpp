//Implementation file for Persistance

#ifdef Persistance 
#include "../Persistance/Persistance.h"

int main()
{	std::cout << "\n  Test Executive \n";
	std::cout << "\n  Creating and saving NoSqlDatabaseApp elements with string data \n";
	std::cout << "\n -------------------------------------------------------\n";
	Dependency db;
	std::vector<std::vector<int>> dbvector;
	std::unordered_map<int, File> revfile;
	toXml(db);
	toxmlstrong(dbvector,revfile);

}

#endif

