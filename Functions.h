#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <memory>
#include <math.h>

using namespace std;

struct Simplex_Element
{
	double value;
	int x;
	int y;
	Simplex_Element(double val, int xx, int yy)
	{
		value = val;
		x = xx;
		y = yy;
	}
};

class Simplex_Table
{
private:
	bool _min_max;
	int _number_of_equations;
	int _number_of_arguments;
	vector<vector<Simplex_Element>> _simplex_table;
	vector<vector<double>> _equations;
	vector<double> _conditional_values;
	vector<double> _function;
public:
	Simplex_Table();
	Simplex_Table(vector<vector<double>>& equations, vector<double>& conditional_values, vector<double>& function, int& number_of_equations, int& number_of_arguments);
	~Simplex_Table();
	const int& Give_Number_Of_Equations();
	const int& Give_Number_Of_Arguments();
	const vector<vector<Simplex_Element>>& Give_Simplex_Table();
	const vector<vector<double>>& Give_Equations();
	const vector<double>& Give_Conditional_Values();
	const vector<double>& Give_Function();
	const bool Give_Min_Max();
	void Copy(Simplex_Table to_copy);
	void Create_Simplex_Table();
	void Create_Simplex_Table_Raw();
	void Print_Problem(bool x_or_y);
	void Print_Canonized_Problem(bool x_or_y);
	void Print_Simplex_Table(bool x_or_y);
	bool Is_Solvable();
	bool Solution_Reached();
	void Opornoe_Solution(bool x_or_y);
	void Jordan_Exclusions(int solve_row, int solve_column, int solve_perem_row, int solve_perem_column);
	void Simplex_Method(bool x_or_y);
	bool Check_If_Valid();
	void Transform_Into_Twin();
	void Find_Strategy(bool x_or_y);
};
