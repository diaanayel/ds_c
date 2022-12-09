#!/bin/bash

cd ./build

tg=$1
test_to_run=$2

clear && \
  cmake -DTARGET_GROUP=$1 .. && \
  cmake --build . && \
  printf "run(r): " && read opt

[[ $opt == "r" && $tg == "release" ]] && ../bin/release/main
[[ $opt == "r" && $tg == "test" ]] && clear && \
  ../bin/test/t_$test_to_run | \
  sed "s/\/d.*\/sl_list\///" | sed ''s/PASS/`printf "\033[32mPASS\033[0m"`/'' | sed ''s/FAIL/`printf "\033[35mFAIL\033[0m"`/''

