/*
 * Estimating the value of Pi using the circle-in-square method.
 */
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <omp.h>
#include <time.h>

int N_ATTEMPTS = 10000000;
int N_THREADS = 4;

/**
 * Estimates the value of Pi serially
 */
void serial_impl() {
    printf("======Serial Implementation======\n");
    clock_t start = clock();
    double n_in_circle = 0;
    for (int n = 0; n < N_ATTEMPTS; ++n) {
        double x = random() / (double) RAND_MAX;
        double y = random() / (double) RAND_MAX;
        if (x * x + y * y < 1) {
            n_in_circle++;
        }
    }
    double pi = 4 * n_in_circle / N_ATTEMPTS;
    printf("Estimated value of pi = %f, actual value = 3.14159\n", pi);
    printf("Took %ld clock ticks to execute\n", clock() - start);
}

/**
 * Estimates the value of Pi in parallel using OpenMP
 */
void parallel_impl() {
    printf("======Parallel Implementation======\n");
    clock_t start = clock();
    omp_set_num_threads(N_THREADS);
    double n_in_circle = 0;
    #pragma omp parallel for reduction(+: n_in_circle)
    for (int n = 0; n < N_ATTEMPTS; ++n) {  // The number of loops is automatically split b/n all threads
        if (random() < 10000) {  // Show that for loop is executing in parallel
            printf("n = %d, current thread = %d\n", n, omp_get_thread_num());
        }
        double x = random() / (double) RAND_MAX;
        double y = random() / (double) RAND_MAX;
        if (x * x + y * y < 1) {
            // #pragma omp critical - no longer needed, because with reduction, a local copy is created for each thread
            n_in_circle++;
        }
    }
    double pi = 4 * n_in_circle / N_ATTEMPTS;
    printf("Estimated value of pi = %f, actual value = 3.14159\n", pi);
    printf("Took %ld clock ticks to execute\n", clock() - start);
}


int main(int argc, char* argv[]) {
    srandom(1995);  // Seed the random number generator
    serial_impl();
    parallel_impl();
}