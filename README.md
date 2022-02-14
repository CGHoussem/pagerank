# PageRank Implementation in C

## Description
C implementation of the PageRank algorithm. Used as an individual practical work for the *High Performance Computing* course held at UVSQ-ISTY, engineering's degree in Computer Science.

### Dataset format
This program will run on any dataset that respects the following dataset format:
> \# commented line  
> NODE_1[TAB]NODE_2  
> NODE_1[TAB]NODE_2  
> NODE_1[TAB]NODE_2  
> NODE_1[TAB]NODE_2

NODE_x: should be an integer respecting the datatype uint (unsigned integer) of 4 bytes.

## Benchmark
The benchmark is done by running the pagerank algorithm on multiple dumping factor values ranging from 0 to 1 with a step equals to 0.025.  
The performance critrea is the time taken for each run. The performance written on the output file is the average of 10 (MAX_AVG_ITER) runs.

### Benchmark output data format
The benchmark output data file will have the following format (this is sample data):
> \# damping; time; iters; node; prob  
> 0.000; 0.00000080; 1; 6; 0.142857  
> 0.025; 0.00000110; 4; 1; 0.145243  
> 0.050; 0.00000160; 4; 1; 0.147638  
> 0.075; 0.00000180; 5; 1; 0.150042  
> . . .    
> 0.925; 0.00003570; 149; 5; 0.224650  
> 0.950; 0.00005390; 226; 5; 0.243999  
> 0.975; 0.00010860; 457; 5; 0.287968  
> 1.000; 0.00011870; 500; 6; 0.525783

The 1st value describes: the damping factor chosen for the run.  
The 2nd value describes: the time took for the algorithm to find the solution or reachs it's maximum iterations.  
The 3rd value describes: the numbers of iterations took to converge or the maximum if it didn't.  
The 4th value describes: the most important node found.  
The 5th value describes: the highest probability found (equivalent to the most important node).

## Code
### utility  scripts

- **gnuplot_script.gnu**: a gnuplot script to plot the performance graph.
- **run_script.sh**: a bash script that installs the *gnuplot* library if it's not installed, compiles the project, runs it using the input filename (passed as an argument) and creates the performance graph (*plot.png*).

### main program
There are 3 different compilation versions:
1. default (used to have a simple summary output)
2. debug (used to verbose debugging outputs)
3. benchmark (used to run a benchmark)

## Compilation & Execution
### Compilation
* default version: `make clean && make`
* debug version: `make clean && make debug`
* benchmark version: `make clean && make benchmark`

### Execution
* default version: `./program [filename] [max_iter] [damping_factor]`
* debug version: `./program [filename] [max_iter] [damping_factor]`
* benchmark version: `./benchmark [filename]`

## Extra
You are able to run the plotting script using the gnuplot script on a data file respecting the benchmark data output format: `gnuplot gnuplot_script.gnu`

