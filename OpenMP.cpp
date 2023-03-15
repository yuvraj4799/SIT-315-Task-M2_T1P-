#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <omp.h>

using namespace std;
using namespace std::chrono;

const int N = 100; // matrix size

void initialize_matrix(int matrix[N][N])
{
    // initialize matrix with random values
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
}

void multiply_matrices(int A[N][N], int B[N][N], int C[N][N])
{
// perform matrix multiplication in parallel using OpenMP
#pragma omp parallel for
    for (int i = 0; i < N; i++)
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
}

int main()
{
    int A[N][N], B[N][N], C[N][N];

    // initialize matrices A and B with random values
    initialize_matrix(A);
    initialize_matrix(B);

    // calculate execution time
    auto start_time = high_resolution_clock::now();
    // perform matrix multiplication
    multiply_matrices(A, B, C);
    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop_time - start_time);

    // print execution time
    cout << "Execution time: " << duration.count() << " nanoseconds\n";

    return 0;
}