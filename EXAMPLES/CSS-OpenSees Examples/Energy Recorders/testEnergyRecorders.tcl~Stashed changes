#by SAJalali (www.CivilSoftScience.com)
#demonstrate the Resid-Type recorders (records the response at the very end of the analysis)

#to call from debugger:
cd "D:/programming/OpenSees.NET/EXAMPLES/CSS-OpenSees Examples/Energy Recorders"


model basic -ndm 2
node 1 0. 0.
node 2 0. 0. -mass 10. 0.001 0.001
fix 1 1 1 1
# uniaxialMaterial Steel01 1 100 100 0.01
uniaxialMaterial Elastic 1 10000
element zeroLength 1 1 2 -mat 1 1 1 -dir 1 2 3

#damping
set w1 [eigen 1]
set zeta 0.02;		# percentage of critical damping
set a0 [expr $zeta*2.0*$w1*$w1/($w1 + $w1)];	# mass damping coefficient based on first and second modes
set a1 [expr $zeta*2.0/($w1 + $w1)];			# stiffness damping coefficient based on first and second modes
rayleigh $a0 $a1 0.0 0.0;	# assign mass-proportional damping to frame beams & columns w/ n modifications
timeSeries Path 1 -dt 0.01 -filePath LomaPrieta.txt -factor 9.81
pattern UniformExcitation 1 1 -accel 1;	#Units: m,s

#test the new recorders:
recorder Node -file motionEnergy.txt -timeSeries 1  -node 2 -dof 1 kineticEnergy
recorder Node -file dampingEnergy.txt -timeSeries 1 -node 2 -dof 1 dampingEnergy
recorder Node -file disp.txt -node 2 -dof 1 disp
recorder Node -file vel.txt  -node 2 -dof 1 vel
recorder Node -file accel.txt -time -node 2 -dof 1 accel
recorder Node -file absAccel.txt  -timeSeries 1 -time -node 2 -dof 1 accel
# recorder Element -file eleDampEnergy.txt -ele 1 dampingEnergy

integrator Newmark 2 1 0.1
analysis Transient
analyze 3000 0.01