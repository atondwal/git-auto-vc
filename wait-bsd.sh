#!/bin/sh
if [ ! -d .git ]; then git init; fi;
while filewait `find . |grep -v ".git"`; do xargs -i{} git commit '-a' '-m' 'autosaved'; done;
