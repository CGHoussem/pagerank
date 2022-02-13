#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void transpose_matrice(float **matrice, uint N, float **result)
{
    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++)
            result[j][i] = matrice[i][j];
    
}

void mult_mat_vec(float **matrice, float *vector, uint N, float *result) 
{
    for (size_t i = 0; i < N; i++)
    {
        float sum_i = 0;
        for (size_t j = 0; j < N; j++)
            sum_i += vector[j] * matrice[i][j];
        result[i] = sum_i;
    }
}

long find_in_array(long *arr, uint n, uint v)
{
    long res = -1;
    for (size_t i = 0; i < n; i++)
        if (arr[i] == v) {
            res = i;
            break;
        }
    return res;
}

float *allocate_fvector(uint N)
{
    return (float *)malloc(sizeof(float) * N);
}

uint *allocate_uivector(uint N)
{
    return (uint *)malloc(sizeof(uint) * N);
}

void init_fvector(float *vector, uint N, float v)
{
    for (size_t i = 0; i < N; i++)
        vector[i] = v;
}

void init_uivector(uint *vector, uint N, uint v)
{
    for (size_t i = 0; i < N; i++)
        vector[i] = v;
}

float **allocate_matrix(uint N)
{
    char err = 0;
    float **matrix = (float **)malloc(N * sizeof(float *));
    // error handling
    if (matrix == NULL)
        return NULL;

    for (size_t i = 0; i < N; i++) {
        matrix[i] = allocate_fvector(N);
        // error2 handling
        if (matrix[i] == NULL) {
            err = 1;
            break;
        }
    }

    // error2 handling
    if (err == 1) {
        free(matrix);
        matrix = NULL;
    }
    return matrix;
}

float **reallocate_matrix(float **matrix, uint N)
{
    char err = 0;
    matrix = (float **)realloc(matrix, N * sizeof(float *));
    // error handling
    if (matrix == NULL)
        return NULL;

    for (size_t i = 0; i < N; i++)
    {
        matrix[i] = (float *)realloc(matrix[i], N * sizeof(float));
        // error2 handling
        if (matrix[i] == NULL)
        {
            err = 1;
            break;
        }
    }

    // error2 handling
    if (err == 1)
    {
        free(matrix);
        matrix = NULL;
    } 

    return matrix;
}

void init_matrix(float **matrix, uint N, float v)
{
    for (size_t i = 0; i < N; i++)
        init_fvector(matrix[i], N, 0.0f);
}

void free_matrix(float **matrix, uint N)
{
    for (size_t i = 0; i < N; i++)
        free(matrix[i]);
    free(matrix);
}
