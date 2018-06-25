/**
 * Using OpenMP for array processing.
 */

#include "common.h"

#define ARR_SIZE 29999
int N_THREADS = 8;

/**
 * Initializes a 2d array, where each element = i * j
 * @param double * array - the array to be initialized
 */
void init_2d_array(double array[][ARR_SIZE]) {
    for (int row = 0; row < ARR_SIZE; ++row)
    {
        for (int col = 0; col < ARR_SIZE; ++col)
        {
            array[row][col] = row * col * 1.0;
        }
    }
}

/**
 * Performs a sequential sum across the 2d array.
 */
void sequential_impl(double data[][ARR_SIZE]) {
    printf("======Sequential implementation======\n");
    init_2d_array(data);
    clock_t start = clock();
    long double sum = 0;
    for (int row = 0; row < ARR_SIZE; ++row) {
        for (int col = 0; col < ARR_SIZE; ++col) {
            sum += data[row][col];
        }
    }
    printf("Took %ld clock ticks to run.\n", clock() - start);
    printf("Sum = %Lf\n", sum);
}

int main(int argc, char *argv[]) {
    printf("hello!\n");
    static double data[ARR_SIZE][ARR_SIZE];  // Without static, get seg fault
    sequential_impl(data);
    return 0;
}