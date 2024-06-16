#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <sstream>

using namespace std;

/*convert string to int*/
int stringToInt(string s) {
    istringstream iss(s);
    int num;
    iss >> num;
    return num;
}
/*check for leap year*/
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
/*count days between date1 and date2*/
int durationInDays(string& date1, string& date2) {
    int day1 = stringToInt(date1.substr(0, 2));
    int month1 = stringToInt(date1.substr(3, 2));
    int year1 = stringToInt(date1.substr(6, 4));

    int day2 = stringToInt(date2.substr(0, 2));
    int month2 = stringToInt(date2.substr(3, 2));
    int year2 = stringToInt(date2.substr(6, 4));

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (isLeapYear(year1)) daysInMonth[2] = 29;
    else daysInMonth[2] = 28;

    int days1 = day1;
    for (int i = 1; i < month1; ++i){
        days1 += daysInMonth[i];
    }

    if (isLeapYear(year2)) daysInMonth[2] = 29;
    else daysInMonth[2] = 28;

    int days2 = day2;
    for (int i = 1; i < month2; ++i){
        days2 += daysInMonth[i];
    }

    int totalDays1 = year1 * 365 + (year1 / 4) - (year1 / 100) + (year1 / 400) + days1;
    int totalDays2 = year2 * 365 + (year2 / 4) - (year2 / 100) + (year2 / 400) + days2;

    return totalDays2 - totalDays1 + 1;
}

class User {
protected:
    string userId;
    string userName;

public:
    User(string _userId, string _userName) : userId(_userId), userName(_userName) {}

    /*pure virtual function, making user class an abstract class*/
    virtual double calculateFine(string issuedDate, string returnDate) = 0;

    string getUserId(){
        return userId;
    }
    string getUserName(){
        return userName;
    }
};

class Student : public User {
public:
    Student(string _userId, string _userName) : User(_userId, _userName) {}
    /*overriding calculateFine funtion*/
    double calculateFine(string issuedDate, string returnDate){
        
        int bookBorrowedDuration = durationInDays(issuedDate, returnDate);
        
        cout << "Book borrowed duration in days : " << bookBorrowedDuration << "\n";

        if(bookBorrowedDuration <= 5){
            cout << "Overdue days : " << 0 <<"\n";
            return 0;
        }
        else{
            cout << "Overdue days : " << bookBorrowedDuration - 5 <<"\n";
            return (bookBorrowedDuration - 5) * 1; 
        }
    }
};

class Teacher : public User {
public:
    Teacher(string id, string n) : User(id, n) {}
    /*overriding calculateFine funtion*/
    double calculateFine(string issuedDate, string returnDate){
        
        int bookBorrowedDuration = durationInDays(issuedDate, returnDate);

        cout << "Book borrowed duration in days : " << bookBorrowedDuration << "\n";

        if(bookBorrowedDuration <= 5){
            cout << "Overdue days : " << 0 <<"\n";
            return 0;
        }
        else{
            cout << "Overdue days : " << bookBorrowedDuration - 5 <<"\n";
            return (bookBorrowedDuration - 5) * 0.5; 
        }
    }
};

#endif 
