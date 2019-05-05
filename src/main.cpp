#include "../inc/menu.hh"


using namespace std;

int main()
{
    char tmp = '.';

    while (tmp != 'q')
    {
        showMenu();
        cin >> tmp;
        menu(tmp);
    }

    return 0;
}
