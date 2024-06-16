# Library Management System

This project implements a Library Management System using Object-Oriented Programming (OOP) in C++. The system includes a `Library` class and a `User` class hierarchy with `Student` and `Teacher` as derived classes.

## Features

- Add books in the library.
- Register and remove users (students and teachers).
- Borrow and return books.
- Display user information and book details.
- Display borrowed books.

## Class Structure

### 1. Library Class 

The `Library` class manages the collection of books and handles the lending process.

#### Members

- `vector<Book*> availableBooks`: A collection of books in the library.
- `vector<User*> registeredUsers`: A collection of users in the library.
- `map<string, vector<pair<string, string> > > issuedBooks`: A map of user IDs to books which user borrowed along with it's issued date.

#### Methods

- `void addBook(book_name, author_name, isbn, quantity)`: Adds a new book to the library.
- `void addUser(user_id, user_name, user_type)`: Registers a new user.
- `void removeUser(user_id, remove_date)`: Remove user entry from library.
- `void issueBook(userID, bookID)`: Lends a book to a user.
- `void returnBook(userID, bookID)`: Returns a borrowed book.
- `void listAvailableBooks()`: Displays all available books in the library.
- `void listRegisteredUsers()`: Displays all registered users.
- `void listIssuedBooks()`: Displays all borrowed books along with user name who borrowed it and issued date.
- `User* findUserById(userId)` : Find user by it's ID.
- `Book* findBookByIsbn(isbn)` : Find book by it's ISBN;

### 2. Book Class

The `Book` class represents a book in the library.

#### Members

- `string title`: Title of the book.
- `string authorName`: The name of the book's author..
- `string isbn`: ISBN number of the book.
- `int quantity`: Available quantity of the book in the library.

#### Methods

- `string getTitle()`: Retrieves the title of the book.
- `string getAuthorName()`: Retrieves the author's name of the book.
- `string getIsbn()`: Retrieves the ISBN number of the book.
- `int getQuantity()`: Retrieves the available quantity of the book.
- `void setQuantity(int quantity)`: Set the quantity of the book.

### 3. User Class

The `User` class is the base class for all users of the library.

#### Members

- `string userId`: The unique ID of the user.
- `string userName`: The name of the user.

#### Methods

- `virtual double calculateFine()`: Calculates the fine for overdue days. This method is virtual to support polymorphism.
- `string getUserId()`: Retrieves the user ID.
- `string getUserName()`: Retrieves the user name.


### 4. Student Class

The `Student` class is derived from the `User` class, representing student users.

#### Methods

- `double calculateFine()`: Calculate $1/day fine for overdue days.

### 5. Teacher Class

The `Teacher` class is derived from the `User` class, representing teacher users.

#### Methods

- `double calculateFine()`: Calculate $0.5/day fine for overdue days.

# Application of OOP Principles

1. **Encapsulation**: 
   - **Definition**: Encapsulation is wrapping up of data and member functions in a single unit called class.
   - **Example**: The `Book` class encapsulate attributes like `title`, `authorName`, and methods like `getTitle()` and `getAuthorName`.

2. **Abstraction**: 
   - **Definition**: Hiding the complex implementation details and showing only the necessary parts to the user.
   - **Example**: The `Library` class provides an abstraction where users can perform actions like issued books and returning books without needing to know the internal details of how these operations are managed.

3. **Inheritance**: 
   - **Definition**: Mechanism where a new class (derived class) is derived from an existing class (base class), inheriting its attributes and methods.
   - **Example**: The `Student` and `Teacher` classes inherit from the `User` class, gaining access to method `calculateFine()`.

4. **Polymorphism**: 
   - **Definition**: Ability of object to take on different forms or behave in different ways depending on the context in which they are used.
   - **Example**: Achieved through function overriding in derived classes. For instance, both `Student` and `Teacher` classes override a virtual method `calculateFine()` defined in the `User` base class. Each derived class can provide its own implementation to calculate different fine for student and teacher.

# Future Enhancements

In the future, we plan to enhance the system with:

- **Database Integration**: Integrate a relational database (e.g., PostgreSQL, MySQL) to store and manage library resources, user data. This integration will ensure data persistence, efficient data retrieval, and scalability as the library grows.


