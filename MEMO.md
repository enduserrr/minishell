# MEMO

## COPY:
* Parse dir
* Token dir
* Makefile
* Executtio() func
* Signals

## NEXT UP:
* Prompt
  * Prompt to display infront of input (readline(prompt))
* Rl_history:
  * Adding and removing previous inputs from rl
* Redirectioning:
  * Redirecting
* Signal handling:
  * For ctr + c, ctr + d and SIG_IGN ctr -/
  * Event hook, HEREDOC handling

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
  * ft_tokens(status, line) -> sets tokens ready
  * ft_parse(status, tokens) -> parses token
  * If verbose set true, put_tokens()
  * Unset env
  * Return (execute);

### 4. ft_tokens(int status, char *s):
  * Line (from readline)
  * Gets tokens with split
  * Free line (rl)

### 5. ft_parse(status, tokens):
  * Evaluates tokens (define operators, redirs, syntax & commands)
  * Removes quotes
  * If verbosed tokens prints the full ones
  * Create_commands(tokens, cmd_table) -> allocs cmd_table and creates cmds

### 6. Unset_env():

### 7. Execute(int status, t_cmd *commands)
  * Execute with one builtin or creates redirections -> pipe handling -> executing cmd's
  * Free's cmd's and returns return value

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