set springks 200
set springkd 20

system partSys dim 22
system partSys particle 0 10 1 3 1 0 2 0
system partSys particle 1 10 2 6 1 0 2 0
system partSys particle 2 10 0 6 1 0 2 0
system partSys particle 3 10 1 6 2 0 2 0
system partSys particle 4 10 1 6 0 0 2 0

system partSys particle 5 10 -5 3 1 0 2 0
system partSys particle 6 10 -4 6 1 0 2 0
system partSys particle 7 10 -6 6 1 0 2 0
system partSys particle 8 10 -5 6 2 0 2 0
system partSys particle 9 10 -5 6 0 0 2 0

system partSys particle 10 5 2 10 1 0 2 0
system partSys particle 11 5 0 10 1 0 2 0
system partSys particle 12 5 1 10 2 0 2 0
system partSys particle 13 5 1 10 0 0 2 0


system partSys particle 14 5 -4 10 1 0 2 0
system partSys particle 15 5 -6 10 1 0 2 0
system partSys particle 16 5 -5 10 2 0 2 0
system partSys particle 17 5 -5 10 0 0 2 0

system partSys particle 18 5 2 12 1 0 2 0
system partSys particle 19 5 1 12 2 0 2 0
system partSys particle 20 5 -4 12 1 0 2 0
system partSys particle 21 5 -5 12 2 0 2 0

simulator partSim link partSys 20
set strength 2

simulator partSim spring 1 18 $springks $springkd $strength
simulator partSim spring 3 19 $springks $springkd $strength
simulator partSim spring 6 20 $springks $springkd $strength
simulator partSim spring 8 21 $springks $springkd $strength

simulator partSim spring 18 19 $springks $springkd 1.4
simulator partSim spring 18 20 $springks $springkd 6
simulator partSim spring 20 21 $springks $springkd 1.4
simulator partSim spring 21 19 $springks $springkd 6


simulator partSim spring 0 1 $springks $springkd 7
simulator partSim spring 0 2 $springks $springkd 7
simulator partSim spring 0 3 $springks $springkd 7
simulator partSim spring 0 4 $springks $springkd 7

simulator partSim spring 1 2 $springks $springkd $strength
simulator partSim spring 2 3 $springks $springkd $strength
simulator partSim spring 3 4 $springks $springkd $strength
simulator partSim spring 4 1 $springks $springkd $strength

simulator partSim spring 1 3 $springks $springkd $strength
simulator partSim spring 2 4 $springks $springkd $strength


simulator partSim spring 1 10 1000 $springkd $strength
simulator partSim spring 2 11 1000 $springkd $strength
simulator partSim spring 3 12 1000 $springkd $strength
simulator partSim spring 4 13 1000 $springkd $strength

simulator partSim spring 10 11 $springks $springkd $strength
simulator partSim spring 11 12 $springks $springkd $strength
simulator partSim spring 12 13 $springks $springkd $strength
simulator partSim spring 13 10 $springks $springkd $strength
simulator partSim spring 10 12 $springks $springkd $strength
simulator partSim spring 11 13 $springks $springkd $strength


simulator partSim spring 6 14 1000 $springkd $strength
simulator partSim spring 7 15 1000 $springkd $strength
simulator partSim spring 8 16 1000 $springkd $strength
simulator partSim spring 9 17 1000 $springkd $strength

simulator partSim spring 14 15 $springks $springkd $strength
simulator partSim spring 15 16 $springks $springkd $strength
simulator partSim spring 16 17 $springks $springkd $strength
simulator partSim spring 17 14 $springks $springkd $strength
simulator partSim spring 14 16 $springks $springkd $strength
simulator partSim spring 15 17 $springks $springkd $strength

#simulator partSim spring 10 14 1000 $springkd 0.5
#simulator partSim spring 11 15 1000 $springkd 0.5
#simulator partSim spring 12 16 1000 $springkd 0.5
#simulator partSim spring 13 17 1000 $springkd 0.5


simulator partSim spring 5 6 $springks $springkd 7
simulator partSim spring 5 7 $springks $springkd 7
simulator partSim spring 5 8 $springks $springkd 7
simulator partSim spring 5 9 $springks $springkd 7

simulator partSim spring 6 7 $springks $springkd $strength
simulator partSim spring 7 8 $springks $springkd $strength
simulator partSim spring 8 9 $springks $springkd $strength
simulator partSim spring 9 6 $springks $springkd $strength

simulator partSim spring 6 8 $springks $springkd $strength
simulator partSim spring 7 9 $springks $springkd $strength

simulator partSim integration symplectic .001
simulator partSim ground 5000 0
simulator partSim gravity -10.8
