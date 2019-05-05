#include "../inc/menu.hh"

void showMenu()
{
 std::cout << std::endl;
 std::cout << "Choose what you want to do:" << std::endl;
 std::cout << "---------------------------" << std::endl;
 std::cout << std::endl;
 std::cout << "1 -   Load from file" << std::endl;
 std::cout << "2 -   Efficiency test" << std::endl;
 std::cout << std::endl;
 std::cout << "q -   Exit" << std::endl;
 std::cout << std::endl;
 std::cout << "Your choice:";
}

void menu(char tmp)
{
    switch (tmp)
    {
        case '1': loadFromFile();
            break;
        case '2': startTest();
            break;
        case 'q': std::cout << "Closing..." << std::endl;
            break;
        default:
            std::cout << std::endl;
            std::cout<< "Invalid option! Chose one of the below:" << std::endl;
            break;
    }
}