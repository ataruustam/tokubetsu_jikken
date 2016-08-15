reset
set xrange [0:1.1]
set xlabel "Distance [mm]"
set ylabel "Efficiency [%]"
unset key
plot "efficiency_change.txt" u 1:4:5 w yerrorbar

set term postscript eps
set out "efficiency_change2.eps"
replot
reset
