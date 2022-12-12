#!/bin/bash

cd ./build

tg=$1

clear && \
  cmake -DTARGET_GROUP=$1 .. && \
  cmake --build . && \
  printf "run(r): " && read opt

printf "file to run: " && read file_to_run

[[ $opt == "r" && $tg == "release" ]] && \
  ../bin/$file_to_run

[[ $opt == "r" && $tg == "test" ]] && clear && \
  ../bin/test/$file_to_run | \
  sed "s/\/d.*\/sl_list\///" | sed ''s/PASS/`printf "\033[32mPASS\033[0m"`/'' | sed ''s/FAIL/`printf "\033[35mFAIL\033[0m"`/''

