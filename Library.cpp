#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include "Library.h"
#include "Books.h"

using namespace std;

void Library::AddBook()
{
    Books obb;
    b.push_back(obb);
}

void Library::DisplayBooks()
{
    for (Books obb : b)
    {
        obb.Displaybook();
    }
}

void Library::LoadBooks()
{
    ifstream infile("BookData.txt", ios::in);
    if (infile.is_open())
    {
        string line;
    Breakout:
        Books obj(1);
        while (getline(infile, line))
        {
            if (line == ";")
            {
                b.push_back(obj);
                goto Breakout;
            }
            size_t Colon_pos = line.find(":");
            if (Colon_pos != string::npos)
            {
                string key = line.substr(0, Colon_pos);
                if (key == "ISBN")
                {
                    string t_ISBN = line.substr(Colon_pos + 2);
                    obj.ISBN = stoi(t_ISBN);
                }
                else if (key == "title")
                {
                    string t_title = line.substr(Colon_pos + 2);
                    obj.title = t_title;
                }
                else if (key == "author")
                {
                    string t_author = line.substr(Colon_pos + 2);
                    obj.author = t_author;
                }
                else if (key == "genre")
                {
                    string t_genre = line.substr(Colon_pos + 2);
                    obj.genre = t_genre;
                }
                else if (key == "avail_status")
                {
                    string t_avail_status = line.substr(Colon_pos + 2);
                    obj.avail_status = stoi(t_avail_status);
                }
            }
        }
    }
    else
    {
        cout << "Book Database File Corrupted";
    }
    infile.close();
};