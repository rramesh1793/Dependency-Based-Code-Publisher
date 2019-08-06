//Implementation file for Dependency.h

#ifdef Dependency

#include "Dependency.h"
#include "../TypeTable/TypeTable.h"

namespace CodeAnalysis
{void main()
{NoSqlDatabaseApp db;
Dependency dbnew;
control c;
std::vector<std::string> allfiles;
c.doActivity(db, dbnew, allfiles);}}

#endif