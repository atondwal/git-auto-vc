#!/bin/sh
export GIT_WORK_TREE=$1
export GIT_DIR=$1/.git/
cd $1
if [ ! -d .git ]; then git init; fi;
cd -
inotifywait -mr -e modify $1 --exclude "\.git" |tee waitlog.log| xargs -i ./git-stash.sh 
