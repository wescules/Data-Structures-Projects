Compile the code using the command:
g++ -std=c++11 *.cpp -o sparse

Run the executable with the command:
./sparse "A=<file>;B=<file>;result=<file>;sort<nlogn/nsquared>"
 
I chose quicksort and bubble sort for my nlogn and n^2 functions, respectively.
I chose these because they were the easiest to implement and most intuitive.
I dont know why but for some reason, on the linux server my code doesnt sort the 
entries correctly, but on my wondows computer (in Visual Studio) it sorts perfectly
fine. I talked to a TA about this and he never really gave me a direct answer about 
how i can solve this issue.