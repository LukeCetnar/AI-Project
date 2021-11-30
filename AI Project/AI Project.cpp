// AI Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

int steps = 0;
struct Blocks{

    std::vector <char> L1, L2;
    char arm1 = ' ';
    char arm2 = ' ';
};


void printBlocks(Blocks B) 
{


    std::cout << "Arm1"  << "\t" << "Arm2\n"<< B.arm1 << "\t" << B.arm2 << std::endl << std::endl;
    size_t max = B.L1.size() > B.L2.size() ? B.L1.size() : B.L2.size();
    size_t min = B.L1.size() < B.L2.size() ? B.L1.size() : B.L2.size();

    if (max == min) 
    {
        for (int i = max - 1; i >= 0; i--) 
        {
            std::cout << B.L1.at(i) << "\t" << B.L2.at(i) << std::endl;
        }

    }
    else
    {
        for (int i = max - 1; i >= 0; i--)
        {
            if (i >= min && B.L1.size() > B.L2.size())
            {
                std::cout << B.L1.at(i) << "\t" << " " << std::endl;
            }
            else if (!(i >= min) && B.L1.size() > B.L2.size())
            {
                std::cout << B.L1.at(i) << "\t" << B.L2.at(i) << std::endl;
            }
            if (i >= min && B.L1.size() < B.L2.size())
            {
                std::cout << " " << "\t" << B.L2.at(i) << std::endl;
            }
            else if (!(i >= min) && B.L1.size() < B.L2.size())
            {
                std::cout << B.L1.at(i) << "\t" << B.L2.at(i) << std::endl;
            }


        }

    }


    std::cout << "---" "\t" << "---" << std::endl;
    std::cout << "L1" "\t" << "L2" << std::endl;
    steps++;


}
/**
 * this function searches for the specified character in each of the block stacks.
 * 
 * \param b the block data stucture to be analized
 * \param x the char to be searched for;
 *  returns true if it is in stack L1 and false if it is in stack L2
 */
bool searchStacks(Blocks B,char x) 
{
    if (!B.L1.empty()) {
        for (int i = 0; i < B.L1.size(); i++)
        {
            if (B.L1.at(i) == x)
            {
                return true;
            }

        }
    }
    return false;


}




int main()
{
    Blocks Current;
    Blocks Desired;
    std::string tmp;

    //section for getting user input for the current and desired state
    std::cout << "Accetpaple inputs are (a,b,c,d,e,f,g,h,i,j,k,l,m,n)\n Enter one of each 14 blocks\n";
    std::cout << "Please enter the current state of the Blocks from bottom to top\nL1?";
    std::cin >> tmp;
    //tmp = "abcde";

    for (int i = 0; i < strlen(tmp.c_str()); i++)
    {
        Current.L1.push_back(tmp.c_str()[i]);
    }
    std::cout << "L2?";

    std::cin >> tmp;
    //tmp = "fghijklmn";
    for (int i = 0; i < strlen(tmp.c_str()); i++)
    {
        Current.L2.push_back(tmp.c_str()[i]);
    }



    std::cout << "Please enter the Desired state of the Blocks from bottom to top\nL1?";
    std::cin >> tmp;
    //tmp = "aejklmnfghd";
    for (int i = 0; i < strlen(tmp.c_str()); i++)
    {
        Desired.L1.push_back(tmp.c_str()[i]);
    }
    std::cout << std::endl;
    std::cout << "L2?";

    std::cin >> tmp;
    //tmp = "cib";
    for (int i = 0; i < strlen(tmp.c_str()); i++)
    {
        Desired.L2.push_back(tmp.c_str()[i]);
    }


    std::cout << "Desired Block state\n";
    printBlocks(Desired);
    std::cout << "Current Block state\n";
    printBlocks(Current);
    std::cout << std::endl;



    //Start the solve proccess


    steps = 0;
    int stackIndex = 0;
    //Step 1: Check to see if L1 Matches the desired L1
    while (Desired.L1 != Current.L1)
    {
        //Step 1a: see if the bottom element matches, if so increment the stack index
        //make sure stack has items in it, protects from out of range exception
        if (!Current.L1.empty())
        {
            //more code stuff to protect from out of range exception
            try
            {
                
                if (Current.L1.at(stackIndex) == Desired.L1.at(stackIndex))
                {
                    stackIndex++;
                }

            }
            catch (const std::exception&)
            {
                if (stackIndex > Current.L1.size())
                {
                    stackIndex++;
                }

            }

        }



        //Step 1b: determine which stack has the desired element in it.
        if (searchStacks(Current, Desired.L1.at(stackIndex)))
        {
            //Step 1c: unstack the identfied stack until the desired element is found
            while (Current.L1.back() != Desired.L1.at(stackIndex))
            {
                std::cout << "Stacking " << Current.L1.back() << " to Stack L2 with Arm2" << std::endl;
                Current.L2.push_back(Current.L1.back());
                Current.L1.pop_back();
                printBlocks(Current);
            }
            // after this is complete then the state should be L1 whith the desired block on top
            //Step 1d:pick up the element into arm 1 to hold onto
            std::cout << "Pick up " << Current.L1.back() << " in arm1" << std::endl;
            Current.arm1 = Current.L1.back();
            Current.L1.pop_back();
            printBlocks(Current);
            //Step 1e: unstack L1 until the desired index is reached
            while (Current.L2.size() != stackIndex)
            {
                std::cout << "Stacking " << Current.L2.back() << " to Stack L1 with Arm2" << std::endl;
                Current.L1.push_back(Current.L2.back());
                Current.L2.pop_back();
                printBlocks(Current);
            }
            //Step 1f: put down the held block in the correct place
            std::cout << "Put Down from Arm1" << Current.arm1 << "to Stack L2" << std::endl;
            Current.L2.push_back(Current.arm1);
            Current.arm1 = ' ';
            printBlocks(Current);



        }
        else
        {//empty L2 in search of the desired block

            while (Current.L2.back() != Desired.L1.at(stackIndex))
            {
                std::cout << "Stacking " << Current.L2.back() << " to Stack L1 with Arm2" << std::endl;
                Current.L1.push_back(Current.L2.back());
                Current.L2.pop_back();
                printBlocks(Current);
            }
            // after this is complete then the state should be L1 whith the desired block on top
            //then we place it in arm 1 to hold onto
            std::cout << "Pick up " << Current.L2.back() << " in arm1" << std::endl;
            Current.arm1 = Current.L2.back();
            Current.L2.pop_back();
            printBlocks(Current);
            //now that the block is in one of the arm i am going to move all of the block to L2 using arm 2
            while (Current.L1.size() != stackIndex)
            {
                std::cout << "Stacking " << Current.L1.back() << " to Stack L2 with Arm2" << std::endl;
                Current.L2.push_back(Current.L1.back());
                Current.L1.pop_back();
                printBlocks(Current);
            }
            // now place the arm2 block onto L1 `
            std::cout << "Put Down from Arm1 " << Current.arm1 << " to Stack L1 " << std::endl;
            Current.L1.push_back(Current.arm1);
            Current.arm1 = ' ';
            printBlocks(Current);

        }


    }
    std::cout << "L1 is compelted in " << steps << " steps" << std::endl;
    //now that Stack L1 is sorted it is time to move onto stack L2
    // I also assume that all of the block are already in L2 just out of order.

    stackIndex = 0;
    //Step 2: Check to see if L2 Matches Desired L2
    while(Desired.L2 != Current.L2)
    {
        std::cout << "Starting L2" << std::endl;
        if (!Current.L2.empty())
        {
            //std::cout << "stack index: " << stackIndex << std::endl;
            try
            {
                if (Current.L2.at(stackIndex) == Desired.L2.at(stackIndex))
                {
                    stackIndex++;
                }

            }
            catch (const std::exception&)
            {
                if (stackIndex > Current.L2.size())
                {
                    stackIndex++;
                }

            }

        }
        if (Current.L2.size() > Desired.L2.size()) 
        {
            std::cout << "Pick up " << Current.L2.back() << " in arm1" << std::endl;
            if (Current.arm1 == ' ') {
            Current.arm1 = Current.L2.back();
            Current.L2.pop_back();
            printBlocks(Current);

            }
            else
            {
                Current.arm2 = Current.L2.back();
                Current.L2.pop_back();
                printBlocks(Current);

            }
            

        
        }
        else {

            if (searchStacks(Current, Desired.L2.at(stackIndex)))
            {//empty L1 in search of the desired block
                while (Current.L1.back() != Desired.L2.at(stackIndex))
                {
                    std::cout << "Stacking " << Current.L1.back() << " to Stack L2 with Arm2" << std::endl;
                    Current.L2.push_back(Current.L1.back());
                    Current.L1.pop_back();
                    printBlocks(Current);
                }
                // after this is complete then the state should be L1 whith the desired block on top
                //then we place it in arm 1 to hold onto
                std::cout << "Pick up " << Current.L1.back() << " in arm1" << std::endl;
                Current.arm1 = Current.L1.back();
                Current.L1.pop_back();
                printBlocks(Current);
                //now that the block is in one of the arm i am going to move all of the block to L1 using arm 2
                while (Current.L2.size() != stackIndex)
                {
                    std::cout << "Stacking " << Current.L2.back() << " to Stack L1 with Arm2" << std::endl;
                    Current.L1.push_back(Current.L2.back());
                    Current.L2.pop_back();
                    printBlocks(Current);
                }
                // now place the arm2 block onto L1 `
                std::cout << "Put Down from Arm1 " << Current.arm1 << " to Stack L2" << std::endl;
                Current.L2.push_back(Current.arm1);
                Current.arm1 = ' ';
                printBlocks(Current);


            }
            else
            {//empty L1 in search of the desired block
                while (Current.L2.back() != Desired.L2.at(stackIndex))
                {
                    std::cout << "Stacking " << Current.L2.back() << " to Stack L1 with Arm2" << std::endl;
                    Current.L1.push_back(Current.L2.back());
                    Current.L2.pop_back();
                    printBlocks(Current);
                }
                // after this is complete then the state should be L1 whith the desired block on top
                //then we place it in arm 1 to hold onto
                std::cout << "Pick up " << Current.L2.back() << " in arm1" << std::endl;
                Current.arm1 = Current.L2.back();
                Current.L2.pop_back();
                printBlocks(Current);
                //now that the block is in one of the arm, move all of the block to L1 using arm 2
                while (Current.L2.size() != stackIndex)
                {
                    std::cout << "Stacking " << Current.L2.back() << " to Stack L1 with Arm2" << std::endl;
                    Current.L1.push_back(Current.L2.back());
                    Current.L2.pop_back();
                    printBlocks(Current);
                }
                // now place the arm1 block onto L2
                std::cout << "Put Down from Arm1 " << Current.arm1 << " to Stack L2" << std::endl;
                Current.L2.push_back(Current.arm1);
                Current.arm1 = ' ';
                printBlocks(Current);
                ;

            }
        }

    }


    //Step 3: Declare success
    std::cout << "everything is compelte this took " << steps << " steps" << std::endl;

    std::cout << "Desired Block state\n";
    printBlocks(Desired);
    std::cout << "Current Block state\n";
    printBlocks(Current);
    std::cout << std::endl;

    




}
