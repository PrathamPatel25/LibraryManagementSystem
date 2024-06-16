#include <iostream>
#include <string>
#include "Book.hpp"
#include "User.hpp"
#include "Library.hpp"

using namespace std;

int main() {
    Library library;
    string loginType;
    int loginChoice, option;
    
    /*Dummy Data Added*/
    library.addBook("Mathematics", "James Stewart", "1", 5); 
    library.addBook("Physics", "Raymond A. Serway", "2", 5); 
    library.addBook("Chemistry", "Theodore E. Brown", "3", 5); 
    library.addBook("Biology", "Neil A. Campbell", "4", 5); 
    library.addBook("Introduction to Algorithms", "Thomas H. Cormen", "5", 5);

    /*Dummy Data Added*/
    library.addUser("1", "Alice", "student");
    library.addUser("2", "Bob", "student");
    library.addUser("3", "Charlie", "student");
    library.addUser("4", "Eve", "teacher");
    library.addUser("5", "Diana", "teacher");

    /*Display Data for User*/
    cout << "Dummy data already added";
    library.listRegisteredUsers();
    library.listAvailableBooks();

    while (true) {

        cout << "\n-------------------------- Our Library --------------------------\n\n";
        cout << "1. Log in\n";
        cout << "2. Exit\n";
        cout << "Enter option : ";
        cin >> loginChoice;

        switch (loginChoice) {
            case 1:
                cout << "Are you logging in as admin or user (Please type 'admin' or 'user') ? : ";
                cin >> loginType;
                break;
            case 2:
                return 0;
        }

        if (loginType == "admin") {
            do {
                cout << "\n-------------------------- Admin options --------------------------\n\n";
                cout << "1. Add Book\n";
                cout << "2. Add User\n";
                cout << "3. Remove User\n";
                cout << "4. Display Available Books\n";
                cout << "5. Display Registered Users\n";
                cout << "6. Display Issued Books\n";
                cout << "7. Log out\n";
                cout << "Enter your option: ";
                cin >> option;

                switch (option) {
                    case 1: {
                        string title, authorName, isbn;
                        int quantity;
                        cout << "Enter book title: ";
                        cin.ignore();
                        getline(cin, title);
                        cout << "Enter book author name: ";
                        getline(cin, authorName);
                        cout << "Enter book ISBN: ";
                        getline(cin, isbn);
                        cout << "Enter book quantity: ";
                        cin >> quantity;
                        library.addBook(title, authorName, isbn, quantity);
                        break;
                    }
                    case 2: {
                        string userName, userId, userType;
                        cout << "Enter user name: ";
                        cin.ignore();
                        getline(cin, userName);
                        cout << "Enter user ID: ";
                        getline(cin, userId);
                        cout << "Enter user type student or teacher (Please type 'student' or 'teacher'): ";
                        getline(cin, userType);
                        if (userType == "student") {
                            library.addUser(userId, userName, userType);
                        } 
                        else if (userType == "teacher") {
                            library.addUser(userId, userName, userType);
                        } 
                        else {
                            cout << "Invalid user type!" << "\n";
                        }
                        break;
                    }
                    case 3: {
                        string userId, removeDate;
                        cout << "Enter user ID: ";
                        cin.ignore();
                        getline(cin, userId);
                        cout << "Enter remove date(dd/mm/yyyy): ";
                        getline(cin, removeDate);
                        library.removeUser(userId, removeDate);
                        break;
                    }
                    case 4: {
                        library.listAvailableBooks();
                        break;
                    }
                    case 5: {
                        library.listRegisteredUsers();
                        break;
                    }
                    case 6: {
                        library.listIssuedBooks();
                        break;
                    }
                    case 7: {
                        cout << "Successfully log out.\n" << "\n";
                        break;
                    }
                    default: {
                        cout << "Invalid choice! Please enter a number between 1 and 6." << "\n";
                        break;
                    }
                }
            } while (option != 7);
        }
        else if (loginType == "user") {
            do {
                cout << "\n-------------------------- User options --------------------------\n\n";
                cout << "1. Issue Book\n";
                cout << "First 5 days without fine, after that $1/day fine for student and $0.5/1day fine for teacher\n";
                cout << "2. Return Book\n";
                cout << "3. Display Books\n";
                cout << "4. log out\n";
                cout << "Enter your choice: ";
                cin >> option;

                switch (option) {
                    case 1: {
                        string userId, isbn, issuedDate;
                        cout << "Enter user ID: ";
                        cin.ignore();
                        getline(cin, userId);
                        cout << "Enter book ISBN: ";
                        getline(cin, isbn);
                        cout << "Enter Issued Date(dd/mm/yyyy): ";
                        getline(cin, issuedDate);
                        library.issueBook(userId, isbn, issuedDate);
                        break;
                    }
                    case 2: {
                        string userId, isbn, returnDate;
                        int daysOverdue;
                        cout << "Enter user ID: ";
                        cin.ignore();
                        getline(cin, userId);
                        cout << "Enter book ISBN: ";
                        getline(cin, isbn);
                        cout << "Enter return date(dd/mm/yyyy): ";
                        getline(cin, returnDate);
                        library.returnBook(userId, isbn, returnDate);
                        break;
                    }
                    case 3: {
                        library.listAvailableBooks();
                        break;
                    }
                    case 4: {
                        cout << "Successfully log out.\n" << "\n";
                        break;
                    }
                    default: {
                        cout << "Invalid choice! Please enter a number between 1 and 4." << "\n";
                        break;
                    }
                }
            } while (option != 4);
        } 
        else {
            cout << "\nInvalid login type.\n";
            cout << "Try again.\n\n" ;
        }
    }
    return 0;
}
