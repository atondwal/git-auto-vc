#!/bin/sh
if [ ! -d .git ]; then git init; fi;
inotifywait -mr -e modify ~/git/git --exclude "\.git" |tee ../waitlog.log| xargs -i{} git commit '-a' '-m' 'autosaved'
