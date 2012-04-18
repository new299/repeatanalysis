

BEGIN{   FS=","; n=1; entry[0] = 0;}

FILENAME != "-" {
	# load each glossary entry into an array
	entry[n] = $0;
        n++;
	next
} 

FILENAME == "-" {if(substr($1,0,1) != "#") {print entry[$1] + $2;} else {print $0;}}

