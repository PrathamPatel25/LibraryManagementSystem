#ifndef BOOK_HPP
#define BOOK_HPP

#include <string>

using namespace std;

class Book {
private:
    string title;
    string authorName;
    string isbn;
    int quantity;

public:
    Book(string _title, string _authorName, string _isbn, int _quantity) : title(_title), authorName(_authorName), isbn(_isbn), quantity(_quantity) {}

    string getTitle(){ 
        return title; 
    }
    string getAuthorName(){
        return authorName;
    }
    string getIsbn(){
        return isbn;
    }
    int getQuantity(){
        return quantity;
    }

    void setQuantity(int _quantity){ 
        quantity = _quantity;
    }
};

#endif