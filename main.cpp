#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

using namespace std;

// Class to represent a book
class Book {
public:
    string ISBN;     // Book ISBN
    string title;    // Book title
    float price;     // Book price

    // Default constructor
    Book() : ISBN(""), title(""), price(0.0f) {}

    // Constructor to initialize a book
    Book(string isbn, string t, float p) : ISBN(isbn), title(t), price(p) {}

    // Print book details
    void print() const {
        cout << "Book: " << title << " | ISBN: " << ISBN << " | Price: $" << price << endl;
    }
};

// Class to represent a customer
class Customer {
public:
    string email;  // Customer email (unique ID)
    string name;   // Customer name
    list<string> orderHistory;  // Linked list to store order history (ISBNs)

    // Default constructor
    Customer() : email(""), name("") {}

    // Constructor to initialize a customer
    Customer(string e, string n) : email(e), name(n) {}

    // Add an order (store ISBN in history)
    void addOrder(const string& bookISBN) {
        orderHistory.push_back(bookISBN);
    }

    // Print customer's order history
    void printOrderHistory() const {
        cout << name << "'s Order History:\n";
        for (const auto& isbn : orderHistory) {
            cout << " - ISBN: " << isbn << endl;
        }
    }
};

// Class to manage the online bookstore
class Bookstore {
private:
    unordered_map<string, Book> books;         // Hash map to store books (ISBN -> Book)
    unordered_map<string, Customer> customers; // Hash map to store customers (email -> Customer)

public:
    // Add a new book to the bookstore
    void addBook(const Book& book) {
        books[book.ISBN] = book;
        cout << "Added book: " << book.title << endl;
    }

    // Add a new customer
    void addCustomer(const Customer& customer) {
        customers[customer.email] = customer;
        cout << "Added customer: " << customer.name << endl;
    }

    // Place an order by customer email and book ISBN
    void placeOrder(const string& email, const string& ISBN) {
        if (customers.find(email) != customers.end() && books.find(ISBN) != books.end()) {
            customers[email].addOrder(ISBN);
            cout << customers[email].name << " placed an order for book with ISBN: " << ISBN << endl;
        } else {
            cout << "Order failed. Customer or Book not found.\n";
        }
    }

    // Show the order history of a customer by email
    void showOrderHistory(const string& email) const {
        if (customers.find(email) != customers.end()) {
            customers.at(email).printOrderHistory();
        } else {
            cout << "Customer not found.\n";
        }
    }

    // Show the details of a book by ISBN
    void showBookDetails(const string& ISBN) const {
        if (books.find(ISBN) != books.end()) {
            books.at(ISBN).print();
        } else {
            cout << "Book not found.\n";
        }
    }
};

// Main function demonstrating the system
int main() {
    Bookstore store;

    // Add books to the store
    store.addBook(Book("978-0131103627", "The C++ Programming Language", 45.99));
    store.addBook(Book("978-0596009205", "Head First Java", 35.50));

    // Add customers
    store.addCustomer(Customer("john.doe@example.com", "John Doe"));
    store.addCustomer(Customer("jane.smith@example.com", "Jane Smith"));

    // Place orders
    store.placeOrder("john.doe@example.com", "978-0131103627");
    store.placeOrder("jane.smith@example.com", "978-0596009205");

    // Show order history for a customer
    store.showOrderHistory("john.doe@example.com");

    // Show book details
    store.showBookDetails("978-0131103627");

    return 0;
}

