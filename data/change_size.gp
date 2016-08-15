unset key
set xrange [4:11]
set yrange [0.9:1.3]
set xlabel "XY Size [mm]"
set ylabel "Rate"

plot "change_size.txt" u 1:4:5 w yerrorbar

set term postscript eps color
set out "change_size_rate.eps"
replot

reset
