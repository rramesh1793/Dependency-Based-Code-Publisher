//Implementation File For TypeTable.h
#include "../TypeTable/TypeTable.h"

namespace CodeAnalysis
{
	void main()
	{

		NoSqlDatabaseApp db;
		TypeAnalysis ta;
		ta.doTypeAnalysis(db);

		system("pause");


	}
}