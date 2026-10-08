#ifndef MERGESORT_H
#define MERGESORT_H

// Our own merge sort (no std::sort).
// It's a template so the same code can sort resources, reservations, etc.
// comesBefore(a, b) returns true if a should go before b.

// merges two sorted halves: arr[left..middle] and arr[middle+1..right]
template <typename T>
void mergeHalves(T arr[], int left, int middle, int right,
                 bool (*comesBefore)(const T&, const T&)) {
    int leftSize = middle - left + 1;
    int rightSize = right - middle;

    // copy each half into its own temp array
    T* leftHalf = new T[leftSize];
    T* rightHalf = new T[rightSize];

    for (int i = 0; i < leftSize; i++) {
        leftHalf[i] = arr[left + i];
    }
    for (int j = 0; j < rightSize; j++) {
        rightHalf[j] = arr[middle + 1 + j];
    }

    int i = 0;     // spot in leftHalf
    int j = 0;     // spot in rightHalf
    int k = left;  // spot in arr

    // keep taking whichever front item should go first
    while (i < leftSize && j < rightSize) {
        // on a tie the left one goes first, so equal items keep their order
        if (comesBefore(rightHalf[j], leftHalf[i])) {
            arr[k] = rightHalf[j];
            j++;
        }
        else {
            arr[k] = leftHalf[i];
            i++;
        }
        k++;
    }

    // one half ran out, copy whatever is left in the other one
    while (i < leftSize) {
        arr[k] = leftHalf[i];
        i++;
        k++;
    }
    while (j < rightSize) {
        arr[k] = rightHalf[j];
        j++;
        k++;
    }

    delete[] leftHalf;
    delete[] rightHalf;
}

// splits the range in half, sorts each half, then merges them back
template <typename T>
void mergeSortRange(T arr[], int left, int right,
                    bool (*comesBefore)(const T&, const T&)) {
    // 0 or 1 item is already sorted
    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;

    mergeSortRange(arr, left, middle, comesBefore);
    mergeSortRange(arr, middle + 1, right, comesBefore);
    mergeHalves(arr, left, middle, right, comesBefore);
}

// this is the one to call: mergeSort(array, size, compareFunction)
// O(n log n) every time
template <typename T>
void mergeSort(T arr[], int size, bool (*comesBefore)(const T&, const T&)) {
    if (size < 2) {
        return;
    }
    mergeSortRange(arr, 0, size - 1, comesBefore);
}

#endif
