#include "pagerank.h"

#include <stdio.h>
#include <math.h>

#define EPSILON 1e-06

uint pagerank(uint N, float **matrix, double *p, float d, uint max_iter)
{
	unsigned char running = 1;
	uint iter = 0;
	double p_new[N];
	double p_old[N];

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

	return iter;
}