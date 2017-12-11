// OptimizationMethodsLab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Functions.h"

int main()
{
	Simplex_Table table;
	Simplex_Table copy;
	table.Create_Simplex_Table_Raw();
	table.Print_Simplex_Table(1);
	copy.Copy(table);
	copy.Transform_Into_Twin();
	cout << "here";
	table.Print_Problem(1);
	table.Print_Canonized_Problem(1);
	copy.Print_Problem(0);
	copy.Print_Canonized_Problem(0);
	table.Print_Simplex_Table(1);
	table.Opornoe_Solution(1);
	table.Simplex_Method(1);
	copy.Print_Simplex_Table(0);
	copy.Opornoe_Solution(0);
	copy.Simplex_Method(0);
	copy.Print_Simplex_Table(0);
	table.Find_Strategy(1);
	copy.Find_Strategy(0);
	system("pause");
	return 0;

}

