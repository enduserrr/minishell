# DEBUG NOTES

## PARSING

### LEAKS

### ALLOC ISSUES (incorrect reads)
* Function path:
  * main/parse/create_cmd/alloc_cmd/new_cmd/ft_calloc/malloc
  * main/tokenizer/get_tkns/ft_strdup/ft_calloc/malloc
* Possible reasons
  * Unitialized memory from malloc
  * Incorrect allocation size (faulty length calculations)
  * Static variable in get_next() in tkns.c
* Mapping allocs:
  * 1x create_user_path() in expand_help.c
  * 2x new_cmd() in parse_help.c
  * 1x new_token in tkns.c
  * 1x main() in main.c
* Solving:
  * Replasing mallocs with ft_calloc
  * tilde_expander(): is 'create_user_path' workin correctly?
  * alloc_cmd(): new token count function for alloccing (in pare_help.c)
    * Error count decreased from 13 -> 6!
  * ft_expand(): 