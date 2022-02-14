set grid
set term png
set output "plot.png"
set multiplot layout 2,1 rowsfirst
set datafile separator ";"
set boxwidth 0.5 relative
set style fill solid
set offset graph 0, graph 0, graph 0.1
# GRAPH 1
set title "Execution Time by Damping factor"
set xlabel "Damping factor"
set ylabel "Time (sec)"
plot "benchmark.dat" u 1:2 w lp notitle, \
    "benchmark.dat" u 1:2 w errorbars notitle
# GRAPH 2
set title "Iterations to converge by Damping factor"
set ylabel "Iteration"
plot "benchmark.dat" u 1:3 w lp notitle
unset multiplot