# DEBUG NOTES

## TOKENIZING
### Token id set correctly?
* Print out token id's

## PARSING
`valgrind --tool=memcheck -s ./minishell "echo 'Hello, World | grep 'Hello' | wc -l"`

### Memory allocation (out of reach access)
* Function path:
  * main/parse/create_cmd/alloc_cmd/new_cmd/ft_calloc/malloc
  * main/tokenizer/get_tkns/ft_strdup/ft_calloc/malloc
* Possible reasons
  * Unitialized memory from malloc
  * Incorrect allocation size (faulty length calculations)
  * Static variable in get_next() in tkns.c
* Mapping allocs:
  * 1x create_user_path() in expand_help.c
  * 2x new_cmd() in parse_utils.c
  * 1x new_token in tkns.c
  * 1x main() in main.c
* Solving:
  * alloc_cmd(): new token count function for alloccing (in pare_help.c)
    * Error count decreased from 13 -> 6!
  * Replasing mallocs with ft_calloc
  * Ft_strdup fixed to correctly allocate mem also for an empty string
    * Error count from 6 -> 0!
