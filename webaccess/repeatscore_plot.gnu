#set pm3d map
#set size square
set logscale cb  
set palette defined ( 0 "#FFFFFF", 0 "#0000FF", 1 "#ffff00", 2 "#ff0000" )
#set palette defined (0 0 0 0, 1 0 0 1, 3 0 1 0, 4 1 0 0, 6 1 1 1)
#set palette model RGB

#set palette defined 

unset ylabel 
unset xlabel 
unset cblabel 
unset colorbox
#unset border
set yrange [-0.5:`echo "$(echo $(wc -l < $filename) - 0.5 | bc -l)"`]
set xrange [0.5:`echo "$(echo $(head $filename -n 1 | wc -w) + 0.5 | bc -l)"`]
unset xtics 
unset ytics
set tmargin 0
set bmargin 0
set lmargin 0
set rmargin 0
unset title
set terminal png size 600,600 
set output "`echo $filename`.nolabels.png"
plot "`echo $filename`" matrix using (1+$1):($2):(1+$3) notitle with image
