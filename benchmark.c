#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "utils.h"
#include "pagerank.h"
#include "benchmark.h"
#include "structures.h"

#define MAX_NODES 		10000
#define MAX_ITERATIONS	500
#define MAX_AVG_ITER	10

int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	FILE *dataset_file = NULL;
	uint N = 0;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: ./benchmark [filename]\n");
		exit(EXIT_FAILURE);
	}

	// read the dataset file
	dataset_file = fopen(argv[1], "r");
	if (dataset_file == NULL)
	{
		fprintf(stderr, "Error reading file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	// allocation and intializing of the adjacency matrix
	float **matrix_a = allocate_matrix(MAX_NODES);
	// error handling
	if (matrix_a == NULL)
	{
		fclose(dataset_file);
		fprintf(stderr, "Error allocating adjacency matrix\n");
		exit(EXIT_FAILURE);
	}
	init_matrix(matrix_a, MAX_NODES, 0.0f);

	// counting and mapping nodes to the adjacency matrix
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

	// reallocat adjacency  matrix (freeing up (MAX_NODES - N) blocks)
	matrix_a = reallocate_matrix(matrix_a, N);
	// error handling
	if (matrix_a == NULL)
	{
		fclose(dataset_file);
		fprintf(stderr, "Error reallocating (reducing size) adjacency matrix\n");
		exit(EXIT_FAILURE);
	}

	// initializing the transpose of matrix
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
	uint *outlink = allocate_uivector(N);
	// error handling
	if (outlink == NULL)
	{
		free_matrix(matrix_a, N);
		free_matrix(matrix_at, N);
		fclose(dataset_file);
		fprintf(stderr, "Error allocating the outputs vector\n");
		exit(EXIT_FAILURE);
	}
	init_uivector(outlink, N, 0);

	// counting
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < N; j++)
			if (matrix_a[i][j] != 0.0f)
				outlink[i] += 1;

	// making the transition matrix
	for (size_t i = 0; i < N; i++) {
		if (outlink[i] == 0) {
			for (size_t j = 0; j < N; j++)
				matrix_a[i][j] = 1.0f / N;
		} else {
			for (size_t j = 0; j < N; j++)
				if (matrix_a[i][j] != 0)
					matrix_a[i][j] /= outlink[i];
		}
	}

	transpose_matrice(matrix_a, N, matrix_at);

	double p[N];
	for (size_t i = 0; i < N; i++)
		p[i] = 1.0f / N;

	// PageRank benchmark
	uint benchmark_n = 41;
	double dumping_factors[benchmark_n];
	double ts_avg[benchmark_n];
	uint iters_to_converge[benchmark_n];
	uint important_node_index[benchmark_n];
	double important_node_prob[benchmark_n];
	double x = 0;
	for (size_t i = 0; i < benchmark_n; i++)
	{
		dumping_factors[i] = x;
		x += 0.025;
	}
	
	for (size_t i = 0; i < benchmark_n; i++)
	{
		double sum = 0.0;
		double d = dumping_factors[i];
		PR pr;
		for (size_t it = 0; it < MAX_AVG_ITER; it++)
		{
			clock_t begin = clock();
			pr = pagerank(N, matrix_at, p, d, MAX_ITERATIONS);
			clock_t end = clock();
			sum += (double)(end - begin) / CLOCKS_PER_SEC;
		}
		iters_to_converge[i] = pr.nbr_iter_convergence;
		important_node_index[i] = pr.important_node_index;
		important_node_prob[i] = pr.important_node_prob;
		ts_avg[i] = sum / MAX_AVG_ITER;
	}

	// creating the benchmark data file
	FILE *output_file = fopen("benchmark.dat", "w");
	fprintf(output_file, "# damping; time; iters; node; prob\n");
	for (size_t i = 0; i < benchmark_n; i++)
		fprintf(output_file, "%.3f; %.8lf; %d; %d; %lf\n", dumping_factors[i], ts_avg[i], iters_to_converge[i], important_node_index[i], important_node_prob[i]);
	fclose(output_file);

	// freeing unecessary memory and closing the dataset file
	if (line)
		free(line);
	fclose(dataset_file);

	free(outlink);
	free_matrix(matrix_a, N);
	free_matrix(matrix_at, N);

	return EXIT_SUCCESS;
}