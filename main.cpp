#include <iostream>
#include <fstream>
#include <string>
#include "functions.h"

int main()
{
	int nodeNum = 0;
	double matrix[MAX * MAX], D[MAX * MAX];
	NODE tmp[MAX];
	int branchNum[MAX * MAX];
	int t[MAX * MAX];
	std::string fileName, words[MAX], startNode;

	do
	{
		std::cout << "==========================================" << std::endl;
		std::cout << "Dostupni fileovi: \"graf1.txt\", \"graf2.txt\"\nNapisi KRAJ za zavrsetak programa." << std::endl;
		std::cout << "Unesi ime file: ";
		std::cin >> fileName;

		std::ifstream inputFile(fileName);

		if (inputFile.is_open())
		{
			inputFile >> nodeNum; //Reads first line of file (number of nodes)

			for (int i = 0; i < nodeNum; i++) // Reads second line of file (sorted words)
				inputFile >> words[i];

			for (int i = 0; i < nodeNum; i++) // Reads adjacency matrix
				for (int j = 0; j < nodeNum; j++)
					inputFile >> matrix[i * nodeNum + j];
			inputFile.close();
		}
		else
			return (fileName == "KRAJ")? 0: 1; // Error: FIle doesn't exist (return 1)

		
		for (int i = 0; i < nodeNum; i++) //Reads adjacency matrix and branchs number of every node
			for (int j = 0; j < nodeNum; j++)
			{
				if (matrix[i * nodeNum + j] == 0)
				{
					branchNum[i * nodeNum + j] = 0;
					D[i * nodeNum + j] = INFINITY;
				}
				else
				{
					branchNum[i * nodeNum + j] = 1;
					D[i * nodeNum + j] = matrix[i * nodeNum + j];
				}
			}
		for (int i = 0; i < nodeNum; i++)
			for (int j = 0; j < nodeNum; j++)
			{
				if (i == j || D[i * nodeNum + j] == INFINITY)
					t[i * nodeNum + j] = -1;
				else if(i != j || D[i * nodeNum + j] < INFINITY)
					t[i * nodeNum + j] = i;
			}
		for (int i = 0; i < nodeNum; i++) //Prints every node to the console
			std::cout << words[i] << " ";
		std::cout << std::endl;

		std::cout << "Unesi pocetni cvor: "; std::cin >> startNode;

		DFS(returnIndex(startNode, words, nodeNum), matrix, nodeNum, words);
		std::cout << std::endl;

		floyd(D, branchNum, nodeNum, t);

		for (int i = 0; i < nodeNum; i++)
		{
			for (int j = 0; j < nodeNum; j++)
				std::cout << matrix[i * nodeNum + j] << " ";
			std::cout << std::endl;

		}
		std::ofstream outputFile("rezultat.txt");
		std::cout << "Modfikaija: " << std::endl;
		std::string mod1, mod2;
		std::cout << "Unesi pocetni i krajnji cvor: ";
		std::cin >> mod1 >> mod2;
		int i1 = returnIndex(mod1, words, nodeNum), i2 = returnIndex(mod2, words, nodeNum);
		
		PATH(i1, i2, words, nodeNum, t);
		std::cout << std::endl;
		for (int i = 0, condition = 0; condition < nodeNum; i++, condition++)
		{
			int branchNumArray[MAX];
			for (int j = 0; j < nodeNum; j++)
			{
				tmp[j].weight = D[i * nodeNum + j];
				tmp[j].nodeName = words[j];
				(i == j) ? branchNumArray[j] = 0 : branchNumArray[j] = branchNum[i * nodeNum + j];
			}

			sort(tmp, nodeNum, branchNumArray);

			outputFile << words[i] << " [";
			if (!outputFile.is_open())
				return 1; // Error: Unable to create file
			int counter;
			double num;
			int flag = 1;
			counter = 0;
			for (int j = 0; j < nodeNum; j++)
			{
				if (tmp[j].weight != INFINITY && words[i] != words[j])
				{
					num = tmp[j].weight;
					for (int k = 1; j + k < nodeNum; k++)
					{
						if (tmp[j].weight == tmp[j + k].weight)
						{
							if (branchNumArray[j] > branchNumArray[j + k])
							{
								outputFile << tmp[j + k].nodeName << ":";
								outputFile << num << " ";
								counter++;
							}
							else
							{
								outputFile << tmp[j++].nodeName << ":";
								outputFile << num << " ";
								counter++;
							}
						}
					}
					if (counter >= 5)
						break;
					outputFile << tmp[j].nodeName << ":";
					outputFile << num << " ";
					counter += (counter == 5) ? 0 : 1;
				}

			}
			outputFile << "]";
			outputFile << std::endl;
		}
		outputFile.close();
	} while (fileName != "KRAJ");
	return 0;
}