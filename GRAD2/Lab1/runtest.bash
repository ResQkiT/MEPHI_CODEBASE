echo Compiling tests...
make testmain
valgrind --leak-check=full ./testmain
bash clean.bash