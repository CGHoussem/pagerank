#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "utils.h"
#include "pagerank.h"
#include "structures.h"

#define MAX_NODES   10000

int main(int argc, char** argv) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *dataset_file = NULL;
    uint N = 0;
    unsigned char max_iter = 100;
    float dumping_factor = 0.85f;
    
    if (argc < 4)
    {
        fprintf(stderr, "Usage: ./main [filename] [max_iter] [dumping_factor]\n");
        exit(EXIT_FAILURE);
    }

    // read the dataset file
    dataset_file = fopen(argv[1], "r");
    if (dataset_file == NULL)
    {
        fprintf(stderr, "Error reading file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    // set the number of max iterations
    max_iter = atoi(argv[2]);

    // set damping factor
    dumping_factor = atof(argv[3]);

    // allocation and intializing of the adjacency  matrix
    #ifdef DEBUG
    printf("allocating & initializing the adjacency matrix..\n");
    #endif
    float **matrix_a = allocate_matrix(MAX_NODES);
    // error handling
    if (matrix_a == NULL) {
        fclose(dataset_file);
        fprintf(stderr, "Error allocating adjacency matrix\n");
        exit(EXIT_FAILURE);
    }
    init_matrix(matrix_a, MAX_NODES, 0.0f);

    // counting and mapping nodes to the adjacency matrix
    #ifdef DEBUG
    printf("counting and mapping nodes to the adjacency matrix..\n");
    #endif
    long nodes[MAX_NODES];
    for (size_t i = 0; i < MAX_NODES; i++)
        nodes[i] = -1;
    size_t node_index = 0;
    while ((read = getline(&line, &len, dataset_file)) != -1)
    {
        // if first character of the line starts with '#' ignore it
        if (*line == '#')
            continue;

        // extraction of both node ids
        uint from_node = atoi(strtok(line, "\t"));
        uint to_node = atoi(strtok(NULL, "\t"));

        // mapping
        long new_from_node = find_in_array(nodes, MAX_NODES, from_node);
        if (new_from_node == -1)
        {
            nodes[node_index] = from_node;
            new_from_node = node_index;
            node_index += 1;
        }
        long new_to_node = find_in_array(nodes, MAX_NODES, to_node);
        if (new_to_node == -1)
        {
            nodes[node_index] = to_node;
            new_to_node = node_index;
            node_index += 1;
        }

        // marking an edge connection
        matrix_a[new_from_node][new_to_node] = 1.0f;
    }
    N = node_index;

    printf("There are %d nodes\n", N);

    // reallocat adjacency  matrix (freeing up (MAX_NODES - N) blocks)
    matrix_a = reallocate_matrix(matrix_a, N);
    // error handling
    if (matrix_a == NULL) 
    {
        fclose(dataset_file);
        fprintf(stderr, "Error reallocating (reducing size) adjacency matrix\n");
        exit(EXIT_FAILURE);
    }

    #ifdef DEBUG
    // print the adjacency matrix
    printf("\t> The adjacency matrix is:\n");
    for (size_t i = 0; i < N; i++) {
        printf("\t|");
        for (size_t j = 0; j < N; j++)
            printf(" %.2f |", matrix_a[i][j]);
        printf("\n");
    }
    #endif

    // initializing the transpose of matrix
    #ifdef DEBUG
    printf("allocating & initializing the transpose of matrix..\n");
    #endif
    float **matrix_at = allocate_matrix(N);
    // error handling
    if (matrix_at == NULL)
    {
        free_matrix(matrix_a, N);
        fclose(dataset_file);
        fprintf(stderr, "Error allocating transpose matrix\n");
        exit(EXIT_FAILURE);
    }
    init_matrix(matrix_at, N, 0.0f);

    // initializing the outputs vector
    #ifdef DEBUG
    printf("allocating & initializing the outputs vector..\n");
    #endif
    uint *out_vector = allocate_uivector(N);
    // error handling
    if (out_vector == NULL)
    {
        free_matrix(matrix_a, N);
        free_matrix(matrix_at, N);
        fclose(dataset_file);
        fprintf(stderr, "Error allocating the outputs vector\n");
        exit(EXIT_FAILURE);
    }
    init_uivector(out_vector, N, 0);
    
    // counting 
    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++)
            if (matrix_a[i][j] != 0.0f)
                out_vector[i] += 1;

    #ifdef DEBUG
    // printing the outputs vector
    printf("\t> The outputs vector is: [");
    for (size_t i = 0; i < N; i++) {
        printf("%d", out_vector[i]);
        if (i != (N-1))
            printf(", ");
    }
    printf("]\n");
    #endif

    // making the transition matrix
    #ifdef DEBUG
    printf("making the transition matrix..\n");
    #endif
    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++)
            if (matrix_a[i][j] != 0)
                matrix_a[i][j] /= out_vector[i];

    #ifdef DEBUG
    // printing the transition matrix
    printf("\t> The transition matrix is:\n");
    for (size_t i = 0; i < N; i++)
    {
        printf("\t|");
        for (size_t j = 0; j < N; j++)
            printf(" %.2f |", matrix_a[i][j]);
        printf("\n");
    }
    #endif

    #ifdef DEBUG
    printf("computing the transpose of matrix..\n");
    #endif
    transpose_matrice(matrix_a, N, matrix_at);

    #ifdef DEBUG
    // printing the transpose matrix
    printf("\t> The transpose of the matrix is:\n");
    for (size_t i = 0; i < N; i++)
    {
        printf("\t|");
        for (size_t j = 0; j < N; j++)
            printf(" %.2f |", matrix_at[i][j]);
        printf("\n");
    }
    #endif

    // initializing of the initial vector
    // chosing a starting node
    // srand(time(0));
    // uint starting_node = rand() % N;
    // printf("\t> starting node index is: #%d\n", starting_node);
    #ifdef DEBUG
    printf("initializing the initial vector\n");
    #endif
    double p[N];
    for (size_t i=0; i < N; i++)
        p[i] = 1.0f / N;
        // p[i] = (i == starting_node) ? 1.0f : 0.0f;
    
    #ifdef DEBUG
    // printing the initial vector
    printf("\t> The initial vector is: [");
    for (size_t i = 0; i < N; i++) {
        printf("%.2f", p[i]);
        if (i!=N-1) printf(", ");
    }
    printf("]\n");
    #endif

    // PageRank benchmark
    clock_t begin = clock();

    uint iter = pagerank(N, matrix_at, p, dumping_factor, max_iter);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    // showing output
    printf("\nNumber of iterations to converge: %d\n", iter);
    printf("The runtime to converge: %f seconds\n", time_spent);
    printf("Final Pagerank values:\n\t[");
    for (size_t i=0; i<N; i++) {
        printf("%.2f", p[i]);
        if (i != N-1)
            printf(", ");
    }
    printf("]\n");

    // verification
    float sum = 0.0f;
    for (size_t i = 0; i < N; i++)
        sum += p[i];
    printf("\t> verification sum: %f\n", sum);

    float max_v = -1.0f;
    unsigned short max_i = 0;
    for (size_t i = 0; i < N; i++)
    {
        if (p[i] > max_v) {
            max_v = p[i];
            max_i = i;
        }
    }
    printf("\t> max probability is: %f\n", max_v);
    printf("\t> most important node is: %d\n", max_i);
    
    // freeing unecessary memory and closing the dataset files
    #ifdef DEBUG
    printf("\nclosing and freeing resources..\n");
    #endif
    if (line)
        free(line);
    fclose(dataset_file);

    free(out_vector);
    free_matrix(matrix_a, N);
    free_matrix(matrix_at, N);


    return EXIT_SUCCESS;
}