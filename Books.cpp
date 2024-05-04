#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include "Books.h"
using namespace std;

Books::Books(bool f) : Load_flag(f) {}
Books::Books()
{
    getdata();
    avail_status = 1;
    Storedata();
}

void Books::getdata()
{
    cout << "Enter Title: " << endl;
    cin.ignore();
    getline(cin, title);
    cout << "Enter Author: " << endl;
    cin.ignore();
    getline(cin, author);
    cout << "Enter Genre: " << endl;
    cin >> genre;
    cout << "Enter ISBN: " << endl;
    cin >> ISBN;
}

void Books::Storedata()
{
    ofstream outfile("BookData.txt", ios::out | ios::app);
    if (outfile.is_open())
    {
        outfile << "ISBN: " << ISBN << endl;
        outfile << "title: " << title << endl;
        outfile << "author: " << author << endl;
        outfile << "genre: " << genre << endl;
        outfile << "avail_status: " << avail_status << endl;
        outfile << ";" << endl;
    }
    else
    {
        cerr << "Error Opening File...";
    }
    outfile.close();
}

void Books::Checkout()
{
    avail_status = 0;
}

void Books::Return()
{
    avail_status = 1;
}

void Books::Displaybook()
{
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Genre: " << genre << endl;
    cout << "Availibility: ";
    if(avail_status == 1) {cout << "Available";}
    else {cout << "Unavailable";};
};