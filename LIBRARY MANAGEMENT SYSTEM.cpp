#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;


class Book {
public:
    int id;
    string title;
    string author;
    bool available; // true if available, false if issued
    
    
    Book(int id, string title, string author) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->available = true; // by default, book is available
    }
};

// Library class definition
class Library {
private:
    vector<Book> books; 
    
public:
    // Function to add a new book
    void addBook(int id, string title, string author) {
        Book newBook(id, title, author);
        books.push_back(newBook);
    }
    
    // Function to search for a book by title
    Book* searchByTitle(string title) {
        for (auto& book : books) {
            if (book.title == title) {
                return &book;
            }
        }
        return nullptr; // Book not found
    }
    
    // Function to search for a book by ID
    Book* searchById(int id) {
        for (auto& book : books) {
            if (book.id == id) {
                return &book;
            }
        }
        return nullptr; 
    }
    
    // Function to issue a book
    void issueBook(int id) {
        for (auto& book : books) {
            if (book.id == id) {
                if (book.available) {
                    book.available = false;
                    return;
                } else {
                    cout << "Book is already issued." << endl;
                    return;
                }
            }
        }
        cout << "Book not found." << endl;
    }
    
    // Function to return a book
    void returnBook(int id) {
        for (auto& book : books) {
            if (book.id == id) {
                if (!book.available) {
                    book.available = true; 
                    return;
                } else {
                    cout << "Book is already available." << endl;
                    return;
                }
            }
        }
        cout << "Book not found." << endl;
    }
    
    // Function to list all books (sorted by ID)
    void listBooks() {
        // Sort books by ID
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.id < b.id;
        });
        
        // Print sorted books
        cout << "List of Books:" << endl;
        for (const auto& book : books) {
            cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author;
            if (book.available) {
                cout << " [Available]" << endl;
            } else {
                cout << " [Issued]" << endl;
            }
        }
    }
    
    // Function to delete a book
    void deleteBook(int id) {
        auto it = find_if(books.begin(), books.end(), [id](const Book& book) {
            return book.id == id;
        });
        
        if (it != books.end()) {
            books.erase(it); // Remove the book
            cout << "Book deleted successfully." << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }
};


int main() {
    cout << "======================== WELCOME TO SIMPLE LIBRARY MANAGEMENT SYSTEM ===========================" << endl;
    Library library;

    // Adding some books
    library.addBook(101, "The Catcher in the Rye", "J.D. Salinger");
    library.addBook(102, "To Kill a Mockingbird", "Harper Lee");
    library.addBook(103, "1984", "George Orwell");
    library.addBook(104, "Pride and Prejudice", "Jane Austen");
    library.addBook(105, "The Great Gatsby", "F. Scott Fitzgerald");

    char choice;
    do {
        int operation;
        cout << "\nChoose an operation:" << endl;
        cout << "1. Search by ID" << endl;
        cout << "2. Issue a book" << endl;
        cout << "3. Return a book" << endl;
        cout << "4. List all books" << endl;
        cout << "5. Delete a book" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice (1-6): ";
        cin >> operation;

        switch (operation) {
            case 1: {
                int id;
                cout << "Enter the ID of the book you want to search: ";
                cin >> id;
                Book* foundBook = library.searchById(id);
                if (foundBook) {
                    cout << "Book found: " << foundBook->title << " by " << foundBook->author << endl;
                } else {
                    cout << "Book not found." << endl;
                }
                break;
            }
            case 2: {
                int id;
                cout << "Enter the ID of the book you want to issue: ";
                cin >> id;
                library.issueBook(id);
                break;
            }
            case 3: {
                int id;
                cout << "Enter the ID of the book you want to return: ";
                cin >> id;
                library.returnBook(id);
                break;
            }
            case 4:
                library.listBooks();
                break;
            case 5: {
                int id;
                cout << "Enter the ID of the book you want to delete: ";
                cin >> id;
                library.deleteBook(id);
                break;
            }
            case 6:
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
        }

        cout << "Do you want to perform another operation? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}

