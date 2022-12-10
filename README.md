# ds repo

### i'll upload some datastructure writen in c to this repo
* [x] singly linked list
* [x] stack (using linked list)

### test framework used is [Unity framework](https://github.com/ThrowTheSwitch/Unity "Unity Test framework")

### to run
* create dirs: build, lib, bin
* edit test/CMakeLists.txt
  * set UNITY PATH to the unity framework clone in your machine 
  * use **add_subdurectory()** to add a specific test folder
* configure libraries and links for each test in test/testFolder/CMakeLists.txt
* build & run using the build script, **named bb** in the source dir (not an obligation)
* you must specify for which group you are building for test/release: ./bb test

* there is a local .vimrc:
  * if you don't know, add **set exrc** to your main vimrc
  * the default mapping is <C-x>
  * change the task to the needed one in it

* **bb** now accepts 2 parameters:
  * the first for the build group
  * the second for the task to be run after build


**any comments or advices appreciated !**
