#include <iostream>

using namespace std;

//int minSegmentFlips(const int* arr, const int size, int k)
//{
//    int flips = 0;
//    int* pendingFlips = new int[size]();
//    int currFlips = 0;
//
//    for (int i = 0; i < size; ++i)
//    {
//        currFlips ^= pendingFlips[i];
//
//        int currentBit = arr[i] ^ currFlips;
//
//        if (currentBit == 0)
//        {
//            if (i + k > size)
//            {
//                delete[] pendingFlips;
//                return -1;
//            }
//
//            flips++;
//
//            currFlips ^= 1;
//
//            if (i + k < size)
//            {
//                pendingFlips[i + k] ^= 1;
//            }
//        }
//    }
//
//    delete[] pendingFlips;
//    return flips;
//}

int minSegmentFlips(const int *arr, const int size, int k)
{
    int flips = 0;
    int *pendingFlips = new int[size + 1]();

    int currFlips = 0;

    for (int i = 0; i < size; ++i)
    {
        currFlips += pendingFlips[i];

        int currentBit = arr[i];

        if (currFlips % 2 == 1)
        {
            currentBit = 1 - currentBit;
        }

        if (currentBit == 0)
        {
            if (i + k > size)
            {
                delete[] pendingFlips;
                return -1;
            }

            flips++;
            currFlips++;
            pendingFlips[i]++;
            pendingFlips[i + k]--;
        }
    }

    delete[] pendingFlips;
    return flips;
}

//int main()
//{
//    int arr1[] = {0, 1, 0};
//    int size1 = sizeof(arr1) / sizeof(arr1[0]);
//    cout << "Minimum segment flips of {0,1,0} with k = 1: " << minSegmentFlips(arr1, size1, 1) << endl;
//
//    int arr2[] = {1,1,0,0,1,1,1,0};
//    int size2 = sizeof(arr2) / sizeof(arr2[0]);
//    cout << "Minimum segment flips of {1,1,0} with k = 2: " << minSegmentFlips(arr2, size2, 2) << " (Not possible with k = 2)" << endl;
//
//    int arr3[] = {0, 0, 0, 1, 0, 1, 1, 0};
//    int size3 = sizeof(arr3) / sizeof(arr3[0]);
//    cout << "Minimum segment flips of {0,0,0,1,0,1,1,0} with k = 3: " << minSegmentFlips(arr3, size3, 3) << endl;
//}