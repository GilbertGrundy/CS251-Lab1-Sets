The program does a series of set operations on two sets inputed on the command line.

It does what is required, but the actual code is a bit of a mess. When I have time
I'm going to split the code into a header file and a function file to go with
main.cpp. 

I also should have made the functions more general, and I ended up re-writing
a lot of functionality. 

Sample Program Run:

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Please enter your elements for set A: 1 2 4 8 16
Please enter your elements for set B: 0 2 4 6 8 10 12 14 16


The roster of the intersection is: 2 4 8 16
And the cardinality of the intersection is: 4

The roster of the union is: 16 8 4 2 1 0 6 10 12 14
And the cardinality of the union is: 10

The roster of the complement A - B is: 1
And the cardinality of the complement A - B is: 1

The roster of the complement B - A is: 14 12 10 6 0
And the cardinality of the complement B - A is: 5

The roster of AXB is: (16,16) (16,14) (16,12) (16,10) (16,8) (16,6) (16,4) (16,2) (16,0) 
(8,16) (8,14) (8,12) (8,10) (8,8) (8,6) (8,4) (8,2) (8,0) (4,16) (4,14) (4,12) (4,10) (4,8) 
(4,6) (4,4) (4,2) (4,0) (2,16) (2,14) (2,12) (2,10) (2,8) (2,6) (2,4) (2,2) (2,0) (1,16) (1,14) 
(1,12) (1,10) (1,8) (1,6) (1,4) (1,2) (1,0)
And the cardinality of AXB is: 45

The cardinality of the power set of AXB is: 2^45

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
