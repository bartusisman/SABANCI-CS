#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <cstdlib>

using namespace std;

// Define the contact struct
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

    bool operator==(const string& otherFullName) const  // another variation of == overload that also detects partials
    {
        return fullName.substr(0, otherFullName.size()) == otherFullName;
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

string upper(const string& str)
{
    string result = str;

    for (size_t i = 0; i < result.size(); ++i)
    {
        result[i] = toupper(result[i]);
    }
    return result;
}

void loadContacts(string filename, vector<Contact> &vec) 
{
    ifstream in;
    string firstName, lastName, phoneNumber, city;

    in.open(filename);
    if (!in) 
    {
        cerr << "Unable to open the file." << endl;
        exit(EXIT_FAILURE);
    }

    while (in >> firstName >> lastName >> phoneNumber >> city) 
    {
        vec.push_back( Contact(upper(firstName), upper(lastName), phoneNumber, city) );
    }
    in.close();
}

void InsertionSort(vector<Contact> & vec)
{
    for (size_t i = 1; i < vec.size(); i++) 
    {
        Contact key = vec[i];
        int j = i - 1;
        while (j >= 0 && vec[j] > key)
        {
            vec[j + 1] = vec[j];
            j = j - 1;
        }
        vec[j + 1] = key;
    }
}

void Merge(vector<Contact>& vec, int start, int mid, int end) 
{
    int leftSize = mid - start + 1;
    int rightSize = end - mid;

    vector<Contact> leftVec(leftSize);
    vector<Contact> rightVec(rightSize);

    for (int i = 0; i < leftSize; i++)
        leftVec[i] = vec[start + i];
    for (int j = 0; j < rightSize; j++)
        rightVec[j] = vec[mid + 1 + j];

    int i = 0, j = 0;
    int k = start;

    while (i < leftSize && j < rightSize) 
    {
        if ( (leftVec[i] < rightVec[j]) || (leftVec[i] == rightVec[j]) )
        {
            vec[k] = leftVec[i];
            i++;
        } 
        else 
        {
            vec[k] = rightVec[j];
            j++;
        }
        k++;
    }

    while (i < leftSize) 
    {
        vec[k] = leftVec[i];
        i++;
        k++;
    }

    while (j < rightSize) 
    {
        vec[k] = rightVec[j];
        j++;
        k++;
    }
}

void MergeSort(vector<Contact> & vec, int start, int end)
{
    if (start >= end) 
    {
        return;
    }
    int mid = start + (end - start) / 2;
    MergeSort(vec, start, mid);
    MergeSort(vec, mid + 1, end);
    Merge(vec, start, mid, end);
}

void SequentialSearch(vector<Contact> & vec, string query)
{
    for (const auto& contact : vec) 
    {
        if (contact == upper(query)) 
        {
            cout << "Contact Found: " << contact << endl;
            return;
        }
    }
    cout << query << " does NOT exist in the dataset" << endl;
}

void BinarySearch(vector<Contact> & vec, string query)
{
    int l = 0, r = vec.size() - 1;
    while (l <= r) 
    {
        int mid = l + (r - l) / 2;
        if (vec[mid] == upper(query)) 
        {
            cout << "Contact Found: " << vec[mid] << endl;
            return;
        }
        if (vec[mid] < upper(query))
            l = mid + 1;
        else
            r = mid - 1;
    }
    cout << query << " does NOT exist in the dataset" << endl;
}

int partition(vector<Contact>& vec, int low, int high) 
{
    Contact pivot = vec[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) 
    {
        if (vec[j] < pivot) 
        {
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return (i + 1);
}

void QuickSort(vector<Contact>& vec, int low, int high)
{
    if (low < high) 
    {
        int pi = partition(vec, low, high);

        QuickSort(vec, low, pi - 1);
        QuickSort(vec, pi + 1, high);
    }
}

void heapify(vector<Contact>& vec, int n, int i) 
{
    int largest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    if (left < n && vec[left] > vec[largest])
        largest = left;

    if (right < n && vec[right] > vec[largest])
        largest = right;

    if (largest != i) 
    {
        swap(vec[i], vec[largest]);
        heapify(vec, n, largest);
    }
}

void HeapSort(vector<Contact>& vec) 
{
    int n = vec.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(vec, n, i);
    for (int i = n - 1; i > 0; i--) 
    {
        swap(vec[0], vec[i]);
        heapify(vec, i, 0);
    }
}

void DisplayVector(vector<Contact> & vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << endl;
    }
    
}


int main() 
{
    // declarations of vectors
    vector<Contact> InsertionVec;
    vector<Contact> QuickVec;
    vector<Contact> MergeVec;
    vector<Contact> HeapVec;

    // Load the contacts from the file to the vectors
    string filename;
    cout << "Please enter the contact file name: ";
    cin >> filename;
    
    loadContacts(filename, InsertionVec);
    loadContacts(filename, QuickVec);
    loadContacts(filename, MergeVec);
    loadContacts(filename, HeapVec);

    
    // Get the query
    string query;
    cout << "Please enter the word to be queried: ";
    cin.ignore();
    getline(cin,query);
    cout << endl;

    // Define variable to hold execution times
    double quickSortTime, insertionSortTime, mergeSortTime, heapSortTime;
    double binarySearchTime, sequentialSearchTime;

    // Run sorting algorithms and measure time
    cout << "Sorting the vector copies" << endl;
    cout << "======================================" << endl;

    auto start = chrono::high_resolution_clock::now();
    QuickSort(QuickVec, 0, QuickVec.size()-1); // Call Quick Sort
    auto end = chrono::high_resolution_clock::now();
    quickSortTime = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
    cout << "Quick Sort Time: " << quickSortTime << " Nanoseconds" << endl;

    start = chrono::high_resolution_clock::now();
    InsertionSort(InsertionVec); // Call Insertion Sort
    end = chrono::high_resolution_clock::now();
    insertionSortTime = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
    cout << "Insertion Sort Time: " << insertionSortTime << " Nanoseconds" << endl;

    start = chrono::high_resolution_clock::now();
    MergeSort(MergeVec, 0, MergeVec.size()-1); // Call Merge Sort
    end = chrono::high_resolution_clock::now();
    mergeSortTime = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
    cout << "Merge Sort Time: " << mergeSortTime << " Nanoseconds" << endl;

    start = chrono::high_resolution_clock::now();
    HeapSort(HeapVec); // Call Heap Sort
    end = chrono::high_resolution_clock::now();
    heapSortTime = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
    cout << "Heap Sort Time: " << heapSortTime << " Nanoseconds" << endl << endl;

    // Run searching algorithms and measure time
    cout << "Searching for " << query << endl;
    cout << "======================================" << endl;

    start = chrono::high_resolution_clock::now();
    BinarySearch(QuickVec, query); // Call Binary Search
    end = chrono::high_resolution_clock::now();
    binarySearchTime = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
    cout << "Binary Search Time: " << binarySearchTime << " Nanoseconds" << endl;

    start = chrono::high_resolution_clock::now();
    SequentialSearch(InsertionVec, query); // Call Sequential Search
    end = chrono::high_resolution_clock::now();
    sequentialSearchTime = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
    cout << "Sequential Search Time: " << sequentialSearchTime << " Nanoseconds" << endl << endl;


    // Calculate speedups
    double searchSpeedup = sequentialSearchTime / binarySearchTime;
    double insertionSortSpeedup = insertionSortTime / quickSortTime;
    double mergeSortSpeedup = mergeSortTime / quickSortTime;
    double heapSortSpeedup = heapSortTime / quickSortTime;

    // Print speedups
    cout << "SpeedUp between Search Algorithms" << endl;
    cout << "======================================" << endl;
    cout << "(Sequential Search/ Binary Search) SpeedUp = " << searchSpeedup << endl << endl;

    cout << "SpeedUps between Sorting Algorithms" << endl;
    cout << "======================================" << endl;
    cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << insertionSortSpeedup << endl;
    cout << "(Merge Sort / Quick Sort) SpeedUp = " << mergeSortSpeedup << endl;
    cout << "(Heap Sort / Quick Sort) SpeedUp = " << heapSortSpeedup << endl;

    return 0;
}
