#include "pagerank.h"

#include <stdio.h>
#include <math.h>

#define EPSILON 1e-06

PR pagerank(uint N, float **matrix, double *p, float d, uint max_iter)
{
	unsigned char running = 1;
	uint iter = 0;
	double p_new[N];
	double p_old[N];
	PR pr;

	// create a copy of p
	for (size_t i = 0; i < N; i++) 
		p_old[i] = p[i];

	while (running)
	{
		// init the vector p_new
		for (size_t i = 0; i < N; i++)
			p_new[i] = 0.0f;

		// update the vector p_new (without the dumping factor)
		for (size_t i = 0; i < N; i++)
			for (size_t j = 0; j < N; j++)
				p_new[i] += matrix[i][j] * p_old[j];

		// update the vector p_new (with the dumping factor)
		for (size_t i = 0; i < N; i++)
			p_new[i] = d * p_new[i] + (1.0f - d) / N;

		// checking if we have to stop or not
		float error = 0.0f;
		for (size_t i = 0; i < N; i++)
			error += fabs(p_new[i] - p_old[i]);

		if (error < EPSILON || iter + 1 >= max_iter)
			running = 0;

		// update the vector p
		for (size_t i = 0; i < N; i++)
			p_old[i] = p_new[i];

		iter += 1;
	}

	pr.nbr_iter_convergence = iter;

	// search for the important node
	double max_v = -1.0f;
    uint max_i = 0;
    for (size_t i = 0; i < N; i++)
    {
        if (p_old[i] >= max_v) {
            max_v = p_old[i];
            max_i = i;
        }
    }
	pr.important_node_index = max_i;
	pr.important_node_prob = max_v;

	return pr;
}