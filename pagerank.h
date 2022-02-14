#pragma once

#include <stdlib.h>
#include "structures.h"

PR pagerank(uint N, float **matrix, double *p, float d, uint max_iter);
