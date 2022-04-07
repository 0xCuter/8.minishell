# Testser for minishell
# Launch with ./test.sh [test_num] or ./test.sh 0 to execute all tests
# Negative number tests are bound to fail with "KO"

case $1 in
   -2) TEST='echo "	a	$SHELL'
   ;;
   -1) TEST='echo \$SHELL'
   ;;
   0) make DEBUG=1 && clear
      i=1
      while [ $i -lt 17 ]
      do
         ./test.sh $i
         echo
         true $(( i++ ))
      done
   ;;
   1) TEST='ls'
   ;;
   2) TEST='echo Test| cat -e |wc -c'
   ;;
   3) TEST='cat Makefile -e|grep .c | wc'
   ;;
   4) TEST='ls| wc	  | 		cat -e'
   ;;
   5) TEST='env  	| 	grep SHELL'
   ;;
   6) TEST='echo $a SHELL|cat -e'
   ;;
   7) TEST='echo $ SHELL|cat -e'
   ;;
   8) TEST='cat test.c <test | wc'
   ;;
   9) TEST="echo '\$SHELL'"
   ;;
   10) TEST='echo test.c <test | pwd'
   ;;
   11) TEST="echo ' \$SHELL'"
   ;;
   12) TEST="echo '	a	\$SHELL'"
   ;;
   13) TEST='cat test.c <test | pwd'
   ;;
   14) TEST='echo "	a	$SHELL"'
   ;;
   15) TEST='echo "a$SHELL"'
   ;;
   16) TEST='echo YOLO$THISISALONGVAR"+astring here yep $SHELL $e$SHELL"$LANG'
   ;;
   17) TEST="echo \$t\"     this 'test' \$SHELL\"LOL' another one \"\$SHELL\""
   ;;
   *) echo Bad argument
   ;;
esac

echo "Test: $1"
echo "Leak result:"
echo $TEST | valgrind --leak-check=full ./minishell 2>&1 | grep "lost:"
echo
MINI_RES=`echo $TEST | ./minishell 2>&-`
echo "Minishell result:"
echo "$MINI_RES"
BASH_RES=`echo $TEST | /bin/bash 2>&-`
echo "Bash result:"
echo "$BASH_RES"

if [[ $MINI_RES == $BASH_RES ]]
then
   echo -en "\e[1;33m"
   echo "-- OK --"
   echo -en "\e[0m"
else
   echo -en "\e[1;31m"
   echo "-- KO --"
   echo -en "\e[0m"
fi
