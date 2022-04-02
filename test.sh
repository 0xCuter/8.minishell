case $1 in
   0) TEST='echo $'
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
   8) TEST='echo \$SHELL'
   ;;
   9) TEST="echo '\$SHELL'"
   ;;
   10) TEST=
   ;;
   11) TEST="echo ' \$SHELL'"
   ;;
   12) TEST="echo '	a	\$SHELL'"
   ;;
   13) TEST='echo "	a	$SHELL'
   ;;
   14) TEST='echo "	a	$SHELL"'
   ;;
   15) TEST='echo "a$SHELL"'
   ;;
   16) TEST='echo YOLO$THISISALONGVAR"+astring here yep $SHELL $e$SHELL"$LANG'
   ;;
   17) TEST="./a.out \$t\"     this 'test' \$SHELL\"LOL' another one \"\$SHELL\""
   ;;
   *) echo Bad argument
   ;;
esac

make DEBUG=1 && clear && echo $TEST | valgrind --leak-check=full ./minishell
