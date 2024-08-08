# MEMO
## DO
* Simplify or remove custom_error()
  * Remove unused error macros from parse.h
  * Remove errno.h if not in use
* Possibly replace S_ISDIR from expand()
* Exit codes
* CTRL-D in heredoc
  * bash: warning: here-document at line 1 delimited by end-of-file (wanted `EOF')

### To do:
* Signals
  * Separate func and call for child process SIGINT too avoid double prompt from Ctr+C
  * Individually call signal() funcs in heredoc, pipes and simple_arg functions
* Change token->id into int corresponding to i's operator
  * Ability to strcmpr content and call funcs with content
* Unified errors and output
  * Error handling frame
  * Writing funcs (errors mainly)
  * Colors for printf's and writes

### Bugs:
* Segfault with ">/</>>/<</|" as the first argument
  * Invalid mem alloc in get_tokens() anddt_strdup()
  * Leads to invalid read in expand_env()
* ''/""/" "/' ' as the argument results in incorrect behaviour

## TEST
### Command & syntax
* Tilde (~(/), ~+(/), ~/, ~-(/), )

## GIT COMMANDS
### Branches:
  * `git fetch origin` (fetch the remote branches)
  * `git branch -r` (list all remote branches)
  * `git branch` (list local branches and show current)
  * `git checkout -b <new_branch> <origin/branch` (new local branch with upstream branch)
  * `git checkout <brach_name>` (switch to a branch)
  * `git branch --delete <branchname>` /delete local branch
  * `git push origin <branch_name>` /push to remote branch
  * `git pull origin <branch_name>` (pull from remote branch)
  * `git ls-files` (list files in remote repository)
#### Start working with specified remote branch:
`git checkout main` >> `git fetch` >> `git checkout -b <new_branch> <origin/branch>`
####  Push changes to remote branch:
`git add .` >> `git commit -m <message>` >> `git push origin <branch>`


### Git history:
* TEMPORARY
  * git log /find the commit hash you want to go to
  * git checkout <commit_hash> /temporarily checkout an earlier commit
  * git checkout <branch_name> /return back to the current version
* PERMANENT
  * git revert <commit_hash> /revert to older commit specified by it's hash
  * git push origin <branch_name> /push it to make it current
* MORE PERMANENT
  * git reset --hard <commit_hash> /reset to a specified older commit
  * git push origin <brach_name> --force /force push it to current branch NOT REVERSABLE (prolly).
