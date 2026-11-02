#include "Inventory.h"
#include <iostream>

// Constructor
Inventory::Inventory() : head(nullptr) {}

// Destructor - delete each Book and Node in the linked list.
Inventory::~Inventory() {
    Node* current = head;

    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current->data;
        delete current;
        current = nextNode;
    }

    head = nullptr;
}

// Add a book to the inventory in alphabetical order by title.
void Inventory::addBook(Book* bookPtr) {
    if (bookPtr == nullptr) {
        std::cout << "Error: Cannot add null book pointer.\n";
        return;
    }

    Node* newNode = new Node(bookPtr);

    // Insert at the beginning if the list is empty or this title
    // belongs before the current first title.
    if (head == nullptr || bookPtr->getTitle() < head->data->getTitle()) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;

        // Move past titles that are less than or equal to the new title.
        // This keeps duplicate titles in their original insertion order.
        while (current->next != nullptr &&
               current->next->data->getTitle() <= bookPtr->getTitle()) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    std::cout << "Book '" << bookPtr->getTitle() << "' added to inventory.\n";
}

// Display all books by traversing the linked list.
void Inventory::displayAll() const {
    if (head == nullptr) {
        std::cout << "No books in inventory.\n";
        return;
    }

    std::cout << "\n=== INVENTORY CONTENTS ===\n";
    std::cout << "Total books: " << getBookCount() << "\n\n";

    Node* current = head;
    std::size_t bookNumber = 1;

    while (current != nullptr) {
        std::cout << "Book #" << bookNumber << ":\n";
        current->data->displayInfo();
        current = current->next;
        ++bookNumber;
    }

    std::cout << "\n";
}

// Remove the first book matching the supplied title.
void Inventory::removeBook(const std::string& title) {
    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data->getTitle() == title) {
            std::cout << "Removing book: " << current->data->getTitle() << "\n";

            if (previous == nullptr) {
                head = current->next;
            } else {
                previous->next = current->next;
            }

            delete current->data;
            delete current;
            return;
        }

        previous = current;
        current = current->next;
    }

    std::cout << "Book '" << title << "' not found in inventory.\n";
}

// Count the nodes in the linked list.
std::size_t Inventory::getBookCount() const {
    std::size_t count = 0;
    Node* current = head;

    while (current != nullptr) {
        ++count;
        current = current->next;
    }

    return count;
}

// Return the Book pointer when a matching title is found.
Book* Inventory::findBook(const std::string& title) const {
    Node* current = head;

    while (current != nullptr) {
        if (current->data->getTitle() == title) {
            return current->data;
        }
        current = current->next;
    }

    return nullptr;
}

// Check whether the linked list is empty.
bool Inventory::isEmpty() const {
    return head == nullptr;
}
