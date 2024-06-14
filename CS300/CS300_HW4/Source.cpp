#include<iostream>
#include<string>
#include<vector>
#include <list>
#include <chrono>
#include <cmath>
#include "BSTree.cpp"

using namespace std;

struct Contact // contact strcuct that stores the informations and has same helpful overload operations
{
    string firstName;
    string lastName;
    string phoneNumber;
    string city;
    string fullName; // firstName + " " + lastName

    Contact() // default constructor
    {}

    Contact(const string& first, const string& last, const string& phone, const string& city_) // automatically assings fullname when a valid instance of the struct is created
        : firstName(first), lastName(last), phoneNumber(phone), city(city_)
    {
        fullName = firstName + " " + lastName;
    }

    bool operator==(const Contact& other) const // == overload for checking if two contacts have the same name
    {
        return fullName == other.fullName;

    }

    bool operator==(const string& otherFullName) const  // another variation of == overload
    {
        return fullName == otherFullName;
    }

    bool operator<(const Contact& other) const // < overload for checking if ismaller
    {
        return fullName < other.fullName;
    }

    bool operator<(const string& other) const // another variation of < overload
    {
        return fullName < other;
    }

    bool operator>(const Contact& other) const // > overload for checking if isbigger
    {
        return fullName > other.fullName;
    }

    bool operator>(const string& other) const // another variation of > overload
    {
        return fullName > other;
    }

    friend ostream& operator<<(ostream& os, const Contact& contact) // << overload for cout << in order to print the informations in the contact with ease
    {
        if (&os == &cout)
        {
            os << contact.fullName << " " << contact.phoneNumber << " " << contact.city;
        }
        return os;
    }
};

template <typename T>
class HashTable
{
private:
    vector<list<T>> table;
    int itemCount;
    double loadFactor;
    const double minLoadFactor = 0.25;
    const double maxLoadFactor = 0.9;

    int hashFunction(T item) 
    {
        return hashString(item.fullName) % table.size();
    }

    int hashString(const string& str) 
    {
        int hash = 0;
        for (char c : str) {
            hash = hash * 31 + c;
        }
        return hash;
    }

    bool isPrime(int n) 
    {
        if (n <= 1) 
        {
            return false;
        }
        if (n <= 3) 
        {
            return true;
        }
        if (n % 2 == 0 || n % 3 == 0) 
        {
            return false;
        }
        for (int i = 5; i * i <= n; i += 6) 
        {
            if (n % i == 0 || n % (i + 2) == 0) 
            {
                return false;
            }
        }
        return true;
    }

    int nextPrime(int n) 
    {
        if (n <= 1) 
        {
            return 2;
        }
        int prime = n;
        bool found = false;
        while (!found) 
        {
            prime++;
            if (isPrime(prime)) 
            {
                found = true;
            }
        }
        return prime;
    }

    void rehash() 
    {
        cout << "rehashed..." << endl;
        cout << "Previous table size: " << table.size();

        vector<list<T>> oldTable = table;
        table.resize(nextPrime(2 * table.size()));
        cout << ", new table size: " << table.size() << ", current unique item count: " << itemCount;

        itemCount = 0;

        for (auto& chain : oldTable) 
        {
            for (T* item : chain) 
            {
                insert(item);
            }
        }

        loadFactor = static_cast<double>(itemCount) / table.size();
        cout << ", Current load factor: " << loadFactor << endl;
    }

public:
    HashTable(int size = 53) : table(size), itemCount(0), loadFactor(0) {}

    void insert(T* item) 
    {
        int index = hashFunction(*item);
        for (T i : table[index]) 
        {
            if (i == *item) 
            {
                return; // Do not insert duplicate contacts
            }
        }
        table[index].push_back(*item);
        itemCount++;

        loadFactor = static_cast<double>(itemCount) / table.size();
        if (loadFactor < minLoadFactor || loadFactor > maxLoadFactor) 
        {
            rehash();
        }
    }

    void remove(string fullName) 
    {
        int index = hashString(fullName) % table.size();
        for (auto it = table[index].begin(); it != table[index].end(); ++it) 
        {
            if (it->fullName == fullName) 
            {
                table[index].erase(it);
                itemCount--;
                loadFactor = static_cast<double>(itemCount) / table.size();
                return;
            }
        }
    }

    T find(string fullName)
    {
        int index = hashString(fullName) % table.size();
        for (T i : table[index])
        {
            if (i.fullName == fullName)
            {
                return i;
            }
        }
        return T(); // Return a default-constructed
    }
};

string upper(const string& str)
{
    string result = str;

    for (size_t i = 0; i < result.size(); ++i)
    {
        result[i] = toupper(result[i]);
    }
    return result;
}

int main()
{
    int choice;
    string filename, firstName, lastName, phoneNumber, city;
    Contact* contact;
    BSTree<Contact> BST;
    HashTable<Contact> Hash;

    ifstream in;
    cout << "Enter the  file name: ";
    cin >> filename;

    in.open(filename);

    if (!in)
    {
        cerr << "Unable to open the contact file." << endl;
        return 1;
    }

    while (in >> firstName >> lastName >> phoneNumber >> city) // Hash table
    {
        contact = new Contact(upper(firstName), upper(lastName), phoneNumber, city);
        Hash.insert(contact);
    }
    
    in.clear();
    in.seekg(0, ios::beg); // ready the file for reading it again

   
    
    while (in >> firstName >> lastName >> phoneNumber >> city) // BSTree
    {
        contact = new Contact(upper(firstName), upper(lastName), phoneNumber, city);
        BST.addItem(contact);
    }

    in.close();


    do
    {
        cout << endl;
        cout << "Choose which action to perform from 1 to 4:" << endl;
        cout << "1 - Search a phonebook contact" << endl;
        cout << "2 - Adding a phonebook contact" << endl;
        cout << "3 - Deleting a phonebook contact" << endl;
        cout << "4 - Press 4 to exit" << endl;

        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
           
        }
        case 2:
        {
          
        }
        case 3:
        {
          
        }
        case 4:
        {
        
        }
    
        default:
        {
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
            break;
        }

        }
    } while (choice != 4);
}