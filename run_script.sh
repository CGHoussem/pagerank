#!/bin/bash
clear

# check the existance of the library "gnuplot"
if ! [[ $(command -v gnuplot) ]]; then
    sudo apt-get update --fix-missing
    sudo apt-get install gnuplot
fi

# check for the filename argument
if [ $# -eq 0 ]; then
    echo "Usage: ./run_script [filename]"
else
    # run the script
    make benchmark
    ./benchmark $1
    gnuplot gnuplot_script
fi
