# minishell_wip

## GIT BRANCH

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

## GIT HISTORY

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
