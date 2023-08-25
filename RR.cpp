// v14asus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// v14.cpp : This files looks at knapsack perfection


//#include "pch.h"
#include <iostream>
#include "math.h"
#include "stdlib.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// minimums
int max(int a, int b)
{
	return (a < b) ? b : a;
}

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int min(int a, int b, int c)
{
	if (a < b)
		return (a < c) ? a : c;
	else
		return (b < c) ? b : c;
}

int min(int a, int b, int c, int d)
{
	if (d < min(a, b, c))
		return d;
	else
		return min(a, b, c);
}

int min(int a, int b, int c, int d, int e)
{
	if (e < min(a, b, c, d))
		return e;
	else
		return min(a, b, c, d);
}

int min(int a, int b, int c, int d, int e, int f)
{
	if (f < min(a, b, c, d, e))
		return f;
	else
		return min(a, b, c, d, e);
}

int min(int a, int b, int c, int d, int e, int f, int g)
{
	if (g < min(a, b, c, d, e, f))
		return g;
	else
		return min(a, b, c, d, e, f);
}

int min(int a, int b, int c, int d, int e, int f, int g, int h)
{
	if (h < min(a, b, c, d, e, f, g))
		return h;
	else
		return min(a, b, c, d, e, f, g);
}

int min(int a, int b, int c, int d, int e, int f, int g, int h, int p)
{
	if (p < min(a, b, c, d, e, f, g, h))
		return p;
	else
		return min(a, b, c, d, e, f, g, h);
}

int min(int a, int b, int c, int d, int e, int f, int g, int h, int p, int r)
{
	if (r < min(a, b, c, d, e, f, g, h, p))
		return r;
	else
		return min(a, b, c, d, e, f, g, h, p);
}
int main()
{
	string filename;
	ifstream inFile;
	int hlength = 2;
	ofstream outFile;
	outFile.open("slnalg.txt");
	ofstream outData;
	int	location_Size = 11;
	int sumfirstpicker = 0;
	int sumsecondpicker = 0;
	int firstpicker = 0, secondpicker = 0;

	//cout << "enter the length of an aisle" << endl << endl;
	//cin >> location_Size;


	for (int h = 0; h < 50; h++)
	{
		stringstream a;
		a << h;
		filename = "prob" + a.str();
		filename += ".txt";
		cout << filename << endl;
		outFile << filename << "----";
		inFile.open(filename.c_str());
		outData.open("vrpopu" + a.str() + ".dat");

		int y;
		int A[1000][4];;
		int count = 0;
		int tempo = 100;
		int change[120];
		int eachLengthFromBottom[100][100];
		int eachLengthFromBottom1[100][100];
		int eachLengthFromUp[100][100];
		int eachOptMove[100][100];

		//Find item number
		int item_Num;
		while (!inFile.eof())
		{
			inFile >> y;
			count++;
		}
		item_Num = (count - 5) / 4;
		inFile.close();

		inFile.open(filename.c_str());

		cout << item_Num << " items found!" << endl;

		//Assign data to matris
		//cout << "data is as below" << endl;

		for (int i = 0; i < item_Num + 1; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				inFile >> A[i][j];
				//cout << A[i][j] << " ";
			}
			//cout << endl << endl;
		}

		// Find number of aisles
		int	aisle_num = 0;
		for (int i = 0; i < item_Num + 1; i++)
		{
			if (aisle_num < A[i][2])
				aisle_num = A[i][2];
		}
		cout << "Aisle number is " << aisle_num << endl;
		//cout << "Location Size is " << location_Size << endl;

		int Matris[100][100]; // assume there are 99 items at most!!
		////////vrp matrix creation
		for (int i = 0; i < item_Num + 1; i++)
		{
			for (int j = i; j < item_Num + 1; j++)
			{
				if (i == j)
				{
					Matris[i][j] = 1000;
					Matris[j][i] = 1000;
				}

				else
				{
					if (A[i][2] == A[j][2])
					{
						Matris[i][j] = abs(A[i][3] - A[j][3]);
						Matris[j][i] = Matris[i][j];
					}

					else
					{
						Matris[i][j] = abs(A[i][2] - A[j][2]) * hlength + min(A[i][3] + A[j][3], 2 * location_Size - A[i][3] - A[j][3]);
						Matris[j][i] = Matris[i][j];
					}
				}

			}

		}
		//cout << "VRP MATRICE IS " << endl;
		outData << "param n :=" << item_Num << "; " << endl;
		//outData << "param K := 1; " << endl;

		outData << "param c : ";

		for (int i = 0; i < item_Num + 1; i++)
		{
			//cout << i << " ";
			outData << i << " ";
		}

		//cout << ":=" << endl;
		outData << ":=" << endl;

		for (int i = 0; i < item_Num; i++)
		{
			//cout << i << " ";
			outData << i << " ";

			for (int j = 0; j < item_Num + 1; j++)
			{

				//cout << Matris[i][j] << " ";
				outData << Matris[i][j] << " ";
			}
			//cout << endl;
			outData << endl;

		}

		//cout << item_Num << " ";
		outData << item_Num << " ";

		for (int i = 0; i < item_Num + 1; i++)
		{
			//cout << Matris[item_Num][i] << " ";
			outData << Matris[item_Num][i] << " ";
		}

		//cout << ";" << endl;
		outData << ";" << endl;

		outData.close();

		//creation of lengths of possible connection types

		int Vcost[100][6];

		//0th Column // which is location_Size
		for (int i = 0; i < aisle_num; i++)
		{
			Vcost[i][0] = location_Size;
			//cout << Vcost[i][0] << endl;
		}
		//cout << endl;

		//1st Column //starting from top
		int mini[100];
		for (int i = 0; i < aisle_num; i++)
		{
			mini[i] = location_Size;

			for (int j = 1; j < item_Num + 1; j++)
			{
				if (A[j][2] == i + 1)
				{

					if (mini[i] > A[j][3])
						mini[i] = A[j][3];
				}
			}
			Vcost[i][1] = (location_Size - mini[i]) * 2;
			//cout << Vcost[i][1] << endl;
		}
		//cout << endl;

		//2nd Column // starting from bottom
		int maxi[100];
		for (int i = 0; i < aisle_num; i++)
		{
			maxi[i] = 0;

			for (int j = 1; j < item_Num + 1; j++)
			{
				if (A[j][2] == i + 1)
				{

					if (maxi[i] < A[j][3])
						maxi[i] = A[j][3];
				}
			}
			Vcost[i][2] = (maxi[i]) * 2;
			//cout << Vcost[i][2] << endl;
		}
		//cout << endl;


		//3th Column // largest gap
		int lGap[100];
		int countItemInAisle[100];
		int B[100][32];
		//give number each item in each aisle
		for (int i = 0; i < aisle_num; i++)
		{
			countItemInAisle[i] = 0;
			for (int j = 1; j < item_Num + 1; j++)
			{
				if (A[j][2] == i + 1)
				{
					countItemInAisle[i]++;
					B[i + 1][countItemInAisle[i]] = A[j][3];
					//cout << countItemInAisle[i] << ":" << B[i + 1][countItemInAisle[i]] << " / ";
				}

			}
			//cout << countItemInAisle[i] << endl;
		}
		//sort each item in each aisle in descending order
		for (int i = 0; i < aisle_num; i++)
		{
			for (int j = 1; j < countItemInAisle[i]; j++)
			{
				for (int k = j + 1; k <= countItemInAisle[i]; k++)
				{
					int temp;
					if (B[i + 1][j] < B[i + 1][k])
					{
						temp = B[i + 1][j];
						B[i + 1][j] = B[i + 1][k];
						B[i + 1][k] = temp;
					}
				}
			}
		}

		//cout << endl;

		for (int i = 0; i < aisle_num; i++)
		{
			for (int j = 1; j <= countItemInAisle[i]; j++)
			{
				cout << B[i + 1][j] << " / ";
			}
			cout << countItemInAisle[i] << endl;
		}
		cout << endl;


		int lengthFromDown[100];
		int lengthFromUp[100];


		//largest gap
		for (int i = 0; i < aisle_num; i++)
		{
			if (countItemInAisle[i] == 0)
			{
				Vcost[i][3] = 0;
				lengthFromDown[i] = 60;
				lengthFromUp[i] = 60;

			}
			else
			{
				if (countItemInAisle[i] == 1)
				{
					Vcost[i][3] = min(Vcost[i][1], Vcost[i][2]);
					if (Vcost[i][3] == Vcost[i][1])
					{
						lengthFromDown[i] = 60;
						lengthFromUp[i] = Vcost[i][1];
					}

					if (Vcost[i][3] == Vcost[i][2])
					{
						lengthFromDown[i] = Vcost[i][2];
						lengthFromUp[i] = 60;
					}
				}
				else
				{
					lGap[i] = 0;
					for (int j = 2; j <= countItemInAisle[i]; j++)
					{
						if ((lGap[i] < B[i + 1][j - 1] - B[i + 1][j]))
						{
							lGap[i] = B[i + 1][j - 1] - B[i + 1][j];
							lengthFromDown[i] = 2 * B[i + 1][j];
							lengthFromUp[i] = 2 * (location_Size - B[i + 1][j - 1]);
						}

						//cout << B[i + 1][j - 1] - B[i + 1][j] << " / ";
					}
					//cout << 2 * (location_Size - lGap[i]) << endl;
					//cout << "-------" << lGap[i];
					Vcost[i][3] = 2 * (location_Size - lGap[i]);
					//cout << Vcost[i][3] << "/" << lengthFromDown[i] + lengthFromUp[i] << endl;
				}
			}
			//cout << countItemInAisle[i] << "-------" << lengthFromDown[i] << endl;

		}

		//cout << endl;

		//4th Column // double of location_Size
		for (int i = 0; i < aisle_num; i++)
		{
			Vcost[i][4] = 2 * location_Size;
			//cout << Vcost[i][4] << endl;
		}
		//cout << endl;

		//5th Column // 
		for (int i = 0; i < aisle_num; i++)
		{
			Vcost[i][5] = 0;
			for (int j = 1; j < item_Num + 1; j++)
			{
				if (A[j][2] == i + 1)
					Vcost[i][5] = 100;
			}
			//cout << Vcost[i][5] << endl;
		}
		//cout << endl;

		//write vcost matrix

		//cout << "Possible length matrix is;" << endl;
		/*
		for (int i = 0; i < aisle_num; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				cout << Vcost[i][j] << " ";
			}
			cout << endl;
		}
		//cout << endl;
		*/
		inFile.close();




		int i, j, k, z1[100], z2[100], value[100], minmaxvalue, aisle2, total;

		int tc1[100][7];

		int tc2[100][7];

		int absdif[100];

		int aisle_Mov[100][7];/**/
		int parent[100][7];/**/

		int aisle_Mov2[100][7];/**/
		int parent2[100][7];/**/

		//one picker TSP optimal solution

			/* Initialize first 1st vertical aisle of total cost(tc1) array for each of 7 state */
		tc1[0][0] = Vcost[0][0];
		aisle_Mov[0][0] = 0;
		parent[0][0] = 0;

		tc1[0][1] = Vcost[0][4];
		aisle_Mov[0][1] = 4;
		parent[0][1] = 0;

		tc1[0][2] = Vcost[0][2];
		aisle_Mov[0][2] = 2;
		parent[0][2] = 0;

		tc1[0][3] = Vcost[0][4];
		aisle_Mov[0][3] = 4;
		parent[0][3] = 0;

		tc1[0][4] = min(Vcost[0][1], Vcost[0][3]);
		if (tc1[0][4] == Vcost[0][1])
		{
			aisle_Mov[0][4] = 1;
		}
		else
		{
			aisle_Mov[0][4] = 3;
		}
		parent[0][4] = 0;

		tc1[0][5] = Vcost[0][5];
		aisle_Mov[0][5] = 5;
		parent[0][5] = 0;
		tc1[0][6] = Vcost[0][5];
		aisle_Mov[0][6] = 5;
		parent[0][6] = 0;

		/* dynamically calculate the rest horizontal.. */
		for (j = 1; j <= 2 * (aisle_num - 1); j++)
		{

			if (j % 2 == 1) // means horizontal movement
			{
				tc1[j][0] = tc1[j - 1][0] + 2 * hlength;

				aisle_Mov[j][0] = 0;
				parent[j][0] = 0;

				tc1[j][1] = min(tc1[j - 1][1] + 2 * hlength,
					tc1[j - 1][3] + 2 * hlength);

				if (tc1[j][1] == tc1[j - 1][1] + 2 * hlength)
				{
					aisle_Mov[j][1] = 1;
					parent[j][1] = 1;
				}
				if (tc1[j][1] == tc1[j - 1][3] + 2 * hlength)
				{
					aisle_Mov[j][1] = 1;
					parent[j][1] = 3;
				}

				tc1[j][2] = min(tc1[j - 1][2] + 2 * hlength,
					tc1[j - 1][3] + 2 * hlength);

				if (tc1[j][2] == tc1[j - 1][2] + 2 * hlength)
				{
					aisle_Mov[j][2] = 2;
					parent[j][2] = 2;
				}
				if (tc1[j][2] == tc1[j - 1][3] + 2 * hlength)
				{
					aisle_Mov[j][2] = 2;
					parent[j][2] = 3;
				}

				tc1[j][3] = tc1[j - 1][3] + 4 * hlength;

				aisle_Mov[j][3] = 3;
				parent[j][3] = 3;

				tc1[j][4] = min(tc1[j - 1][1] + 4 * hlength,
					tc1[j - 1][2] + 4 * hlength,
					tc1[j - 1][4] + 4 * hlength);

				if (tc1[j][4] == tc1[j - 1][1] + 4 * hlength)
				{
					aisle_Mov[j][4] = 3;
					parent[j][4] = 1;
				}
				if (tc1[j][4] == tc1[j - 1][2] + 4 * hlength)
				{
					aisle_Mov[j][4] = 3;
					parent[j][4] = 2;
				}
				if (tc1[j][4] == tc1[j - 1][4] + 4 * hlength)
				{
					aisle_Mov[j][4] = 3;
					parent[j][4] = 4;
				}

				tc1[j][5] = tc1[j - 1][5] + 100 * hlength;
				aisle_Mov[j][5] = 4;
				parent[j][5] = 5;

				tc1[j][6] = min(tc1[j - 1][1] + 100 * hlength,
					tc1[j - 1][2] + 100 * hlength,
					tc1[j - 1][3] + 100 * hlength,
					tc1[j - 1][6] + 100 * hlength);

				if (tc1[j][6] == tc1[j - 1][1] + 100 * hlength)
				{
					aisle_Mov[j][6] = 4;
					parent[j][6] = 1;
				}
				if (tc1[j][6] == tc1[j - 1][2] + 100 * hlength)
				{
					aisle_Mov[j][6] = 4;
					parent[j][6] = 2;
				}
				if (tc1[j][6] == tc1[j - 1][3] + 100 * hlength)
				{
					aisle_Mov[j][6] = 4;
					parent[j][6] = 3;
				}
				if (tc1[j][6] == tc1[j - 1][6] + 100 * hlength)
				{
					aisle_Mov[j][6] = 4;
					parent[j][6] = 5;
				}
			}

			/* ... and vertical aisles of total cost(tc) array for each of 7 state */

			else // means vertical movement
			{

				tc1[j][0] = min(tc1[j - 1][0] + Vcost[j / 2][1],
					tc1[j - 1][0] + Vcost[j / 2][2],
					tc1[j - 1][0] + Vcost[j / 2][3],
					tc1[j - 1][0] + Vcost[j / 2][4],
					tc1[j - 1][0] + Vcost[j / 2][5],
					tc1[j - 1][1] + Vcost[j / 2][0],
					tc1[j - 1][2] + Vcost[j / 2][0],
					tc1[j - 1][3] + Vcost[j / 2][0],
					tc1[j - 1][4] + Vcost[j / 2][0],
					tc1[j - 1][5] + Vcost[j / 2][0]);

				/**/
				if (tc1[j][0] == tc1[j - 1][0] + Vcost[j / 2][1])
				{
					aisle_Mov[j][0] = 1;
					parent[j][0] = 0;
				}
				if (tc1[j][0] == tc1[j - 1][0] + Vcost[j / 2][2])
				{
					aisle_Mov[j][0] = 2;
					parent[j][0] = 0;
				}
				if (tc1[j][0] == tc1[j - 1][0] + Vcost[j / 2][3])
				{
					aisle_Mov[j][0] = 3;
					parent[j][0] = 0;
				}
				if (tc1[j][0] == tc1[j - 1][0] + Vcost[j / 2][4])
				{
					aisle_Mov[j][0] = 4;
					parent[j][0] = 0;
				}
				if (tc1[j][0] == tc1[j - 1][0] + Vcost[j / 2][5])
				{
					aisle_Mov[j][0] = 5;
					parent[j][0] = 0;
				}
				if (tc1[j][0] == tc1[j - 1][1] + Vcost[j / 2][0])
				{
					aisle_Mov[j][0] = 0;
					parent[j][0] = 1;
				}
				if (tc1[j][0] == tc1[j - 1][2] + Vcost[j / 2][0])
				{
					aisle_Mov[j][0] = 0;
					parent[j][0] = 2;
				}
				if (tc1[j][0] == tc1[j - 1][3] + Vcost[j / 2][0])
				{
					aisle_Mov[j][0] = 0;
					parent[j][0] = 3;
				}
				if (tc1[j][0] == tc1[j - 1][4] + Vcost[j / 2][0])
				{
					aisle_Mov[j][0] = 0;
					parent[j][0] = 4;
				}
				if (tc1[j][0] == tc1[j - 1][5] + Vcost[j / 2][0])
				{
					aisle_Mov[j][0] = 0;
					parent[j][0] = 5;
				}

				/**/

				tc1[j][1] = min(tc1[j - 1][1] + Vcost[j / 2][1],
					tc1[j - 1][1] + Vcost[j / 2][5],
					tc1[j - 1][5] + Vcost[j / 2][1]);
				/**/
				if (tc1[j][1] == tc1[j - 1][1] + Vcost[j / 2][1])
				{
					aisle_Mov[j][1] = 1;
					parent[j][1] = 1;
				}
				if (tc1[j][1] == tc1[j - 1][1] + Vcost[j / 2][5])
				{
					aisle_Mov[j][1] = 5;
					parent[j][1] = 1;
				}
				if (tc1[j][1] == tc1[j - 1][5] + Vcost[j / 2][1])
				{
					aisle_Mov[j][1] = 1;
					parent[j][1] = 5;
				}
				/**/

				tc1[j][2] = min(tc1[j - 1][2] + Vcost[j / 2][2],
					tc1[j - 1][2] + Vcost[j / 2][5],
					tc1[j - 1][5] + Vcost[j / 2][2]);
				/**/
				if (tc1[j][2] == tc1[j - 1][2] + Vcost[j / 2][2])
				{
					aisle_Mov[j][2] = 2;
					parent[j][2] = 2;
				}
				if (tc1[j][2] == tc1[j - 1][2] + Vcost[j / 2][5])
				{
					aisle_Mov[j][2] = 5;
					parent[j][2] = 2;
				}
				if (tc1[j][2] == tc1[j - 1][5] + Vcost[j / 2][2])
				{
					aisle_Mov[j][2] = 2;
					parent[j][2] = 5;
				}
				/**/

				tc1[j][3] = min(tc1[j - 1][0] + Vcost[j / 2][0],
					tc1[j - 1][1] + Vcost[j / 2][4],
					tc1[j - 1][2] + Vcost[j / 2][4],
					tc1[j - 1][3] + Vcost[j / 2][1],
					tc1[j - 1][3] + Vcost[j / 2][2],
					tc1[j - 1][3] + Vcost[j / 2][3],
					tc1[j - 1][3] + Vcost[j / 2][4],
					tc1[j - 1][3] + Vcost[j / 2][5],
					tc1[j - 1][4] + Vcost[j / 2][4],
					tc1[j - 1][5] + Vcost[j / 2][4]);
				/**/
				if (tc1[j][3] == tc1[j - 1][0] + Vcost[j / 2][0])
				{
					aisle_Mov[j][3] = 0;
					parent[j][3] = 0;
				}
				if (tc1[j][3] == tc1[j - 1][1] + Vcost[j / 2][4])
				{
					aisle_Mov[j][3] = 4;
					parent[j][3] = 1;
				}
				if (tc1[j][3] == tc1[j - 1][2] + Vcost[j / 2][4])
				{
					aisle_Mov[j][3] = 4;
					parent[j][3] = 2;
				}
				if (tc1[j][3] == tc1[j - 1][3] + Vcost[j / 2][1])
				{
					aisle_Mov[j][3] = 1;
					parent[j][3] = 3;
				}
				if (tc1[j][3] == tc1[j - 1][3] + Vcost[j / 2][2])
				{
					aisle_Mov[j][3] = 2;
					parent[j][3] = 3;
				}
				if (tc1[j][3] == tc1[j - 1][3] + Vcost[j / 2][3])
				{
					aisle_Mov[j][3] = 3;
					parent[j][3] = 3;
				}
				if (tc1[j][3] == tc1[j - 1][3] + Vcost[j / 2][4])
				{
					aisle_Mov[j][3] = 4;
					parent[j][3] = 3;
				}
				if (tc1[j][3] == tc1[j - 1][0] + Vcost[j / 2][0])
				{
					aisle_Mov[j][3] = 0;
					parent[j][3] = 0;
				}
				if (tc1[j][3] == tc1[j - 1][0] + Vcost[j / 2][0])
				{
					aisle_Mov[j][3] = 0;
					parent[j][3] = 0;
				}
				if (tc1[j][3] == tc1[j - 1][0] + Vcost[j / 2][0])
				{
					aisle_Mov[j][3] = 0;
					parent[j][3] = 0;
				}
				/**/

				tc1[j][4] = min(tc1[j - 1][1] + Vcost[j / 2][2],
					tc1[j - 1][1] + Vcost[j / 2][3],
					tc1[j - 1][2] + Vcost[j / 2][1],
					tc1[j - 1][2] + Vcost[j / 2][3],
					tc1[j - 1][4] + Vcost[j / 2][1],
					tc1[j - 1][4] + Vcost[j / 2][2],
					tc1[j - 1][4] + Vcost[j / 2][3],
					tc1[j - 1][4] + Vcost[j / 2][5],
					tc1[j - 1][5] + Vcost[j / 2][3]);

				/**/
				if (tc1[j][4] == tc1[j - 1][1] + Vcost[j / 2][2])
				{
					aisle_Mov[j][4] = 2;
					parent[j][4] = 1;
				}
				if (tc1[j][4] == tc1[j - 1][1] + Vcost[j / 2][3])
				{
					aisle_Mov[j][4] = 3;
					parent[j][4] = 1;
				}
				if (tc1[j][4] == tc1[j - 1][2] + Vcost[j / 2][1])
				{
					aisle_Mov[j][4] = 1;
					parent[j][4] = 2;
				}
				if (tc1[j][4] == tc1[j - 1][2] + Vcost[j / 2][3])
				{
					aisle_Mov[j][4] = 3;
					parent[j][4] = 2;
				}
				if (tc1[j][4] == tc1[j - 1][4] + Vcost[j / 2][1])
				{
					aisle_Mov[j][4] = 1;
					parent[j][4] = 4;
				}
				if (tc1[j][4] == tc1[j - 1][4] + Vcost[j / 2][2])
				{
					aisle_Mov[j][4] = 2;
					parent[j][4] = 4;
				}
				if (tc1[j][4] == tc1[j - 1][4] + Vcost[j / 2][3])
				{
					aisle_Mov[j][4] = 3;
					parent[j][4] = 4;
				}
				if (tc1[j][4] == tc1[j - 1][4] + Vcost[j / 2][5])
				{
					aisle_Mov[j][4] = 5;
					parent[j][4] = 4;
				}
				if (tc1[j][4] == tc1[j - 1][5] + Vcost[j / 2][3])
				{
					aisle_Mov[j][4] = 3;
					parent[j][4] = 5;
				}
				/**/

				tc1[j][5] = tc1[j - 1][5] + Vcost[j / 2][5];
				aisle_Mov[j][5] = 5;
				parent[j][5] = 5;

				tc1[j][6] = tc1[j - 1][6] + Vcost[j / 2][5];
				aisle_Mov[j][6] = 5;
				parent[j][6] = 6;

			}

		}
		// Writing all total cost increases in order to debug

		/*cout << "Solution;" << endl;
		for (j = 0; j <= 2 * (aisle_num - 1); j++)
		{
			cout << "(" << tc1[j][0] << "," << parent[j][0] << "," << aisle_Mov[j][0] << ") ";
			cout << "(" << tc1[j][1] << "," << parent[j][1] << "," << aisle_Mov[j][1] << ") ";
			cout << "(" << tc1[j][2] << "," << parent[j][2] << "," << aisle_Mov[j][2] << ") ";
			cout << "(" << tc1[j][3] << "," << parent[j][3] << "," << aisle_Mov[j][3] << ") ";
			cout << "(" << tc1[j][4] << "," << parent[j][4] << "," << aisle_Mov[j][4] << ") ";
			cout << "(" << tc1[j][5] << "," << parent[j][5] << "," << aisle_Mov[j][5] << ") ";
			cout << "(" << tc1[j][6] << "," << parent[j][6] << "," << aisle_Mov[j][6] << ") " << endl;
			//buraya bak
		}
		cout << endl;*/

		z1[0] = min(tc1[2 * (aisle_num - 1)][1], tc1[2 * (aisle_num - 1)][2],
			tc1[2 * (aisle_num - 1)][3], tc1[2 * (aisle_num - 1)][6]);

		int opt_mov[100];
		int	optColumn[100];

		int opt_mov2[100];
		int	optColumn2[100];


		if (z1[0] == tc1[2 * (aisle_num - 1)][1])
		{
			opt_mov[2 * (aisle_num - 1)] = aisle_Mov[2 * (aisle_num - 1)][1];
			optColumn[2 * (aisle_num - 1)] = 1;
		}
		if (z1[0] == tc1[2 * (aisle_num - 1)][2])
		{
			opt_mov[2 * (aisle_num - 1)] = aisle_Mov[2 * (aisle_num - 1)][2];
			optColumn[2 * (aisle_num - 1)] = 2;
		}
		if (z1[0] == tc1[2 * (aisle_num - 1)][3])
		{
			opt_mov[2 * (aisle_num - 1)] = aisle_Mov[2 * (aisle_num - 1)][3];
			optColumn[2 * (aisle_num - 1)] = 3;
		}
		if (z1[0] == tc1[2 * (aisle_num - 1)][6])
		{
			opt_mov[2 * (aisle_num - 1)] = aisle_Mov[2 * (aisle_num - 1)][6];
			optColumn[2 * (aisle_num - 1)] = 6;
		}

		for (j = 2 * (aisle_num - 1); j > 0; j--)
		{
			opt_mov[j - 1] = aisle_Mov[j - 1][parent[j][optColumn[j]]];
			optColumn[j - 1] = parent[j][optColumn[j]];
		}


		int LowB = z1[0] / 2;

		//cout << endl << "Optimal Time for the 1-OPP is " << z1[0] << endl << "--------------TSP---------------- " << endl;
		outFile << "1OPP-OPT " << z1[0] << endl;
		outFile << "2OPP-LB " << LowB << endl;

		cout << "0" << "-->>";
		for (j = 0; j <= 2 * (aisle_num - 1); j += 2)
		{
			//cout << countItemInAisle[j / 2];
			cout << opt_mov[j] << " -- ";//optimum movements 
		}
		cout << z1[0] << " !!!!!!!!!!!!! " << endl;

		// 2 picker solution starts here

		for (i = 0; i <= 2 * (aisle_num - 1); i += 2)
		{

			/* Initialize first 1st vertical aisle of total cost(tc1) array for each of 7 state */
			tc1[0][0] = Vcost[0][0];
			aisle_Mov[0][0] = 0;
			parent[0][0] = 0;

			tc1[0][1] = Vcost[0][4];
			aisle_Mov[0][1] = 4;
			parent[0][1] = 0;

			tc1[0][2] = Vcost[0][2];
			aisle_Mov[0][2] = 2;
			parent[0][2] = 0;

			tc1[0][3] = Vcost[0][4];
			aisle_Mov[0][3] = 4;
			parent[0][3] = 0;

			tc1[0][4] = min(Vcost[0][1], Vcost[0][3]);
			if (tc1[0][4] == Vcost[0][1])

			{
				aisle_Mov[0][4] = 1;
			}
			else
			{
				aisle_Mov[0][4] = 3;
			}
			parent[0][4] = 0;

			tc1[0][5] = Vcost[0][5];
			aisle_Mov[0][5] = 5;
			parent[0][5] = 0;
			tc1[0][6] = Vcost[0][5];
			aisle_Mov[0][6] = 5;
			parent[0][6] = 0;

			/* dynamically calculate the rest horizontal.. */
			for (j = 1; j <= i; j++)
			{

				if (j % 2 == 1)
				{
					tc1[j][0] = tc1[j - 1][0] + 2 * hlength;

					aisle_Mov[j][0] = 0;
					parent[j][0] = 0;

					tc1[j][1] = min(tc1[j - 1][1] + 2 * hlength,
						tc1[j - 1][3] + 2 * hlength);

					if (tc1[j][1] == tc1[j - 1][1] + 2 * hlength)
					{
						aisle_Mov[j][1] = 1;
						parent[j][1] = 1;
					}
					if (tc1[j][1] == tc1[j - 1][3] + 2 * hlength)
					{
						aisle_Mov[j][1] = 1;
						parent[j][1] = 3;
					}

					tc1[j][2] = min(tc1[j - 1][2] + 2 * hlength,
						tc1[j - 1][3] + 2 * hlength);

					if (tc1[j][2] == tc1[j - 1][2] + 2 * hlength)
					{
						aisle_Mov[j][2] = 2;
						parent[j][2] = 2;
					}
					if (tc1[j][2] == tc1[j - 1][3] + 2 * hlength)
					{
						aisle_Mov[j][2] = 2;
						parent[j][2] = 3;
					}

					tc1[j][3] = tc1[j - 1][3] + 4 * hlength;

					aisle_Mov[j][3] = 3;
					parent[j][3] = 3;

					tc1[j][4] = min(tc1[j - 1][1] + 4 * hlength,
						tc1[j - 1][2] + 4 * hlength,
						tc1[j - 1][4] + 4 * hlength);

					if (tc1[j][4] == tc1[j - 1][1] + 4 * hlength)
					{
						aisle_Mov[j][4] = 3;
						parent[j][4] = 1;
					}
					if (tc1[j][4] == tc1[j - 1][2] + 4 * hlength)
					{
						aisle_Mov[j][4] = 3;
						parent[j][4] = 2;
					}
					if (tc1[j][4] == tc1[j - 1][4] + 4 * hlength)
					{
						aisle_Mov[j][4] = 3;
						parent[j][4] = 4;
					}

					tc1[j][5] = tc1[j - 1][5] + 100 * hlength;
					aisle_Mov[j][5] = 4;
					parent[j][5] = 5;

					tc1[j][6] = min(tc1[j - 1][1] + 100 * hlength,
						tc1[j - 1][2] + 100 * hlength,
						tc1[j - 1][3] + 100 * hlength,
						tc1[j - 1][6] + 100 * hlength);

					if (tc1[j][6] == tc1[j - 1][1] + 100 * hlength)
					{
						aisle_Mov[j][6] = 4;
						parent[j][6] = 1;
					}
					if (tc1[j][6] == tc1[j - 1][2] + 100 * hlength)
					{
						aisle_Mov[j][6] = 4;
						parent[j][6] = 2;
					}
					if (tc1[j][6] == tc1[j - 1][3] + 100 * hlength)
					{
						aisle_Mov[j][6] = 4;
						parent[j][6] = 3;
					}
					if (tc1[j][6] == tc1[j - 1][6] + 100 * hlength)
					{
						aisle_Mov[j][6] = 4;
						parent[j][6] = 5;
					}
				}

				/* ... and vertical aisles of total cost(tc) array for each of 7 state */

				else
				{

					tc1[j][0] = min(tc1[j - 1][0] + Vcost[j / 2][1],
						tc1[j - 1][0] + Vcost[j / 2][2],
						tc1[j - 1][0] + Vcost[j / 2][3],
						tc1[j - 1][0] + Vcost[j / 2][4],
						tc1[j - 1][0] + Vcost[j / 2][5],
						tc1[j - 1][1] + Vcost[j / 2][0],
						tc1[j - 1][2] + Vcost[j / 2][0],
						tc1[j - 1][3] + Vcost[j / 2][0],
						tc1[j - 1][4] + Vcost[j / 2][0],
						tc1[j - 1][5] + Vcost[j / 2][0]);

					/**/
					if (tc1[j][0] == tc1[j - 1][0] + Vcost[j / 2][1])
					{
						aisle_Mov[j][0] = 1;
						parent[j][0] = 0;
					}
					if (tc1[j][0] == tc1[j - 1][0] + Vcost[j / 2][2])
					{
						aisle_Mov[j][0] = 2;
						parent[j][0] = 0;
					}
					if (tc1[j][0] == tc1[j - 1][0] + Vcost[j / 2][3])
					{
						aisle_Mov[j][0] = 3;
						parent[j][0] = 0;
					}
					if (tc1[j][0] == tc1[j - 1][0] + Vcost[j / 2][4])
					{
						aisle_Mov[j][0] = 4;
						parent[j][0] = 0;
					}
					if (tc1[j][0] == tc1[j - 1][0] + Vcost[j / 2][5])
					{
						aisle_Mov[j][0] = 5;
						parent[j][0] = 0;
					}
					if (tc1[j][0] == tc1[j - 1][1] + Vcost[j / 2][0])
					{
						aisle_Mov[j][0] = 0;
						parent[j][0] = 1;
					}
					if (tc1[j][0] == tc1[j - 1][2] + Vcost[j / 2][0])
					{
						aisle_Mov[j][0] = 0;
						parent[j][0] = 2;
					}
					if (tc1[j][0] == tc1[j - 1][3] + Vcost[j / 2][0])
					{
						aisle_Mov[j][0] = 0;
						parent[j][0] = 3;
					}
					if (tc1[j][0] == tc1[j - 1][4] + Vcost[j / 2][0])
					{
						aisle_Mov[j][0] = 0;
						parent[j][0] = 4;
					}
					if (tc1[j][0] == tc1[j - 1][5] + Vcost[j / 2][0])
					{
						aisle_Mov[j][0] = 0;
						parent[j][0] = 5;
					}

					/**/

					tc1[j][1] = min(tc1[j - 1][1] + Vcost[j / 2][1],
						tc1[j - 1][1] + Vcost[j / 2][5],
						tc1[j - 1][5] + Vcost[j / 2][1]);
					/**/
					if (tc1[j][1] == tc1[j - 1][1] + Vcost[j / 2][1])
					{
						aisle_Mov[j][1] = 1;
						parent[j][1] = 1;
					}
					if (tc1[j][1] == tc1[j - 1][1] + Vcost[j / 2][5])
					{
						aisle_Mov[j][1] = 5;
						parent[j][1] = 1;
					}
					if (tc1[j][1] == tc1[j - 1][5] + Vcost[j / 2][1])
					{
						aisle_Mov[j][1] = 1;
						parent[j][1] = 5;
					}
					/**/

					tc1[j][2] = min(tc1[j - 1][2] + Vcost[j / 2][2],
						tc1[j - 1][2] + Vcost[j / 2][5],
						tc1[j - 1][5] + Vcost[j / 2][2]);
					/**/
					if (tc1[j][2] == tc1[j - 1][2] + Vcost[j / 2][2])
					{
						aisle_Mov[j][2] = 2;
						parent[j][2] = 2;
					}
					if (tc1[j][2] == tc1[j - 1][2] + Vcost[j / 2][5])
					{
						aisle_Mov[j][2] = 5;
						parent[j][2] = 2;
					}
					if (tc1[j][2] == tc1[j - 1][5] + Vcost[j / 2][2])
					{
						aisle_Mov[j][2] = 2;
						parent[j][2] = 5;
					}
					/**/

					tc1[j][3] = min(tc1[j - 1][0] + Vcost[j / 2][0],
						tc1[j - 1][1] + Vcost[j / 2][4],
						tc1[j - 1][2] + Vcost[j / 2][4],
						tc1[j - 1][3] + Vcost[j / 2][1],
						tc1[j - 1][3] + Vcost[j / 2][2],
						tc1[j - 1][3] + Vcost[j / 2][3],
						tc1[j - 1][3] + Vcost[j / 2][4],
						tc1[j - 1][3] + Vcost[j / 2][5],
						tc1[j - 1][4] + Vcost[j / 2][4],
						tc1[j - 1][5] + Vcost[j / 2][4]);
					/**/
					if (tc1[j][3] == tc1[j - 1][0] + Vcost[j / 2][0])
					{
						aisle_Mov[j][3] = 0;
						parent[j][3] = 0;
					}
					if (tc1[j][3] == tc1[j - 1][1] + Vcost[j / 2][4])
					{
						aisle_Mov[j][3] = 4;
						parent[j][3] = 1;
					}
					if (tc1[j][3] == tc1[j - 1][2] + Vcost[j / 2][4])
					{
						aisle_Mov[j][3] = 4;
						parent[j][3] = 2;
					}
					if (tc1[j][3] == tc1[j - 1][3] + Vcost[j / 2][1])
					{
						aisle_Mov[j][3] = 1;
						parent[j][3] = 3;
					}
					if (tc1[j][3] == tc1[j - 1][3] + Vcost[j / 2][2])
					{
						aisle_Mov[j][3] = 2;
						parent[j][3] = 3;
					}
					if (tc1[j][3] == tc1[j - 1][3] + Vcost[j / 2][3])
					{
						aisle_Mov[j][3] = 3;
						parent[j][3] = 3;
					}
					if (tc1[j][3] == tc1[j - 1][3] + Vcost[j / 2][4])
					{
						aisle_Mov[j][3] = 4;
						parent[j][3] = 3;
					}
					if (tc1[j][3] == tc1[j - 1][0] + Vcost[j / 2][0])
					{
						aisle_Mov[j][3] = 0;
						parent[j][3] = 0;
					}
					if (tc1[j][3] == tc1[j - 1][0] + Vcost[j / 2][0])
					{
						aisle_Mov[j][3] = 0;
						parent[j][3] = 0;
					}
					if (tc1[j][3] == tc1[j - 1][0] + Vcost[j / 2][0])
					{
						aisle_Mov[j][3] = 0;
						parent[j][3] = 0;
					}
					/**/

					tc1[j][4] = min(tc1[j - 1][1] + Vcost[j / 2][2],
						tc1[j - 1][1] + Vcost[j / 2][3],
						tc1[j - 1][2] + Vcost[j / 2][1],
						tc1[j - 1][2] + Vcost[j / 2][3],
						tc1[j - 1][4] + Vcost[j / 2][1],
						tc1[j - 1][4] + Vcost[j / 2][2],
						tc1[j - 1][4] + Vcost[j / 2][3],
						tc1[j - 1][4] + Vcost[j / 2][5],
						tc1[j - 1][5] + Vcost[j / 2][3]);

					/**/
					if (tc1[j][4] == tc1[j - 1][1] + Vcost[j / 2][2])
					{
						aisle_Mov[j][4] = 2;
						parent[j][4] = 1;
					}
					if (tc1[j][4] == tc1[j - 1][1] + Vcost[j / 2][3])
					{
						aisle_Mov[j][4] = 3;
						parent[j][4] = 1;
					}
					if (tc1[j][4] == tc1[j - 1][2] + Vcost[j / 2][1])
					{
						aisle_Mov[j][4] = 1;
						parent[j][4] = 2;
					}
					if (tc1[j][4] == tc1[j - 1][2] + Vcost[j / 2][3])
					{
						aisle_Mov[j][4] = 3;
						parent[j][4] = 2;
					}
					if (tc1[j][4] == tc1[j - 1][4] + Vcost[j / 2][1])
					{
						aisle_Mov[j][4] = 1;
						parent[j][4] = 4;
					}
					if (tc1[j][4] == tc1[j - 1][4] + Vcost[j / 2][2])
					{
						aisle_Mov[j][4] = 2;
						parent[j][4] = 4;
					}
					if (tc1[j][4] == tc1[j - 1][4] + Vcost[j / 2][3])
					{
						aisle_Mov[j][4] = 3;
						parent[j][4] = 4;
					}
					if (tc1[j][4] == tc1[j - 1][4] + Vcost[j / 2][5])
					{
						aisle_Mov[j][4] = 5;
						parent[j][4] = 4;
					}
					if (tc1[j][4] == tc1[j - 1][5] + Vcost[j / 2][3])
					{
						aisle_Mov[j][4] = 3;
						parent[j][4] = 5;
					}
					/**/

					tc1[j][5] = tc1[j - 1][5] + Vcost[j / 2][5];
					aisle_Mov[j][5] = 5;
					parent[j][5] = 5;

					tc1[j][6] = tc1[j - 1][6] + Vcost[j / 2][5];
					aisle_Mov[j][6] = 5;
					parent[j][6] = 6;
				}

			}

			// Writing all total cost increases in order to debug

			/*

			cout << "Solution;" << endl;
			for (j = 0; j <= i; j++)
			{
				cout << "(" << tc1[j][0] << "," << parent[j][0] << "," << aisle_Mov[j][0] << ") ";
				cout << "(" << tc1[j][1] << "," << parent[j][1] << "," << aisle_Mov[j][1] << ") ";
				cout << "(" << tc1[j][2] << "," << parent[j][2] << "," << aisle_Mov[j][2] << ") ";
				cout << "(" << tc1[j][3] << "," << parent[j][3] << "," << aisle_Mov[j][3] << ") ";
				cout << "(" << tc1[j][4] << "," << parent[j][4] << "," << aisle_Mov[j][4] << ") ";
				cout << "(" << tc1[j][5] << "," << parent[j][5] << "," << aisle_Mov[j][5] << ") ";
				cout << "(" << tc1[j][6] << "," << parent[j][6] << "," << aisle_Mov[j][6] << ") " << endl;
			}
				cout << endl;
			*/

			z1[i] = min(tc1[i][1], tc1[i][2], tc1[i][3], tc1[i][6]);

			if (z1[i] == tc1[i][1])
			{
				opt_mov[i] = aisle_Mov[i][1];
				optColumn[i] = 1;
			}
			if (z1[i] == tc1[i][2])
			{
				opt_mov[i] = aisle_Mov[i][2];
				optColumn[i] = 2;
			}
			if (z1[i] == tc1[i][3])
			{
				opt_mov[i] = aisle_Mov[i][3];
				optColumn[i] = 3;
			}
			if (z1[i] == tc1[i][6])
			{
				opt_mov[i] = aisle_Mov[i][6];
				optColumn[i] = 6;
			}

			for (j = i; j > 0; j--)
			{
				opt_mov[j - 1] = aisle_Mov[j - 1][parent[j][optColumn[j]]];
				optColumn[j - 1] = parent[j][optColumn[j]];
			}

			//for (j = 0; j <= i; j ++)
			//{
			//cout << opt_mov[j] << endl;
			//}
			// to upgrade solution for 2-opp

			for (j = 0; j <= i; j += 2)
			{
				if (opt_mov[j] == 2)
				{
					eachLengthFromBottom[i][j] = Vcost[j / 2][2];
					eachLengthFromUp[i][j] = 2 * location_Size;
				}

				else
				{
					if (opt_mov[j] == 3)
					{
						eachLengthFromBottom[i][j] = lengthFromDown[j / 2];
						eachLengthFromUp[i][j] = lengthFromUp[j / 2];
					}
					else
					{
						if (opt_mov[j] == 1)
						{
							eachLengthFromBottom[i][j] = 2 * location_Size;
							eachLengthFromUp[i][j] = Vcost[j / 2][1];
						}
						else
						{
							eachLengthFromBottom[i][j] = 2 * location_Size;
							eachLengthFromUp[i][j] = 2 * location_Size;
						}

					}
				}
			}
			for (j = 0; j <= i; j += 2)
			{
				//cout << countItemInAisle[j / 2];
				//cout << " - " << opt_mov[j];
				eachOptMove[i][j] = opt_mov[j];
			}
			//cout << endl;

			//cout << z1[i] << endl;

			/* Initialize first 1st vertical aisle of total cost(tc2) array for each of 7 state */

			tc2[i + 2][0] = Vcost[(i + 2) / 2][0] + (i + 2) * hlength;
			aisle_Mov2[i + 2][0] = 0;
			parent2[i + 2][0] = 0;

			tc2[i + 2][1] = Vcost[(i + 2) / 2][4] + (i + 2) * hlength;
			aisle_Mov2[i + 2][1] = 4;
			parent2[i + 2][1] = 0;

			tc2[i + 2][2] = Vcost[(i + 2) / 2][2] + (i + 2) * hlength;
			aisle_Mov2[i + 2][2] = 2;
			parent2[i + 2][2] = 0;

			tc2[i + 2][3] = Vcost[(i + 2) / 2][4] + (i + 2) * hlength;
			aisle_Mov2[i + 2][3] = 4;
			parent2[i + 2][3] = 0;

			tc2[i + 2][4] = min(Vcost[(i + 2) / 2][1], Vcost[(i + 2) / 2][3]) + (i + 2) * hlength;
			if (tc2[i + 2][4] == Vcost[(i + 2) / 2][1] + (i + 2) * hlength)
			{
				aisle_Mov2[i + 2][4] = 1;
			}
			else
			{
				aisle_Mov2[i + 2][4] = 3;
			}
			parent2[i + 2][4] = 0;

			tc2[i + 2][5] = Vcost[(i + 2) / 2][5] + (i + 2) * hlength;
			aisle_Mov2[i + 2][5] = 5;
			parent2[i + 2][5] = 0;

			tc2[i + 2][6] = Vcost[(i + 2) / 2][5] + (i + 2) * hlength;
			aisle_Mov2[i + 2][6] = 5;
			parent2[i + 2][6] = 0;

			/* dynamically calculate the rest horizontal.. */
			for (k = i + 3; k <= 2 * (aisle_num - 1); k++)
			{
				if (k % 2 == 1)
				{
					tc2[k][0] = tc2[k - 1][0] + 2 * hlength;
					aisle_Mov2[k][0] = 0;
					parent2[k][0] = 0;


					tc2[k][1] = min(tc2[k - 1][1] + 2 * hlength,
						tc2[k - 1][3] + 2 * hlength);

					if (tc2[k][1] == tc2[k - 1][1] + 2 * hlength)
					{
						aisle_Mov2[k][1] = 1;
						parent2[k][1] = 1;
					}
					if (tc2[k][1] == tc2[k - 1][3] + 2 * hlength)
					{
						aisle_Mov2[k][1] = 1;
						parent2[k][1] = 3;
					}

					tc2[k][2] = min(tc2[k - 1][2] + 2 * hlength,
						tc2[k - 1][3] + 2 * hlength);

					if (tc2[k][2] == tc2[k - 1][2] + 2 * hlength)
					{
						aisle_Mov2[k][2] = 2;
						parent2[k][2] = 2;
					}
					if (tc2[k][2] == tc2[k - 1][3] + 2 * hlength)
					{
						aisle_Mov2[k][2] = 2;
						parent2[k][2] = 3;
					}

					tc2[k][3] = tc2[k - 1][3] + 4 * hlength;
					aisle_Mov2[k][3] = 3;
					parent2[k][3] = 3;

					tc2[k][4] = min(tc2[k - 1][1] + 4 * hlength,
						tc2[k - 1][2] + 4 * hlength,
						tc2[k - 1][4] + 4 * hlength);

					if (tc2[k][4] == tc2[k - 1][1] + 4 * hlength)
					{
						aisle_Mov2[k][4] = 3;
						parent2[k][4] = 1;
					}
					if (tc2[k][4] == tc2[k - 1][2] + 4 * hlength)
					{
						aisle_Mov2[k][4] = 3;
						parent2[k][4] = 2;
					}
					if (tc2[k][4] == tc2[k - 1][4] + 4 * hlength)
					{
						aisle_Mov2[k][4] = 3;
						parent2[k][4] = 4;
					}


					tc2[k][5] = tc2[k - 1][5] + 100 * hlength;
					aisle_Mov2[k][5] = 4;
					parent2[k][5] = 5;


					tc2[k][6] = min(tc2[k - 1][1] + 100 * hlength,
						tc2[k - 1][2] + 100 * hlength,
						tc2[k - 1][3] + 100 * hlength,
						tc2[k - 1][6] + 100 * hlength);

					if (tc2[k][6] == tc2[k - 1][1] + 100 * hlength)
					{
						aisle_Mov2[k][6] = 4;
						parent2[k][6] = 1;
					}
					if (tc2[k][6] == tc2[k - 1][2] + 100 * hlength)
					{
						aisle_Mov2[k][6] = 4;
						parent2[k][6] = 2;
					}
					if (tc2[k][6] == tc2[k - 1][3] + 100 * hlength)
					{
						aisle_Mov2[k][6] = 4;
						parent2[k][6] = 3;
					}
					if (tc2[k][6] == tc2[k - 1][6] + 100 * hlength)
					{
						aisle_Mov2[k][6] = 4;
						parent2[k][6] = 5;
					}

				}

				/* ... and vertical aisles of total cost(tc) array for each of 7 state */

				else
				{

					tc2[k][0] = min(tc2[k - 1][0] + Vcost[k / 2][1],
						tc2[k - 1][0] + Vcost[k / 2][2],
						tc2[k - 1][0] + Vcost[k / 2][3],
						tc2[k - 1][0] + Vcost[k / 2][4],
						tc2[k - 1][0] + Vcost[k / 2][5],
						tc2[k - 1][1] + Vcost[k / 2][0],
						tc2[k - 1][2] + Vcost[k / 2][0],
						tc2[k - 1][3] + Vcost[k / 2][0],
						tc2[k - 1][4] + Vcost[k / 2][0],
						tc2[k - 1][5] + Vcost[k / 2][0]);

					/**/
					if (tc2[k][0] == tc2[k - 1][0] + Vcost[k / 2][1])
					{
						aisle_Mov2[k][0] = 1;
						parent2[k][0] = 0;
					}
					if (tc2[k][0] == tc2[k - 1][0] + Vcost[k / 2][2])
					{
						aisle_Mov2[k][0] = 2;
						parent2[k][0] = 0;
					}
					if (tc2[k][0] == tc2[k - 1][0] + Vcost[k / 2][3])
					{
						aisle_Mov2[k][0] = 3;
						parent2[k][0] = 0;
					}
					if (tc2[k][0] == tc2[k - 1][0] + Vcost[k / 2][4])
					{
						aisle_Mov2[k][0] = 4;
						parent2[k][0] = 0;
					}
					if (tc2[k][0] == tc2[k - 1][0] + Vcost[k / 2][5])
					{
						aisle_Mov2[k][0] = 5;
						parent2[k][0] = 0;
					}
					if (tc2[k][0] == tc2[k - 1][1] + Vcost[k / 2][0])
					{
						aisle_Mov2[k][0] = 0;
						parent2[k][0] = 1;
					}
					if (tc2[k][0] == tc2[k - 1][2] + Vcost[k / 2][0])
					{
						aisle_Mov2[k][0] = 0;
						parent2[k][0] = 2;
					}
					if (tc2[k][0] == tc2[k - 1][3] + Vcost[k / 2][0])
					{
						aisle_Mov2[k][0] = 0;
						parent2[k][0] = 3;
					}
					if (tc2[k][0] == tc2[k - 1][4] + Vcost[k / 2][0])
					{
						aisle_Mov2[k][0] = 0;
						parent2[k][0] = 4;
					}
					if (tc2[k][0] == tc2[k - 1][5] + Vcost[k / 2][0])
					{
						aisle_Mov2[k][0] = 0;
						parent2[k][0] = 5;
					}


					tc2[k][1] = min(tc2[k - 1][1] + Vcost[k / 2][1],
						tc2[k - 1][1] + Vcost[k / 2][5],
						tc2[k - 1][5] + Vcost[k / 2][1]);

					/**/
					if (tc2[k][1] == tc2[k - 1][1] + Vcost[k / 2][1])
					{
						aisle_Mov2[k][1] = 1;
						parent2[k][1] = 1;
					}
					if (tc2[k][1] == tc2[k - 1][1] + Vcost[k / 2][5])
					{
						aisle_Mov2[k][1] = 5;
						parent2[k][1] = 1;
					}
					if (tc2[k][1] == tc2[k - 1][5] + Vcost[k / 2][1])
					{
						aisle_Mov2[k][1] = 1;
						parent2[k][1] = 5;
					}

					tc2[k][2] = min(tc2[k - 1][2] + Vcost[k / 2][2],
						tc2[k - 1][2] + Vcost[k / 2][5],
						tc2[k - 1][5] + Vcost[k / 2][2]);

					/**/
					if (tc2[k][2] == tc2[k - 1][2] + Vcost[k / 2][2])
					{
						aisle_Mov2[k][2] = 2;
						parent2[k][2] = 2;
					}
					if (tc2[k][2] == tc2[k - 1][2] + Vcost[k / 2][5])
					{
						aisle_Mov2[k][2] = 5;
						parent2[k][2] = 2;
					}
					if (tc2[k][2] == tc2[k - 1][5] + Vcost[k / 2][2])
					{
						aisle_Mov2[k][2] = 2;
						parent2[k][2] = 5;
					}

					/**/

					tc2[k][3] = min(tc2[k - 1][0] + Vcost[k / 2][0],
						tc2[k - 1][1] + Vcost[k / 2][4],
						tc2[k - 1][2] + Vcost[k / 2][4],
						tc2[k - 1][3] + Vcost[k / 2][1],
						tc2[k - 1][3] + Vcost[k / 2][2],
						tc2[k - 1][3] + Vcost[k / 2][3],
						tc2[k - 1][3] + Vcost[k / 2][4],
						tc2[k - 1][3] + Vcost[k / 2][5],
						tc2[k - 1][4] + Vcost[k / 2][4],
						tc2[k - 1][5] + Vcost[k / 2][4]);

					/**/
					if (tc2[k][3] == tc2[k - 1][0] + Vcost[k / 2][0])
					{
						aisle_Mov2[k][3] = 0;
						parent2[k][3] = 0;
					}
					if (tc2[k][3] == tc2[k - 1][1] + Vcost[k / 2][4])
					{
						aisle_Mov2[k][3] = 4;
						parent2[k][3] = 1;
					}
					if (tc2[k][3] == tc2[k - 1][2] + Vcost[k / 2][4])
					{
						aisle_Mov2[k][3] = 4;
						parent2[k][3] = 2;
					}
					if (tc2[k][3] == tc2[k - 1][3] + Vcost[k / 2][1])
					{
						aisle_Mov2[k][3] = 1;
						parent2[k][3] = 3;
					}
					if (tc2[k][3] == tc2[k - 1][3] + Vcost[k / 2][2])
					{
						aisle_Mov2[k][3] = 2;
						parent2[k][3] = 3;
					}
					if (tc2[k][3] == tc2[k - 1][3] + Vcost[k / 2][3])
					{
						aisle_Mov2[k][3] = 3;
						parent2[k][3] = 3;
					}
					if (tc2[k][3] == tc2[k - 1][3] + Vcost[k / 2][4])
					{
						aisle_Mov2[k][3] = 4;
						parent2[k][3] = 3;
					}
					if (tc2[k][3] == tc2[k - 1][0] + Vcost[k / 2][0])
					{
						aisle_Mov2[k][3] = 0;
						parent2[k][3] = 0;
					}
					if (tc2[k][3] == tc2[k - 1][0] + Vcost[k / 2][0])
					{
						aisle_Mov2[k][3] = 0;
						parent2[k][3] = 0;
					}
					if (tc2[k][3] == tc2[k - 1][0] + Vcost[k / 2][0])
					{
						aisle_Mov2[k][3] = 0;
						parent2[k][3] = 0;
					}



					tc2[k][4] = min(tc2[k - 1][1] + Vcost[k / 2][2],
						tc2[k - 1][1] + Vcost[k / 2][3],
						tc2[k - 1][2] + Vcost[k / 2][1],
						tc2[k - 1][2] + Vcost[k / 2][3],
						tc2[k - 1][4] + Vcost[k / 2][1],
						tc2[k - 1][4] + Vcost[k / 2][2],
						tc2[k - 1][4] + Vcost[k / 2][3],
						tc2[k - 1][4] + Vcost[k / 2][5],
						tc2[k - 1][5] + Vcost[k / 2][3]);
					/**/
					if (tc2[k][4] == tc2[k - 1][1] + Vcost[k / 2][2])
					{
						aisle_Mov2[k][4] = 2;
						parent2[k][4] = 1;
					}
					if (tc2[k][4] == tc2[k - 1][1] + Vcost[k / 2][3])
					{
						aisle_Mov2[k][4] = 3;
						parent2[k][4] = 1;
					}
					if (tc2[k][4] == tc2[k - 1][2] + Vcost[k / 2][1])
					{
						aisle_Mov2[k][4] = 1;
						parent2[k][4] = 2;
					}
					if (tc2[k][4] == tc2[k - 1][2] + Vcost[k / 2][3])
					{
						aisle_Mov2[k][4] = 3;
						parent2[k][4] = 2;
					}
					if (tc2[k][4] == tc2[k - 1][4] + Vcost[k / 2][1])
					{
						aisle_Mov2[k][4] = 1;
						parent2[k][4] = 4;
					}
					if (tc2[k][4] == tc2[k - 1][4] + Vcost[k / 2][2])
					{
						aisle_Mov2[k][4] = 2;
						parent2[k][4] = 4;
					}
					if (tc2[k][4] == tc2[k - 1][4] + Vcost[k / 2][3])
					{
						aisle_Mov2[k][4] = 3;
						parent2[k][4] = 4;
					}
					if (tc2[k][4] == tc2[k - 1][4] + Vcost[k / 2][5])
					{
						aisle_Mov2[k][4] = 5;
						parent2[k][4] = 4;
					}
					if (tc2[k][4] == tc2[k - 1][5] + Vcost[k / 2][3])
					{
						aisle_Mov2[k][4] = 3;
						parent2[k][4] = 5;
					}

					/**/

					tc2[k][5] = tc2[k - 1][5] + Vcost[k / 2][5];
					aisle_Mov2[k][5] = 5;
					parent2[k][5] = 5;


					tc2[k][6] = tc2[k - 1][6] + Vcost[k / 2][5];
					aisle_Mov2[k][6] = 5;
					parent2[k][6] = 6;

				}
			}

			// Writing all total cost increases in order to debug

			/*for (k = i + 2; k <= 2 * (aisle_num - 1); k++)

			{
				cout << "(" << tc2[k][0] << "," << parent2[k][0] << "," << aisle_Mov2[k][0] << ") ";
				cout << "(" << tc2[k][1] << "," << parent2[k][1] << "," << aisle_Mov2[k][1] << ") ";
				cout << "(" << tc2[k][2] << "," << parent2[k][2] << "," << aisle_Mov2[k][2] << ") ";
				cout << "(" << tc2[k][3] << "," << parent2[k][3] << "," << aisle_Mov2[k][3] << ") ";
				cout << "(" << tc2[k][4] << "," << parent2[k][4] << "," << aisle_Mov2[k][4] << ") ";
				cout << "(" << tc2[k][5] << "," << parent2[k][5] << "," << aisle_Mov2[k][5] << ") ";
				cout << "(" << tc2[k][6] << "," << parent2[k][6] << "," << aisle_Mov2[k][6] << ") " << endl;


			}
			cout << endl;
			*/

			z2[i] = min(tc2[2 * (aisle_num - 1)][1], tc2[2 * (aisle_num - 1)][2], tc2[2 * (aisle_num - 1)][3], tc2[2 * (aisle_num - 1)][6]);

			if (z2[i] == tc2[2 * (aisle_num - 1)][1])
			{
				opt_mov2[2 * (aisle_num - 1)] = aisle_Mov2[2 * (aisle_num - 1)][1];
				optColumn2[2 * (aisle_num - 1)] = 1;
			}
			if (z2[i] == tc2[2 * (aisle_num - 1)][2])
			{
				opt_mov2[2 * (aisle_num - 1)] = aisle_Mov2[2 * (aisle_num - 1)][2];
				optColumn2[2 * (aisle_num - 1)] = 2;
			}
			if (z2[i] == tc2[2 * (aisle_num - 1)][3])
			{
				opt_mov2[2 * (aisle_num - 1)] = aisle_Mov2[2 * (aisle_num - 1)][3];
				optColumn2[2 * (aisle_num - 1)] = 3;
			}
			if (z2[i] == tc2[2 * (aisle_num - 1)][6])
			{
				opt_mov2[2 * (aisle_num - 1)] = aisle_Mov2[2 * (aisle_num - 1)][6];
				optColumn2[2 * (aisle_num - 1)] = 6;
			}

			for (j = 2 * (aisle_num - 1); j > i + 2; j--)
			{
				opt_mov2[j - 1] = aisle_Mov2[j - 1][parent2[j][optColumn2[j]]];
				optColumn2[j - 1] = parent2[j][optColumn2[j]];
			}
			/*//*//*/*//**/
			if (i + 2 <= 2 * (aisle_num - 1))
			{
				outFile << "2ndPICKERoptMOVE(i+2) " << opt_mov2[i + 2] << endl;//optimum movements 
			}

			//outFile << "2ndPICKERoptMOVE(i+4) " << opt_mov2[i + 4] << endl;//optimum movements 

			for (j = i + 2; j <= 2 * (aisle_num - 1); j += 2)
			{

				outFile << "2ndPICKERoptMOVE " << opt_mov2[j] << endl;//optimum movements 

				if (opt_mov2[j] == 2)
				{
					eachLengthFromBottom[i][j] = Vcost[j / 2][2];
					eachLengthFromUp[i][j] = 2 * location_Size;
				}

				else
				{
					if (opt_mov2[j] == 3)
					{
						eachLengthFromBottom[i][j] = lengthFromDown[j / 2];
						eachLengthFromUp[i][j] = lengthFromUp[j / 2];
					}
					else
					{
						if (opt_mov2[j] == 1)
						{
							eachLengthFromBottom[i][j] = 2 * location_Size;
							eachLengthFromUp[i][j] = Vcost[j / 2][1];
						}
						else
						{
							eachLengthFromBottom[i][j] = 2 * location_Size;
							eachLengthFromUp[i][j] = 2 * location_Size;
						}

					}
				}
			}
			//cout << "Move - PossibleBottomMove" << endl;
			for (j = i + 2; j <= 2 * (aisle_num - 1); j += 2)
			{
				//cout << countItemInAisle[j / 2];
				//cout << " - " << opt_mov2[j];
				eachOptMove[i][j] = opt_mov2[j];
			}
			//cout << endl;


			//cout << z2[i] << endl << "----------------------------" << endl;

			absdif[i] = abs(z2[i] - z1[i]);

			//improving the result


			//cout << absdif[i] << endl;

			value[i] = max(z2[i], z1[i]);
			cout << (i + 2) / 2 << "-->>";
			for (j = 0; j <= 2 * (aisle_num - 1); j += 2)
			{
				//cout << countItemInAisle[j / 2];
				cout << eachOptMove[i][j] << " -- ";//optimum movements 
			}
			cout << z1[i] << " -- " << z2[i];
			cout << endl;

			//outFile << "1stPICKERFIRSTMOVE " << eachOptMove[i][0] << endl;//optimum movements 
			//outFile << "2NDPICKERFIRSTMOVE " << eachOptMove[i][i+2] << endl;//optimum movements 

			//outFile << "EACHOPTMOVE(i)(i) " << eachOptMove[i][i] << endl;//optimum movements 


			//cout << value[i] << endl;
			int K[120][120];
			int K2[120][120];
			if (z2[i] < z1[i]) // means last try

			{
				//  sol alt taraf
				// Build table K[][] in bottom up manner
				/*outFile << "EACHOPTMOVE(i)(i)atz2[i]<z1[i] " << eachOptMove[i][i] << " EACHOPTMOVE(i)(i+2)atz2[i]<z1[i] " << eachOptMove[i][i + 2] << " "; //optimum movements

				if (eachOptMove[i][i] ==  3) // if (i)(i) up ise
				{
					if (eachOptMove[i][i + 2] == 0 || eachOptMove[i][i + 2] == 1 || eachOptMove[i][i + 2] == 3)
					{

						for (j = 0; j <= i; j += 2)
						{
							eachLengthFromBottom1[i][j] = eachLengthFromBottom[i][j];
						}
						eachLengthFromBottom1[i][i + 2] = eachLengthFromUp[i][i] + 2 * hlength;
						for (j = 0; j <= i + 4; j += 2)
						{
							for (int w = 0; w <= 2 * absdif[i]; w += 2)
							{
								if (j == 0 || w == 0)
								{
									K[j][w] = 0;
									K2[j][w] = abs(z1[i] - z2[i] - 2 * K[j][w]);
								}
								else if (2 * eachLengthFromBottom1[i][j - 2] <= w)
								{
									K[j][w] = max(eachLengthFromBottom1[i][j - 2] + K[j - 2][w - 2 * eachLengthFromBottom1[i][j - 2]], K[j - 2][w]);
									K2[j][w] = abs(z1[i] - z2[i] - 2 * K[j][w]);
								}
								else
								{
									K[j][w] = K[j - 2][w];
									K2[j][w] = abs(z1[i] - z2[i] - 2 * K[j][w]);
								}
								//cout << "K[" << j << "][" << w << "]=" << K[j][w] << endl;
							}
						}
						for (j = 0; j <= i + 4; j += 2)
						{
							for (int w = 0; w <= 2 * absdif[i]; w += 2)
							{
								if (tempo > K2[j][w])
								{
									tempo = K2[j][w];
									change[i] = K[j][w];
								}
								cout << K[j][w] << "--";
							}
							cout << endl;
						}
						cout << endl << endl;

						for (j = 0; j <= i + 4; j += 2)
						{
							for (int w = 0; w <= 2 * absdif[i]; w += 2)
							{
								cout << K2[j][w] << "--";
							}
							cout << endl;
						}

						outFile << "yuppi" << endl;
					}
				}
				else
				{*/
				for (j = 0; j <= i + 2; j += 2)
				{
					for (int w = 0; w <= 2 * absdif[i]; w += 2)
					{
						if (j == 0 || w == 0)
						{
							K[j][w] = 0;
							K2[j][w] = abs(z1[i] - z2[i] - 2 * K[j][w]);
						}
						else if (2 * eachLengthFromBottom[i][j - 2] <= w)
						{
							K[j][w] = max(eachLengthFromBottom[i][j - 2] + K[j - 2][w - 2 * eachLengthFromBottom[i][j - 2]], K[j - 2][w]);
							K2[j][w] = abs(z1[i] - z2[i] - 2 * K[j][w]);
						}
						else
						{
							K[j][w] = K[j - 2][w];
							K2[j][w] = abs(z1[i] - z2[i] - 2 * K[j][w]);
						}
						//cout << "K[" << j << "][" << w << "]=" << K[j][w] << endl;
					}
				}


				for (j = 0; j <= i + 2; j += 2)
				{
					for (int w = 0; w <= 2 * absdif[i]; w += 2)
					{
						if (tempo > K2[j][w])
						{
							tempo = K2[j][w];
							change[i] = K[j][w];

						}
						cout << K[j][w] << "--";
					}
					cout << endl;
				}

				cout << endl << endl;

				for (j = 0; j <= i + 2; j += 2)
				{
					for (int w = 0; w <= 2 * absdif[i]; w += 2)
					{
						cout << K2[j][w] << "--";
					}
					cout << endl;
				}
				//}

				z1[i] = z1[i] - change[i];
				z2[i] = z2[i] + change[i];

				cout << z1[i] << "**";
				cout << z2[i] << endl;

				//outFile << "EACHOPTMOVE-2 " << eachOptMove[i - 2][i] << endl;//optimum movements 
				//outFile << "EACHOPTMOVE-1 " << eachOptMove[i - 2][0] << endl;//optimum movements 
				value[i] = max(z2[i], z1[i]);
				// Build  sag  taraf
				if (eachOptMove[i - 2][i] == 3)//optmov at i for 2nd picker is 3 i mean lgap in i-2 time
				{
					outFile << "HELLO WORLD" << endl;
					if (eachOptMove[i - 2][i - 2] == 2)
					{
						if (2 * (hlength + eachLengthFromBottom[i - 2][i]) <= 2 * absdif[i - 2])
						{
							z1[i - 2] = z1[i - 2] + eachLengthFromBottom[i - 2][i] + 2 * hlength;
							z2[i - 2] = z2[i - 2] - eachLengthFromBottom[i - 2][i];
							value[i - 2] = max(z2[i - 2], z1[i - 2]);
							//coa1 = eachLengthFromBottom[i - 2][i];
						}
					}
					if (eachOptMove[i - 2][i - 2] == 1)
					{
						if (2 * (hlength + eachLengthFromUp[i - 2][i]) <= 2 * absdif[i - 2])
						{
							z1[i - 2] = z1[i - 2] + eachLengthFromUp[i - 2][i] + 2 * hlength;
							z2[i - 2] = z2[i - 2] - eachLengthFromUp[i - 2][i];
							value[i - 2] = max(z2[i - 2], z1[i - 2]);
							//coa2 = eachLengthFromUp[i - 2][i];
						}
					}
					if (eachOptMove[i - 2][i - 2] == 0 || 3)
					{
						if (2 * (hlength + max(eachLengthFromUp[i - 2][i], eachLengthFromBottom[i - 2][i])) <= 2 * absdif[i - 2])
						{
							if (abs(absdif[i - 2] - 2 * (hlength + max(eachLengthFromUp[i - 2][i], eachLengthFromBottom[i - 2][i]))) <= abs(absdif[i - 2] - 2 * (hlength + min(eachLengthFromUp[i - 2][i], eachLengthFromBottom[i - 2][i]))))
							{
								z1[i - 2] = z1[i - 2] + max(eachLengthFromUp[i - 2][i], eachLengthFromBottom[i - 2][i]) + 2 * hlength;
								z2[i - 2] = z2[i - 2] - max(eachLengthFromUp[i - 2][i], eachLengthFromBottom[i - 2][i]);
							}
							else
							{
								z1[i - 2] = z1[i - 2] + min(eachLengthFromUp[i - 2][i], eachLengthFromBottom[i - 2][i]) + 2 * hlength;
								z2[i - 2] = z2[i - 2] - min(eachLengthFromUp[i - 2][i], eachLengthFromBottom[i - 2][i]);
							}

							value[i - 2] = max(z2[i - 2], z1[i - 2]);
						}
						else
						{
							if (2 * (hlength + min(eachLengthFromUp[i - 2][i], eachLengthFromBottom[i - 2][i])) <= 2 * absdif[i - 2])
							{
								z1[i - 2] = z1[i - 2] + min(eachLengthFromUp[i - 2][i], eachLengthFromBottom[i - 2][i]) + 2 * hlength;
								z2[i - 2] = z2[i - 2] - min(eachLengthFromUp[i - 2][i], eachLengthFromBottom[i - 2][i]);
								value[i - 2] = max(z2[i - 2], z1[i - 2]);
							}
						}
					}
				}
				/*// Build  sol ust taraf

				if (eachOptMove[i][i] == 1 || 3)
				{
					if (eachOptMove[i][i + 2] == 0 || 1 || 3)
					{
						if (2 * (hlength + eachLengthFromUp[i][i]) <= absdif[i])
						{
							z1[i] = z1[i] - eachLengthFromUp[i][i];
							z2[i] = z2[i] + eachLengthFromUp[i][i] + 2 * hlength;
							//cout << z1[i] << z2[i] << endl;
							value[i] = max(z2[i], z1[i]);
						}
					}
				}
				//build sag ust taraf
				if (z1[i - 2] == min(tc1[i - 2][1], tc1[i - 2][3], tc1[i - 2][6]))
				{
					if (eachOptMove[i - 2][i] == 3)//optmov at i for 2nd picker is 3 i mean lgap in i-2 time
					{
						if (2 * (hlength + ?) <= absdif[i - 2])
						{
							z1[i - 2] = z1[i - 2] + ? + 2 * hlength;
							z2[i - 2] = z2[i - 2] - ?;
							value[i - 2] = max(z2[i - 2], z1[i - 2]);
						}
					}

				}*/
				//cout << z1[i] << z2[i] << endl;


				break;
			}

		}



		minmaxvalue = (value[i] < value[i - 2]) ? value[i] : value[i - 2];
		total = (value[i] < value[i - 2]) ? z1[i] + z2[i] : z1[i - 2] + z2[i - 2];
		aisle2 = (value[i] < value[i - 2]) ? (i + 4) / 2 : (i + 2) / 2;
		int TheOther = total - minmaxvalue;

		outFile << "2OPP-TOT " << total << "." << endl;

		//cout << "The MinMax is " << minmaxvalue << " and 2nd picker starts from aisle " << aisle2 << "." << endl;
		//cout << "The other picker walks " << TheOther << " units." << endl;



		outFile << "2OPP-MinMax " << minmaxvalue;
		if (minmaxvalue <= (total / 2))
		{
			outFile << " -- ---- ---- --- ----- - - -- OPTIMAL";
		}
		outFile << " 2nd picker starts from aisle " << aisle2 << "." << endl;
		outFile << "2OPP-the Later " << TheOther << endl;
		if (sumfirstpicker < sumsecondpicker)
		{
			firstpicker = minmaxvalue;
			secondpicker = TheOther;
			//cout << firstpicker << endl;
			//cout << secondpicker << endl;
			sumfirstpicker += firstpicker;
			sumsecondpicker += secondpicker;
		}
		else
		{
			firstpicker = TheOther;
			secondpicker = minmaxvalue;
			//cout << firstpicker << endl;
			//cout << secondpicker << endl;
			sumfirstpicker += firstpicker;
			sumsecondpicker += secondpicker;
		}

		//cout << "---" << sumfirstpicker << endl;
		//cout << "---" << sumsecondpicker << endl;
	}

	//cout << "The firstpicker's total is " << sumfirstpicker << " units." << endl;
	//cout << "The secondpicker's total is " << sumsecondpicker << " units." << endl << endl;
	outFile << "The firstpicker's total is " << sumfirstpicker << " units." << endl;
	outFile << "The secondpicker's total is " << sumsecondpicker << " units." << endl;


	int pause = 0;
	cin >> pause;
	return 0;
}
