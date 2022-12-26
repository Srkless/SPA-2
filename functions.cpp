#include <string>
#include <iostream>
#include "functions.h"

int returnIndex(std::string name, std::string words[MAX], int nodeNum)
{
	for (int i = 0; i < nodeNum; i++)
		if (name == words[i])
			return i;
}
// DFS, modifikovana logika DFS-a koji se naucio na programiranju 2
void DFS(int index, double matrix[MAX * MAX], int nodeNum, std::string words[MAX])
{
	bool visit[MAX];
	for (int i = 0; i < nodeNum; i++)
		visit[i] = false;

	dfsVisit(index, visit, matrix, nodeNum, words);

	for (int i = 0; i < nodeNum; i++)
		if (!visit[i])
		{
			dfsVisit(i, visit, matrix, nodeNum, words);
		}
}
void dfsVisit(int index, bool* visit, double matrix[MAX * MAX], int nodeNum, std::string words[MAX])
{
	visit[index] = true;
	std::cout << words[index] << " ";
	for (int i = 0; i < nodeNum; i++)
		if (!visit[i] && matrix[index * nodeNum + i])
		{
			dfsVisit(i, visit, matrix, nodeNum, words);
		}
}

// Floydov algoritam, logika koja je naucena na programiranju 2 uz malu modifikaciju popravljanja gresaka i racunanja grana svakog cvora
void floyd(double D[MAX * MAX], int branchNum[MAX * MAX], int nodeNum, int t[MAX * MAX])
{
	for (int k = 0; k < nodeNum; k++)
		for (int i = 0; i < nodeNum; i++)
			for (int j = 0; j < nodeNum; j++)
				if (D[i * nodeNum + j] > D[i * nodeNum + k] + D[k * nodeNum + j])
				{
					D[i * nodeNum + j] = D[i * nodeNum + k] + D[k * nodeNum + j];
					branchNum[i * nodeNum + j] += 2;
					t[i * nodeNum + j] = t[k * nodeNum + j];
				}

	for (int i = 0; i < nodeNum; i++) // Fixing errors with the main diagonal
		for (int j = 0; j < nodeNum; j++)
		{
			if (i == j)
				D[i * nodeNum + j] = INFINITY;
		}
}

// Selection sort algoritam uz malu modifikaciju
void sort(NODE* matrix, int nodeNum, int* branchNumArray)
{
	for (int i = 0; i < nodeNum; i++)
		for (int j = i + 1; j < nodeNum; j++)
		{
			if (matrix[i].weight == INFINITY)
				continue;
			if (matrix[i].weight > matrix[j].weight)
			{
				double tmp = matrix[i].weight;
				int num = branchNumArray[i];
				std::string s = matrix[i].nodeName;
				

				matrix[i].weight = matrix[j].weight;
				branchNumArray[i] = branchNumArray[j];
				matrix[i].nodeName = matrix[j].nodeName;

				matrix[j].weight = tmp;
				branchNumArray[j] = num;
				matrix[j].nodeName = s;
			}
		}
}

void PATH(int i, int j, std::string words[MAX], int nodeNum, int t[MAX*MAX])
{
	if (i == j)
	{
		std::cout << words[i] << " ";
		return;
	}
	else
	{
		if (t[i * nodeNum + j] == -1)
		{
			std::cout << "Ne postoji put izmedju ova 2 cvora";
			return;
		}
		else
		{
			PATH(i, t[i * nodeNum + j], words, nodeNum, t);
			std::cout << words[j] << " ";
		}


	}
}