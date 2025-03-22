#include <iostream>
#include <fstream>
#include <limits>

using namespace std;
template <typename T>
class StatisticalCalculation
{
private:
    T* data;
    int size{};
    void merge(int left, int middle, int right); // helper function for merge sort
public:
    StatisticalCalculation(int size);
    ~StatisticalCalculation();

    void sort(int left, int right); // implement merge sort to sort the data

    double findMedian();
    T findMin() const;
    T findMax() const;
    double findMean() const;
    T findSummation() const;

    void displayArray() const;
    void inputData();
    void statisticsMenu();


};

template <typename T>
StatisticalCalculation<T>::StatisticalCalculation(int size) : size(size)
{
    this->data = new T[size];
    this->size = size;
}

template <typename T>
StatisticalCalculation<T>::~StatisticalCalculation()
{
    delete[] data;
}

template <typename T>
void StatisticalCalculation<T>::merge(int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Temporary arrays to hold left and right subarrays
    T l[n1];
    T r[n2];
    for (int i = 0; i < n1; ++i)
    {
        l[i] = this->data[left + i];
    }
    for (int i = 0; i < n2; ++i)
    {
        r[i] = this->data[middle + i + 1];
    }

    // Merge the two subarrays back into the original array
    int i = 0, j = 0, k = left;

    // Compare elements from both subarrays and place the smaller one into the original array
    while (i < n1 && j < n2)
    {
        if (l[i] <= r[j])
        {
            this->data[k] = l[i];  // Place element from left subarray
            i++;
        }
        else
        {
            this->data[k] = r[j];  // Place element from right subarray
            j++;
        }
        k++;
    }

    // Copy any remaining elements from the left subarray
    while (i < n1)
    {
        this->data[k] = l[i];
        k++, i++;
    }

    // Copy any remaining elements from the right subarray
    while (j < n2)
    {
        this->data[k] = r[j];
        k++, j++;
    }
}

template <typename T>
void StatisticalCalculation<T>::sort(int left, int right)
{
    if (left >= right)
    {
        return;
    }
    else
    {
        int middle = left + (right - left) / 2;
        sort(left, middle);
        sort(middle + 1, right);

        // Merge the two sorted halves
        merge(left, middle, right);
    }
}

template <typename T>
T StatisticalCalculation<T>::findSummation() const
{
    T sum = 0;
    for (int i = 0; i < this->size; ++i)
    {
        sum += this->data[i];
    }
    return sum;
}

template <typename T>
void StatisticalCalculation<T>::displayArray() const
{
    cout << '[';
    for (int i = 0; i < this->size; ++i)
    {
        cout << this->data[i];
        if (i != this->size - 1)
        {
            cout << ", ";
        }
    }
    cout << ']' << endl;
}

template <typename T>
double StatisticalCalculation<T>::findMean() const
{
    return (double)this->findSummation() / (double)this->size;
}

template <typename T>
double StatisticalCalculation<T>::findMedian()
{
    sort(0, this->size - 1);
    if (this->size % 2 != 0)
    {
        return (T)(this->data[size / 2]);
    }
    return ((double)this->data[int(size / 2)] + (double)this->data[int(size / 2) - 1]) / 2;
}

template <typename T>
T StatisticalCalculation<T>::findMin() const
{
    T min = this->data[0];
    for (int i = 0; i < this->size; ++i)
    {
        if (this->data[i] < min)
        {
            min = this->data[i];
        }
    }
    return min;
}

template <typename T>
T StatisticalCalculation<T>::findMax() const
{
    T max = this->data[0];
    for (int i = 0; i < this->size; ++i)
    {
        if (this->data[i] > max)
        {
            max = this->data[i];
        }
    }
    return max;
}

template <typename T>
void StatisticalCalculation<T>::inputData()
{
    string filename;
    cout << "Enter filename:";
    cin >> filename;
    ifstream file(filename);
    if (!file){
        cerr << "Error: Could not open file!" << endl;
        exit(-1);
    }

    for (int i = 0; i < this->size; ++i)
    {
        file >> this->data[i];
    }
    file.close();
    sort(0, this->size - 1);
    displayArray();
}

template <typename T>
void StatisticalCalculation<T>::statisticsMenu()
{
    cout << "Select a statistical calculation:\n";
    cout << "1. Find Median\n";
    cout << "2. Find Minimum\n";
    cout << "3. Find Maximum\n";
    cout << "4. Find Mean\n";
    cout << "5. Find Summation\n";
    string choice;
    cout << "Enter your choice (1-5):";
    cin >> choice;
    while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5")
    {
        cerr << "Invalid choice please try again.\nEnter your choice (1-5):";
        cin >> choice;
    }
    if (choice == "1")
    {
        cout << "Median: " << this->findMedian() << endl;
    }
    if (choice == "2")
    {
        cout << "Minimum: " << this->findMin() << endl;
    }
    if (choice == "3")
    {
        cout << "Maximum: " << this->findMax() << endl;
    }
    if (choice == "4")
    {
        cout << "Mean: " << this->findMean() << endl;
    }
    if (choice == "5")
    {
        cout << "Summation: " << this->findSummation() << endl;
    }
}

int getStatSize(const string& prompt) noexcept(false){
    int size;
    while (true){
        try{
            cout << prompt;
            cin >> size;
            if (cin.fail() || size < 0){
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
//int main()
//{
//    int size = getStatSize("Enter the number of elements:");
//    cin.ignore(1, '\n');
//    StatisticalCalculation<int> s(size);
//    s.inputData();
//    s.statisticsMenu();
//}
