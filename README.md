# General task
    * Task02/day04/subtask01

# CGreen
    * For cgreen test you need to install it from github repository ("https://github.com/cgreen-devs/cgreen")
    * Go to 'cgreen' folder, and write
        ** make
        ** make test
        ** make install (sudo)
    * After that 'cgreen' be installed in next path: /usr/local/lib
    * If try to run my cgreen tests you will see error like that: "libcgreen.so.1: file or directory not found"
    * For fix this error you need write in terminal to variable LD_LIBRARY_PATH path to this library
    * export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
    * If you'll close terminal you must be again write this command
    * For fix this, write this command in end of file ~/.bashrc, after that in terminal 'source ~/.bashrc'


# Instruction
    * Write in terminal "cmake ." - for compilation CMakeLists.txt
    * Write in terminal "make" - for run target 'build' which create folders and compilation C files
    * Write in terminal "make test" - for run tests (Before that you need to do **make**)
    * For see more information about my tests you can write "ctest -V" in terminal, or open "Testing/Temporary/LastTest.log" in profect file
# Author 
    Kushch A.
