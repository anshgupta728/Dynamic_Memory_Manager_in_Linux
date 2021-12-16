# MINOR 1 PROJECT
# Title:  Dynamic Memory Manager in Linux using C

# Team Details: (Group 28)
1. Ansh Gupta (500075765, AI ML, B2, R177219035)
2. Vitesh Sethi (500076357, CCVT, B4, R110219154)
3. Aryan Rastogi (500075858, AI ML, B2, R177219053)

# Project Objectives :
1) To develop a custom memory manager that can allocate/deallocate memory to a process/application
2) To overcome the issue of memory fragmentation which is one of the major issue in standard Glibc library 
3) To show statistics of memory in use via every structure so that programmer does not need to keep track of allocations and deallocations.

# Project Applications:
1) Custom memory allocators are used by students, programmers and technical companies working in the system programming domain in order to overcome the limitations of the standard Glibc memory manager. 
2) In this project, a similar custom memory allocator is being developed that can be applied in place of the standard memory manager. 

# Output Screenshot1:
![image](https://user-images.githubusercontent.com/60087551/145463659-56f4f99d-67b3-47f5-bfe7-a4af8eccecff.png)

# Output Screenshot2:
![image](https://user-images.githubusercontent.com/60087551/145463793-1c023060-cf87-4ccd-ac50-65b8667c9920.png)


Compilation Steps:

Step 1: gcc -g -c testapp.c -o testapp.o

Step 2: gcc -g -c mm.c -o mm.o

Step 3: gcc -g -c gluethread/glthread.c -o gluethread/glthread.o

Step 4: gcc -g gluethread/glthread.o mm.o testapp.o test.exe

Step 5: ./test.exe
