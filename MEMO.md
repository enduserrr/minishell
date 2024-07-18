# MEMO

## NEXT UP:
* Check parsing funcs and correct references
* Prototype funcs needed from main to parse
* Signal handling
* Briefs for parsing funcs and a recap

## APPROX EXEC ORDER:
### 1. Main(int ac, char **av):
  * Check for verbose
  * Init shell & configure terminal
  * Welcome message
  * Return (run_shell());

### 2. Run_shell(int status, char *execute):
  * Runs and loops input/tokenize/parse/validate/execute/free loop until a told otherwise
  * Gets prompt
  * Calls readline
  * Listens for kill signals

### 3. Handle_line(int status, char *line):
  * Tokenizer(status, line) -> sets tokens ready
  * Parse(status, tokens) -> parses token
  * If verbose set true, put_tkns()
  * Unset env
  * Return (execute);

### 4. Tokenizer(int status, char *s):
  * Line (from readline)
  * Gets tokens with split
  * Free line (rl)

### 5. Parse(status, tokens):
  * Evaluates tokens (define operators, redirs, syntax & commands)
  * Removes quotes
  * If verbosed tokens prints the full ones
  * Create_commands(tokens, cmd_table) -> allocs cmd_table and creates cmds

### 6. Unset_env():

### 7. Execute(int status, t_cmd *commands)
  * Execute with one builtin or creates redirections -> pipe handling -> executing cmd's
  * Free's cmd's and returns return value
  * 

## USEFUL FUNCTIONS
### Asprintf 
`int asprintf(char **strp, const char *fmt, ...);`
* Allocates sufficient memory for a formatted string with a terminating null character in the end which is to be stored to the buffer given to it as an argument
* Return nb of the bytes allocated or -1 if an error occured
* Buffer must be free'd manually.

### String Insert
`char *str_insert(char *s, char *c, size_t start, size_t len);`
* Insert string into an other string starting from specified location for the specified length.
* Allocates space needed for the new longer string

## About token id's
(“2>&1” redirects STDERR to STDOUT. Since “2>1” means “redirect STDERR to file 1,” “&1” is added to refer to STDOUT, not a file.)
### HEREDOC
  * Means heredocument and is a way to include a block of text within bash script
  * Can contain commands, variable or any text
  * No worrying about special characters
### HEREDOC_EOF
  * Heredocuments end of file
### OUT_A_RED (>>)
  * Redirects the output to append it to target file or to create it if it doesn't exist
### OUT_A_FILE
  * The file to append the redirected output

## DEFINITIONS
### Verbose
  *

## Useful commands
### GIT BRANCH
  * git fetch origin / fetch the remote branches
  * git branch -r /list all remote branches
  * git branch /list local branches
  * git checkout -b <new_branch> /create a new branch and switch to it
  * git checkout <brach_name> /switch to a branch
  * git branch --delete <branchname> /delete local branch
  * git push origin <branch_name> /push to remote branch
  * git pull origin <branch_name> /pull remote branch (first create matching local one)
  * git ls-files /list files in git
When working on the project start by fetching remote branches, creating them locally with 'checkout' and switching to the correct one to work inside of. Then when pushing 'git push origin <branch_name>'
### GIT HISTORY
* Temporary:
  * git log /find the commit hash you want to go to
  * git checkout <commit_hash> /temporarily checkout an earlier commit
  * git checkout <branch_name> /return back to the current version

*  Permanently:
  * git revert <commit_hash> /revert to older commit specified by it's hash
  * git push origin <branch_name> /push it to make it current

* CCP Policy (rewrite history):
  * git reset --hard <commit_hash> /reset to a specified older commit
  * git push origin <brach_name> --force /force push it to current branch NOT REVERSABLE (prolly).