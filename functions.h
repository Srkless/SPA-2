#pragma once
#define MAX 20

typedef struct node
{
	double weight;
	std::string nodeName;
}NODE;

int returnIndex(std::string name, std::string words[MAX], int nodeNum);
void DFS(int index, double matrix[MAX * MAX], int nodeNum, std::string words[MAX]);
void dfsVisit(int index, bool* visit, double matrix[MAX * MAX], int nodeNum, std::string words[MAX]);
void floyd(double D[MAX * MAX], int branchNum[MAX * MAX], int nodeNum, int t[MAX * MAX]);
void sort(NODE* matrix, int nodeNum, int* branchNumArray);
void PATH(int i, int j, std::string words[MAX], int nodeNum, int t[MAX * MAX]);