set grid
set term png large size 1280,720 enhanced font 'Verdana,16'
set output "plot.png"
set multiplot layout 2,2 rowsfirst
set datafile separator ";"
set boxwidth 0.5 relative
set style fill solid
set offset graph 0, graph 0, graph 0.1
set style line 1 lc rgb 'red' pt 7 ps 2
set style line 2 lc rgb 'blue' pt 6
set style line 3 lc rgb '0x00AA00' pt 6
set style line 4 lc rgb 'gold' pt 7
# GRAPH 1
# set output "time_damping.png"
set title "Execution Times by Damping factor"
set xlabel "Damping factor"
set ylabel "Time (sec)"
plot "benchmark.dat" u 1:2 w lp ls 2 notitle
# GRAPH 2
# set output "iters_damping.png"
set title "Number of iterations to converge by Damping factor"
set ylabel "# Iteration"
plot "benchmark.dat" u 1:3 w lp ls 3 notitle
# GRAPH 3
# set output "nodes_damping.png"
set title "The important nodes found by Damping factor"
set ylabel "Node Index"
plot "benchmark.dat" u 1:4 w p ls 1 notitle
# GRAPH 4
# set output "prob_damping.png"
set title "Probabilities of the important node found by Damping factor"
set ylabel "Probabiliy of the Node"
plot "benchmark.dat" u 1:5 w lp ls 4 notitle
unset multiplot