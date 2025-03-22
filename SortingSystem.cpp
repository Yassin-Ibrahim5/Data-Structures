#include <iostream>
#include <fstream>
#include <type_traits>
#include <chrono>
#include <iomanip>
#include <cctype>
#include <limits>
using namespace std;

template <typename T>
class SortingSystem
{
private:
    T* data;
    int size;
    // helper count sort to help in radix sort
    void helperCountSort(int exp);
public:
    SortingSystem(int n);
    ~SortingSystem();
    void insertionSort();
    void selectionSort();
    void bubbleSort();
    void shellSort();
    void mergeSort(int left, int right);
    void quickSort(int left, int right);
    void countSort();
    void radixSort();
    void bucketSort();

    // helper functions
    void merge(int left, int mid, int right);
    int partition(int low, int high);

    void displayData();

    void measureSortTime(void(SortingSystem::*sortFunc)());
    // overloading the measureSortTime function for sorting functions that require parameters
    void measureSortTime(void(SortingSystem::*sortFunc)(int,int), int left, int right);
    void showMenu();

    // getter for the data array
    T* getData();
};

template <typename T>
T *SortingSystem<T>::getData(){return this->data;}

template<typename T>
void SortingSystem<T>::measureSortTime(void (SortingSystem<T>::*sortFunc)(int, int), int left, int right)
{
    auto start = chrono::high_resolution_clock::now();
    (this->*sortFunc)(left, right);
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start);
    long double t = elapsed.count() / 10e9;
    cout << "Sorting time: " << fixed << setprecision(9) << t << " seconds\n";
}

template<typename T>
void SortingSystem<T>::measureSortTime(void(SortingSystem<T>::*sortFunc)())
{
    auto start = chrono::high_resolution_clock::now();
    (this->*sortFunc)();
    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start);
    long double t = elapsed.count() / 10e9;
    cout << "Sorting time: " << fixed << setprecision(9) << t << " seconds\n";

}

template<typename T>
void SortingSystem<T>::displayData()
{
    cout << '[';
    for (int i = 0; i < this->size; ++i)
    {
        cout << setprecision(2) << this->data[i];
        if (i != this->size - 1)
        {
            cout << ", ";
        }
    }
    cout << ']' << endl;
}

template<typename T>
void SortingSystem<T>::showMenu()
{

    cout << "Initial Data: ";
    displayData();
    cout << "Select a sorting algorithm:\n";
    cout << "1. Insertion Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Bubble Sort\n";
    cout << "4. Shell Sort\n";
    cout << "5. Merge Sort\n";
    cout << "6. Quick Sort\n";
    cout << "7. Count Sort (Only for integers)\n";
    cout << "8. Radix Sort (Only for integers)\n";
    cout << "9. Bucket Sort (Only for floats)\n";

    string choice;
    cout << "Enter your choice (1-9):";
    cin >> choice;
    while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6" && choice != "7" && choice != "8" && choice != "9")
    {
        cerr << "Invalid choice please try again.\nEnter your choice (1-9)";
        cin >> choice;
    }
    if (choice == "1")
    {
        cout << "Sorting using insertion sort...\n";
//        this->insertionSort();
        this->measureSortTime(&SortingSystem<T>::insertionSort);
        cout << "Sorted data: ";
        displayData();
    }
    if (choice == "2")
    {
        cout << "Sorting using selection sort...\n";
//        this->selectionSort();
        this->measureSortTime(&SortingSystem<T>::selectionSort);
        cout << "Sorted data: ";

        displayData();
    }
    if (choice == "3")
    {
        cout << "Sorting using bubble sort...\n";
//        this->bubbleSort();
        this->measureSortTime(&SortingSystem<T>::bubbleSort);
        cout << "Sorted data: ";

        displayData();
    }
    if (choice == "4")
    {
        cout << "Sorting using shell sort...\n";
//        this->shellSort();
        this->measureSortTime(&SortingSystem<T>::shellSort);
        cout << "Sorted data: ";

        displayData();
    }
    if (choice == "5")
    {
        cout << "Sorting using merge sort...\n";
//        this->mergeSort(0, this->size - 1);
        this->measureSortTime(&SortingSystem<T>::mergeSort, 0, this->size - 1);
        cout << "Sorted data: ";

        displayData();
    }
    if (choice == "6")
    {
        cout << "Sorting using quick sort...\n";
//        this->quickSort(0, this->size - 1);
        this->measureSortTime(&SortingSystem<T>::quickSort, 0, this->size - 1);
        cout << "Sorted data: ";

        displayData();
    }
    if (choice == "7")
    {
        if constexpr (is_same<T, int>::value)
        {
            cout << "Sorting using count sort...\n";
//            this->countSort();
            this->measureSortTime(&SortingSystem<T>::countSort);
            cout << "Sorted data: ";
        }
        else
        {
            cout << "Count sort can only be used on integers.\n";
        }
        displayData();
    }
    if (choice == "8")
    {
        if constexpr (is_same<T, int>::value)
        {
            cout << "Sorting using radix sort...\n";
//            this->radixSort();
            this->measureSortTime(&SortingSystem<T>::radixSort);
            cout << "Sorted data: ";
        }
        else
        {
            cout << "Radix sort can only be used on integers.\n";
        }
        displayData();
    }
    if (choice == "9")
    {
        if constexpr (is_same<T, float>::value)
        {
            cout << "Sorting using bucket sort...\n";
//            this->bucketSort();
            this->measureSortTime(&SortingSystem<T>::bucketSort);
            cout << "Sorted data: ";
        }
        else
        {
            cout << "Bucket sort can only be used on floating point numbers.\n";
        }
        displayData();
    }
}

template <typename T>
SortingSystem<T>::SortingSystem(int n) : size(n)
{
    this->size = n;
    this->data = new T[this->size];
}

template <typename T>
SortingSystem<T>::~SortingSystem()
{
    delete[] this->data;
}

template <typename T>
void SortingSystem<T>::insertionSort()
{
    for (int i = 1; i < this->size; ++i)
    {
        cout << "Iteration " << i << ": ";
        displayData();
        int j = i;
        while (j > 0 && data[j - 1] > data[j])
        {
            swap(data[j], data[j - 1]);
            j--;
        }
    }
}

template <typename T>
void SortingSystem<T>::selectionSort()
{
    for (int i = 0; i < this->size; ++i)
    {
        cout << "Iteration " << (i + 1) << ": ";
        displayData();
        for (int j = i + 1; j < this->size; ++j)
        {
            int least = i;
            if (data[j] < data[least])
            {
                least = j;
            }
            swap(data[least], data[i]);
        }
    }
}

template <typename T>
void SortingSystem<T>::bubbleSort()
{
    for (int i = 0; i < this->size; ++i)
    {
        cout << "Iteration " << (i + 1) << ": ";
        displayData();
        for (int j = this->size - 1; j > i; j--)
        {
            if (data[j] < data[j - 1])
            {
                swap(data[j], data[j - 1]);
            }
        }
    }
}

template <typename T>
void SortingSystem<T>::shellSort()
{
    for (int gap = this->size / 2; gap > 0; gap /= 2)
    {
        int iterCount = 1;
        cout << "Iteration " << (iterCount) << ": ";
        iterCount++;
        displayData();
        for (int i = gap; i < this->size; ++i)
        {
            T temp = data[i];
            int j;
            for (j = i; j >= gap && data[j - gap] > temp; j -= gap)
            {
                data[j] = data[j - gap];
            }
            data[j] = temp;
        }
    }
}

template <typename T>
void SortingSystem<T>::merge(int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    T* l = new T[n1];
    T* r = new T[n2];
    for (int i = 0; i < n1; ++i)
    {
        l[i] = data[left + i];
    }
    for (int i = 0; i < n2; ++i)
    {
        r[i] = data[mid + i + 1];
    }
    cout << "Merging: [";
    for (int x = left; x <= right; ++x)
    {
        cout << this->data[x];
        if (x != right)
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (l[i] <= r[j])
        {
            data[k] = l[i];
            i++;
        }else
        {
            data[k] = r[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        data[k] = l[i];
        k++, i++;
    }
    while (j < n2)
    {
        data[k++] = r[j++];
        k++, j++;
    }
    cout << "After Merging: [";
    for (int x = left; x <= right; ++x)
    {
        cout << this->data[x];
        if (x != right)
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    delete[] l;
    delete[] r;
}

template <typename T>
void SortingSystem<T>::mergeSort(int left, int right)
{
    if (left >= right)
    {
        return;
    }
    else
    {
        int middle = left + (right - left) / 2;
        mergeSort(left, middle);
        mergeSort(middle + 1, right);
        merge(left, middle, right);
    }
}

template <typename T>
int SortingSystem<T>::partition(int low, int high)
{
    T pivot = data[low];
    int i = low;
    for (int j = low + 1; j <= high; ++j)
    {
        if (data[j] < pivot)
        {
            i++;
            swap(data[i], data[j]);
        }
    }
    swap(data[i], data[low]);
    return i;
}

template <typename T>
void SortingSystem<T>::quickSort(int left, int right)
{
    if (left >= right)
    {
        return;
    }
    else
    {
        int pivotIndex = partition(left, right);
        cout << "Pivot: " << this->data[pivotIndex] << endl;
        cout << "After partitioning: ";
        this->displayData();
        quickSort(left, pivotIndex - 1);
        quickSort(pivotIndex + 1, right);
    }
}

template <typename T>
void SortingSystem<T>::countSort()
{
    int* sorted = new int[this->size]();
    int M = 0;
    for (int i = 0; i < this->size; ++i)
    {
        M = max(M, this->data[i]);
    }
    int* counter = new int[M + 1]();


    for (int i = 0; i < this->size; ++i)
    {
        counter[this->data[i]]++;
    }

    cout << "Frequency count array: [";
    for (int i = 0; i < M + 1; ++i)
    {
        cout << counter[i];
        if (i != M)
        {
            cout << ", ";
        }
    }
    cout << "]\n";

    for (int i = 1; i <= M; ++i)
    {
        counter[i] += counter[i - 1];
    }
    cout << "Cumulative sum array: [";
    for (int i = 0; i < M + 1; ++i)
    {
        cout << counter[i];
        if (i != M)
        {
            cout << ", ";
        }
    }
    cout << "]\n";
    for (int i = this->size - 1; i >= 0; i--)
    {
        sorted[counter[data[i]] - 1] = data[i];
        counter[data[i]]--;
    }
    for (int i = 0; i < this->size; ++i)
    {
        this->data[i] = sorted[i];
    }
    delete[] sorted;
    delete[] counter;
}

template <typename T>
void SortingSystem<T>::helperCountSort(int exp)
{
    int* output = new int[this->size];
    int* count = new int[10];
    for (int i = 0; i < 10; ++i)
    {
        count[i] = 0;
    }
    for (int i = 0; i < this->size; ++i)
    {
        count[(data[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; ++i)
    {
        count[i] += count[i - 1];
    }
    for (int i = this->size - 1; i >= 0; i--)
    {
        output[count[(this->data[i] / exp) % 10] - 1] = this->data[i];
        count[(this->data[i] / exp) % 10]--;
    }
    for (int i = 0; i < this->size; ++i)
    {
        this->data[i] = output[i];
    }
    cout << "After sorting by digit (exp = " << exp << "): ";
    displayData();
    delete[] output;
    delete[] count;
}

template <typename T>
void SortingSystem<T>::radixSort()
{
    int m = 0;
    for (int i = 0; i < this->size; ++i)
    {
        m = max(m, data[i]);
    }
    for (int exp = 1; m / exp > 0; exp *= 10)
    {
        this->helperCountSort(exp);
    }
}

template <typename T>
void SortingSystem<T>::bucketSort()
{

    T minValue = data[0], maxValue = data[0];
    for (int i = 1; i < this->size; i++) {
        if (data[i] < minValue) minValue = data[i];
        if (data[i] > maxValue) maxValue = data[i];
    }
    auto** buckets = new float*[this->size];
    auto* bucketSizes = new int[this->size]();

    for (int i = 0; i < this->size; ++i)
    {
        buckets[i] = new float[this->size];
    }

    for (int i = 0; i < this->size; ++i)
    {
         int bi = (int)((data[i] - minValue) / (maxValue - minValue + 0.0001) * (this->size - 1));
        buckets[bi][bucketSizes[bi]++] = this->data[i];
    }

    cout << "Buckets after distribution:\n";
    for (int i = 0; i < this->size; ++i)
    {
        cout << "Bucket " << i << ": [";

        for (int j = 0; j < bucketSizes[i]; ++j)
        {
            cout << buckets[i][j];
            if (j != bucketSizes[i] - 1)
            {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }

    for (int i = 0; i < this->size; ++i)
    {
        // implement insertion sort on each bucket
        cout << "Sorting bucket " << i << " using insertion sort:\n";
        for (int j = 1; j < bucketSizes[i]; ++j)
        {
            int k = j;
            while (k > 0 && buckets[i][k - 1] > buckets[i][k])
            {
                swap(buckets[i][k], buckets[i][k - 1]);
                k--;

                cout << "Iteration " << j << ": [";
                for (int x = 0; x < bucketSizes[i]; ++x)
                {
                    cout << buckets[i][x];
                    if (x != bucketSizes[i] - 1)
                    {
                        cout << ", ";
                    }
                }
                cout << ']' << endl;
            }
        }
    }

    int index = 0;
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < bucketSizes[i]; ++j)
        {
            this->data[index++] = buckets[i][j];
        }
    }
    for (int i = 0; i < this->size; ++i)
    {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucketSizes;
}

bool isInteger(const string& s)
{
    for (char ch : s)
    {
        if (!isdigit(ch) && ch != '-')
        {
            return false;
        }
    }
    return true;
}

bool isFloat(const string& s)
{
    return ((s.find('.') != string::npos) || (s.find('e') != string::npos) || (s.find('E') != string::npos));
}

int getDataSize(const string& prompt) noexcept(false){
    int size;
    while (true)
    {
        try{
            cout << prompt;
            cin >> size;
            if (cin.fail() || size < 0)
            {
                throw invalid_argument("Invalid input. Size must be a non-negative integer.");
            }
            return size;
        }catch (const invalid_argument& e){
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main()
{
    char again = 'y';
    while (again == 'y'){
        int size = getDataSize("Enter the number of items you want to sort:");
        cin.ignore(1,'\n');
        bool hasFloat = false;
        bool hasString = false;

        auto* inputValues = new string[size];
        string filename;
        cout << "Enter filename:";
        cin >> filename;
        ifstream inputFile(filename);
        if (!inputFile){
            cerr << "Error: Could not open file!" << endl;
            exit(-1);
        }
        for (int i = 0; i < size; ++i)
        {
            inputFile >> inputValues[i];
            if (!isInteger(inputValues[i])){
                if (isFloat(inputValues[i])){
                    hasFloat = true;
                }
                else
                {
                    hasString = true;
                }
            }
        }
        if (hasString){
            SortingSystem<string> s(size);
            for (int i = 0; i < size; ++i)
            {
                s.getData()[i] = inputValues[i];
            }
            s.showMenu();
        }
        else if (hasFloat){
            SortingSystem<float> s(size);
            for (int i = 0; i < size; ++i)
            {
                s.getData()[i] = stof(inputValues[i]);
            }
            s.showMenu();
        }
        else{
            SortingSystem<int> s(size);
            for (int i = 0; i < size; ++i)
            {
                s.getData()[i] = stoi(inputValues[i]);
            }
            s.showMenu();
        }
        cout << "Would you like to sort another dataset (y/n): ";
        cin >> again;
        if (again == 'n')
        {
            cout << "Thank you for using the sorting system! Goodbye!" << endl;
            delete[] inputValues;
            inputFile.close();
            return 0;
        }
        while (again != 'y' && again != 'n'){
            cerr << "Please choose a valid option.\n";
            cerr << "Would you like to sort another dataset (y/n): ";
            cin >> again;
        }
        delete[] inputValues;
    }
    cout << "Thank you for using the sorting system! Goodbye!" << endl;
    return 0;
}
