#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <vector>
#include <map>
#include <algorithm>

#include "Book.hpp"
#include "User.hpp"

using namespace std;

class Library {
private:
    vector<Book*> availableBooks;
    vector<User*> registeredUsers;
    map<string, vector<pair<string, string> > > issuedBooks;
    /* {userId, {{isbn, issuedDate}}} */

public:
    ~Library() {
        for (auto& book : availableBooks) {
            delete book;
        }
        for (auto& user : registeredUsers) {
            delete user;
        }
    }

    void addBook(string _title, string _authorName, string _isbn, int _quantity) {
        
        /*Check if book is already available or not, if available then just add quantity*/
        for(auto& it: availableBooks){
            string isbn = it->getIsbn();
            if(isbn == _isbn){
                if(it->getTitle() == _title && it->getAuthorName() == _authorName){
                    it->setQuantity(it->getQuantity() + _quantity);
                }
                else{
                    cout<< "Book already available with different title or/and author name, please check.\n";
                }
                return;
            }
        }
        /*If book not available, then add new book*/
        Book* book = new Book(_title, _authorName, _isbn, _quantity);
        availableBooks.push_back(book);
    }

    void addUser(string _userId, string _userName, string userType) {
        
        /*Check if user exists or user ID allocated or not*/
        for(auto it: registeredUsers){
            string userId = it->getUserId();
            if(userId == _userId){
                if(it->getUserName() == _userName){
                    cout << "User with this ID and name already exists please check.\n";
                }
                else{
                    cout << "User ID allocated please check.\n";
                }
                return;
            }
        }
        /*If user not available, then add new user*/
        User* user;
        if(userType == "student"){
            user = new Student(_userId, _userName);
        }
        if(userType == "teacher"){
            user = new Teacher(_userId, _userName);
        }
        registeredUsers.push_back(user);
    }

    void removeUser(string& _userId, string& returnDate) {
        User* user = findUserById(_userId);

        if (user == NULL) {
            cout << "User not found." << "\n";
            return;
        }

        /*If user borrow one or more book, then collect it first*/
        if(issuedBooks.find(_userId) != issuedBooks.end()){
            cout<< "\nBooks Collected before removing.\n";

            auto& isbnAndIssuedDate = issuedBooks[_userId];

            for (auto it = isbnAndIssuedDate.begin(); it != isbnAndIssuedDate.end(); it++) {
                string isbn = it->first;
                string issuedDate = it->second;
                Book* book = findBookByIsbn(isbn);
                book->setQuantity(book->getQuantity() + 1);
                cout << "Book '" << book->getTitle() << "' returned by " << user->getUserName() << ".\n";
                double fine = user->calculateFine(issuedDate, returnDate);
                cout << "Fine: $" << fine << "\n\n";
            }
            /*remove user from issued book list*/
            issuedBooks.erase(_userId);
        }

        registeredUsers.erase(remove(registeredUsers.begin(), registeredUsers.end(), user), registeredUsers.end());
        cout << "User '" << user->getUserName() << "' has been removed from the library." << "\n";
        delete user;
    }

    void issueBook(string& _userId, string& _isbn, string& issuedDate) {
        User* user = findUserById(_userId);
        if (user == NULL) {
            cout << "User not found." << "\n";
            return;
        }
        Book* book = findBookByIsbn(_isbn);
        if (book == NULL) {
            cout << "Book not found." << "\n";
            return;
        }

        if (book->getQuantity() > 0) {
            book->setQuantity(book->getQuantity() - 1);
            issuedBooks[_userId].push_back({_isbn, issuedDate});
            cout << "Book '" << book->getTitle() << "' issued to " << user->getUserName() << "\n";
        } 
        else {
            cout << "Insufficient book stock." << "\n";
        }
    }

    void returnBook(string& _userId, string& _isbn, string& returnDate) {
        User* user = findUserById(_userId);
        if (user == NULL) {
            cout << "User not found." << "\n";
            return;
        }
        Book* book = findBookByIsbn(_isbn);
        if (book == NULL) {
            cout << "Book not found." << "\n";
            return;
        }

        string issuedDate;
        auto& isbnAndIssuedDate = issuedBooks[_userId];

        /*remove entry for returned book from issued book list*/
        for (auto it = isbnAndIssuedDate.begin(); it != isbnAndIssuedDate.end(); it++) {
            if (it->first == _isbn) {
                issuedDate = it->second;
                isbnAndIssuedDate.erase(it);
                break;
            }
        }
        /*remove user from issued book list if all books are collected from user*/
        if(issuedBooks[_userId].empty()){
            issuedBooks.erase(_userId);
        }
        
        cout << "Book '" << book->getTitle() << "' returned by " << user->getUserName() << ".\n";
        book->setQuantity(book->getQuantity() + 1);
        double fine = user->calculateFine(issuedDate, returnDate);
        cout << "Fine: $" << fine << "\n\n";
    }

    void listAvailableBooks(){
        cout << "-------------------------- Available Books --------------------------\n";
        for (auto& book : availableBooks) {
            cout << "Title: " << book->getTitle() << "\nAuthor: " << book->getAuthorName() << "\nISBN: " << book->getIsbn() << "\nQuantity: " << book->getQuantity() << "\n\n";
        }
    }

    void listIssuedBooks(){
        cout << "\n-------------------------- Issued Books --------------------------\n";
        for (auto& pair : issuedBooks) {
            User* user = findUserById(pair.first);
            cout << "User: " << user->getUserName() << "\n";
            for (auto& itr : pair.second) {
                Book* book = findBookByIsbn(itr.first);
                cout << "Book: " << book->getTitle() << "\nIssuedDate: " << itr.second << "\n";
            }
            cout << "\n";
        }
    }

    void listRegisteredUsers(){
        cout << "\n-------------------------- Registered Users --------------------------\n";
        for (auto& user : registeredUsers) {
            cout << "User ID: " << user->getUserId() << "\nUser Name: " << user->getUserName() << "\n\n";
        }
    }

private:
    User* findUserById(string _userId){
        for (auto& user : registeredUsers) {
            if (user->getUserId() == _userId) {
                return user;
            }
        }
        return NULL;
    }

    Book* findBookByIsbn(string& isbn){
        for (auto& book : availableBooks) {
            if (book->getIsbn() == isbn) {
                return book;
            }
        }
        return NULL;
    }
};

#endif 
