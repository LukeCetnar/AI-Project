// AI Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Blocks.h"
#include <iostream>
#include <string>
#include <vector>
using std::vector;
struct Node
{
	int state;
	vector<Node*> child;
};

// Utility function to create a new tree node
Node* newNode(int key)
{
	Node* temp = new Node;
	temp->state = key;
	return temp;
}

int main()
{
	std::string L1, L2, arms;

	//section for getting user input for the current and desired state
	std::cout << "Accetpaple inputs are (a,b,c,d,e,f,g,h,i,j,k,l,m,n)\n Enter one of each 14 blocks\n";
	std::cout << "Please enter the current state of the Blocks from bottom to top\n";
	std::cout << "L1?\n";
	//std::cin >> L1;
	L1 = "abcd";
	std::cout << "L2?\n";
	//std::cin >> L2;
	L2 = "efg";
	std::cout << "Arms?\n";
	//std::cin >> arms;
	arms = "  ";

	Blocks* Initial = new Blocks(L1, L2, arms);

	std::cout << "Please enter the Desired state of the Blocks from bottom to top\n";
	//std::cin >> L1;
	L1 = "gef";
	std::cout << "L2?\n";
	//std::cin >> L2;
	L2 = "cadb";
	std::cout << "Arms?\n";
	//std::cin >> arms;
	arms = "  ";

	Blocks* Desired = new Blocks(L1, L2, arms);

	std::cout << "Desired Block state\n" << *Desired;
	std::cout << "Current Block state\n" << *Initial;
	std::cout << std::endl;

	int stateCounter = 0;
	std::vector<Blocks> states;
	Blocks* Current = (Blocks*)malloc(sizeof Blocks);
	Blocks* tmp = (Blocks*)malloc(sizeof Blocks);
	memcpy(Current, Initial, sizeof Blocks);

	Node* root = newNode(stateCounter);
	std::cout << "Some Bull Shit Block state\n" << *Current;

	states.push_back(*Current);

	for (size_t i = 0; i < 6; i++)
	{
		memcpy(tmp, Current, sizeof Blocks);

		if (i == 0 && Current->movePre(0))
		{
			//Do the action and make a tree node
			tmp->move(0);
			states.push_back(*tmp);
			stateCounter++;
			Node* root = newNode(stateCounter);
		}
		else if (i == 1 && Current->movePre(1))
		{
			tmp->move(1);
			stateCounter++;
			Node* root = newNode(stateCounter);
		}
		else if (i == 2 && Current->pickUpPre(0))
		{
			tmp->pickUp(0);
			stateCounter++;
			Node* root = newNode(stateCounter);
		}
		else if (i == 3 && Current->pickUpPre(1))
		{
			tmp->pickUp(1);
			stateCounter++;
			Node* root = newNode(stateCounter);
		}
		else if (i == 4 && Current->putDownPre(1))
		{
			tmp->putDown(0);
			stateCounter++;
			Node* root = newNode(stateCounter);
		}
		else if (i == 5 && Current->putDownPre(1))
		{
			tmp->putDown(1);
			stateCounter++;
			Node* root = newNode(stateCounter);
		}

		if (tmp->checkEqual(*Desired))
		{
			std::cout << "WTf we DID IT \n";
			return stateCounter;
		}
	}
}