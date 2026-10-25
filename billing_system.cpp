#include <iostream>
#include <fstream>
using namespace std;

class Product {
public:
    int id=1, qty, minStock;
    string name, category;
    float price;
};

class Inventory : public Product {
public:

    void addProduct() {
        ofstream file("products.txt", ios::app);

        ifstream check("products.txt");
        int last_id=0;
        while(check>>id>>name>>category>>price>>qty>>minStock){
            last_id=id;
        }
        id=last_id+1;

        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Category: ";
        cin >> category;
        cout << "Enter Price: ";
        cin >> price;
        cout << "Enter Quantity: ";
        cin >> qty;
        cout << "Enter Minimum Stock: ";
        cin >> minStock;

        file << id << " " << name << " " << category << " " << price << " " << qty << " " << minStock << endl;

        file.close();
        cout << "Product added!\n";
    }

    void showProducts() {
        ifstream file("products.txt");

        cout << "\nID Name Category Price Quantity MinStock\n";

        while (file >> id >> name >> category >> price >> qty >> minStock) {
            cout << id << " " << name << " " << category << " " << price << " " << qty << " " << minStock << endl;
        }

        file.close();
    }

    void addStock() {
        int amount;
        string searchname;
        bool found = false;

        cout << "Enter Product name: ";
        cin >> searchname;
        cout << "Enter quantity to add: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Invalid quantity!\n";
            return;
        }

        ifstream file("products.txt");
        ofstream temp("temp.txt");

        while (file >> id >> name >> category >> price >> qty >> minStock) {
            if (name == searchname) {
                qty += amount;
                found = true;
            }

            temp << id << " " << name << " " << category << " " << price << " " << qty << " " << minStock << endl;
        }

        file.close();
        temp.close();

        if (found) {
            ifstream input("temp.txt");
            ofstream output("products.txt");

            while (input >> id >> name >> category >> price >> qty >> minStock) {
                output << id << " " << name << " " << category << " " << price << " " << qty << " " << minStock << endl;
            }

            input.close();
            output.close();
            cout << "Stock added successfully!\n";
        } else {
            cout << "Product not found!\n";
        }
    }

    void lowStock() {
        ifstream file("products.txt");
        bool found = false;

        while (file >> id >> name >> category >> price >> qty >> minStock) {
            if (qty <= minStock) {
                cout << name << " has low stock! " << "Quantity: " << qty << endl;
                found = true;
            }

        }

        file.close();

        if (!found)
            cout << "All products have sufficient stock.\n";
    }

    void sellProduct() {
        int amount;
        string searchname;
        bool found = false, sold = false;
        float total = 0;

        cout << "Enter Product name: ";
        cin >> searchname;
        cout << "Enter quantity to sell: ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Invalid quantity!\n";
            return;
        }

        ifstream file("products.txt");
        ofstream temp("temp.txt");

        while (file >> id >> name >> category >> price >> qty >> minStock) {
            if (name == searchname) {
                found = true;

                if (amount <= qty) {
                    qty -= amount;
                    total = price * amount;
                    sold = true;
                } else {
                    cout << "Not enough stock!\n";
                }
            }

            temp << id << " " << name << " " << category << " " << price << " " << qty << " " << minStock << endl;
        }

        file.close();
        temp.close();

        if (sold) {
            ifstream input("temp.txt");
            ofstream output("products.txt");

            while (input >> id >> name >> category >> price >> qty >> minStock) {
                output << id << " " << name << " " << category << " " << price << " " << qty << " " << minStock << endl;
            }

            input.close();
            output.close();

            float discount, tax, finalBill;

            cout << "Enter discount percentage: ";
            cin >> discount;

            if (discount < 0 || discount > 100) {
                cout << "Invalid discount!\n";
                return;
            }

            discount = total * discount / 100;
            tax = (total - discount) * 5 / 100;
            finalBill = total - discount + tax;

            cout << "\n----- CUSTOMER BILL -----\n";
            cout << "Product: " << name << endl;
            cout << "Total: Rs. " << total << endl;
            cout << "Discount: Rs. " << discount << endl;
            cout << "Tax (5%): Rs. " << tax << endl;
            cout << "Final Bill: Rs. " << finalBill << endl;

            ofstream receipt("receipts.txt", ios::app);
            receipt << "Product ID: " << searchname
                    << " Quantity: " << amount
                    << " Total: " << finalBill << endl;
            receipt.close();

            ofstream sales("sales.txt", ios::app);
            sales << searchname << " " << amount
                  << " " << total << endl;
            sales.close();

            cout << "Product sold successfully!\n";
        } else if (!found) {
            cout << "Product not found!\n";
        }
    }
     
void salesReport() {
    ifstream file("sales.txt");

    string soldName;
    int amount;
    float price, totalSales = 0;

    while (file >> soldName >> amount >> price) {
        totalSales += price;
    }

    file.close();

    cout << "Total Sales: Rs. " << totalSales << endl;

    ifstream products("products.txt");
    float stockValue = 0;

    while (products >> id >> name >> category >> price >> qty >> minStock) {
        stockValue += price * qty;
    }

    products.close();

    cout << "Inventory Value: Rs. "
         << stockValue << endl;
}

};

int main() {
    Inventory obj;
    int choice;

    do {
        cout << "\n===== INVENTORY SYSTEM =====\n";
        cout << "1. Add Product\n";
        cout << "2. Show Products\n";
        cout << "3. Add Stock\n";
        cout << "4. Sell Product and Print Bill\n";
        cout << "5. Low Stock Warning\n";
        cout << "6. Sales Report\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
            obj.addProduct();
            break;
            case 2: 
            obj.showProducts(); 
            break;
            case 3: 
            obj.addStock(); 
            break;
            case 4: 
            obj.sellProduct(); 
            break;
            case 5: 
            obj.lowStock(); 
            break;
            case 6: 
            obj.salesReport(); 
            break;
            case 7: cout << "Thank you!\n"; 
            break;
            default: cout << "Wrong choice!\n";
        }

    } while (choice != 7);

    return 0;
}
