/**

**/
#include "Blocks.h"

Blocks::Blocks(std::string sL1, std::string sL2, std::string arms)
{
	reassgin(sL1, sL2, arms);
}

bool Blocks::reassgin(std::string sL1, std::string sL2, std::string arms)
{
	for (int i = 0; i < strlen(sL1.c_str()); i++)
	{
		L1.push_back(sL1.c_str()[i]);
	}

	for (int i = 0; i < strlen(sL2.c_str()); i++)
	{
		L2.push_back(sL2.c_str()[i]);
	}

	std::get<0>(arm1) = arms.c_str()[0];
	std::get<0>(arm2) = arms.c_str()[1];
	std::get<1>(arm1) = 0;
	std::get<1>(arm2) = 1;

	return true;
}

bool Blocks::checkEqual(Blocks B)
{
	return (L1 == B.L1 &&
		L2 == B.L2 &&
		arm1 == B.arm1 &&
		arm2 == B.arm2);
}

bool Blocks::movePre(int i)
{
	//arm has a block

	switch (i)
	{
	case 1:
		return (arm1.first != ' ');
	case 2:
		return (arm2.first != ' ');
	}
	return false;
}

void Blocks::move(int i)
{
	switch (i)
	{
	case 1:
		arm1.second ^ 0x1;
		break;
	case 2:
		arm2.second ^ 0x1;
		break;
	}
	return;
}

bool Blocks::pickUpPre(int i)
{
	//arm does not have block
	//location below has a block
	switch (i)
	{
	case 1:
		if (arm1.first == ' ')
		{
			switch (arm1.second)
			{
			case 0:
				return !L1.empty();

			case 1:
				return !L2.empty();
			}
		}
		break;
	case 2:
		if (arm2.first == ' ')
		{
			switch (arm2.second)
			{
			case 0:
				return !L1.empty();

			case 1:
				return !L2.empty();
			}
		}
	}
	return false;
}

void Blocks::pickUp(int i)
{
	switch (i)
	{
	case 1:
		switch (arm1.second)
		{
		case 0:
			arm1.first = L1.back();
			L1.pop_back();
		case 1:
			arm1.first = L2.back();
			L2.pop_back();
		}

	case 2:
		switch (arm2.second)
		{
		case 0:
			arm2.first = L1.back();
			L1.pop_back();
		case 1:
			arm2.first = L2.back();
			L2.pop_back();
		}
	}
}

bool Blocks::putDownPre(int i)
{
	//has a block
	switch (i)
	{
	case 1:
		return (arm1.first != ' ');
	case 2:
		return (arm2.first != ' ');
	}
	return false;
}

void Blocks::putDown(int i)
{
	switch (i)
	{
	case 1:
		switch (arm1.second)
		{
		case 0:
			L1.push_back(arm1.first);
			arm1.first = ' ';
		case 1:
			L2.push_back(arm1.first);
			arm1.first = ' ';
		}

	case 2:
		switch (arm2.second)
		{
		case 0:
			L1.push_back(arm2.first);
			arm2.first = ' ';
		case 1:
			L2.push_back(arm2.first);
			arm2.first = ' ';
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Blocks& B)
{
	if (std::get<1>(B.arm1) == 0)
	{
		os << "\n\n\nArm1" << "\t" << "Arm2\n" << std::get<0>(B.arm1) << "\t" << std::get<0>(B.arm2) << std::endl << std::endl;
	}
	else
	{
		os << "\n\n\nArm2" << "\t" << "Arm1\n" << std::get<0>(B.arm2) << "\t" << std::get<0>(B.arm1) << std::endl << std::endl;
	}

	size_t max = B.L1.size() > B.L2.size() ? B.L1.size() : B.L2.size();
	size_t min = B.L1.size() < B.L2.size() ? B.L1.size() : B.L2.size();

	if (max == min)
	{
		for (int i = max - 1; i >= 0; i--)
		{
			os << B.L1.at(i) << "\t" << B.L2.at(i) << std::endl;
		}
	}
	else
	{
		for (int i = max - 1; i >= 0; i--)
		{
			if (i >= min && B.L1.size() > B.L2.size())
			{
				os << B.L1.at(i) << "\t" << " " << std::endl;
			}
			else if (!(i >= min) && B.L1.size() > B.L2.size())
			{
				os << B.L1.at(i) << "\t" << B.L2.at(i) << std::endl;
			}
			if (i >= min && B.L1.size() < B.L2.size())
			{
				os << " " << "\t" << B.L2.at(i) << std::endl;
			}
			else if (!(i >= min) && B.L1.size() < B.L2.size())
			{
				os << B.L1.at(i) << "\t" << B.L2.at(i) << std::endl;
			}
		}
	}

	os << "---" "\t" << "---" << std::endl;
	os << "L1" "\t" << "L2" << std::endl << std::endl << std::endl;

	return os;
}