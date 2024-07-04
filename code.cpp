#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;
    string issuedTo;

    Book(int bookId, string bookTitle, string bookAuthor)
        : id(bookId), title(bookTitle), author(bookAuthor), isIssued(false), issuedTo("") {}
    
    void toggleIssueStatus() {
        isIssued = !isIssued;
    }
};
class Library {
private:
    vector<Book> books;
    unordered_map<int, Book*> issuedBooks;
public:
    Library() {
        addBook(951, "1984", "George Orwell");
        addBook(753, "To Kill a Mockingbird", "Harper Lee");
        addBook(159, "The Great Gatsby", "F. Scott Fitzgerald");
        addBook(357, "Moby Dick", "Herman Melville");
        addBook(761, "Pride and Prejudice", "Jane Austen");
        addBook(913, "War and Peace", "Leo Tolstoy");
        addBook(572, "The Catcher in the Rye", "J.D. Salinger");
        addBook(943, "The Hobbit", "J.R.R. Tolkien");
        addBook(133, "Brave New World", "Aldous Huxley");
        addBook(031, "Jane Eyre", "Charlotte Bronte");
    }
    void addBook(int id, string title, string author) {
        books.push_back(Book(id, title, author));
    }
    Book* searchBookById(int id) {
        for (auto& book : books) {
            if (book.id == id) return &book;
        }
        return nullptr;
    }
    Book* searchBookByTitle(string title) {
        for (auto& book : books) {
            if (book.title == title) return &book;
        }
        return nullptr;
    }
    void issueBook(int id, string studentName) {
        Book* book = searchBookById(id);
        if (book && !book->isIssued) {
            book->toggleIssueStatus();
            book->issuedTo = studentName;
            issuedBooks[id] = book;
            cout << "Book issued to " << studentName << endl;
        } else {
            cout << "Book is not available for issuing" << endl;
        }
    }
    void returnBook(int id) {
        auto it = issuedBooks.find(id);
        if (it != issuedBooks.end()) {
            it->second->toggleIssueStatus();
            it->second->issuedTo = "";
            issuedBooks.erase(it);
            cout << "Book returned successfully" << endl;
        } else {
            cout << "Book was not issued" << endl;
        }
    }
    void listAllBooks() {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.title < b.title; 
        });
        for (const auto& book : books) {
            cout << book.id << " " << book.title << " by " << book.author << " - " 
                 << (book.isIssued ? "Issued to " + book.issuedTo : "Available") << endl;
        }
    }
    void listAvailableBooks() {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.title < b.title; 
        });
        for (const auto& book : books) {
            if (!book.isIssued) {
                cout << book.id << " " << book.title << " by " << book.author << " - Available" << endl;
            }
        }
    }
    void listIssuedBooks() {
        for (const auto& pair : issuedBooks) {
            const Book& book = *pair.second;
            cout << book.id << " " << book.title << " by " << book.author << " - Issued to " << book.issuedTo << endl;
        }
    }
    void deleteBook(int id) {
        books.erase(remove_if(books.begin(), books.end(),
            [id](Book& book) { return book.id == id; }), books.end());
    }
    void showCredits() {
        cout << "\nThis project was made by Shivang Agrawal.\n";
        cout << "Thank you for using the Library Management System.\n";
    }
};
void displayMenu() {
    cout << "Library Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Search Book by ID" << endl;
    cout << "3. Search Book by Title" << endl;
    cout << "4. Issue Book" << endl;
    cout << "5. Return Book" << endl;
    cout << "6. List All Books" << endl;
    cout << "7. Delete Book" << endl;
    cout << "8. Show Credits" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice: ";
}
int main() {
    Library lib;
    int choice, id;
    string title, author, studentName;
    while (true) {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Book Title: ";
                getline(cin, title);
                cout << "Enter Book Author: ";
                getline(cin, author);
                lib.addBook(id, title, author);
                break;
            case 2:
                cout << "Enter Book ID: ";
                cin >> id;
                if (Book* book = lib.searchBookById(id)) {
                    cout << "Book Found: " << book->id << " " << book->title << " by " << book->author
                              << " - " << (book->isIssued ? "Issued to " + book->issuedTo : "Available") << endl;
                } else {
                    cout << "Book not found." << endl;
                }
                break;
            case 3:
                cin.ignore();
                cout << "Enter Book Title: ";
                getline(cin, title);
                if (Book* book = lib.searchBookByTitle(title)) {
                    cout << "Book Found: " << book->id << " " << book->title << " by " << book->author
                              << " - " << (book->isIssued ? "Issued to " + book->issuedTo : "Available") << endl;
                } else {
                    cout << "Book not found." << endl;
                }
                break;
            case 4:
                cout << "Available Books:" << endl;
                lib.listAvailableBooks();
                cout << "Enter Book ID to issue: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Student Name: ";
                getline(cin, studentName);
                lib.issueBook(id, studentName);
                break;
            case 5:
                cout << "Issued Books:" << endl;
                lib.listIssuedBooks();
                cout << "Enter Book ID to return: ";
                cin >> id;
                lib.returnBook(id);
                break;
            case 6:
                lib.listAllBooks();
                break;
            case 7:
                cout << "Enter Book ID to delete: ";
                cin >> id;
                lib.deleteBook(id);
                break;
            case 8:
                lib.showCredits();
                break;
            case 9:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}