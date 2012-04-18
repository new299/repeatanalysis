set size 4,1

set xlabel "Position"
set ylabel "Clustering"
set terminal postscript color lw 3 'phv'

set output 'pos.ps'
plot 'pos.cluster' with points pointtype 31 pointsize 2
