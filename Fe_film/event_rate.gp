#event_rateのグラフを描く
reset
set ylabel "Ratio"
set xlabel "Thickness [mm]"
f(x)=a*(1-exp(-b*x))
a=-1
c=15
b=50
fit f(x) "event_rate5.txt" via a,b
g(x)=f(x)/a;
plot "event_rate5.txt" using 1:(($2)/a) title "Emission rate", g(x) title "Fit"


set terminal postscript eps color
set out "event_rate4_6.eps"
replot
reset
