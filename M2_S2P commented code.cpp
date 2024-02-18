#include <chrono> // Including the chrono library for time-related functionality
#include <cstdlib> // Including the cstdlib library for functions like malloc and srand
#include <iostream> // Including the iostream library for standard input/output operations
#include <time.h> // Including the time.h library for time-related functions

using namespace std::chrono;
using namespace std;

// Function to generate a random vector of given size
void randomVector(int vector[], int size) {
  // Looping through each element of the vector
  for (int i = 0; i < size; i++) {
    // Generating a random number between 0 and 99 and assigning it to the current element
    vector[i] = rand() % 100;
  }
}

int main() {
  unsigned long size = 100000000; // Defining the size of the vectors
  srand(time(0)); // Seeding the random number generator with the current time
  int *v1, *v2, *v3; // Declaring pointers to hold the vectors
  auto start = high_resolution_clock::now(); // Starting the timer
  
  // Dynamically allocating memory for the vectors
  v1 = (int *)malloc(size * sizeof(int));
  v2 = (int *)malloc(size * sizeof(int));
  v3 = (int *)malloc(size * sizeof(int));
  
  // Generating random vectors
  randomVector(v1, size);
  randomVector(v2, size);

  // Performing element-wise addition of the vectors
  for (int i = 0; i < size; i++) {
    v3[i] = v1[i] + v2[i];
  }
  
  auto stop = high_resolution_clock::now(); // Stopping the timer
  auto duration = duration_cast<microseconds>(stop - start); // Calculating the duration of the operation
  
  // Outputting the duration of the operation
  cout << "Time taken by function :" << duration.count() << " microseconds"
       << endl;
  return 0; // Returning 0 to indicate successful execution
}
