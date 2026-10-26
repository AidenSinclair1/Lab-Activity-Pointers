
/*
Name: Aiden Sinclair
Date: October 22, 2026
Purpose: Manage a book inventory using pointers, vectors,
         destructors, and RAII.
Assignment: Pointers and Vectors Lab
*/

#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// Represents a single book.
class Book {
private:
    string title;
    string author;
    double price;

public:
    // Initializes the book's information.
    Book(string bookTitle, string bookAuthor, double bookPrice)
        : title(bookTitle), author(bookAuthor), price(bookPrice) {
    }

    // Displays the book's information.
    void displayInfo() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Price: $" << price << endl;
        cout << "------------------------" << endl;
    }
};

// Manages the dynamically allocated Book objects.
class Inventory {
private:
    vector<Book*> books;

public:
    // Adds a book pointer to the inventory.
    void addBook(Book* bookPtr) {
        if (bookPtr != nullptr) {
            books.push_back(bookPtr);
            cout << "Book added successfully!\n";
        }
    }

    // Displays every book in the inventory.
    void displayAll() const {
        if (books.empty()) {
            cout << "The inventory is empty.\n";
            return;
        }

        cout << "\n--- Book Inventory ---\n";

        for (size_t i = 0; i < books.size(); ++i) {
            cout << "Book #" << i << endl;
            books[i]->displayInfo();
        }
    }

    // Deletes a book before removing its pointer.
    void removeBook(int index) {
        if (index < 0 ||
            static_cast<size_t>(index) >= books.size()) {
            cout << "Invalid book index.\n";
            return;
        }

        delete books[index];
        books.erase(books.begin() + index);

        cout << "Book removed successfully!\n";
    }

    // Frees every remaining dynamically allocated book.
    ~Inventory() {
        for (Book* bookPtr : books) {
            delete bookPtr;
        }

        books.clear();

        cout << "Inventory destroyed. Remaining books cleaned up.\n";
    }
};

int main() {
    // Inventory owns the dynamically allocated Book objects.
    Inventory store;

    int choice = 0;

    do {
        cout << "\n===== Book Inventory Menu =====\n";
        cout << "1. Add New Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Remove Book\n";
        cout << "4. Quit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                string title;
                string author;
                double price;

                cout << "Enter book title: ";
                getline(cin, title);

                cout << "Enter author: ";
                getline(cin, author);

                cout << "Enter price: ";

                if (!(cin >> price) || price < 0) {
                    cout << "Invalid price. Book was not added.\n";
                    cin.clear();
                    cin.ignore(
                        numeric_limits<streamsize>::max(), '\n'
                    );
                    break;
                }

                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );

                // Dynamically allocate a new Book.
                Book* newBook = new Book(title, author, price);

                // Transfer ownership to the Inventory.
                store.addBook(newBook);
                break;
            }

            case 2:
                store.displayAll();
                break;

            case 3: {
                int index;

                cout << "Enter the book index to remove: ";

                if (!(cin >> index)) {
                    cout << "Invalid index.\n";
                    cin.clear();
                    cin.ignore(
                        numeric_limits<streamsize>::max(), '\n'
                    );
                    break;
                }

                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );

                store.removeBook(index);
                break;
            }

            case 4:
                cout << "Exiting the program...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    // store is destroyed automatically when main ends.
    // Its destructor deletes all remaining books.
    return 0;
}

