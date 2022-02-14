#pragma once
#include <stdio.h>
#include <stdlib.h>

// used to read and map nodes from a file
typedef struct mapping
{
	uint node_idx;
	uint new_node_idx;
} mapping;

// used for the benchmark
typedef struct PR
{
    uint nbr_iter_convergence;
    uint important_node_index;
    double important_node_prob;
} PR;
