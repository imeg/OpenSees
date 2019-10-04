# written: fmk
# date: 02/99
#
# purpose: example1 in OpenSeesIntro.tex
#
# $Revision: 1.4 $
# $Date: 2002-12-17 02:03:54 $
# $Source: /usr/local/cvs/OpenSees/EXAMPLES/ExampleScripts/example1.tcl,v $


#create the ModelBuilder object
wipe
model BasicBuilder -ndm 2 -ndf 2

# build the model 

# add nodes - command: node nodeId xCrd yCrd
node 1   0.0  0.0
node 2 144.0  0.0
node 3 168.0  0.0
node 4  72.0 96.0

# add material - command: uniaxialMaterial <matType> matID <matArgs>
uniaxialMaterial Elastic 1 3000

# add truss elements - command: element truss trussID node1 node2 A matID
element truss 1 1 4 10.0 1
element truss 2 2 4 5.0 1
element truss 3 3 4 5.0 1

# add feap truss elements - command: element fTruss trussID node1 node2 A E
#element fTruss 1 1 4 10.0 3000
#element fTruss 2 2 4 5.0 3000
#element fTruss 3 3 4 5.0 3000

# set the boundary conditions - command: fix nodeID xResrnt? yRestrnt?
fix 1 1 1 
fix 2 1 1
fix 3 1 1

pattern Plain 1 "Linear" {
    # apply the load - command: load nodeID xForce yForce
    load 4 100 -50
}

recorder Node -xml nodes.xml -time -node 1 2 3 4 -dof 1 2 vel;
recorder Node -file nodes.txt -time -node 1 2 3 4 -dof 1 2 vel;
recorder Element -file Elements.txt -time -ele 1 2 3 forces
recorder Element -xml Elements.xml -time -ele 1 2 3 forces
# build the components for the analysis object
system BandSPD
constraints Plain
integrator LoadControl 1.0
algorithm Linear
numberer RCM

# create the analysis object 
analysis Static 

# perform the analysis
analyze 10
# print the results at node and at all elements
