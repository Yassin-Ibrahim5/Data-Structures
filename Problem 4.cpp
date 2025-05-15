#include <iostream>
#include <string>

using namespace std;

class Patient
{
private:
    string name;
    int severity;
    int arrival_time;


public:
    Patient()
    {
        this->name = "";
        this->severity = 0;
        this->arrival_time = 0;
    }

    Patient(string name, int severity, int arrival)
    {
        this->name = name;
        this->severity = severity;
        this->arrival_time = arrival;
    }

    int getSeverity()
    {
        return severity;
    }

    int getArrival()
    {
        return arrival_time;
    }

    string getName()
    {
        return name;
    }
};

bool isHigherPriority(Patient p1, Patient p2)
{
    if (p1.getSeverity() != p2.getSeverity())
    {
        return p1.getSeverity() > p2.getSeverity();
    }
    return p1.getArrival() > p2.getArrival();

}

class MaxHeap
{
private:
    Patient *heap;
    int size;
    int capacity;

public:
    explicit MaxHeap(int cap = 10)
    {
        capacity = cap;
        size = 0;
        heap = new Patient[capacity];
    }

    ~MaxHeap()
    {
        delete[] heap;  // free memory
    }

    void swap(Patient &a, Patient &b)
    {
        Patient temp = a;
        a = b;
        b = temp;
    }

    void resize()
    {
        capacity *= 2;
        Patient *newHeap = new Patient[capacity];
        for (int i = 0; i < size; ++i)
        {
            newHeap[i] = heap[i];
        }

        delete[] heap;
        heap = newHeap;


    }

    Patient *peek()
    {
        if (size == 0)
        {
            return nullptr;
        }
        return &heap[0];
    }

    int parent(int index)
    {
        if (index > size or index < 0)
        {

        } else
        {
            index = (index - 1) / 2;
            return index;
        }

    }

    void MaxHeapify(int index)
    {
        if (size == 0 or index > size or index < 0)
        {
            return;
        } else
        {
            while (index > 0)
            {
                if (isHigherPriority(heap[index], heap[parent(index)]))
                {
                    swap(heap[index], heap[parent(index)]);
                    index = parent(index);
                } else
                {
                    break;
                }

            }
        }

    }

    void heapifyDown(int index)
    {
        int left, right, largest;
        while (index < size)
        {
            left = 2 * index + 1;
            right = 2 * index + 2;
            largest = index;

            if (left < size && isHigherPriority(heap[left], heap[largest]))
                largest = left;
            if (right < size && isHigherPriority(heap[right], heap[largest]))
                largest = right;

            if (largest != index)
            {
                swap(heap[index], heap[largest]);
                index = largest;
            } else
            {
                break;
            }
        }

    }

    void insert(Patient p)
    {
        if (size == capacity)
        {
            resize();
        }
        heap[size] = p;
        MaxHeapify(size);
        size++;

    }


    Patient *extract_Max()
    {
        if (size == 0)
        {
            return nullptr;
        }
        Patient *max = new Patient(heap[0]);
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return max;

    }

    void print_heap()
    {
        if (size == 0)
        {
            return;
        } else
        {
            cout << "Heap: [ ";
            for (int i = 0; i < size; ++i)
                cout << heap[i].getName() << ", ";
            cout << "]" << endl;
        }

    }

};

//int main()
//{
//    Patient patients[]{
//            {"Alice",   80,  1},
//            {"Bob",     90,  2},
//            {"Charlie", 70,  3},
//            {"David",   85,  4},
//            {"Eve",     90,  5},
//            {"Frank",   75,  6},
//            {"Grace",   95,  7},
//            {"Henry",   80,  8},
//            {"Ivy",     70,  9},
//            {"Jack",    100, 10}
//    };
//    MaxHeap myHeap;
//    for (auto &patient: patients)
//    {
//        cout << "Inserting: " << patient.getName() << endl;
//        myHeap.insert(patient);
//        myHeap.print_heap();
//    }
//    cout << "\nTreatment Order:" << endl;
//    Patient *p;
//    while ((p = myHeap.extract_Max()) != nullptr)
//    {
//        cout << "Treating: " << p->getName() << ' ' << p->getSeverity() << ',' << p->getArrival() << endl;
//        delete p;
//    }
//}
