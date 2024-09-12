#include <iostream>

using namespace std;
class Customer{
private:
    string customerId;
    string customerName;
    string email; 
    string address;

public:
    void addtoCart(){

    }

};

class Product{
private:
    string productId; 
    string name;
    string description;
    float price;

public:
    void updateStock(int quantity){

    }

    string getDetail(){
        return "Product Detail";
    }
};
class Order{
    private:
    string orderId;
    string orderDate;
    string orderStatus;
    public:

    Product product; 

    void placeOrder(){

    }
    void cancelOrder(){

    }
};

class ShoppingCart{
    private:
    string cartId;

};
int main(){

}