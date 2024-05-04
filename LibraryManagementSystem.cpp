#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
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

class User {
    string name;
    int tISBN;
        public: 
            void getinfo();
            void StoreUser();
            friend class Library;
};

class Library {
    vector<Books> b;
    vector<User> u;
    public: 
        void AddBook();
        void DisplayBooks();
        void LoadBooks();
        void MainMenu();
        void BookSearch();
        void UserCheckout();
        void UserReturn();
        void LoadUsers();
        std::vector<Books>::iterator ISBNSearch(int tISBN);
};

int main() {
    Library l;
    l.LoadBooks();
    l.LoadUsers();
    l.MainMenu();
    l.DisplayBooks();
}

//Books Member Funcitons

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
    cout << "You Have Checked Out \"" << title  << "\"By " << author << endl;
}

void Books::Return()
{
    avail_status = 1;
    cout << "You Have Returned \"" << title  << "\"By " << author << endl;
}

void Books::Displaybook()
{
    cout << endl << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Genre: " << genre << endl;
    cout << "Availibility: ";
    if(avail_status == 1) {cout << "Available" << endl << endl;}
    else {cout << "Unavailable" << endl << endl;};
};

//Library Member Functions

void Library::MainMenu() {
        char choice;
    do {
        cout << endl << "Welcome To Our Library" << endl;
        cout << "Please Enter Your Choice: " << endl;
        cout << "[S] To Search For Books." << endl;
        cout << "[C] To Checkout A Book." << endl;
        cout << "[R] To Return A Book." << endl;
        cout << "[E] To EXIT The Program..." << endl;
        cin >> choice;
        switch(choice) {
            case 'S':
            case 's': {BookSearch();break;}
            case 'C':
            case 'c': {UserCheckout();break;}
            case 'R':
            case 'r': {UserReturn();break;}
        }
    }
    while(!(choice == 'e' || choice == 'E'));
}
void Library::BookSearch() {
    int schoice;
    char exitchoice;
    cout << "Search By: " << "[1] Title  " << "[2] Author  " << "[3] Genre  " << endl;
    cout << "Press Anything Else To Exit" << endl;
    cin >> schoice;
    switch(schoice) {
        case 1: {
            cout << "Enter Title(Please Follow \"Title Case\" While Typing): " << endl;
            string ftitle;
            cin.ignore();
            getline(cin,ftitle);
            for(Books obb: b) {
                if (obb.title == ftitle) {
                    obb.Displaybook();
                }
            }
            break;
            }
        case 2: {
            cout << "Enter Author(Please Follow \"Title Case\" While Typing): " << endl;
            string fauthor;
            cin.ignore();
            getline(cin,fauthor);
            for(Books obb: b) {
                if(obb.author == fauthor) {
                    obb.Displaybook();
                }
            }
            break;
        }
        case 3: {
            cout << "Enter Genre(Please Follow \"Title Case\" While Typing): " << endl;
            string fgenre;
            cin >> fgenre;
            for(Books obb: b) {
                if(obb.genre == fgenre) {
                    obb.Displaybook();
                }
            }
            break;
        }
        default: {
            cout << "Exiting Search...." << endl;
            break;
        }
        }
    }
 
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
}

void Library::UserCheckout() {
    User tu;
    tu.getinfo();
    cout << "Enter ISBN Of Book To CheckOut: ";
    cin >> tu.tISBN;
    auto CheckoutBook = ISBNSearch(tu.tISBN);
    if(CheckoutBook != b.end()) {
        tu.StoreUser();
        u.push_back(tu);
        CheckoutBook->Checkout();
     }
     else {
        cout << "This ISBN Number Does Not Exist In Database" << endl;
     }
    
}

std::vector<Books>::iterator Library::ISBNSearch(int tISBN) {
            for (auto it = b.begin(); it != b.end();it++) {
            if(it->ISBN == tISBN) {
                return it;
            }
        }
            return b.end();
    }


void Library::UserReturn() {
    string tname;
    bool flag = 0;
    cout << "Enter Your Name:  ";
    cin.ignore();
    getline(cin,tname);
    for (auto it = u.begin(); it != u.end();it++) {
        if(tname == it->name) {
            auto ReturnBook = ISBNSearch(it->tISBN);
            ReturnBook->Return();
            flag = 1;
            u.erase(it);
            break;
        }
    }
    if(flag == 0) {cout << "Name Does Not Exist In Database" << endl;}
}

void User::getinfo() {
    cout << "Enter Name: " << endl;
    cin.ignore();
    getline(cin,name);
}

void User::StoreUser() {
    ofstream outfile("UserData.txt",ios::out | ios::app); 
        if(outfile.is_open()) {
            outfile << "name: " << name << endl;
            outfile << "ISBN: " << tISBN << endl;     
            outfile << ";";       
        }
        else {cerr << "Error Opening User File";}
        outfile.close();
}

void Library::LoadUsers() {
    ifstream infile("UserData.txt",ios::in); 
        if(infile.is_open()) {
            string line;
        Breakaway:    
            User uobj;
            while(getline(infile,line)) {
                if(line == ";") {
                    u.push_back(uobj);
                    goto Breakaway;
                }
                size_t Colon_pos = line.find(":");
                if(Colon_pos != string::npos) {
                    string key = line.substr(0,Colon_pos);
                    if(key == "name") {
                        string fname = line.substr(Colon_pos + 2);
                        uobj.name = fname;
                    }
                    else if(key == "ISBN") {
                        string fISBN = line.substr(Colon_pos + 2);
                        uobj.tISBN = stoi(fISBN);
                    }
                }
            }
        }
        else {cerr << "Error Loading UserData File...";}
}