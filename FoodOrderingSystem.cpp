#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memo

// OrderPrototype interface
class OrderPrototype {
public:
    virtual std::unique_ptr<OrderPrototype> clone() const = 0;
    virtual ~OrderPrototype() {}
};

// Order class that implements OrderPrototype
class Order : public OrderPrototype {
private:
    int orderId;
    User* customer;
    Restaurant* restaurant;
    Rider* rider;
    std::vector<std::unique_ptr<OrderItem>> items;
    float totalAmount;
    std::string status;

public:
    Order(int orderId, User* customer, Restaurant* restaurant, std::vector<std::unique_ptr<OrderItem>> items, float totalAmount);
    ~Order();  // Destructor to clean up any resources, if necessary

    std::unique_ptr<OrderPrototype> clone() const override;
    void assignRider(Rider* rider);
    void updateStatus(const std::string& newStatus);
    void addItem(std::unique_ptr<OrderItem> item);
    void removeItem(const OrderItem* item);
    
    // ... Other Order methods ...
    // Getters and setters
};

// OrderItem base class
class OrderItem {
protected:
    std::string name;
    float price;
    int ItemID;

public:
    OrderItem(std::string name, float price,int ItemID);
    virtual ~OrderItem();
    virtual std::unique_ptr<OrderItem> clone() const = 0;
    
    // ... Other OrderItem methods ...
    // Getters and setters
};

// Singleton OrderManager class
class OrderManager {
private:
    static OrderManager* instance;
    std::unordered_map<int, std::unique_ptr<Order>> orders;

    OrderManager();

public:
    static OrderManager* getInstance();
    void addOrder(std::unique_ptr<Order> order);
    Order* getOrder(int orderId);

    OrderManager(const OrderManager&) = delete;
    OrderManager& operator=(const OrderManager&) = delete;
    ~OrderManager();

    // ... Other OrderManager methods ...
};

OrderManager* OrderManager::instance = nullptr;

// User class
class User {
private:
    int userId;
    std::string name;
    std::string email;
    std::string address;
    std::vector<Order*> orders;

public:
    User(int userId, std::string name, std::string email, std::string address);
    ~User();
    
    void registerUser();
    void manageInformation();
    void browseMenu(const Restaurant& restaurant);
    void placeOrder(Order* order);
    void trackOrderStatus(int orderId);
    void accessOrderHistory();
    
    // ... Other User methods ...
    // Getters and setters
};

// Restaurant class
class Restaurant {
private:
    int restaurantId;
    std::string name;
    std::string address;
    std::vector<Order*> orders;

public:
    Restaurant(int restaurantId, std::string name, std::string address);
    ~Restaurant();
    
    void registerRestaurant();
    void updateMenu(const std::vector<std::string>& newMenu);  // Here std::string can be changed to a Menu class if needed
    void receiveOrderNotification(Order* order);
    void receivePayment(float amount);
    void offerPromotions();
    
    // ... Other Restaurant methods ...
    // Getters and setters
};

// Rider class
class Rider {
private:
    int riderId;
    std::string name;
    std::string vehicleType;
    std::vector<Order*> assignedOrders;

public:
    Rider(int riderId, std::string name, std::string vehicleType);
    ~Rider();
    
    void registerRider();
    void receiveOrderNotification(Order* order);
    void updateOrderStatus(Order* order, const std::string& newStatus);
    void completeDelivery(Order* order);
    
    // ... Other Rider methods ...
    // Getters and setters
};

// Concrete OrderItem classes like Pizza, Burger would go here...
// They would inherit from OrderItem and implement the clone method.

// Main function or other parts of the application...
// ...

