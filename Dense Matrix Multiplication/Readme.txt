To run make sure that these are in the working directory: 1.ans, 2.ans, 3.ans,
 1.txt, 2.txt, 3.txt, ArgumentManager.h, densmult.cpp, Makefile, test.sh.

Compile the code with the following command: g++ -std=c++11 *.cpp -o densemult
This makes a densemult executable. Next to test individual test cases use the command:
./densemult "A=<filename>.txt;C=<filename>.out"

Type in  'ls' into the command line to find the new '.out' file that has been created. 
To test against multiple test cases type in: 'sh test.sh'. This will generate several 
different files into your present working directory so be sure to clean them out once done 
working with using the make clean command.

Disclosure:
The only part that was inspired by an outside source was the multiplication algorithm which was
disccused in many online forums and amonst classmates. 
