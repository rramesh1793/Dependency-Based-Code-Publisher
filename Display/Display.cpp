//Implementation file for Display which uses Display.h

#ifdef Display
#include "Display.h"
namespace CodeAnalysis
{ int main()
	{   control c;
		Dependency dbnew;
		NoSqlDatabaseApp db;
		std::vector<std::string> allfiles;
		std::vector<vector<int>> revfileMap;
		std::unordered_map<int, File> rev;
		Display_Type_Analysis(db);
		Display_Dependency_Table(dbnew);
		Display_StrConnComp(revfileMap,rev);
		return 0;

	}
}

#endif