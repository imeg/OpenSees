cd "D:/programming/OpenSees.NET/EXAMPLES/CSS-OpenSees Examples/InternalForce Recorder"
model basic -ndm 2
node 1 0. 0.
node 2 1. 0.

fix 1 1 1 1
geomTransf Linear 1
element elasticBeamColumn 1 1 2 1. 1. 1. 1

pattern Plain 1 Linear {
	load 2 0. -1. 1.
}
foreach fac "0.0 0.25 0.5 0.75 1.0" {
	recorder Element -file interForce_$fac.txt -time -ele 1 InternalForce $fac
}
integrator LoadControl 1.
analysis Static
analyze 1