#include <string>
#include <iostream>
#include <sstream>
#include "sources/OrgChart.cpp"

using namespace std;
using namespace ariel;

int main(){
    OrgChart myOrg;
    int input;
    string tempString;
    string tempString2;
    cout << "Hello welcome to OrgChart" << endl << "in order to add new people to your organization you can use these function" << endl 
            << "(*) To add root enter 1" << endl << "(*) To add sub enter 2" << endl << "(*) To print in level order enter 3" << endl
            << "(*) To print in reverse level order enter 4" << endl << "(*) To print in preorder enter 5" << endl <<"(*) When you done enter 0" << endl;
    std::cin >> input;
    while (input != 0)
    {
        switch (input)
        {
        case 1: // to add or change root
            cout << endl <<"Enter the name of your root: ";
            std::cin >> tempString;
            try{
                myOrg.add_root(tempString);
            }
            catch(const std::exception& e){
                std::cerr << e.what() << '\n';
            }
            cout << endl <<"If you want to add more subs or root use the same input!";
            std::cin >> input;
            break;
        case 2:
            cout << endl <<"Enter the name of your father : ";
            std::cin >> tempString;
            cout << endl << "Enter the name of your sub : ";
            std::cin >> tempString2;
            try{
                myOrg.add_sub(tempString,tempString2);
            }
            catch(const std::exception& e){
                std::cerr << e.what() << '\n';
            }
            cout << endl <<"If you want to add more subs or root use the same input!";
            std::cin >> input;
            break;
        case 3:// for level order print
              for (auto it = myOrg.begin_level_order(); it != myOrg.end_level_order(); ++it){
                cout << (*it) << " " ;
            }
            cout << endl <<"If you want to add more subs or root use the same input!";
            std::cin >> input;
            break;
        case 4:// for reverse level order print
            for (auto it = myOrg.begin_reverse_order(); it != myOrg.reverse_order(); ++it){
                cout << (*it) << " " ;
            }
            cout << endl <<"If you want to add more subs or root use the same input!";
            std::cin >> input;
            break;
        case 5:// for preorder print
            for (auto it=myOrg.begin_preorder(); it!=myOrg.end_preorder(); ++it) {
                cout << (*it) << " " ;
                }
            cout << endl <<"If you want to add more subs or root use the same input!";
            std::cin >> input;
            break;
        case 0://for exit
            cout << "Thank you for using our OrgChart!"<< endl;
            std::cin >> input;
        default:
        cout << "Hello welcome to OrgChart" << endl << "in order to add new people to your organization you can use these function" << endl 
            << "(*) To add root enter 1" << endl << "(*) To add sub enter 2" << endl << "(*) To print in level order enter 3" << endl
            << "(*) To print in reverse level order enter 4" << endl << "(*) To print in preorder enter 5" << endl <<"(*) When you done enter 0" << endl;
            std::cin >> input;
            break;
        }
    }
    
}