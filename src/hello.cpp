#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    cout << "Input command to run!" << endl;
    string command;
    cin >> command;

    const char *c = command.c_str();    //str을 char*로 변환

    system(c);
    return 0;

}