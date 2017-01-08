Compile the code using the command:
g++ -std=c++11 *.cpp -o sparse
Run the executable with the command:
./sparse "operation=<add|multiply>;storage=<array|linkedlist>;recursive=<Y/N>;A=<file>;B=<file>;result=<file>". 

Currently the program can store arrays and add them recursively and non-recursively. 

Code disclosure:
I had trouble sorting the output array so I modified some of the code from this example: https://shihho.wordpress.com/2012/11/28/sort_with_vectors/

For the linekd list sotrage I modified the addnode function to be doubly linked from this website: http://www.dreamincode.net/forums/topic/220422-adding-sparse-matrices-in-linked-list-format-problems/
