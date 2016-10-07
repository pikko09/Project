// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "LWR_Dynamic_Model_Lib.h"
#include <string>
#include "math.h"

#define DIM 7

using namespace std;

int main()
{
	float q[DIM], tauf[DIM], vel[DIM], tau[DIM];
	float** B;
	float D[DIM];
	B = (float**)malloc(DIM * sizeof(float*));
	int i = 0;
	int j = 0;
	for (i = 0; i < DIM; i++)
		B[i] = (float*)malloc(DIM * sizeof(float*));
	string word;
	FILE *fd;
	char* pEnd;
	const char* c;
	/* apre il file */
	ifstream filePos;
	ifstream fileTau;
	ifstream fileVel;
	filePos.open("pos.txt");
	fileTau.open("tau.txt");
	fileVel.open("vel.txt");
	i = 0;
	while (filePos >> word)
	{	c = word.c_str();
		q[i] = atof(c);
		fileTau >> word;
		c = word.c_str();
		tau[i] = atof(c);
		fileVel >> word;
		c = word.c_str();
		vel[i] = atof(c);
		i++;
	}
	CLWR_Dynamic_Model_Lib* a;
	a = new CLWR_Dynamic_Model_Lib();
	a->get_B(B,q,NULL);
	a->get_friction(tauf, vel);
	for (i = 0; i < DIM; i++)
		D[i] = tauf[i] / vel[i];

	ofstream fileOut;
	fileOut.open("Friction.txt");
	for (i = 0; i < DIM; i++)
	{
		cout << tauf[i] << endl;
		fileOut << tauf[i] << " ";
	}
	fileOut << endl;
	fileOut.close();
	
	fileOut.open("Inertia.txt");
	for (i = 0; i < DIM; i++)
	{
		for (j = 0; j < DIM; j++)
		{
			cout << B[i][j] << " ";
			fileOut << B[i][j] << " ";
		}
		cout << endl;
		fileOut << '\n';
	}
	fileOut.close();

	fileOut.open("FrictionMatrix.txt");
	for (i = 0; i < DIM; i++)
	{
		for (j = 0; j < DIM; j++)
		{
			if (i == j)
			{
				cout << D[i] << " ";
				fileOut << D[i] << " ";
			}
			else
			{
				cout << 0 << " ";
				fileOut << 0 << " ";
			}
		}
		cout << endl;
		fileOut << '\n';
	}
	fileOut.close();
	getchar();

}

