set num 500
system partSys dim $num

set count 0
while {$count < $num} {
	set rando [expr rand() ]
	set rando2 [expr rand()]
	system partSys particle $count 1 [expr $rando] [expr $rando] [expr $rando] 0 10 0
	set count [expr $count + 1]
	system partSys particle $count 1 [expr $rando + 2] [expr $rando + 5] [expr $rando] 0 10 0
	set count [expr $count + 1]
}

simulator partSim link partSys $num
set scount 0
set scount2 1
while {$scount < $num} {
	simulator partSim spring $scount $scount2 20 5 6
	set scount [expr $scount + 2]
	set scount2 [expr $scount2 + 2]

}

#simulator partSim integration euler .001
#simulator partSim integration symplectic .01
simulator partSim integration verlet .01
simulator partSim ground 1000 -5
simulator partSim gravity -9.8


