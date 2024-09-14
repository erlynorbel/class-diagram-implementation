#include <iostream>
#include <string>
#include <iomanip>  // Added for tabular formatting

using namespace std;

const int MAX_PRODUCTS = 100;
const int MAX_CART_ITEMS = 100;
const int MAX_ORDERS = 100;

class Product {
private:
    // Product details
    string productId;
    string name;
    string description;
    float price;
    int stock;

public:
    // Default constructor to create an empty product
    Product() : productId(""), name(""), description(""), price(0.0), stock(0) {}

    // Constructor to create a product with the given details
    Product(const string& productId, const string& name, const string& description, float price, int stock)
        : productId(productId), name(name), description(description), price(price), stock(stock) {}

    string getProductId() const { return productId; }
    string getName() const { return name; }
    string getDescription() const { return description; }
    float getPrice() const { return price; }
    int getStock() const { return stock; }

  // Update the stock quantity of the product  
    void updateStock(int quantity) {
        if (stock >= quantity) {
            stock -= quantity;
        } else {
            cout << "Not enough stock available." << endl;
        }
    }

    // Get a detailed description of the product
    string getDetail() const {
        return "ID: " + productId + ", Name: " + name + ", Price: $" + to_string(price) + ", Stock: " + to_string(stock);
    }
};

class ShoppingCart {
private:
// Shopping cart details
    string cartId;
    Product cartItems[MAX_CART_ITEMS];
    int quantities[MAX_CART_ITEMS];
    int itemCount;

public:
// Default constructor to create an empty shopping cart
    ShoppingCart() : cartId(""), itemCount(0) {}

// Constructor to create a shopping cart with the given cart ID
    ShoppingCart(const string& cartId) : cartId(cartId), itemCount(0) {}

// Add a product to the shopping cart with the given quantity
    void addToCart(Product& product, int quantity) {
        if (itemCount < MAX_CART_ITEMS) {
            cartItems[itemCount] = product;
            quantities[itemCount] = quantity;
            itemCount++;
            cout << "Added " << quantity << " of " << product.getName() << " to the cart." << endl;
            product.updateStock(quantity);
        } else {
            cout << "Cart is full. Cannot add more items." << endl;
        }
    }
    // View the contents of the shopping cart
    void viewCart() const {
        if (itemCount == 0) {
            cout << "Your shopping cart is empty!" << endl;
            return;
        }

        cout << "Shopping Cart Contents:" << endl;
        for (int i = 0; i < itemCount; ++i) {
            cout << cartItems[i].getDetail() << ", Quantity: " << quantities[i] << endl;
        }
    }
  // Clear the shopping cart  
    void clearCart() {
        itemCount = 0;
        cout << "Shopping cart cleared." << endl;
    }
    
// Getters for shopping cart items and quantities
    Product* getCartItems() { return cartItems; }
    int* getQuantities() { return quantities; }
    int getItemCount() const { return itemCount; }
};

class Order {
private:
    // Order details
    string orderId;
    string orderDate;
    string orderStatus;
    float totalAmount;
    Product orderedProducts[MAX_CART_ITEMS];
    int quantities[MAX_CART_ITEMS];
    int orderItemCount;

public:
    // Default constructor to create an empty order
    Order() : orderId(""), orderDate(""), orderStatus(""), totalAmount(0.0), orderItemCount(0) {}

    // Constructor to create an order with the given order ID, date, status, and total amount
    Order(const string& orderId, const string& orderDate, const string& orderStatus, float totalAmount)
        : orderId(orderId), orderDate(orderDate), orderStatus(orderStatus), totalAmount(totalAmount), orderItemCount(0) {}

    // Place an order with the items from the given shopping cart
    void placeOrder(ShoppingCart& cart) {
        orderItemCount = cart.getItemCount();
        for (int i = 0; i < orderItemCount; ++i) {
            orderedProducts[i] = cart.getCartItems()[i];
            quantities[i] = cart.getQuantities()[i];
            totalAmount += orderedProducts[i].getPrice() * quantities[i];
        }
        orderStatus = "Placed";
        cout << "Order placed successfully! Order ID: " << orderId << ", Total Amount: $" << totalAmount << endl;
    }

    // Cancel the order
    void cancelOrder() {
        orderItemCount = 0;
        orderStatus = "Cancelled";
        cout << "Order " << orderId << " has been cancelled." << endl;
    }

    // View the details of the order
    void viewOrderDetails() const {
        cout << "\nOrder ID: " << orderId << ", Date: " << orderDate << ", Status: " << orderStatus << ", Total Amount: $" << totalAmount << endl;
        
        // Print table header
        cout << left << setw(10) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        cout << "----------------------------------------------------------" << endl;

        for (int i = 0; i < orderItemCount; ++i) {
            cout << left << setw(10) << orderedProducts[i].getProductId()
                 << setw(20) << orderedProducts[i].getName()
                 << setw(10) << orderedProducts[i].getPrice()
                 << setw(10) << quantities[i] << endl;
        }
    }
};

class Customer {
private:
// Customer details
    string customerId;
    string customerName;
    string email;
    string address;
    ShoppingCart cart;
    Order orderHistory[MAX_ORDERS];
    int orderCount;

public:
// Constructor to create a customer with the given details
    Customer(const string& customerId, const string& name, const string& email, const string& address)
        : customerId(customerId), customerName(name), email(email), address(address), cart("CART_" + customerId), orderCount(0) {}

// Add a product to the shopping cart with the given quantity
    void addToCart(Product& product, int quantity) {
        cart.addToCart(product, quantity);
    }

// View the contents of the shopping cart
    void viewCart() const {
        cart.viewCart();
    }

// Place an order with the items in the shopping cart
    void placeOrder() {
        if (cart.getItemCount() == 0) {
            cout << "Cart is empty, cannot place an order." << endl;
            return;
        }
// Create a new order with the items in the cart
        string orderId = "ORD_" + to_string(orderCount + 1);
        Order newOrder(orderId, "2024-09-14", "Placed", 0.0);
        newOrder.placeOrder(cart);
        orderHistory[orderCount++] = newOrder;
        cart.clearCart();
    }

// View the order history of the customer
    void viewOrderHistory() const {
        if (orderCount == 0) {
            cout << "No orders have been placed yet." << endl;
            return;
        }
// Print order details for each order in the history
        for (int i = 0; i < orderCount; ++i) {
            orderHistory[i].viewOrderDetails();
        }
    }
};

void displayMenu() {
    // Display the main menu options
    cout << "\n--- SAVEWAY ---\n";
    cout << "1. View Products\n";
    cout << "2. Add Product to Cart\n";
    cout << "3. View Shopping Cart\n";
    cout << "4. Place Order\n";
    cout << "5. View Order History\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    // Create sample products
    Product products[MAX_PRODUCTS] = {
        Product("P001", "Laptop", "High-performance laptop", 1200.0, 10),
        Product("P002", "Smartphone", "Latest smartphone model", 800.0, 20),
        Product("P003", "Headphones", "Noise-cancelling headphones", 150.0, 30),
        Product("P004", "Tablet", "10-inch tablet", 400.0, 15),
        Product("P005", "Smartwatch", "Fitness smartwatch", 250.0, 25),
        Product("P006", "Wireless Earbuds", "Bluetooth earbuds", 100.0, 40),
        Product("P007", "Monitor", "27-inch 4K monitor", 300.0, 5),
        Product("P008", "Keyboard", "Mechanical gaming keyboard", 80.0, 10),
        Product("P009", "Mouse", "Wireless mouse", 40.0, 20),
        Product("P010", "External Hard Drive", "1TB USB 3.0 hard drive", 60.0, 10)
    };
    int productCount = 3;

    // Create a customer
    Customer customer("C001", "John Doe", "john@example.com", "123 Street, City");


    bool user = true;

    // Main menu loop
    while (user) {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {  // View Products
                cout << "\nAvailable Products:\n";
                for (int i = 0; i < productCount; ++i) {
                    cout << products[i].getDetail() << endl;
                }
                break;
            }
            case 2: {  // Add Product to Cart
                string productId;
                int quantity;
                cout << "\nEnter the Product ID to add to cart: ";
                cin >> productId;
                cout << "Enter the quantity: ";
                cin >> quantity;

                // Convert productId to uppercase
                for (char& c : productId) {
                    c = toupper(c);
                }

                bool found = false;
                for (int i = 0; i < productCount; ++i) {
                    if (products[i].getProductId() == productId) {
                        customer.addToCart(products[i], quantity);
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Product not found!" << endl;
                }
                break;
            }
            case 3: {  // View Shopping Cart
                customer.viewCart();
                break;
            }
                        case 4: {  // Place Order
                customer.placeOrder();
                break;
            }
            case 5: {  // View Order History
                customer.viewOrderHistory();
                break;
            }
            case 6: {  // Exit
                cout << "Exiting program. Goodbye!" << endl;
                delete[] products;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
