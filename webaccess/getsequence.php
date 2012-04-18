<HTML>
<head>

<style type="text/css" media="screen">
  
  .sequence_repeats_table
  {
  }

  .sequence_repeats
  {
    width: 1152px;
    display: table-row;
  }

  .sequence_id
  {
//    height:100%;
    width: 148px;
    border:1px;
    border-style:solid;
    border-color:black;
    display: table-cell;
  }
 
  .sequence_repeat_outer
  {
    width:1000px;
//    height:100%;
    border:1px;
    border-style:solid;
    border-color:black;
    display: table-cell;
  }
 
  .sequence_repeats_sequence
  {
    float:left;
//    height:100%;
    width: 598px;
//    border-right:1px;
//    border-left:0px;  
//    border-top:0px;  
//    border-bottom:0px;  
//    border-style:solid;
//    border-color:black;
  }

  .sequence_repeats_locations
  {
    float:right;
//    height:100%;
    width: 398px;
  //  border:1px;
  //  border-style:solid;
  //  border-color:black;
  }

</style>

</head>

<BODY>

<?php

set_time_limit(0);

include('config.php');

$max_repeats = $_GET['max_repeats'];
$max_length   = $_GET['max_length'];

$pos_str = substr($_GET['position'],1);
list($xpos,$ypos) = split(",",$pos_str);

$length  = ceil($xpos/(600/$max_length));
$repeats = floor((600-$ypos)/(600/$max_repeats));
$file    = $_GET['base_name'];
$breaks  = $_GET['breaks'];

if(strcmp($breaks,"true") == 0) {
  $breaksymbol="35";
} else {
  $breaksymbol="";
}

echo "repeats: " . $repeats . "<br>";
echo "length: " . $length . "<br>";

$fname = $repeat_tools_base . '/temp/' . $file . '.getsequence.' . $length . '.' . $repeats;
$a = exec('nice rm -rf ' . $fname . '*' );
echo $a;
$a = exec('nice ' . $repeat_tools_base . '/getsequence ' . $repeat_tools_base . '/temp/' . $file . '.flat.breaks ' . $repeats . ' ' . $length . ' '  . $repeat_tools_base . '/temp/' . $file . '.flat.breaks.contig_starts ' . $breaksymbol . ' > ' . $fname);
echo $a;


#echo "<center><IMG SRC=\"./temp/" . $file . '.getsequence.' . $length . '.' . $repeats . ".png\"><BR>";
echo "<center><BR><A HREF=\"./temp/" . $file . '.getsequence.' . $length . '.' . $repeats . "\">Repeats in Fasta format</A><BR>";
#$a = exec('nice ' . $repeat_tools_base . '/getsequencefasta2html ' . $fname . ' ' . $fname . '.html');
$a1 = exec('nice ' . $repeat_tools_base . '/getsequence2graphdata ' . $fname . ' ' . $repeat_tools_base . '/temp/' . $file);

$fh = fopen($fname . '.html', 'r') or die("ERROR 2: Can't open file, please contact new299@zepler.org");

$html = fread($fh, filesize($fname . '.html')) ;
fclose($fh);

?>
<BR><BR>
<div class="sequence_repeats_table">
<div class="sequence_repeats">
  <div class ="sequence_id">
    ID
  </div>
  <div class="sequence_repeat_outer">
    <div class="sequence_repeats_sequence">
      Sequence
    </div>
    <div class ="sequence_repeats_locations">
      Positions
    </div>
  </div>
</div>

<?php 

echo $html;

?>

<div  class="sequence_repeats">
</div>
</div>
<br>
<br>
<h2>Contig names</h2>
<?php

$fh = fopen($repeat_tools_base . '/temp/' . $file . '.contignames.html','r') or die("ERROR 3: Can't open file, please contact new299@zepler.org");
$contigshtml = fread($fh, filesize($repeat_tools_base . '/temp/' . $file . '.contignames.html')) ;
fclose($fh);
echo $contigshtml;

?>

</HTML>
</BODY>
