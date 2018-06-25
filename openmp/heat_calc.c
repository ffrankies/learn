/**
 * Heat Calculation problem.
 */
#include "common.h"

#define ARR_SIZE 20000
#define N_THREADS 4

double cx = 0.1;
double cy = 0.1;

/**
 * Peeks into a heatmap
 */
void peek(double heatmap[][ARR_SIZE]) {
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            printf("%lf ", heatmap[row][col]);
        }
        printf("\n");
    }
}

/**
 * Draws the heatmap onto the given 2d array.
 * @param double [][ARR_SIZE] heatmap - the heatmap to be drawn
 */
void draw_heatmap(double heatmap[][ARR_SIZE]) {
    for (int row = 0; row < ARR_SIZE; ++row) {
        for (int col = 0; col < ARR_SIZE; ++col) {
            double value = row;
            if (value > col) {
                value = col;
            }
            if (value > (ARR_SIZE - 1 - row)) {
                value = ARR_SIZE - 1 - row;
            }
            if (value > (ARR_SIZE - 1 - col)) {
                value = ARR_SIZE - 1 - col;
            }
            heatmap[row][col] = value * value;
        }
    }
}

/**
 * Performs the calculation sequentially
 */
void sequential_calc(double heatmap[ARR_SIZE][ARR_SIZE], double temp[ARR_SIZE][ARR_SIZE]) {
    printf("======Sequential Calculation======\n");
    clock_t start = clock();
    for (int row = 1; row < ARR_SIZE-1; ++row) {
        for (int col = 1; col < ARR_SIZE-1; ++col) {
            double tempx = cx * (heatmap[row][col-1] + heatmap[row][col+1] - 2 * heatmap[row][col]);
            double tempy = cy * (heatmap[row-1][col] + heatmap[row+1][col] - 2 * heatmap[row][col]);
            temp[row][col] = heatmap[row][col] + tempx + tempy;
        }
    }
    printf("Calculation took %ld clock ticks\n", clock() - start);
    peek(temp);
}

/**
 * Performs the calculation in parallel
 */
void parallel_calc(double heatmap[ARR_SIZE][ARR_SIZE], double temp[ARR_SIZE][ARR_SIZE]) {
    printf("======Parallel Calculation======\n");
    omp_set_num_threads(N_THREADS);
    clock_t start = clock();
    #pragma omp parallel for
    for (int row = 1; row < ARR_SIZE-1; ++row) {
        for (int col = 1; col < ARR_SIZE-1; ++col) {
            double tempx = cx * (heatmap[row][col-1] + heatmap[row][col+1] - 2 * heatmap[row][col]);
            double tempy = cy * (heatmap[row-1][col] + heatmap[row+1][col] - 2 * heatmap[row][col]);
            temp[row][col] = heatmap[row][col] + tempx + tempy;
        }
    }
    printf("Calculation took %ld clock ticks\n", clock() - start);
    peek(temp);
}

int main(int argc, char* argv[]) {
    static double heatmap[2][ARR_SIZE][ARR_SIZE];
    draw_heatmap(heatmap[0]);
    peek(heatmap[0]);
    sequential_calc(heatmap[0], heatmap[1]);
    parallel_calc(heatmap[0], heatmap[1]);
}