# MEMO

## Approx exec order:
1. Main
  * Check for verbose
  * Init shell & configure terminal
  * Welcome message
  * Return (run_shell());

2. Run_shell()
  * Runs and loops input/tokenize/parse/validate/execute/free loop until a told otherwise
  * Gets prompt
  * Calls readline
  * Listens to kill signal from user input (readline

3. Handle_line()
  * Tokenizer(status, line) -> sets tokens ready
  * Parse(status, tokens) -> parses token
  * If verbose set true, put_tkns()
  * Unset env
  * Return (execute);

4. Tokenizer
  * Line (from readline)
  * Gets tokens with split
  * Free line (rl)

5. Parse(status, tokens)
  * Evaluates tokens (define operators, redirs, syntax & commands)
  * Removes quotes
  * If verbosed tokens prints the full ones
  * Create_commands(tokens, cmd_table) -> allocs cmd_table and creates cmds

6. Unset env

7. Execute(status, commands)
  * Execute with one builtin or creates redirections -> pipe handling -> executing cmd's
  * Free's cmd's and returns return value
  * 



