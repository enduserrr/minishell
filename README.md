# minishell_wip

## GIT STUFF

### Branching

- git fetch origin / fetch the remote branches
- git branch -r /list all remote branches
- git branch /list local branches
- git checkout -b <new_branch> /create a new branch and switch to it ('git checkout arttu')
- git checkout <brach_name> /switch to a branch
- git branch --delete <branchname> /delete local branch
- git push origin <branch_name> /push to remote branch
- git pull origin <branch_name> /pull remote branch (first create matching local one)
- git ls-files /list files in git

When working on the project start by fetching remote branches, creating them locally with 'checkout' and switching to the correct one to work inside of. Then when pushing 'git push origin <branch_name>'

### History

Temporary:
- git log /find the commit hash you want to go to
- git checkout <commit_hash> /temporarily checkout an earlier commit
- git checkout <branch_name> /return back to the current version

Permanently:
- git revert <commit_hash> /revert to older commit specified by it's hash
- git push origin <branch_name> /push it to make it current

CCP Policy (rewrite history):
- git reset --hard <commit_hash> /reset to a specified older commit
- git push origin <brach_name> --force /force push it to current branch
NOT REVERSABLE (prolly).

## COMPILERS

Translates high-level language into machine code, bytecode or another computer executable target language. The translator between the coder telling what to do to the computer interpreting what to do, both in their own set languages.

Main stages of compiling:
- Lexical analysis (tokenising) | breaks the code into understandable pieces
- Syntax analysis (parsing) | arranges the pieces according to formatting rules
- Semantic analysis | figuring out the intented functionality (meaning and logic)
- Optimisation | efficiency, deleting redundancies etc (won't change functionality)
- Code generation | creating the translation in the target laguage

### Tokenising: (snytax analysis)
The process of analysing a character sequence and separating it into individual recognised tokens. Example: int x = 10; into int, x, =, 10, ;.

### Parsing: (lexical analysis)
Arranges the tokens into a hierarchical structure called a parse tree or syntax tree.
To parse: to divide something into smaller parts, identifying them and their relation to each of the singular parts. Dividing into component parts.