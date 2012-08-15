#!/bin/sh
cd $1
if [ ! -d .git ]; then git init; fi;
inotifywait -mr -e modify . --exclude "\.git" |tee ../waitlog.log| xargs -i{} git commit '-a' '-m' 'autosaved'
