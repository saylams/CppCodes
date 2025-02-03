// ZS1.cpp : Zone MultiBlock VRP Data building and S Shape heuristic
//


//#include "pch.h"
//#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <cstdlib> 
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

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
	int vlength = 0;
	ofstream outFile;
	outFile.open("slnalg.txt");
	ofstream outData;
	int	location_Size;


	cout << "enter the length of an aisle" << endl << endl;
	cin >> location_Size;


	for (int h = 0; h < 1; h++)
	{
		stringstream a;
		a << h;
		filename = "prob" + a.str();
		filename += ".txt";
		cout << filename << endl;
		//outFile << filename << "----" << endl;
		inFile.open(filename.c_str());
		outData.open("vrpmulti" + a.str() + ".dat");

		int y;
		int A[1000][4];
		int count = 0;
		int change[120];
		//int eachOptMove[100][100][100];

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

		//outFile << item_Num << " items found!" << endl;

		//Assign data to matris-build A[i][j]
		//outFile << "data is as below" << endl;

		for (int i = 0; i < item_Num + 1; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				inFile >> A[i][j];
				//outFile << A[i][j] << " ";
			}
			//outFile << endl << endl;
		}

		// Find number of aisles
		int	aisle_num = 0;
		for (int i = 0; i < item_Num + 1; i++)
		{
			if (aisle_num < A[i][2])
				aisle_num = A[i][2];
		}
		//outFile << "Aisle number is " << aisle_num << endl;

		// Find number of blocks for full case
		int	fullblock_num = 0;
		for (int i = 0; i < item_Num + 1; i++)
		{
			if (fullblock_num < A[i][1])
				fullblock_num = A[i][1];
		}
		//outFile << "Block number is " << fullblock_num << endl;



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
					if (A[i][1] == A[j][1])
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

					else
					{
						Matris[i][j] = abs((A[i][1] - 1) * location_Size + A[i][3] - ((A[j][1] - 1) * location_Size + A[j][3])) + abs(A[i][1] - A[j][1]) * vlength + abs(A[i][2] - A[j][2]) * hlength;
						Matris[j][i] = Matris[i][j];
					}
				}
			}
		}
		////outFile << "VRP MATRICE IS " << endl;
		outData << "param n := " << item_Num << "; " << endl;
		outData << "param K := 2; " << endl;
		outData << "param m := " << aisle_num << "; " << endl << endl;
		outData << "param a := " << endl;

		for (int i = 0; i < item_Num; i++)
		{
			{
				outData << A[i][0] << " ";
				outData << A[i][2] << " ";
			}
			outData << endl;
		}
		outData << A[item_Num][0] << " ";
		outData << A[item_Num][2] << ";" << endl << endl;
		outData << "param c : ";

		for (int i = 0; i < item_Num + 1; i++)
		{
			//outFile << i << " ";
			outData << i << " ";
		}

		//outFile << ":=" << endl;
		outData << ":=" << endl;

		for (int i = 0; i < item_Num; i++)
		{
			//outFile << i << " ";
			outData << i << " ";

			for (int j = 0; j < item_Num + 1; j++)
			{

				//outFile << Matris[i][j] << " ";
				outData << Matris[i][j] << " ";
			}
			//outFile << endl;
			outData << endl;

		}

		//outFile << item_Num << " ";
		outData << item_Num << " ";

		for (int i = 0; i < item_Num + 1; i++)
		{
			//outFile << Matris[item_Num][i] << " ";
			outData << Matris[item_Num][i] << " ";
		}

		//outFile << ";" << endl;
		outData << ";" << endl;

		outData.close();

		//creation of lengths of possible connection types

		int Vcost[10][100][6];

		//0th Column // which is location_Size // |
		for (int k = 0; k < fullblock_num; k++)
		{
			for (int i = 0; i < aisle_num; i++)
			{
				Vcost[k][i][0] = location_Size;
				//outFile << Vcost[i][0] << endl;
			}
		}


		//outFile << endl;

		//1st Column //starting from top // U
		int mini;
		for (int k = 0; k < fullblock_num; k++)
		{
			for (int i = 0; i < aisle_num; i++)
			{
				mini = location_Size;

				for (int j = 1; j < item_Num + 1; j++)
				{
					if (A[j][1] == k + 1)
					{
						if (A[j][2] == i + 1)
						{

							if (mini > A[j][3])
								mini = A[j][3];
						}
					}

				}
				Vcost[k][i][1] = (location_Size - mini) * 2;
				//outFile << Vcost[i][1] << endl;
			}
			//outFile << endl;
		}



		//2nd Column // starting from bottom //n
		int maxi;
		for (int k = 0; k < fullblock_num; k++)
		{
			for (int i = 0; i < aisle_num; i++)
			{
				maxi = 0;

				for (int j = 1; j < item_Num + 1; j++)
				{
					if (A[j][1] == k + 1)
					{
						if (A[j][2] == i + 1)
						{

							if (maxi < A[j][3])
								maxi = A[j][3];
						}
					}

				}
				Vcost[k][i][2] = maxi * 2;
				//outFile << Vcost[i][2] << endl;
			}
			//outFile << endl;
		}



		//3th Column // largest gap //Un
		int lGap[10][100];
		int countItemInSubAisle[10][100];
		int countItemInAisle[100];
		int B[10][100][32];

		//give number each item in each aisle
		for (int i = 0; i < aisle_num; i++)
		{
			countItemInAisle[i] = 0;
			for (int j = 1; j < item_Num + 1; j++)
			{
				if (A[j][2] == i + 1)
				{
					countItemInAisle[i]++;
				}

			}
			//outFile << countItemInAisle[i] << endl;
		}


		//give number each item in each subaisle
		for (int k = 0; k < fullblock_num; k++)
		{
			for (int i = 0; i < aisle_num; i++)
			{
				countItemInSubAisle[k][i] = 0;
				for (int j = 1; j < item_Num + 1; j++)
				{
					if (A[j][1] == k + 1)
					{
						if (A[j][2] == i + 1)
						{
							countItemInSubAisle[k][i]++;
							B[k][i][countItemInSubAisle[k][i]] = A[j][3];
							//outFile << countItemInAisle[i] << ":" << B[i + 1][countItemInAisle[i]] << " / ";
						}
					}


				}
				//outFile << countItemInAisle[i] << endl;
			}
		}


		//sort each item in each aisle in descending order
		for (int l = 0; l < fullblock_num; l++)
		{
			for (int i = 0; i < aisle_num; i++)
			{
				for (int j = 1; j < countItemInSubAisle[l][i]; j++)
				{
					for (int k = j + 1; k <= countItemInSubAisle[l][i]; k++)
					{
						int temp;
						if (B[l][i][j] < B[l][i][k])
						{
							temp = B[l][i][j];
							B[l][i][j] = B[l][i][k];
							B[l][i][k] = temp;
						}
					}
				}
			}

		}

		////outFile << endl;

		//for (int k = 0; k < fullblock_num; k++)
		for (int k = fullblock_num - 1; k >= 0; k--)
		{
			//outFile << "Details for block " << k + 1 << endl;
			for (int i = 0; i < aisle_num; i++)
			{
				for (int j = 1; j <= countItemInSubAisle[k][i]; j++)
				{
					//outFile << B[k][i][j] << " / ";
				}
				//outFile << countItemInSubAisle[k][i] << endl;
			}
			//outFile << endl;
		}
		//outFile << endl;


		int lengthFromDown[10][100];
		int lengthFromUp[10][100];


		//largest gap
		for (int k = 0; k < fullblock_num; k++)
		{
			for (int i = 0; i < aisle_num; i++)
			{
				if (countItemInSubAisle[k][i] == 0)
				{
					Vcost[k][i][3] = 0;
					lengthFromDown[k][i] = 60;
					lengthFromUp[k][i] = 60;

				}
				else
				{
					if (countItemInSubAisle[k][i] == 1)
					{
						Vcost[k][i][3] = min(Vcost[k][i][1], Vcost[k][i][2]);
						if (Vcost[k][i][3] == Vcost[k][i][1])
						{
							lengthFromDown[k][i] = 60;
							lengthFromUp[k][i] = Vcost[k][i][1];
						}

						if (Vcost[k][i][3] == Vcost[k][i][2])
						{
							lengthFromDown[k][i] = Vcost[k][i][2];
							lengthFromUp[k][i] = 60;
						}
					}
					else
					{
						lGap[k][i] = 0;
						for (int j = 2; j <= countItemInSubAisle[k][i]; j++)
						{
							if ((lGap[k][i] < B[k][i][j - 1] - B[k][i][j]))
							{
								lGap[k][i] = B[k][i][j - 1] - B[k][i][j];
								lengthFromDown[k][i] = 2 * B[k][i][j];
								lengthFromUp[k][i] = 2 * (location_Size - B[k][i][j - 1]);
							}

							////outFile << B[k][i][j - 1] - B[k][i][j] << " / ";
						}
						////outFile << 2 * (location_Size - lGap[i]) << endl;
						////outFile << "-------" << lGap[i];
						Vcost[k][i][3] = 2 * (location_Size - lGap[k][i]);
						////outFile << Vcost[i][3] << "/" << lengthFromDown[i] + lengthFromUp[i] << endl;
					}
				}
				////outFile << countItemInAisle[i] << "-------" << lengthFromDown[i] << endl;

			}
		}


		////outFile << endl;

		//4th Column // double of location_Size // ||

		for (int k = 0; k < fullblock_num; k++)
		{
			for (int i = 0; i < aisle_num; i++)
			{
				Vcost[k][i][4] = 2 * location_Size;
				////outFile << Vcost[i][4] << endl;
			}
			////outFile << endl;
		}


		//5th Column // no item case

		for (int k = 0; k < fullblock_num; k++)
		{
			for (int i = 0; i < aisle_num; i++)
			{
				Vcost[k][i][5] = 0;

				for (int j = 1; j < item_Num + 1; j++)
				{
					if (A[j][1] == k + 1)
					{
						if (A[j][2] == i + 1)
							Vcost[k][i][5] = 100;
					}

				}
				////outFile << Vcost[i][5] << endl;
			}
			////outFile << endl;
		}



		//write vcost matrix

		////outFile << "Possible length matrix is;" << endl;
		/*
		for (int k = 0; k < fullblock_num; k++)
		{
			for (int i = 0; i < aisle_num; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					//outFile << Vcost[i][j] << " ";
				}
				//outFile << endl;
			}
		}


		*/
		//outFile << endl;
		inFile.close();

		//loop for SS[p][q] starts here

		int SS[100][100];

		for (int p = 1; p <= aisle_num; p++)
		{
			for (int q = p; q <= aisle_num; q++)
			{
				//outFile << endl << "SS[" << p - 1 << "][" << q - 1 << "]:" << endl;
				//cout << endl << "SS[" << p - 1 << "][" << q - 1 << "]:" << endl;
				//the leftmost aisle for each SS[p][q] configuration
				int	leftMostAisleNum = q;
				for (int i = 1; i <= item_Num; i++)
				{
					if ((A[i][2] >= p) && (leftMostAisleNum > A[i][2]))
						leftMostAisleNum = A[i][2];
				}

				//outFile << "leftMostAisleNum is " << leftMostAisleNum << endl;

				// Find number of blocks for each SS[p][q] configuration
				int	block_num = 0;
				for (int i = 0; i < item_Num + 1; i++)
				{
					if ((A[i][2] >= p) && (A[i][2] <= q) && (block_num < A[i][1]))
						block_num = A[i][1];
				}
				//outFile << "Block number is " << block_num << endl;

				// Find number of aisles for each block
				int	firstAisleNumforBlock[10];
				int	lastAisleNumforBlock[10];

				for (int k = 0; k < block_num; k++)
				{
					lastAisleNumforBlock[k] = p;
					for (int i = 1; i < item_Num + 1; i++)
					{
						if ((A[i][2] >= p) && (A[i][2] <= q) && (A[i][1] == k + 1) && (lastAisleNumforBlock[k] < A[i][2]))
						{
							lastAisleNumforBlock[k] = A[i][2];
						}
					}

					//outFile << "lastAisleNum for block " << k + 1 << " is " << lastAisleNumforBlock[k] << endl;

					firstAisleNumforBlock[k] = q;
					for (int i = 1; i < item_Num + 1; i++)
					{
						if ((A[i][2] >= p) && (A[i][2] <= q) && (A[i][1] == k + 1) && (firstAisleNumforBlock[k] > A[i][2]))
						{
							firstAisleNumforBlock[k] = A[i][2];
						}
					}
					//outFile << "firstAisleNum for block " << k + 1 << " is " << firstAisleNumforBlock[k] << endl;
				}

				//outFile << endl;

				int numofFilledSubAislefortheLastBlock = 0;
				int	numofFilledSubAisleAfterLeftMostAisleforBlock[10];

				for (int i = leftMostAisleNum - 1; i < lastAisleNumforBlock[block_num - 1]; i++)
				{
					if (countItemInSubAisle[block_num - 1][i] != 0)
					{
						numofFilledSubAislefortheLastBlock++;
					}
				}
				//outFile << "numofFilledSubAislefortheLastBlock is " << numofFilledSubAislefortheLastBlock << endl;

				for (int k = 0; k < block_num - 1; k++)
				{
					numofFilledSubAisleAfterLeftMostAisleforBlock[k] = 0;

					for (int i = leftMostAisleNum; i < lastAisleNumforBlock[k]; i++)
					{
						if (countItemInSubAisle[k][i] != 0)
						{
							numofFilledSubAisleAfterLeftMostAisleforBlock[k]++;
						}
					}
					//outFile << "numofFilledSubAisleAfterLeftMostAisleforBlock " << k + 1 << " is " << numofFilledSubAisleAfterLeftMostAisleforBlock[k] << endl;
				}

				int firstAisleNumAfterLeftMostAisleforBlock[10];

				for (int k = 0; k < block_num - 1; k++)
				{
					firstAisleNumAfterLeftMostAisleforBlock[k] = lastAisleNumforBlock[k];

					for (int i = 1; i < item_Num + 1; i++)
					{
						if ((A[i][2] >= p) && (A[i][2] <= q) && (A[i][1] == k + 1) && (leftMostAisleNum < A[i][2]))
						{
							if (firstAisleNumAfterLeftMostAisleforBlock[k] > A[i][2])
								firstAisleNumAfterLeftMostAisleforBlock[k] = A[i][2];
						}

					}

					//outFile << "firstAisleNumAfterLeftMostAisleforBlock " << k + 1 << " is " << firstAisleNumAfterLeftMostAisleforBlock[k] << endl;
				}
				// Route calculation starts here
				// going from the depot to the front of the leftmost pick aisle +
				// traverse the left pick aisle up to the front cross aisle of the farthest block +
				// Go to the right through the front cross aisle of the farthest block until a subaisle with a pick is reached

				SS[p - 1][q - 1] = hlength * (leftMostAisleNum - 1) + (location_Size + vlength) * (block_num - 1) + hlength * (firstAisleNumforBlock[block_num - 1] - leftMostAisleNum);

				//outFile << "the current tour length before the last block movement is " << SS[p - 1][q - 1] << endl;

				//Clear the last block and go to the lower block either to the leftmost or rightmost aisle

				if (block_num == 1)
				{
					if (numofFilledSubAislefortheLastBlock % 2 == 1)
					{
						SS[p - 1][q - 1] = SS[p - 1][q - 1] + (numofFilledSubAislefortheLastBlock - 1) * location_Size + Vcost[block_num - 1][lastAisleNumforBlock[block_num - 1] - 1][2] + (lastAisleNumforBlock[block_num - 1] - firstAisleNumforBlock[block_num - 1]) * hlength;
						//outFile << "-------------- " << (numofFilledSubAislefortheLastBlock - 1) * location_Size << endl;
						//outFile << "-------------- " << Vcost[block_num - 1][lastAisleNumforBlock[block_num - 1] - 1][2] << endl;
						//outFile << "-------------- " << (lastAisleNumforBlock[block_num - 1] - firstAisleNumforBlock[block_num - 1]) * hlength << endl;
					}
					else
					{
						SS[p - 1][q - 1] = SS[p - 1][q - 1] + (numofFilledSubAislefortheLastBlock)*location_Size + (lastAisleNumforBlock[block_num - 1] - firstAisleNumforBlock[block_num - 1]) * hlength;
						//outFile << "-------------- " << (numofFilledSubAislefortheLastBlock)*location_Size << endl;
						//outFile << "-------------- " << (lastAisleNumforBlock[block_num - 1] - firstAisleNumforBlock[block_num - 1]) * hlength << endl;

					}

					//outFile << "the current tour length after the last block movements is " << SS[p - 1][q - 1] << endl;

					//finally return to depot

					SS[p - 1][q - 1] = SS[p - 1][q - 1] + (lastAisleNumforBlock[block_num - 1] - 1) * hlength;
				}
				
				else
				{
					if (numofFilledSubAislefortheLastBlock % 2 == 1)
					{
						SS[p - 1][q - 1] = SS[p - 1][q - 1] + (numofFilledSubAislefortheLastBlock - 1) * location_Size + Vcost[block_num - 1][lastAisleNumforBlock[block_num - 1] - 1][2] + (lastAisleNumforBlock[block_num - 1] - firstAisleNumforBlock[block_num - 1]) * hlength;
						//outFile << "-------------- " << (numofFilledSubAislefortheLastBlock - 1) * location_Size << endl;
						//outFile << "-------------- " << Vcost[block_num - 1][lastAisleNumforBlock[block_num - 1] - 1][2] << endl;
						//outFile << "-------------- " << (lastAisleNumforBlock[block_num - 1] - firstAisleNumforBlock[block_num - 1]) * hlength << endl;
					}
					else
					{
						SS[p - 1][q - 1] = SS[p - 1][q - 1] + (numofFilledSubAislefortheLastBlock)*location_Size + (lastAisleNumforBlock[block_num - 1] - firstAisleNumforBlock[block_num - 1]) * hlength;
						//outFile << "-------------- " << (numofFilledSubAislefortheLastBlock)*location_Size << endl;
						//outFile << "-------------- " << (lastAisleNumforBlock[block_num - 1] - firstAisleNumforBlock[block_num - 1]) * hlength << endl;

					}

					//outFile << "the current tour length after the last block movements is " << SS[p - 1][q - 1] << endl;

					int entryAisle[10];
					int exitAisle[10];

					exitAisle[block_num - 1] = lastAisleNumforBlock[block_num - 1];

					for (int k = block_num - 2; k > 0; k--)
					{
						if (abs(exitAisle[k + 1] - lastAisleNumforBlock[k]) <= abs(exitAisle[k + 1] - firstAisleNumAfterLeftMostAisleforBlock[k]))
						{
							entryAisle[k] = lastAisleNumforBlock[k];
							exitAisle[k] = firstAisleNumAfterLeftMostAisleforBlock[k];
						}
						else
						{
							entryAisle[k] = firstAisleNumAfterLeftMostAisleforBlock[k];
							exitAisle[k] = lastAisleNumforBlock[k];
						}
					}
					entryAisle[0] = lastAisleNumforBlock[0];
					exitAisle[0] = firstAisleNumAfterLeftMostAisleforBlock[0];


					//Clear the rest of the blocks and connections between blocks

					for (int k = block_num - 2; k >= 0; k--)
					{
						if (numofFilledSubAisleAfterLeftMostAisleforBlock[k] % 2 == 1)
						{
							SS[p - 1][q - 1] = SS[p - 1][q - 1] + abs(exitAisle[k + 1] - entryAisle[k]) * hlength + (numofFilledSubAisleAfterLeftMostAisleforBlock[k]) * location_Size + (lastAisleNumforBlock[k] - firstAisleNumAfterLeftMostAisleforBlock[k]) * hlength + vlength;
							//outFile << "-------------- " << vlength << endl;
							//outFile << "-------------- " << abs(exitAisle[k + 1] - entryAisle[k]) * hlength << endl;
							//outFile << "-------------- " << (numofFilledSubAisleAfterLeftMostAisleforBlock[k]) * location_Size << endl;
							//outFile << "-------------- " << (lastAisleNumforBlock[k] - firstAisleNumAfterLeftMostAisleforBlock[k]) * hlength << endl;
						}
						else if (numofFilledSubAisleAfterLeftMostAisleforBlock[k] == 0)
						{
							SS[p - 1][q - 1] = SS[p - 1][q - 1] + abs(exitAisle[k + 1] - entryAisle[k]) * hlength + location_Size + (lastAisleNumforBlock[k] - firstAisleNumAfterLeftMostAisleforBlock[k]) * hlength + vlength;
							//outFile << "-------------- " << vlength << endl;
							//outFile << "-------------- " << abs(exitAisle[k + 1] - entryAisle[k]) * hlength << endl;
							//outFile << "-------------- " << location_Size << endl;
							//outFile << "-------------- " << (lastAisleNumforBlock[k] - firstAisleNumAfterLeftMostAisleforBlock[k]) * hlength << endl;
						}

						else
						{

							SS[p - 1][q - 1] = SS[p - 1][q - 1] + abs(exitAisle[k + 1] - entryAisle[k]) * hlength + (numofFilledSubAisleAfterLeftMostAisleforBlock[k] - 1) * location_Size + Vcost[k][exitAisle[k] - 1][2] + (lastAisleNumforBlock[k] - firstAisleNumAfterLeftMostAisleforBlock[k]) * hlength + vlength;
							//outFile << "-------------- " << vlength << endl;
							//outFile << "-------------- " << abs(exitAisle[k + 1] - entryAisle[k]) * hlength << endl;
							//outFile << "-------------- " << (numofFilledSubAisleAfterLeftMostAisleforBlock[k] - 1) * location_Size << endl;
							//outFile << "-------------- " << Vcost[k][exitAisle[k] - 1][2] << endl;
							//outFile << "-------------- " << (lastAisleNumforBlock[k] - firstAisleNumAfterLeftMostAisleforBlock[k]) * hlength << endl;

						}

					}
					//outFile << "the current tour length before returning to depot is " << SS[p - 1][q - 1] << endl;

					//finally return to depot

					SS[p - 1][q - 1] = SS[p - 1][q - 1] + (exitAisle[0] - 1) * hlength;
				}





				if (countItemInAisle[q - 1] == 0)
				{
					if (p < q)
					{
						////outFile << "hello  ";
						SS[p - 1][q - 1] = SS[p - 1][q - 2];
					}
					else
					{
						////outFile << "ciao  ";
						SS[p - 1][q - 1] = 0;
					}
				}


				//cout << "Final tour length is " << SS[p - 1][q - 1] << endl;

				outFile << "Final tour length for S[" << p - 1 << "][" << q - 1 << "] is " << SS[p - 1][q - 1] << endl;


			}
		}

		int minPickWave[100][100];

		////outFile << "---------------------" << endl << "minPickWave[i][j]=" << endl << endl;
		////outFile << "---------------------" << endl << "minPickWave[i][j]=" << endl << endl;

		//calculates 1-picker column of minPickWave[i][j] array 
		for (int i = 0; i < aisle_num; i++)
		{
			minPickWave[i][0] = SS[0][i];
			////outFile << minPickWave[i][0] << ", ";
		}

		////outFile << endl;

		//calculates i=j cells of minPickWave[i][j] array 
		for (int i = 1; i < aisle_num; i++)
		{
			if (minPickWave[i - 1][i - 1] > SS[i][i])
			{
				minPickWave[i][i] = minPickWave[i - 1][i - 1];
			}
			else
			{
				minPickWave[i][i] = SS[i][i];
			}
			////outFile << minPickWave[i][i] << "-- ";
		}

		////outFile << endl;


		//calculates rest of minPickWave[i][j] array 


		for (int i = 2; i < aisle_num; i++)
		{
			for (int j = 1; j <= i - 1; j++)
			{
				int temp1 = 1000;
				for (int k = j - 1; k <= i - 1; k++)
				{
					if (temp1 > max(minPickWave[k][j - 1], SS[k + 1][i]))
						temp1 = max(minPickWave[k][j - 1], SS[k + 1][i]);
				}

				minPickWave[i][j] = temp1;
				////outFile << minPickWave[i][j] << "** ";

			}
		}

		////outFile << endl << "-------------------------" << endl;
		////outFile << endl << "-------------------------" << endl;
		/*
		for (i = 0; i < aisle_num; i++)
		{
			for (j = 0; j <= i; j++)
			{
				//outFile << minPickWave[i][j] << ", ";
				//outFile << minPickWave[i][j] << ", ";
			}

			//outFile << endl;
			//outFile << endl;

		}*/


		outFile << "Minmax ";
		for (int j = 0; j < aisle_num; j++)
		{
			//cout << minPickWave[aisle_num - 1][j] << ", ";
			outFile << minPickWave[aisle_num - 1][j] << " ";
		}

		outFile << endl;
		//outFile << endl;


		////outFile << endl << "-------------------------" << endl;
		////outFile << endl << "-------------------------" << endl;

	}



	////outFile << "The firstpicker's total is " << sumfirstpicker << " units." << endl;
	////outFile << "The secondpicker's total is " << sumsecondpicker << " units." << endl << endl;

	int pause = 0;
	cin >> pause;
	return 0;
}


