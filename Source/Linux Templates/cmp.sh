while true; do
    let "t+=1"
    ./gen
    ./
    ./check
    diff -b .out check.out
    if [ $? -eq 0 ]; then echo "$t:ac!"
    else {
	echo "$t:wa!"
 	break	
    }
    fi 
done
