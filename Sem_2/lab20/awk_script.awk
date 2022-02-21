BEGIN {
	print "Loading...";
}

{
	if (age > 0) {
		if ($2 > age) {
                	dif=$2-age
                	print $1,"is",dif,"years older than",age,"years"
        	}
	} else {
		if ($2 < -age) {
        	        dif=-age-$2
              		print $1,"is",dif,"years younger than",-age,"years"
	        }

	}

}

END {
	print "Closing..."
}
