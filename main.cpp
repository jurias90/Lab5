/**
Lab #4
    Group CPP2
    Team Memebers: Jesus Urias, Nhung Vo
    Purpose: The purpose of this lab is implement a BST ADT for DrachmaCurrency
**/

#include <iostream>
#include "HashTable.h"
#include "DrachmaCurrency.h"

using namespace std;

int main()
{
    HashTable *table = new HashTable();
    double choice = 0;
    int index = 0;
    table->insert(new DrachmaCurrency(57.12));
    table->insert(new DrachmaCurrency(23.44));
    table->insert(new DrachmaCurrency(87.43));
    table->insert(new DrachmaCurrency(68.99));
    table->insert(new DrachmaCurrency(111.22));
    table->insert(new DrachmaCurrency(44.55));
    table->insert(new DrachmaCurrency(77.77));
    table->insert(new DrachmaCurrency(18.36));
    table->insert(new DrachmaCurrency(345.67));
    table->insert(new DrachmaCurrency(36.18));
    table->insert(new DrachmaCurrency(48.48));
    table->insert(new DrachmaCurrency(101.00));
    table->insert(new DrachmaCurrency(11.00));


    table->print();
    cout << endl;
    cout << "Let's search for  value on the table." << endl;
    cout << "Please enter a value to search in the table (xx.xx format) or -1 to quit: ";
    cin >> choice;
    while (choice != -1) {
        index = table->search(choice);
        if (index != -1) {
            cout << "Value found at index " << index << endl;
        }
        else {
            cout << "Invalid Data" << endl;
        }
        cout << "Please enter a value to search in the table (xx.xx format) or -1 to quit: ";
        cin >> choice;
    }
   }