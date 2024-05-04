#include<string>
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
        void Displaybook();
        friend class Library;
};