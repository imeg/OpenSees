#by SAJalali (www.CivilSoftScience.com)
#demonstrate the Resid-Type recorders (records the response at the very end of the analysis)

#to call from debugger:
cd "D:/programming/OpenSees.NET/EXAMPLES/CSS-OpenSees Examples/ResidRecorderTest"


model basic -ndm 2
node 1 0. 0.
node 2 0. 0.
fix 1 1 1 1
uniaxialMaterial Steel01 1 100 100 0.01
element zeroLength 1 1 2 -mat 1 1 1 -dir 1 2 3
pattern Plain 1 Linear {
	load 2 1. 0 0
}

#test the new recorders:
recorder Node -file Node.txt -time -node 2 -dof 1 disp
recorder ResidNode -file residNode.txt -time -node 2 -dof 1 disp

#the following does not work here to zero-distance between nodes, kept for demonstration
#recorder ResidDrift -file residDrift.txt -time -iNode 1 -jNode 2 -dof 1 -perpDirn 1

recorder Element -file Element.txt -time -ele 1 material 1 stressStrain
recorder ResidElement -file residElement.txt -time -ele 1 material 1 stressStrain

integrator DisplacementControl 2 1 0.1
analysis Static
analyze 30