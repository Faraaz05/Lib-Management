#ifndef BOOKS_H
#define BOOKS_H
#include<string>
using namespace std;
class Books {
    string title,author,genre;
    int ISBN;
    bool avail_status;
    bool Load_flag;
    public: 
        Books(bool f);
        Books();
        void getdata();
        void Storedata();
        void Checkout();  
        void Return();
        void Displaybook();
        friend class Library;
};
#endif //BOOKS_H