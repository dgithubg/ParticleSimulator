system partSys dim 23
system partSys particle 0 1 0 4 0 0 0 0 
system partSys particle 1 1 1 4 -1 0 0 0 
system partSys particle 2 1 2 4 -2 0 0 0 
system partSys particle 3 1 3 4 -4 0 0 0 
system partSys particle 4 1 4 4 -4 0 0 0  
system partSys particle 5 1 5 4 -4 0 0 0 
system partSys particle 6 1 6 4 -2 0 0 0 
system partSys particle 7 1 7 4 -1 0 0 0 
system partSys particle 8 1 8 4 -0.5 0 0 0 
system partSys particle 9 1 11 4 -3 0 0 0 
system partSys particle 10 1 11 6 0 0 0 0 
system partSys particle 11 1 11 4 3 0 0 0 
system partSys particle 12 1 11 2 0 0 0 0 
system partSys particle 13 1 8 4 0.5 0 0 0 
system partSys particle 14 1 7 4 1 0 0 0 
system partSys particle 15 1 6 4 2 0 0 0 
system partSys particle 16 1 5 4 4 0 0 0 
system partSys particle 17 1 4 4 4 0 0 0 
system partSys particle 18 1 3 4 4 0 0 0 
system partSys particle 19 1 2 4 2 0 0 0 
system partSys particle 20 1 1 4 1 0 0 0 
system partSys particle 21 1 4 6 0 0 0 0 
system partSys particle 22 1 4 2 0 0 0 0 

simulator partSim link partSys 2
simulator partSim spring 0 1 2 5 1
simulator partSim spring 1 2 2 5 1
simulator partSim spring 2 3 2 5 1
simulator partSim spring 3 4 2 5 1
simulator partSim spring 4 5 2 5 1
simulator partSim spring 5 6 2 5 1
simulator partSim spring 6 7 2 5 1
simulator partSim spring 7 8 2 5 1
simulator partSim spring 8 9 2 5 2
simulator partSim spring 9 10 2 5 2
simulator partSim spring 9 11 2 5 2
simulator partSim spring 10 11 2 5 2
simulator partSim spring 11 12 2 5 2
simulator partSim spring 11 13 2 5 2
simulator partSim spring 12 9 2 5 2
simulator partSim spring 12 10 2 5 2
simulator partSim spring 12 13 2 5 2
simulator partSim spring 13 14 2 5 1
simulator partSim spring 14 15 2 5 1
simulator partSim spring 15 16 2 5 1
simulator partSim spring 16 17 2 5 1
simulator partSim spring 17 18 2 5 1
simulator partSim spring 18 19 2 5 1
simulator partSim spring 19 20 2 5 1
simulator partSim spring 20 0 99 5 1
simulator partSim spring 21 0 99 5 3
simulator partSim spring 22 0 99 5 3
simulator partSim spring 21 3 99 5 2
simulator partSim spring 22 3 99 5 2
simulator partSim spring 21 5 99 5 2
simulator partSim spring 22 5 99 5 2
simulator partSim spring 21 8 99 5 2
simulator partSim spring 22 8 99 5 2
simulator partSim spring 21 13 99 5 3
simulator partSim spring 22 13 99 5 3
simulator partSim spring 21 15 99 5 2
simulator partSim spring 22 15 99 5 2
simulator partSim spring 21 18 99 5 2
simulator partSim spring 22 18 99 5 2
simulator partSim spring 21 22 99 5 3




#simulator partSim integration euler .001
#simulator partSim integration symplectic .01
simulator partSim integration verlet .01
simulator partSim ground 1000 20
simulator partSim gravity -9.8


