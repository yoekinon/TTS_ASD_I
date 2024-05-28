#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

struct Product {
    int id;
    string name;
    int quantity;
    double price;
};

class Warehouse {
private:
    vector<Product> products;
    int nextId;

    int findProductIndexById(int id) {
        for (size_t i = 0; i < products.size(); ++i) {
            if (products[i].id == id) {
                return i;
            }
        }
        return -1; // Not found
    }

    void saveProductsToFile() const {
        ofstream file("products.txt");
        if (file.is_open()) {
            for (const auto& product : products) {
                file << product.id << "\n"
                     << product.name << "\n"
                     << product.quantity << "\n"
                     << product.price << "\n";
            }
            file.close();
        } else {
            cout << "Tidak Bisa Membuka File." << endl;
        }
    }

    void loadProductsFromFile() {
        ifstream file("products.txt");
        if (file.is_open()) {
            products.clear();
            int id, quantity;
            string name;
            double price;
            while (file >> id) {
                file.ignore();
                getline(file, name);
                file >> quantity >> price;
                products.push_back({id, name, quantity, price});
                if (id >= nextId) {
                    nextId = id + 1;
                }
            }
            file.close();
        } else {
            cout << "File tidak dapat terbaca" << endl;
        }
    }

public:
    Warehouse() : nextId(1) {
        loadProductsFromFile();
    }

    void addProduct(const string& name, int quantity, double price) {
        Product newProduct = {nextId++, name, quantity, price};
        products.push_back(newProduct);
        saveProductsToFile();
    }

    void readProducts() const {
        for (const auto& product : products) {
            cout << "ID: " << product.id
                 << ", Nama: " << product.name
                 << ", Quantity: " << product.quantity
                 << ", Harga: Rp. " << product.price << endl;
        }
    }

    void updateProduct(int id, const string& name, int quantity, double price) {
        int index = findProductIndexById(id);
        if (index != -1) {
            products[index].name = name;
            products[index].quantity = quantity;
            products[index].price = price;
            saveProductsToFile();
        } else {
            cout << "Produk tidak ditemukan." << endl;
        }
    }

    void deleteProduct(int id) {
        int index = findProductIndexById(id);
        if (index != -1) {
            products.erase(products.begin() + index);
            saveProductsToFile();
        } else {
            cout << "Produk tidak ditemukan." << endl;
        }
    }

    double calculateAveragePrice() const {
        if (products.empty()) {
            return 0.0;
        }
        double total = 0;
        for (const auto& product : products) {
            total += product.price;
        }
        return total / products.size();
    }

    void searchProductByName(const string& name) const {
        bool found = false;
        for (const auto& product : products) {
            if (product.name.find(name) != string::npos) {
                cout << "ID: " << product.id
                     << ", Nama: " << product.name
                     << ", Quantity: " << product.quantity
                     << ", Harga: Rp. " << product.price << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Tidak ada produk yang ditemukan dengan nama: " << name << endl;
        }
    }
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    Warehouse warehouse;
    int choice;
    do {
        clearScreen();
        cout << "\nWarehouse Management System\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Lihat Barang\n";
        cout << "3. Update Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Rata Rata Harga Barang\n";
        cout << "6. Cari Produk\n";
        cout << "0. Exit\n";
        cout << "Masukkan Pilihan: ";
        cin >> choice;

        clearScreen();
        switch (choice) {
            case 1: {
                string name;
                int quantity;
                double price;
                cout << "Masukkan nama barang: ";
                cin.ignore();
                getline(cin, name);
                cout << "Masukkan jumlah: ";
                cin >> quantity;
                cout << "Masukkan harga: ";
                cin >> price;
                warehouse.addProduct(name, quantity, price);
                break;
            }
            case 2:
                warehouse.readProducts();
                break;
            case 3: {
                int id;
                string name;
                int quantity;
                double price;
                cout << "Masukkan id barang: ";
                cin >> id;
                cout << "Masukkan nama: ";
                cin.ignore();
                getline(cin, name);
                cout << "Masukkan quantity: ";
                cin >> quantity;
                cout << "Masukkan harga: ";
                cin >> price;
                warehouse.updateProduct(id, name, quantity, price);
                break;
            }
            case 4: {
                int id;
                cout << "Masukkan id barang untuk dihapus: ";
                cin >> id;
                warehouse.deleteProduct(id);
                break;
            }
            case 5:
                cout << "Rata rata harga barang: Rp. " << warehouse.calculateAveragePrice() << endl;
                break;
            case 6: {
                string name;
                cout << "Masukkan nama barang: ";
                cin.ignore();
                getline(cin, name);
                warehouse.searchProductByName(name);
                break;
            }
            case 0:
                cout << "Exit" << endl;
                break;
            default:
                cout << "Masukkan salah, silahkan ulangi" << endl;
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 0);

    return 0;
}
