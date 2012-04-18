set ylabel "Unique substrings u"
set xlabel "Substring length l"
set xtics 1,`echo $repeatscore_xtics`
set title ""
set key off

set terminal postscript eps color
set output "`echo $filename`.unique.eps"
plot "`echo $filename`.unique" using 1:2 with lines

set terminal png size 600,600 font "arial" 8
set output "`echo $filename`.unique.png"
plot "`echo $filename`.unique" using 1:2 with lines
