#include <iostream>
#include "duree.h"
using namespace std;


int main()
{
    Duree duree1(0, 10, 28), duree2(0, 10, 28);

    if (duree1 < duree2)
        cout << "La duree1 est inferieur à la duree2";
    else
    {
        if(duree1 != duree2)
        {
            cout << "La duree2 est inferieur à la duree1";
        }
        else
        {
            cout << "La duree1 et la duree2 sont identiques";
        }
    }
    cout << endl;
    return 0;
}