cd "F:/Omran Elm Afzar/OpenSees.NET new/OpenSees.NET/EXAMPLES/CSS-OpenSees Examples/Steel05"
model basic -ndm 2
node 1 0 0
node 2 0 0
fix 1 1 1 1

# UniaxialMaterial Steel05 $matTag $Fy $E $b $ductilityCapacity $postCapEFac $gama $c $resFac <$R0 $cR1 $cR2> <$a1 $a2 $a3 $a4> <$sigInit>
# uniaxialMaterial Steel02 1 1. 1. 0.01
uniaxialMaterial Steel05 1 1. 1. 0.05 4. -0.2 25 1 0.2 15 0 0
# uniaxialMaterial Bilin 1 1. 0.01 0.01 1. -1. 100 100 100 100 1 1 1 1 3 3 5.15 5.15 0.2 0.2 10 10 1 1 1
uniaxialMaterial Elastic 2 100
element zeroLength 1 1 2 -mat 1 2 2 -dir 1 2 3
recorder Element -file stressStrain.txt -time -ele 1 material 1 stressStrain
recorder Element -file tangent.txt -time -ele 1 material 1 tangent
timeSeries Linear 1 
pattern Plain 1 1 {
	load 2 1. 0. 0.
}

set ampList "4. 8. 12."
# set ampList "10."
foreach amp $ampList {
	lappend list $amp
	lappend list [expr -2.*$amp]
	lappend list $amp
}
# set list "-10."
puts "list= $list"
constraints Transformation;     				
numberer Plain;						
system BandGeneral;					
test NormDispIncr 1.e-5 50 ; 		
algorithm ModifiedNewton;					

foreach delta $list {
	integrator DisplacementControl 2 1 [expr $delta/200.]
	analysis Static
	analyze 100
}
