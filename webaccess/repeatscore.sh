#! /bin/bash
export filename=$1.score
export repeat_tools_base=$2
export repeatscore_repeats=$3
export repeatscore_length=$4
export repeatscore_raw=$5
export repeatscore_reverse=$6

echo "<BR>filename: " $filename "<BR>"
echo "<BR>repeat_tools_base2: " $repeat_tools_base "<BR>"
echo "<BR>repeatscore_repeats: " $repeatscore_repeats "<BR>"
echo "<BR>repeatscore_length: " $repeatscore_length "<BR>"
echo "<BR>repeatscore_raw: " $repeatscore_raw "<BR>"
echo "<BR>repeatscore_reverse: " $repeatscore_reverse "<BR>"

if [ "$repeatscore_raw" != "on" ];
then 
  echo "<BR>Parsing with fasta2flat<BR>"
  $repeat_tools_base/fasta2flat $1 $1.flat $1.contignames $1.configpositions > $1.fasta2flat.stdout &> $1.fasta2flat.stderr
  # $repeat_tools_base/getcontignames.i686 $1 > $1.contignames

  if [ "$repeatscore_reverse" = "on" ];
  then
    mv $1.flat $1.flat.forward
    $repeat_tools_base/reverseflat $1.flat.forward $1.reverse.flat
    # $repeat_tools_base/fasta2flat $1.reverse $1.reverse.flat
    awk '{ print $0 " REVERSE STRAND";}' $1.contignames > $1.contignames.reverse
    cat $1.contignames.reverse >> $1.contignames

    cp $1.flat.forward $1.flat.bothstrands
    echo "" >> $1.flat.bothstrands
    cat $1.reverse.flat >> $1.flat.bothstrands
    cp $1.flat.bothstrands $1.flat
  fi

  export repeatscore_breaksymbol="35"
  echo "<BR>Adding #s with repchar<BR>"
  $repeat_tools_base/repchar $1.flat $1.flat.breaks
  $repeat_tools_base/symbolpos $1.flat.breaks > $1.flat.breaks.contig_starts
  wc -c < $1.flat.breaks >> $1.flat.breaks.contig_starts

fi

if [ "$repeatscore_raw" == "on" ];
then
  cp $1 $1.flat.breaks
  echo "no name" > $1.contignames
  wc -c < $1.flat.breaks > $1.flat.breaks.contig_starts
  echo "<BR>Copying raw file for repeatscore<BR>"
  export repeatscore_breaksymbol=""
  echo "<BR>Num breaks: " $repeatscore_nobreaks "<BR>"
fi

echo "<BR>Run repeatscore<BR>"

awk 'BEGIN{n=0;};{print "<A NAME=\"" n "\">" n ": " $0 "</A><BR>";n++;};' $1.contignames > $1.contignames.html

$repeat_tools_base/repeatscore_printonly $1.flat.breaks $3 $4 $repeatscore_breaksymbol > $filename.unrotated
$repeat_tools_base/rotate_matrix $filename.unrotated > $filename

#$repeat_tools_base/rotate_matrix $filename.unrotated > $filename.untrimmed
#$repeat_tools_base/trim_matrix   $filename.untrimmed $4 $3 > $filename

export repeatscore_xtics=1
export repeatscore_length=`head -n 1 $filename | wc -w`
comparison=`echo $repeatscore_length '>= 50'  | bc`
if [ $comparison -gt 0 ] ;
then
  export repeatscore_xtics=10
fi

comparison=`echo $repeatscore_length '>= 1000'  | bc`
if [ $comparison -gt 0 ] ;
then
  export repeatscore_xtics=100
fi

comparison=`echo $repeatscore_length '>= 10000'  | bc`
if [ $comparison -gt 0 ] ;
then
  export repeatscore_xtics=1000
fi


export repeatscore_ytics=1

comparison=`echo $repeatscore_repeats '>= 50'  | bc`
if [ $comparison -gt 0 ] ;
then
  export repeatscore_ytics=10
fi

comparison=`echo $repeatscore_repeats '>= 1000'  | bc`
if [ $comparison -gt 0 ] ;
then
  export repeatscore_ytics=100
fi

comparison=`echo $repeatscore_repeats '>= 10000'  | bc`
if [ $comparison -gt 0 ] ;
then
  export repeatscore_ytics=1000
fi

head -n 1 $filename | awk 'BEGIN{RS=" "; n=1;}; {if($1) {print n " " $1; n++;}}' > $filename.unique
/usr/local/bin/gnuplot $repeat_tools_base/unique_plot.gnu

TERM=ansi
/usr/local/bin/gnuplot $repeat_tools_base/repeatscore_plot_nolabels.gnu
/usr/local/bin/gnuplot $repeat_tools_base/repeatscore_plot_labels.gnu
#$repeat_tools_base/bbfix $1.score.nolabels.eps
$repeat_tools_base/bbfix $1.score.labels.eps
#/usr/bin/convert -density 150 $1.score.nolabels.eps $1.score.nolabels.png
/usr/bin/convert -crop 57x600+0+0 $1.score.labels.left.png $1.score.labels.left.crop.png
/usr/bin/convert -crop 600x40+0+560 $1.score.labels.bottom.png $1.score.labels.bottom.crop.png
/usr/bin/convert -crop 116x600+483+0 $1.score.labels.left.png $1.score.labels.colorbox.crop.png
#/usr/bin/convert -crop 100x600+490+0 $1.score.labels.colorbox.png $1.score.labels.colorbox.crop.png
