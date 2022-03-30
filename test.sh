if [[ $1 == 1 ]]
then
	TEST="ls"
elif [[ $1 == 2 ]]
then
	TEST="echo Test| cat -e |wc -c"
elif [[ $1 == 3 ]]
then
	TEST="cat Makefile -e|grep .c | wc"
elif [[ $1 == 4 ]]
then
	TEST="ls| wc	  | 		cat -e"
elif [[ $1 == 5 ]]
then
	TEST="env  	| 	grep SHELL"
elif [[ $1 == 6 ]]
then
	TEST="cat << 	e"
elif [[ $1 == 7 ]]
then
	TEST="cat << 	e |wc"
elif [[ $1 == 8 ]]
then
	TEST=ls
elif [[ $1 == 9 ]]
then
	TEST="cat <<e"
else
	echo Bad argument
fi

clear
make DEBUG=1
echo $TEST | valgrind --leak-check=full ./minishell
