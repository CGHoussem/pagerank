#pragma once

void transpose_matrice(float **matrice, uint N, float **result);

void mult_mat_vec(float **matrice, float* vector, uint N, float* result);

long find_in_array(long *arr, uint n, uint v);

float *allocate_fvector(uint N);

uint *allocate_uivector(uint N);

void init_fvector(float *vector, uint N, float v);

void init_uivector(uint *vector, uint N, uint v);

float **allocate_matrix(uint N);

float **reallocate_matrix(float** matrix, uint N);

void init_matrix(float **matrix, uint N, float v);

void free_matrix(float **matrix, uint N);
