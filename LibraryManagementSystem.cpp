#include <iostream>
#include<vector>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;

class Library;
class User;

class Books {
    string title,author,genre;
    int ISBN;
    bool avail_status;
    bool Load_flag;
    public: 
        Books(bool f) : Load_flag(f) {} 
        Books() {
            getdata();
            avail_status = 1;
            Storedata();
        }
        void getdata() {
            cout << "Enter Title: " << endl;
            cin.ignore();
            getline(cin,title);
            cout << "Enter Author: " << endl;
            cin.ignore();
            getline(cin,author);
            cout << "Enter Genre: " << endl;
            cin >> genre;
            cout << "Enter ISBN: " << endl;
            cin >> ISBN;   
        }
        void Storedata() {
            ofstream outfile("BookData.txt",ios::out | ios::app);
            if(outfile.is_open()) {
                outfile << "ISBN: " << ISBN << endl;
                outfile << "title: " << title << endl;
                outfile << "author: " << author << endl;
                outfile << "genre: " << genre << endl;
                outfile << "avail_status: " << avail_status << endl;
                outfile << ";" << endl;
            }
            else {
                cerr  << "Error Opening File...";
            }
            outfile.close();
        }
        void Checkout() {
            avail_status = 0;
        }
        void Return() {
            avail_status = 1;
        }    
        void Displaybook() {
            cout << setw(7) << left << ISBN << setw(20) << left<< title << setw(20) << left <<  author << setw(10) << left << genre;
            if(avail_status == 1) {
                cout << setw(15) << left << "Available";
            }
            else {
                cout << setw(15) << left << "Unavailable";
            }
        }
        friend class Library;
};

class Library {
    vector<Books> b;
    public: 
        void AddBook() {
            Books obb;
            b.push_back(obb);
        }
        void DisplayBooks() {
            for(Books obb : b) {
                obb.Displaybook();
            }
        }
        void LoadBooks() {
            ifstream infile("BookData.txt",ios::in);
            if(infile.is_open()) {
                string line;
                Breakout:
                    Books obj(1);
                    while(getline(infile,line)) {
                        if(line == ";") {
                            b.push_back(obj);
                            goto Breakout;
                        }
                        size_t Colon_pos = line.find(":");
                        if(Colon_pos != string::npos) {
                            string key = line.substr(0,Colon_pos);
                            if(key == "ISBN") {
                                string t_ISBN = line.substr(Colon_pos + 2);
                                obj.ISBN = stoi(t_ISBN);
                            }
                            else if(key == "title") {
                                string t_title = line.substr(Colon_pos + 2);
                                obj.title = t_title;
                            }
                            else if(key == "author") {
                                string t_author = line.substr(Colon_pos + 2);
                                obj.author = t_author;
                            }
                            else if(key == "genre") {
                                string t_genre = line.substr(Colon_pos + 2);
                                obj.genre = t_genre;
                            }
                            else if(key == "avail_status") {
                                string t_avail_status = line.substr(Colon_pos + 2);
                                obj.avail_status = stoi(t_avail_status);
                            }
                        }
                }
            }
            else {
                cout << "Book Database File Corrupted";
            }
            infile.close();
        }
};

int main() {
    Library l;
    l.LoadBooks();
    l.DisplayBooks();
}