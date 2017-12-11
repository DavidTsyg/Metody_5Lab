#include "stdafx.h"
#include "Functions.h"

using namespace std;

Simplex_Table::Simplex_Table() {}
Simplex_Table::Simplex_Table(vector<vector<double>>& equations, vector<double>& conditional_values, vector<double>& function, int& number_of_equations, int& number_of_arguments)
{
	_equations = equations;
	_conditional_values = conditional_values;
	_function = function;
	_number_of_equations = number_of_equations;
	_number_of_arguments = number_of_arguments;
	vector<Simplex_Element> buffer_vector;
	for (auto i = 0; i < _number_of_equations; ++i)
	{
		buffer_vector.push_back(Simplex_Element(_conditional_values[i], _number_of_arguments + 1 + i, 0));
		for (auto j = 0; j < _equations[0].size(); ++j)
			buffer_vector.push_back(Simplex_Element(_equations[i][j], _number_of_arguments + 1 + i, j + 1));
		_simplex_table.push_back(buffer_vector);
		buffer_vector.clear();
	}
	for (auto i = 0; i < _function.size(); ++i)
		buffer_vector.push_back(Simplex_Element((_function[i])*(-1), _number_of_arguments + 1 + i, 0));
	_simplex_table.push_back(buffer_vector);
}
Simplex_Table::~Simplex_Table() {}

void Simplex_Table::Copy(Simplex_Table to_copy)
{
	_simplex_table.clear();
	for (auto i = to_copy.Give_Simplex_Table().begin(); i != to_copy.Give_Simplex_Table().end(); ++i)
	{
		_simplex_table.push_back(*i);
	}
	_equations.clear();
	for (auto i = to_copy.Give_Equations().begin(); i != to_copy.Give_Equations().end(); ++i)
	{
		_equations.push_back(*i);
	}
	_conditional_values.clear();
	for (auto i = to_copy.Give_Conditional_Values().begin(); i != to_copy.Give_Conditional_Values().end(); ++i)
	{
		_conditional_values.push_back(*i);
	}
	_function.clear();
	for (auto i = to_copy.Give_Function().begin(); i != to_copy.Give_Function().end(); ++i)
	{
		_function.push_back(*i);
	}
	_min_max = to_copy.Give_Min_Max();
	_number_of_equations = to_copy.Give_Number_Of_Equations();
	_number_of_arguments = to_copy.Give_Number_Of_Arguments();
}

const int& Simplex_Table::Give_Number_Of_Equations() { return _number_of_equations; }
const int& Simplex_Table::Give_Number_Of_Arguments() { return _number_of_arguments; }
const vector<vector<Simplex_Element>>& Simplex_Table::Give_Simplex_Table() { return _simplex_table; }
const vector<vector<double>>& Simplex_Table::Give_Equations() { return _equations; }
const vector<double>& Simplex_Table::Give_Conditional_Values() { return _conditional_values; }
const vector<double>& Simplex_Table::Give_Function() { return _function; }
const bool Simplex_Table::Give_Min_Max() { return _min_max; }

void Simplex_Table::Create_Simplex_Table()
{
	double buffer;
	vector<Simplex_Element> buffer_vector;
	cout << "min or max (for max input 1, for min input 0) : ";
	cin >> _min_max;
	cout << "Input the number of equations ( more than 0 ) : ";
	cin >> _number_of_equations;
	while (_number_of_equations == 0)
	{
		cout << "Input the number of equations ( more than 0 ) : ";
		cin >> _number_of_equations;
	}
	cout << "Input the number of arguments ( more than 0 ) : ";
	cin >> _number_of_arguments;
	while (_number_of_arguments == 0)
	{
		cout << "Input the number of arguments ( more than 0 ) : ";
		cin >> _number_of_arguments;
	}

	if (_number_of_equations > _number_of_arguments)
	{
		cout << "The number of arguments is lesss than the number of equations";
		exit(EXIT_FAILURE);
	}
	cout << "Now filling up equations" << endl;
	for (auto i = 0; i < _number_of_equations; ++i)
	{
		double buffer;
		vector<double> empty;
		_equations.push_back(empty);
		for (auto j = 0; j < _number_of_arguments; ++j)
		{
			cout << "Input the multiplier by the number : ";
			cin >> buffer;
			_equations[i].push_back(buffer);
		}
		cout << "Input the conditional value : ";
		cin >> buffer;
		_conditional_values.push_back(buffer);
	}
	cout << "Creating the function" << endl;
	cout << "Input the free value : ";
	cin >> buffer;
	_function.push_back(buffer);
	cout << "Input the funtion arguments" << endl;
	for (auto i = 0; i < _number_of_arguments; ++i)
	{
		cout << "x" << i + 1 << " : ";
		cin >> buffer;
		_function.push_back(buffer);
	}
	for (auto i = 0; i < _number_of_equations; ++i)
	{
		buffer_vector.push_back(Simplex_Element(_conditional_values[i], _number_of_arguments + 1 + i, 0));
		for (auto j = 0; j < _equations[0].size(); ++j)
			buffer_vector.push_back(Simplex_Element(_equations[i][j], _number_of_arguments + 1 + i, j + 1));
		_simplex_table.push_back(buffer_vector);
		buffer_vector.clear();
	}
	for (auto i = 0; i < _function.size(); ++i)
	{
		if (!_min_max)
		{
			if (_function[i] != 0)
				buffer_vector.push_back(Simplex_Element(_function[i], _number_of_equations + 1, i));
			else
				buffer_vector.push_back(Simplex_Element((_function[i]) * (-1), _number_of_equations + 1, i));
		}
		else
		{
			if (_function[i] != 0)
				buffer_vector.push_back(Simplex_Element(_function[i], _number_of_equations + 1, i));
			else
				buffer_vector.push_back(Simplex_Element(_function[i], _number_of_equations + 1, i));
		}
	}
	_simplex_table.push_back(buffer_vector);

}

void Simplex_Table::Create_Simplex_Table_Raw()
{
	_simplex_table.clear();
	double buffer;
	vector<Simplex_Element> buffer_vector;
	_min_max = 1;
	_number_of_equations = 5;
	_number_of_arguments = 4;
	double first_row[] = { 1, 13, 2, 4, 0 };
	double second_row[] = { 1, 7, 6, 10, 14 };
	double third_row[] = { 1, 8, 14, 6, 3 };
	double fourth_row[] = { 1, 3, 18, 18, 0 };
	double fifth_row[] = { 1, 8, 7, 11, 14 };
	double sixth_row[] = { 0, 1, 1, 1, 1 };
	vector<double> empty;
	_equations.clear();
	_equations.push_back(empty);
	for (auto j = 0; j < 4; ++j)
	{
		_equations[0].push_back(first_row[j + 1]);
	}
	_equations.push_back(empty);
	for (auto j = 0; j < 4; ++j)
	{
		_equations[1].push_back(second_row[j + 1]);
	}
	_equations.push_back(empty);
	for (auto j = 0; j < 4; ++j)
	{
		_equations[2].push_back(third_row[j + 1]);
	}
	_equations.push_back(empty);
	for (auto j = 0; j < 4; ++j)
	{
		_equations[3].push_back(fourth_row[j + 1]);
	}
	_equations.push_back(empty);
	for (auto j = 0; j < 4; ++j)
	{
		_equations[4].push_back(fifth_row[j + 1]);
	}
	_conditional_values.clear();
	_conditional_values.push_back(first_row[0]); _conditional_values.push_back(second_row[0]); _conditional_values.push_back(third_row[0]); _conditional_values.push_back(fourth_row[0]); _conditional_values.push_back(fifth_row[0]);
	_function.clear();
	for (auto i = 0; i < 5; ++i)
	{
		_function.push_back(sixth_row[i]);
	}
	for (auto i = 0; i < _number_of_equations ; ++i)
	{
		buffer_vector.push_back(Simplex_Element(_conditional_values[i], _number_of_arguments + 1 + i, 0));
		for (auto j = 0; j < _equations[0].size(); ++j)
			buffer_vector.push_back(Simplex_Element(_equations[i][j], _number_of_arguments + 1 + i, j + 1));
		_simplex_table.push_back(buffer_vector);
		buffer_vector.clear();
	}

	for (auto i = 0; i < _function.size(); ++i)
	{
		buffer_vector.push_back(Simplex_Element(_function[i], _number_of_equations + _number_of_arguments, i));
	}
	_simplex_table.push_back(buffer_vector);
}

void Simplex_Table::Print_Problem(bool x_or_y)
{
	if (x_or_y)
	{
		for (auto i = 0; i < _simplex_table.size() - 1; ++i)
		{
			for (auto j = 1; j < _simplex_table[0].size() - 1; ++j)
			{
				if (_simplex_table[i][j].value != 0)
				{
					if (_simplex_table[i][j].value > 0)
						cout << _simplex_table[i][j].value << "y" << j << " + ";
					else
						cout << _simplex_table[i][j].value*(-1) << "y" << j << " + ";
				}
				else
					continue;
			}
			if (_simplex_table[i][_simplex_table[i].size() - 1].value != 0)
			{
				if (_simplex_table[i][_simplex_table[i].size() - 1].value > 0)
					cout << _simplex_table[i][_simplex_table[i].size() - 1].value << "y" << _simplex_table[0].size() << " <= h" << endl;
				else
					cout << _simplex_table[i][_simplex_table[i].size() - 1].value*(-1) << "y" << _simplex_table[0].size() << " <= h" << endl;
			}
			else
				cout << " <= h" << endl;
		}
		for (auto i = 0; i < _simplex_table[0].size() - 1; ++i)
		{
			cout << "y" << i + 1<< " + ";
		}
		cout << "y" << _simplex_table[0].size()<< " = 1" << endl;
	}
	else
	{
		for (auto i = 0; i < _simplex_table.size() - 1; ++i)
		{
			for (auto j = 1; j < _simplex_table[0].size() - 1; ++j)
			{
				if (_simplex_table[i][j].value != 0)
				{
					if (_simplex_table[i][j].value > 0)
						cout << _simplex_table[i][j].value << "x" << j << " + ";
					else
						cout << _simplex_table[i][j].value*(-1) << "x" << j  << " + ";
				}
				else
					continue;
			}
			if (_simplex_table[i][_simplex_table[i].size() - 1].value != 0)
			{
				if (_simplex_table[i][_simplex_table[i].size() - 1].value > 0)
					cout << _simplex_table[i][_simplex_table[i].size() - 1].value << "x" << _simplex_table[0].size() << " >= g" << endl;
				else
					cout << _simplex_table[i][_simplex_table[i].size() - 1].value*(-1) << "x" << _simplex_table[0].size() << " >= g" << endl;
			}
			else
				cout << " >= g" << endl;
		}
		for (auto i = 0; i < _simplex_table[0].size() - 1; ++i)
		{
			cout << "x" << i + 1 << " + ";
		}
		cout << "x" << _simplex_table[0].size() << " = 1" << endl;
	}
}

void Simplex_Table::Print_Canonized_Problem(bool x_or_y)
{
	if (x_or_y)
	{
		for (auto i = 0; i < _simplex_table.size() - 1; ++i)
		{
			for (auto j = 1; j < _simplex_table[0].size() - 1; ++j)
			{
				if (_simplex_table[i][j].value != 0)
				{
					if (_simplex_table[i][j].value > 0)
						cout << _simplex_table[i][j].value << "v" << j << " + ";
					else
						cout << _simplex_table[i][j].value*(-1) << "v" << j << " + ";
				}
				else
					continue;
			}
			if (_simplex_table[i][_simplex_table[i].size() - 1].value != 0)
			{
				if (_simplex_table[i][_simplex_table[i].size() - 1].value > 0)
					cout << _simplex_table[i][_simplex_table[i].size() - 1].value << "v" << _simplex_table[0].size() << " <= 1" << endl;
				else
					cout << _simplex_table[i][_simplex_table[i].size() - 1].value*(-1) << "v" << _simplex_table[0].size() << " <= 1" << endl;
			}
			else
				cout << " <= 1" << endl;
		}
		for (auto i = 0; i < _simplex_table[0].size() - 1; ++i)
		{
			cout << "v" << i + 1 << " + ";
		}
		cout << "v" << _simplex_table[0].size() << " = 1/h" << endl;
	}
	else
	{
		for (auto i = 0; i < _simplex_table.size() - 1; ++i)
		{
			for (auto j = 1; j < _simplex_table[0].size() - 1; ++j)
			{
				if (_simplex_table[i][j].value != 0)
				{
					if (_simplex_table[i][j].value > 0)
						cout << _simplex_table[i][j].value << "u" << j << " + ";
					else
						cout << _simplex_table[i][j].value*(-1) << "u" << j << " + ";
				}
				else
					continue;
			}
			if (_simplex_table[i][_simplex_table[i].size() - 1].value != 0)
			{
				if (_simplex_table[i][_simplex_table[i].size() - 1].value > 0)
					cout << _simplex_table[i][_simplex_table[i].size() - 1].value << "u" << _simplex_table[0].size() << " >= 1" << endl;
				else
					cout << _simplex_table[i][_simplex_table[i].size() - 1].value*(-1) << "u" << _simplex_table[0].size() << " >= 1" << endl;
			}
			else
				cout << " >= g" << endl;
		}
		for (auto i = 0; i < _simplex_table[0].size() - 1; ++i)
		{
			cout << "u" << i + 1 << " + ";
		}
		cout << "u" << _simplex_table[0].size() << " = 1/g" << endl;
	}
}

void Simplex_Table::Print_Simplex_Table(bool x_or_y)
{
	cout << "This is the simplex table" << endl;
	string buffer;
	cout << std::setw(8) << " ";
	cout << std::setw(8) << "Si0";
	if (x_or_y)
	{

		for (auto i = 1; i < _simplex_table[0].size(); ++i)
		{
			buffer = "v";
			buffer += to_string((_simplex_table[0][i]).y);
			cout << std::setw(8) << buffer;
		}
		cout << endl;
		for (auto i = 0; i < _simplex_table.size() - 1; ++i)
		{
			buffer = "v";
			buffer += to_string(_simplex_table[i][0].x);
			cout << std::setw(8) << buffer;
			for (auto j = 0; j < _simplex_table[i].size(); ++j)
			{
				cout << std::setw(8) << defaultfloat << std::setprecision(3) << _simplex_table[i][j].value;
			}
			cout << endl;
		}
	}
	else
	{
		for (auto i = 1; i < _simplex_table[0].size(); ++i)
		{
			buffer = "u";
			buffer += to_string((_simplex_table[0][i]).y);
			cout << std::setw(8) << buffer;
		}
		cout << endl;
		for (auto i = 0; i < _simplex_table.size() - 1; ++i)
		{
			buffer = "u";
			buffer += to_string(_simplex_table[i][0].x);
			cout << std::setw(8) << buffer;
			for (auto j = 0; j < _simplex_table[i].size(); ++j)
			{
				cout << std::setw(8) << defaultfloat << std::setprecision(3) << _simplex_table[i][j].value;
			}
			cout << endl;
		}
	}
	cout << std::setw(8) << "F";
	for (auto i = 0; i < (_simplex_table.back()).size(); ++i)
	{
		cout << std::setw(8) << defaultfloat << std::setprecision(3) << ((_simplex_table.back())[i]).value;
	}
	cout << endl << endl;
}

bool Simplex_Table::Is_Solvable()
{
	int solvable = 1;
	int check_row = -1;

	for (auto i = 0; i < _simplex_table.size() - 1; ++i)
	{
		if (_simplex_table[i][0].value < 0)
		{
			check_row = i;
			solvable = 0;
			break;
		}
	}
	if (check_row != -1)
	{
		for (auto j = 1; j < _simplex_table.back().size(); ++j)
		{
			if (_simplex_table[check_row][j].value < 0)
			{
				solvable = 1;
			}
		}
	}
	return solvable;
}

bool Simplex_Table::Solution_Reached()
{
	bool no_negatives = 1, no_positives = 1;
	for (auto i = 0; i < _simplex_table.size() - 1; ++i)
	{
		if (_simplex_table[i][0].value < 0)
		{
			no_negatives = 0;
			break;
		}
	}
	for (auto i = 1; i < _simplex_table.back().size(); ++i)
	{
		if (_simplex_table.back()[i].value > 0)
		{
			no_positives = 0;
			break;
		}
	}
	if (no_negatives && no_positives)
		return 1;
	else
		return 0;
}

void Simplex_Table::Jordan_Exclusions(int solve_row, int solve_column, int solve_perem_column, int solve_perem_row)
{
	vector<vector<double>> buffer_vector_vector;
	vector<double> buffer_vector;
	double solve_value = _simplex_table[solve_row][solve_column].value;
	for (auto i = 0; i < _simplex_table.back().size(); ++i)
	{
		_simplex_table[solve_row][i].x = solve_perem_row;
	}
	for (auto i = 0; i < _simplex_table.size(); ++i)
	{
		_simplex_table[i][solve_column].y = solve_perem_column;
	}
	for (auto i = 0; i < _simplex_table.size(); ++i)
	{
		for (auto j = 0; j < _simplex_table.back().size(); ++j)
		{
			if (j != solve_column)
			{
				if (i == solve_row)
					buffer_vector.push_back(_simplex_table[i][j].value / solve_value);
				else
				{
					buffer_vector.push_back(_simplex_table[i][j].value - ((_simplex_table[solve_row][j].value * _simplex_table[i][solve_column].value) / solve_value));
				}
			}
			else
			{
				if (i == solve_row)
					buffer_vector.push_back(((double)1) / solve_value);
				else
					buffer_vector.push_back(0 - ((((double)1) * _simplex_table[i][solve_column].value) / solve_value));
			}
		}
		buffer_vector_vector.push_back(buffer_vector);
		buffer_vector.clear();
	}
	for (auto i = 0; i < _simplex_table.size(); ++i)
	{
		for (auto j = 0; j < _simplex_table.back().size(); ++j)
		{
			_simplex_table[i][j].value = buffer_vector_vector[i][j];
		}
	}
	buffer_vector.clear();
}

void  Simplex_Table::Opornoe_Solution(bool x_or_y)
{
	int solve_perem_column;
	int solve_perem_row;
	int solve_row;
	int solve_column;
	double solve_value;
	if (Is_Solvable())
	{
		for (auto i = 0; i < _simplex_table.size() - 1; ++i)
		{
			if (_simplex_table[i][0].value < 0)
			{
				solve_row = i;
				solve_perem_row = _simplex_table[i][0].x;
				for (auto j = 1; j < _simplex_table.back().size(); ++j)
				{
					if (_simplex_table[i][j].value < 0)
					{
						solve_column = j;
						solve_perem_column = _simplex_table[i][j].y;
						solve_value = _simplex_table[i][j].value;
						Jordan_Exclusions(solve_row, solve_column, solve_perem_row, solve_perem_column);
						if (x_or_y)
						{
							cout << "Solve element is " << solve_value << " with basis perem v" << solve_perem_row << " and free perem v" << solve_perem_column << endl;
							Print_Simplex_Table(1);
						}
						else
						{
							cout << "Solve element is " << solve_value << " with basis perem u" << solve_perem_column << " and free perem u" << solve_perem_row << endl;
							Print_Simplex_Table(0);
						}
						break;
					}
				}
			}
		}
		cout << "Base solution" << endl;
		if (x_or_y)
			Print_Simplex_Table(1);
		else
			Print_Simplex_Table(0);
		cout << endl;
	}
	else
	{
		if (x_or_y)
			Print_Simplex_Table(1);
		else
			Print_Simplex_Table(0);
		cout << "Unsolvable simplex table" << endl;
	}
}
void Simplex_Table::Simplex_Method(bool x_or_y)
{
	bool out_of_negatives = 0;
	bool out_of_positives = 0;
	double min_negative;
	double max_positive;
	double min_pos_div;
	int solve_perem_column;
	int solve_perem_row;
	int solve_row;
	int solve_column;
	double solve_value;
	vector<vector<double>> buffer_vector_vector;
	vector<double> buffer_vector;
	if (Is_Solvable())
	{
		while (!Solution_Reached())
		{
			for (auto i = 0; i < _simplex_table.size() - 1; ++i)
			{
				if (_simplex_table[i][0].value < 0)
				{
					solve_row = i;
					solve_perem_row = _simplex_table[i][0].x;
					for (auto j = 1; j < _simplex_table.back().size(); ++j)
					{
						if (_simplex_table[i][j].value < 0)
						{
							solve_column = j;
							solve_perem_column = _simplex_table[i][j].y;
							solve_value = _simplex_table[i][j].value;
							Jordan_Exclusions(solve_row, solve_column, solve_perem_row, solve_perem_column);
							if (x_or_y)
							{
								cout << "Solve element is " << solve_value << " with basis perem v" << solve_perem_row << " and free perem v" << solve_perem_column << endl;
								Print_Simplex_Table(1);
							}
							else
							{
								cout << "Solve element is " << solve_value << " with basis perem u" << solve_perem_column << " and free perem u" << solve_perem_row << endl;
								Print_Simplex_Table(0);
							}
							break;
						}
					}
				}
			}
			max_positive = 0;
			out_of_positives = 1;
			for (auto i = 1; i < _simplex_table.back().size(); ++i)
			{
				if (_simplex_table.back()[i].value > 0)
				{
					out_of_positives = 0;
					max_positive = _simplex_table.back()[i].value;
					solve_column = i;
					solve_perem_column = _simplex_table.back()[i].y;
					break;
				}

			}
			for (auto i = 1; i < _simplex_table.back().size(); ++i)
			{
				if (_simplex_table.back()[i].value > max_positive)
				{
					out_of_positives = 0;
					max_positive = _simplex_table.back()[i].value;
					solve_column = i;
					solve_perem_column = _simplex_table.back()[i].y;
				}
			}
			if (out_of_positives == 1)
				break;
			for (auto i = 0; i < _simplex_table.size() - 1; ++i)
			{
				if (_simplex_table[i][solve_column].value != 0)
				{
					if ((_simplex_table[i][0].value) / (_simplex_table[i][solve_column].value) > 0)
					{
						min_pos_div = (_simplex_table[i][0].value) / (_simplex_table[i][solve_column].value);
						solve_row = i;
						solve_perem_row = _simplex_table[i][0].x;
						break;
					}
				}
				else
					continue;
			}
			for (auto i = 0; i < _simplex_table.size() - 1; ++i)
			{
				if (_simplex_table[i][solve_column].value != 0)
				{
					if (((_simplex_table[i][0].value) / (_simplex_table[i][solve_column].value) > 0) && ((_simplex_table[i][0].value) / (_simplex_table[i][solve_column].value) < min_pos_div))
					{
						min_pos_div = (_simplex_table[i][0].value) / (_simplex_table[i][solve_column].value);
						solve_row = i;
						solve_perem_row = _simplex_table[i][0].x;
					}
				}
				else
					continue;
			}
			solve_value = _simplex_table[solve_row][solve_column].value;
			if(x_or_y)
				cout << "Solve element is " << solve_value << " with basis perem v" << solve_perem_row << " and free perem v" << solve_perem_column << endl;
			else
				cout << "Solve element is " << solve_value << " with basis perem u" << solve_perem_column << " and free perem u" << solve_perem_row << endl;
			Jordan_Exclusions(solve_row, solve_column, solve_perem_row, solve_perem_column);
			if (x_or_y)
				Print_Simplex_Table(1);
			else
				Print_Simplex_Table(0);
		}
	}
	else
	{
		if (x_or_y)
			Print_Simplex_Table(1);
		else
			Print_Simplex_Table(0);
		cout << "Unsolvable simplex table" << endl;
	}
}

bool Simplex_Table::Check_If_Valid()
{
	vector<double> buf;
	buf.push_back(0);
	buf.push_back(0);
	buf.push_back(0);
	for (auto i = 0; i < _simplex_table.size() - 1; ++i)
	{
		if (_simplex_table[i][0].x == 1)
		{
			if (_simplex_table[i][0].value < 0)
			{
				return false;
			}
			buf[0] += _simplex_table[i][0].value * 4;
			buf[1] += _simplex_table[i][0].value * 1;
			buf[2] += _simplex_table[i][0].value * 0;
		}
		if (_simplex_table[i][0].x == 2)
		{
			if (_simplex_table[i][0].value < 0)
			{
				return false;
			}
			buf[0] += _simplex_table[i][0].value * 1;
			buf[1] += _simplex_table[i][0].value * 4;
			buf[2] += _simplex_table[i][0].value * 0.5;
		}
		if (_simplex_table[i][0].x == 3)
		{
			if (_simplex_table[i][0].value < 0)
			{
				return false;
			}
			buf[0] += _simplex_table[i][0].value * 1;
			buf[1] += _simplex_table[i][0].value * 0;
			buf[2] += _simplex_table[i][0].value * 4;
		}
	}
	if ((buf[0] > 5) || (buf[1] > 7) || (buf[2] > 6))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Simplex_Table::Transform_Into_Twin()
{
	vector<vector<Simplex_Element>> buffer_vector_vector;
	vector<Simplex_Element> buffer_vector;
	_min_max = !_min_max;
	cout << _simplex_table[0].size();
	cout << _simplex_table.size();
	for (auto i = 1; i < _simplex_table[0].size(); ++i)
	{
		buffer_vector.clear();
		buffer_vector.push_back(Simplex_Element(-1, _number_of_arguments + i, 0));
		for (auto j = 0; j < _simplex_table.size() - 1; ++j)
		{
			buffer_vector.push_back(Simplex_Element(_simplex_table[j][i].value*(-1), _number_of_arguments + i, j + 1));
		}
		buffer_vector_vector.push_back(buffer_vector);
	}
	buffer_vector.clear();
	buffer_vector.push_back(Simplex_Element(0,  _number_of_arguments + _number_of_equations, 0));
	for (auto i = 1; i < _simplex_table[0].size() ; ++i)
	{
		buffer_vector.push_back(Simplex_Element(-1, _number_of_arguments + _number_of_equations, i));
	}
	buffer_vector.push_back(Simplex_Element(-1, _number_of_arguments + _number_of_equations, _number_of_equations));
	buffer_vector_vector.push_back(buffer_vector);
	_simplex_table.clear();
	for (auto i = 0; i < buffer_vector_vector.size(); ++i)
	{
		_simplex_table.push_back(buffer_vector_vector[i]);
	}
	Print_Simplex_Table(0);
}

void Simplex_Table::Find_Strategy(bool x_or_y)
{
	if (x_or_y)
	{
		vector<int> buf;
		double H = 1.0 / _simplex_table.back()[0].value*(-1);
		cout << "Z = " << _simplex_table.back()[0].value*(-1) << endl;
		cout << "H = 1/Z = " << H << endl;
		for (auto i = 0; i < _simplex_table.size(); ++i)
		{
			if (_simplex_table[i][0].x <= _number_of_arguments)
			{
				cout << "y" << _simplex_table[i][0].x << " = v" << _simplex_table[i][0].x << "h = " << _simplex_table[i][0].value*H << endl;
				buf.push_back(_simplex_table[i][0].x);
			}
		}
		for (auto i = 1; i <= _number_of_arguments; ++i)
		{
			bool is_present = 0;
			for (auto j = 0; j < buf.size(); ++j)
			{
				if (i == buf[j])
				{
					is_present = 1;
					break;
				}
			}
			if (!is_present)
			{
				cout << "y" << i << " = v" << i << "h = " << 0 << endl;
			}
		}
	}
	else
	{
		vector<int> buf;
		double g = 1.0 / _simplex_table.back()[0].value;
		cout << "W = " << _simplex_table.back()[0].value << endl;
		cout << "g = 1/W = " << g << endl;
		for (auto i = 0; i < _simplex_table.size(); ++i)
		{
			if (_simplex_table[i][0].x <= _number_of_equations)
			{
				cout << "x" << _simplex_table[i][0].x << " = u" << _simplex_table[i][0].x << "g = " << _simplex_table[i][0].value*g << endl;
				buf.push_back(_simplex_table[i][0].x);
			}
		}
		for (auto i = 1; i <= _number_of_equations; ++i)
		{
			bool is_present = 0;
			for (auto j = 0; j < buf.size(); ++j)
			{
				if (i == buf[j])
				{
					is_present = 1;
					break;
				}
			}
			if (!is_present)
			{
				cout << "x" << i << " = u" << i << "g = " << 0 << endl;
			}
		}
	}
}



















