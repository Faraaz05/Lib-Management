#ifndef LIBRARY_H
#define LIBRARY_H

#include<vector>
#include "Books.h"

using namespace std;

class Library {
    vector<Books> b;
    public: 
        void AddBook();
        void DisplayBooks();
        void LoadBooks();
};
#endif