#include <chrono>
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <time.h>

using namespace std::chrono;
using namespace std;

void randomVector(int vector[], int size) {
  for (int i = 0; i < size; i++) {
    vector[i] = rand() % 100;
  }
}

struct ThreadArgs {
  int* v1;
  int* v2;
  int* v3;
  int start;
  int end;
};

void* vectorAddition(void* arg) {
  ThreadArgs* args = (ThreadArgs*)arg;
  int* v1 = args->v1;
  int* v2 = args->v2;
  int* v3 = args->v3;
  int start = args->start;
  int end = args->end;

  for (int i = start; i < end; i++) {
    v3[i] = v1[i] + v2[i];
  }

  pthread_exit(NULL);
}

int main() {
  unsigned long size = 100000000;
  srand(time(0));
  int* v1 = (int*)malloc(size * sizeof(int));
  int* v2 = (int*)malloc(size * sizeof(int));
  int* v3 = (int*)malloc(size * sizeof(int));
  randomVector(v1, size);
  randomVector(v2, size);

  int num_threads = 4; // You can adjust the number of threads as needed
  pthread_t threads[num_threads];
  ThreadArgs thread_args[num_threads];

  auto start = high_resolution_clock::now();

  int chunk_size = size / num_threads;
  for (int i = 0; i < num_threads; i++) {
    thread_args[i].v1 = v1;
    thread_args[i].v2 = v2;
    thread_args[i].v3 = v3;
    thread_args[i].start = i * chunk_size;
    thread_args[i].end = (i == num_threads - 1) ? size : (i + 1) * chunk_size;
    pthread_create(&threads[i], NULL, vectorAddition, (void*)&thread_args[i]);
  }

  for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

  free(v1);
  free(v2);
  free(v3);

  return 0;
}
