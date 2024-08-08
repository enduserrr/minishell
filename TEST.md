# TESTING

## 1: simple command with absolute path without options | ALL OK!
* /bin/ls OK!
* empty command OK!
* only spaces OK!
* only tabs OK!


## 2: arguments | ALL OK!
* /bin/ls (with arguments) OK!
* /bin/ls -la OK!
* /bin/ls -l OK!

## 3: echo | ALL OK!
* echo hello OK!
* echo hello ripuli OK!
* echo -n hello OK!
* echo -n hello ripuli OK!
* echo | cat -e OK!

## 4: exit | ALL OK!
* exit OK! (EXIT)
* exit 4 OK! (EXIT)
* exit r OK! (ERR MESSAGE)
* exit 4 4 4 OK! (ERR MESSAGE)
* exit g 4 OK! (EXIT & ERR MESSAGE)

## 5: return values | ALL OK!
* /bin/ls --> echo $? OK!
* ls -la | grep mini --> echo $? OK!
* cd .. --> echo $? OK!
* cd    --> echo $? OK!

## 6: signals | ALL OK!
* ctrl c OK!
  * parent OK!
  * child OK!
  * heredoc OK!
* ctrl \ OK!
  * parent OK!
  * child OK!
  * heredoc OK!
* ctrl D
  * parent OK!
  * child OK!
  * heredoc OK!

## 7: douple quotes | ERRORS!
* echo "hello "" ERROR!
* echo "" hello "" OK!
* cat "  infile""
* ls -la | " grep -hello " OK!
* echo "cat.lol.c | cat > lol.c" OK!
* echo "hello" "" | cat -e ERROR!

## 8: singlequotes
-

## 9: env
* env

## 10: export
* export HELO= helo
* export HELLO=helo=helo
* export hello===hello
* export hello=jello kello=kello
* [10:29 AM]
* 11: unset
* unset MAIL
* unset PWD
* unset PATH

## 12: relative path

Execute commands but this time use a relative path.
Repeat multiple times in different directories with a complex relative path (lots of ..).

## 13: environment path
* unset PATH
* export PATH=/home/eleppala/bin:/usr/local/sbin:/usr/local/bin

## 14: redirections | OK kaikki paitsi wc -l 
* < infile | grep hello ERROR!
* < infile | grep world ERROR!
* < infile | grep hello > out ERROR!
* < infile | grep hello >> out ERROR!
* < infile | wc -l >> out ERROR!
* ls -la >> out OK!
* ls > out OK!
* echo hello > out OK!
* echo helo helo > out OK!
* echo -n hello >> out OK!
* << EOF OK!
* echo -n "Moro" > out OK!

## 14: pipes | ERRORS!
* 'cat infile | grep bla | more' OK!
* cat infile | grep hello | grep world OK!
* cat infile | wc -l OK!
* cat Makefile | wc -w OK!
* ls -la | grep eleppala | grep 2020 | grep shiet OK!
* ls -la | grep eleppala | grep 2020 | grep mini OK!
* cat nofile | grep jee | more OK!
* cat nofile | grep gg | more OK!
* < Makefile | grep .c > out ERROR!

## 15: go grazy | ERRORS!
* type something ctrl c --> enter OK!
* navigate with arrow up and down OK!
* not working commands like pfsfjrjiorsiojs ororjorsjprs OK!
* cat | cat | ls ERROR!
* long commands with multiple args OK!

## 16: environment variables | ALL OK!
* Execute echo with some environment variables ($variable) as arguments. OK!
* Check that $ is interpreted as an environment variable. OK!
* Check that double quotes interpolate $. OK!
* Check that USER exists. Otherwise, set it. OK?
* echo "$USER" should print the value of the USER variable. OK!
* echo $PATH | cat -e OK!
* echo "$USER" | cat -e OK!
