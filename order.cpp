
/********************************************************************************
* Definitions
********************************************************************************/
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;
/********************************************************************************
* Code
********************************************************************************/
// argc : argument cout
// argv : argument vector
int main(int argc, const char** argv)
{
    int check = argc>1?0:1;
    /*
    * [check]
    * - if nothing input -> check = 1
    * - else -> check = 0
    */
    if(check)
    {
        cout << "The user input nothing\n";
        return -1;
    }
    //else if user input something, print ignore $0
    for(int i = 1; i < argc; i++)
    {
        cout << setw(2) << i << ". " << argv[i] << '\n';
    }
    // int number;
    //  while (true) {
    //     cout << "Nhap stt trong menu: ";
    //     cin >> number;

    //     // Check if the number is valid
    //     if (cin.fail() || number < 1 || number >= argc) {
    //         cin.clear(); // Reset cin status
    //         cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the remaining characters
    //         cout << "Nhap lai so hop le tu 1 - " << argc - 1 << ".\n";
    //     } else {
    //         break; // Exit the loop when entered correctly
    //     }
    // }
    // cout << argv[number] << endl;

    // return number;
}



// run bash terminal
// cd build
// g++ -o order order.cpp
// ./order 

































































