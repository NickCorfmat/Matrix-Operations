Nicolas Corfmat<br>
CruzID: ncorfmat<br>
Assignment: pa4

```
DESCRIPTION
``` 
This program implements a Matrix ADT and performs matrix calculations on two matrices defined in a user-specified input file.

```
FILES
```
+ `List.h` Header file containing the interface for the List ADT.
+ `List.c` C file containing the List ADT.
+ `ListTest.c` C file containing code for testing the List ADT.
+ `Matrix.h` Header file containing the interface for the Matrix ADT.
+ `Matrix.c` C file containing the Matrix ADT.
+ `MatrixTest.c` C file containing code for testing the Matrix ADT functions.
+ `Sparse.c` Contains the main() function that performs matrix computations based on user input.
+ `Makefile` Supports the compilation of all the .c programs in the pa3 directory.
+ `README.md` Contains information regarding the files in the pa4 directory and how to run them.

```
BUILD
``` 
To build, run `make` on the terminal command line within the pa4 assignment directory followed by one of the following: `Sparse`, `MatrixTest`, and/or `ListTest`. This creates respective executable files which can then be run.
```
CLEAN
```
Running `make clean` will remove all the executable (.o) files from the pa3 assignment directory as well as other compiler-generated files.
```
RUNNING
```
To run, type `./Sparse` followed by a space separated **input** and **output** text file.
