#pragma once
#include <vector>
#include <iostream>
#include <assert.h>
#include <tuple>


class Blocks
{



public:
	Blocks(std::string L1, std::string L2, std::string arms);

	//helpers
	bool reassgin(std::string sL1, std::string sL2, std::string arms);
	friend std::ostream& operator<<(std::ostream& os, const Blocks& B);
	bool checkEqual(Blocks B);
	

	//Actions
	//precondition checks
	bool movePre(int i);
	bool pickUpPre(int i);
	bool putDownPre(int i);
	bool stackPre(int i);
	bool unstackPre(int i);

	//actions
	void move(int i);
	void pickUp(int i);
	void putDown(int i);
	void stack(int i);
	void unstack(int i);
	
private:


	std::vector <char> L1, L2;
	std::pair<char, int> arm1, arm2;

	

};

