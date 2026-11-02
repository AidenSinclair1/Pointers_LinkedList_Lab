#ifndef INVENTORY_H
#define INVENTORY_H

#include "Book.h"
#include <cstddef>
#include <string>

class Inventory {
private:
    // Each node owns one Book and points to the next node.
    struct Node {
        Book* data;
        Node* next;

        explicit Node(Book* bookPtr) : data(bookPtr), next(nullptr) {}
    };

    Node* head;

public:
    // Constructor
    Inventory();

    // Destructor - deletes every Book and its corresponding Node.
    ~Inventory();

    // Prevent shallow copies of the linked-list pointers.
    Inventory(const Inventory& other) = delete;
    Inventory& operator=(const Inventory& other) = delete;

    // Add a book while maintaining alphabetical order by title.
    void addBook(Book* bookPtr);

    // Display all books in the inventory.
    void displayAll() const;

    // Remove the first book matching the supplied title.
    void removeBook(const std::string& title);

    // Get the number of books.
    std::size_t getBookCount() const;

    // Search for a book by title.
    Book* findBook(const std::string& title) const;

    // Check whether the inventory is empty.
    bool isEmpty() const;
};

#endif // INVENTORY_H
