#include <iostream>
#include <cstdlib>
#include <thread> // Include std::thread for C++11 threading support
#include <chrono>

using namespace std::chrono;

// Struct to hold data for each thread
struct ThreadData {
    int* v1;
    int* v2;
    int* v3;
    int start;
    int end;
};

// Function to generate a random vector of given size
void randomVector(int vector[], int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100;
    }
}

// Function executed by each thread to perform element-wise addition
void parallelElementWiseAddition(ThreadData* data) {
    for (int i = data->start; i < data->end; i++) {
        data->v3[i] = data->v1[i] + data->v2[i];
    }
}

int main() {
    unsigned long size = 100000000;
    srand(time(0));
    int* v1 = (int*)malloc(size * sizeof(int));
    int* v2 = (int*)malloc(size * sizeof(int));
    int* v3 = (int*)malloc(size * sizeof(int));

    randomVector(v1, size);
    randomVector(v2, size);

    auto start = high_resolution_clock::now();

    int numThreads = std::thread::hardware_concurrency();
    std::thread threads[numThreads]; // Using std::thread instead of pthread_t
    ThreadData threadData[numThreads];
    int chunkSize = size / numThreads;
    int startIdx = 0;

    // Create threads and divide the work among them
    for (int i = 0; i < numThreads; ++i) {
        int endIdx = (i == numThreads - 1) ? size : startIdx + chunkSize;
        threadData[i] = { v1, v2, v3, startIdx, endIdx };
        threads[i] = std::thread(parallelElementWiseAddition, &threadData[i]); // Using std::thread constructor
        startIdx = endIdx;
    }

    // Join all threads
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join(); // Joining threads
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    free(v1);
    free(v2);
    free(v3);

    return 0;
}
