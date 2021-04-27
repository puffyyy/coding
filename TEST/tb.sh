function max()
{
	$max=$1
	$t2=$2
	$t3=$3

	if [ max -lt t2 ];then
		max=t2;
	fi
	if [ max -lt t3 ];then
		max=t3;
	fi
	return max;
}

max 1 2 3
echo $?
exit;
