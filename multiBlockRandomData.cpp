// multiBlockRandomData.cpp : Instance Developper with Multi Blocks

//

//#include "pch.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <direct.h>

using namespace std;


int main()
{
	string filename;
	int aisle_num = 30;
	int	location_Size = 11;
	int item_Num = 10;
	int blockNum = 3;
	int instance_Num = 50;
	ofstream outFile;

	_mkdir("hes");


	for (int h = 0; h < instance_Num; h++)
	{
		stringstream a;
		a << h;
		filename = "prob" + a.str();
		filename += ".txt";
		cout << filename << endl;
		outFile.open(filename.c_str());
		srand(time(0) + h);
		outFile << 0 << " " << 1 << " " << 1 << " " << 0 << endl;
		for (int i = 1; i < item_Num + 1; i++)
		{
			outFile << i << " ";
			outFile << 1 + (rand() % (blockNum)) << " ";
			outFile << 1 + (rand() % (aisle_num)) << " ";
			outFile << 1 + (rand() % (location_Size - 1)) << endl;
		}

		outFile.close();

	}

	cout << "b_" << blockNum << "_m_" << aisle_num << "_C_" << location_Size << "_n_" << item_Num << endl;

	int pause = 0;
	cin >> pause;
	return 0;
}
