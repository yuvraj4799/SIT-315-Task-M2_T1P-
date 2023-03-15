#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <pthread.h>
using namespace std;
using namespace std::chrono;

const int N = 100;       
const int NUM_THREADS = 2;
int A[N][N], B[N][N], C[N][N];

void initialize_matrix(int matrix[N][N])
{
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
}

void *thread_function(void *thread_arg)
{
    int thread_id = *(int *)thread_arg;
    int num_rows_per_thread = N / NUM_THREADS;
    int start_row = thread_id * num_rows_per_thread;
    int end_row =
        (thread_id == NUM_THREADS - 1) ? N : start_row + num_rows_per_thread;

    for (int i = start_row; i < end_row; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

int main()
{
    initialize_matrix(A);
    initialize_matrix(B);

    auto start_time = high_resolution_clock::now();

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, (void *)&thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop_time - start_time);

    cout << "Execution time: " << duration.count() << " nanoseconds\n";
    return 0;
}