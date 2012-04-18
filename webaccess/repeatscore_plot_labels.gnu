set pm3d map
#set size square
set logscale cb
set palette defined ( 0 "#FFFFFF", 0 "#0000FF", 1 "#ffff00", 2 "#ff0000" )
set ylabel "Repetitions r"
set xlabel "Substring length l"
set cblabel "Repeatscore log(C(l,r)+1)"
set yrange [-0.5:`echo "$(echo $(wc -l < $filename) - 0.5 | bc -l)"`]
set xrange [0.5:`echo "$(echo $(head $filename -n 1 | wc -w) + 0.5 | bc -l)"`]
set xtics 1,`echo $repeatscore_xtics`
set ytics 0,`echo $repeatscore_ytics`
set title ""
set terminal postscript eps color
set output "`echo $filename`.labels.eps"
plot "`echo $filename`" matrix using (1+$1):($2):(1+$3) notitle with image

set lmargin 8
set rmargin 4
set tmargin 0
set bmargin 0

set terminal png size 600,600 font "Helvetica" 8
set output "`echo $filename`.labels.left.png"
plot "`echo $filename`" matrix using (1+$1):($2):(1+$3) notitle with image

set lmargin 0 
set rmargin 0
set tmargin 0
set bmargin 3 
unset cblabel
unset colorbox

set terminal png size 600,600 font "Helvetica" 8
set output "`echo $filename`.labels.bottom.png"
plot "`echo $filename`" matrix using (1+$1):($2):(1+$3) notitle with image

#set colorbox size 100, 600
set colorbox 
set cblabel "Repeatscore log(C(l,r)+1)"
set terminal png size 600,600 font "Helvetica" 8
unset xtics 
unset ytics
unset xlabel
unset ylabel
set lmargin 0
set rmargin 3 
set tmargin 0
set bmargin 3

set output "`echo $filename`.labels.colorbox.png"
plot "`echo $filename`" matrix using (1+$1):($2):(1+$3) notitle with image

