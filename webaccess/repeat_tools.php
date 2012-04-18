<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<link rel="stylesheet" href="./4g.css">
<title>The 4G Project</title>

<style type="text/css" media="screen">
  .floatleft
  {
    float: left;
  }

  .xaxis_outer 
  {
    height:100px;
    width:658px;
  }  
  
  .topspace_outer 
  {
    height:1px;
    width:658px;
  }

  .topspace
  {
    float: right;
    height:10px;
    width:602px;
    background:white;
  }

  .top_outer 
  {
    height:1px;
    width:658px;
  }

  .top
  {
    float: right;
    width:602px;
    height:1px;
    background:black;
  }
  
  .xaxis
  {
    width: 602px;
    float: right;
  }

  .plot
  {
    float:center;
    margin:auto;
    height:652px;
    width:773px;
    background:white;
  }
  
  .plot2
  {
    width:600px;
    height:600px;
    float:center;
    margin:auto;
  }

  .downloads
  {
    margin:auto;
    width:757px;
    float:center;
    text-align:center;
    align:center;
  }

</style>

</head>
<body>
<div class="mainpage">
<div class="header">

<!-- <img align="left" src="http://www.4g.soton.ac.uk/images/4G_150.png" alt="4G Logo">
-->

<div class="header_text">
Repeat Analysis Tool

</div>

</div>

<?php
  set_time_limit(900);


  include('config.php');

  if($_POST['entrytype'] == 'upload') {
    if($_FILES['userfile']['size'] <= 0) {
      echo "<H2>Error no or zero size file supplied, please try again.<br><br><br><br><br><br></H2>";
      exit(0);
    }
    $temp = tempnam($repeat_tools_base . "/temp","rep");
    $b = exec('cp ' . $_FILES['userfile']['tmp_name'] . ' ' . $temp);
    $rs_raw = "off";
  }

  if($_POST['entrytype'] == 'direct') {
    $rs_raw = "off";
    $temp = tempnam($repeat_tools_base . "/temp","rep");
    $fh = fopen($temp, 'w') or die("Can't open file, please contact new299@zepler.org");
    fwrite($fh, $_POST['direct']) ;
    fclose($fh);
    
    exec($repeat_tools_base . "/fasta2flat " . $temp . " " . $temp . ".tflat &> " . $temp . ".fasta2flat_res");

    $a = exec('grep -c unknown ' . $temp . '.fasta2flat_res');
    if($a == "1") {
      exec('mv ' . $temp . ' ' . $temp . '.original');
      exec('sed \':a; $!N;s/[^a-z,A-Z,0-9]//g;ta\' ' . $temp . '.original > ' . $temp);
      $rs_raw = "on";
    }
  }

    $rs_repeatsmax = $_POST['repeat_max'];
    $rs_lengthmax  = $_POST['length_max'];
    $rs_reverse    = $_POST['reverse'];

    if($rs_raw == "off") {
      $rs_breaks="true";
    } else {
      $rs_breaks="false";
    }

    if($rs_reverse == "") {
      $rs_reverse="off";
    }

    // Process file with GNUPlot
    $a = exec('nohup nice ' . $repeat_tools_base . '/repeatscore.sh ' . $temp . ' ' . $repeat_tools_base . ' ' . $rs_repeatsmax . ' ' . $rs_lengthmax . ' ' . $rs_raw . ' ' . $rs_reverse . ' > ' . $repeat_tools_base . '/debug');
#  echo $a;

?>

<div class="content">
<?php

    $a = exec('grep -c unknown ./temp/' . basename($temp) .'.fasta2flat_res');
    if($a == "1" && $repeatscore_raw == "off") {
      echo 'Unable to parse this fasta of genbank file. <br>';
      echo 'Please check the file or contact the author at: new299@zepler.org';
      exit(0);
    }

    // Draw plot, and links to data

      echo '<div class="content_text">';
        echo '<div class="plot">';
          echo '<div>';

            echo '<div class="topspace_outer">';
              echo '<div class="topspace">';
              echo '</div>';
            echo '</div>';

            echo '<div class="top_outer">';
              echo '<div class="top">';
              echo '</div>';
            echo '</div>';

            echo '<div class="floatleft">';
              echo '<IMG SRC="./temp/'. basename($temp) .'.score.labels.left.crop.png" border=0>';
            echo '</div>';

            $max_repeats = exec('wc -l ./temp/' . basename($temp) . '.score | awk \'{print $1}\''); 
            $max_length  = exec('head ./temp/'  . basename($temp) . '.score -n 1 | wc -w | awk \'{print $1}\''); 
            echo '<div class="floatleft">';

              echo '<a target="_blank" href="getsequence.php?base_name=' . basename($temp) . '&breaks=' . $rs_breaks . '&max_repeats=' . $max_repeats . '&max_length=' . $max_length . '&position=">';
                echo '<IMG ISMAP SRC="./temp/'. basename($temp) .'.score.nolabels.png" border=0 id="repeatscore">';
              echo '</a>';
            echo '</div>';

            echo '<div class="floatleft">';
              echo '<IMG SRC="./temp/'. basename($temp) .'.score.labels.colorbox.crop.png" border=0>';
            echo '</div>';
          echo '</div>';

          echo '<div class="xaxis_outer">';
            echo '<div class="xaxis">';
              echo '<IMG WIDTH=602px SRC="./temp/'. basename($temp) .'.score.labels.bottom.crop.png" border=0>';
            echo '</div>';
          echo '</div>';
        echo '</div>';

        
        echo '<BR><div class="plot2">';
        echo '<IMG SRC="./temp/' . basename($temp) . '.score.unique.png"  border=0>';
        echo '</div>';

        echo '<div class="downloads">';
           echo '<BR><BR><A HREF="./temp/'. basename($temp) . '.score.labels.eps">Repeat score (EPS)</A><BR>';
           echo '<A HREF="./temp/'. basename($temp) . '.score">Repeat score (Raw matrix)</A><BR>';
           echo '<A HREF="./temp/'. basename($temp) . '.score.unique.eps">Unique substrings (EPS)</A><BR>';
           echo '<A HREF="./temp/'. basename($temp) . '.score.unique">Unique substrings (Raw data)</A><BR><BR>';
           echo '<A HREF="./index.html">Process another?</A><BR><BR><BR>';
        echo '</div>';
    echo '</div>';
?>
</div></div>
</HTML>
</BODY>
