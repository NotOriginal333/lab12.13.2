//12.13.3
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Price {
	string productName;
	string shopName;
	double price;
};

class OpenHashTable {
private:
	static const int SIZE = 100; 
	Price* table[SIZE];

	int hashFunction(const string& key) {
		int hash = 0;
		for (char c : key) {
			hash += c;
		}
		return hash % SIZE;
	}

public:
	OpenHashTable() {
		for (int i = 0; i < SIZE; ++i) {
			table[i] = nullptr; 
		}
	}

	void addPrice(const Price& price) {
		int index = hashFunction(price.productName);
		while (table[index] != nullptr) {
			index = (index + 1) % SIZE; 
		}
		table[index] = new Price(price);
	}

	void displayPrices() {
		for (int i = 0; i < SIZE; ++i) {
			if (table[i] != nullptr) {
				cout << "Product: " << table[i]->productName << ", Shop: " << table[i]->shopName << ", Price: " << table[i]->price << " UAH\n";
			}
		}
	}

	bool searchProductByName(const string& productName) {
		int index = hashFunction(productName);
		while (table[index] != nullptr) {
			if (table[index]->productName == productName) {
				cout << "Product: " << table[index]->productName << ", Shop: " << table[index]->shopName << ", Price: " << table[index]->price << " UAH\n";
				return true;
			}
			index = (index + 1) % SIZE;
		}
		cout << "Product with name \"" << productName << "\" not found.\n";
		return false;
	}

	void deletePriceByName(const string& productName) {
		int index = hashFunction(productName);
		while (table[index] != nullptr) {
			if (table[index]->productName == productName) {
				delete table[index];
				table[index] = nullptr;
				cout << "Product " << productName << " deleted successfully.\n";
				return;
			}
			index = (index + 1) % SIZE; 
		}
		cout << "Product with name \"" << productName << "\" not found.\n";
	}

	void saveToFile(const string& filename) {
		ofstream file(filename);
		if (!file) {
			cout << "Error opening file.\n";
			return;
		}

		for (int i = 0; i < SIZE; ++i) {
			if (table[i] != nullptr) {
				file << table[i]->productName << " " << table[i]->shopName << " " << table[i]->price << "\n";
			}
		}

		file.close();
		cout << "Data saved to " << filename << ".\n";
	}

	void loadFromFile(const string& filename) {
		ifstream file(filename);
		if (!file) {
			cout << "Error opening file.\n";
			return;
		}

		for (int i = 0; i < SIZE; ++i) {
			delete table[i];
			table[i] = nullptr;
		}

		Price temp;
		while (file >> temp.productName >> temp.shopName >> temp.price) {
			addPrice(temp);
		}

		file.close();
		cout << "Data loaded from " << filename << ".\n";
	}

	~OpenHashTable() {
		for (int i = 0; i < SIZE; ++i) {
			delete table[i];
		}
	}
};

int main() {
	OpenHashTable hashTable;

	int choice;
	string filename;

	do {
		cout << "1. Add product\n";
		cout << "2. Display all products\n";
		cout << "3. Search product by name\n";
		cout << "4. Delete product by name\n";
		cout << "5. Save to file\n";
		cout << "6. Load from file\n";
		cout << "7. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice) {
		case 1: {
			Price price;
			cout << "Enter product name: ";
			cin >> price.productName;
			cout << "Enter shop name: ";
			cin >> price.shopName;
			cout << "Enter price in UAH: ";
			cin >> price.price;
			hashTable.addPrice(price);
			break;
		}
		case 2:
			hashTable.displayPrices();
			break;
		case 3: {
			string productName;
			cout << "Enter the product name to search: ";
			cin >> productName;
			hashTable.searchProductByName(productName);
			break;
		}
		case 4: {
			string productName;
			cout << "Enter the product name to delete: ";
			cin >> productName;
			hashTable.deletePriceByName(productName);
			break;
		}
		case 5: {
			cout << "Enter filename to save: ";
			cin >> filename;
			hashTable.saveToFile(filename);
			break;
		}
		case 6: {
			cout << "Enter filename to load: ";
			cin >> filename;
			hashTable.loadFromFile(filename);
			break;
		}
		case 7:
			cout << "Exiting...\n";
			break;
		default:
			cout << "Invalid choice. Please try again.\n";
		}
	} while (choice != 7);

	return 0;
}
//12.13.3