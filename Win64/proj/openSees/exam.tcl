wipe
puts "System"
model basic -ndm 3 -ndf 6
puts "restraint"
node 1 0.000E+000 0.000E+000 9.500E+003
node 2 0.000E+000 0.000E+000 1.250E+004
node 3 0.000E+000 4.000E+003 9.500E+003
node 4 0.000E+000 4.000E+003 1.250E+004
node 5 0.000E+000 7.000E+003 9.500E+003
node 6 0.000E+000 7.000E+003 1.250E+004
node 7 5.000E+003 0.000E+000 9.500E+003
node 8 5.000E+003 0.000E+000 1.250E+004
node 9 5.000E+003 4.000E+003 9.500E+003
node 10 5.000E+003 4.000E+003 1.250E+004
node 11 5.000E+003 7.000E+003 9.500E+003
node 12 5.000E+003 7.000E+003 1.250E+004
node 13 9.000E+003 0.000E+000 9.500E+003
node 14 9.000E+003 0.000E+000 1.250E+004
node 15 9.000E+003 4.000E+003 9.500E+003
node 16 9.000E+003 4.000E+003 1.250E+004
node 17 9.000E+003 7.000E+003 9.500E+003
node 18 9.000E+003 7.000E+003 1.250E+004
node 19 0.000E+000 0.000E+000 6.500E+003
node 20 0.000E+000 4.000E+003 6.500E+003
node 21 0.000E+000 7.000E+003 6.500E+003
node 22 5.000E+003 0.000E+000 6.500E+003
node 23 5.000E+003 4.000E+003 6.500E+003
node 24 5.000E+003 7.000E+003 6.500E+003
node 25 9.000E+003 0.000E+000 6.500E+003
node 26 9.000E+003 4.000E+003 6.500E+003
node 27 9.000E+003 7.000E+003 6.500E+003
node 28 0.000E+000 0.000E+000 3.500E+003
node 29 0.000E+000 4.000E+003 3.500E+003
node 30 0.000E+000 7.000E+003 3.500E+003
node 31 5.000E+003 0.000E+000 3.500E+003
node 32 5.000E+003 4.000E+003 3.500E+003
node 33 5.000E+003 7.000E+003 3.500E+003
node 34 9.000E+003 0.000E+000 3.500E+003
node 35 9.000E+003 4.000E+003 3.500E+003
node 36 9.000E+003 7.000E+003 3.500E+003
node 37 0.000E+000 0.000E+000 0.000E+000
node 38 0.000E+000 4.000E+003 0.000E+000
node 39 0.000E+000 7.000E+003 0.000E+000
node 40 5.000E+003 0.000E+000 0.000E+000
node 41 5.000E+003 4.000E+003 0.000E+000
node 42 5.000E+003 7.000E+003 0.000E+000
node 43 9.000E+003 0.000E+000 0.000E+000
node 44 9.000E+003 4.000E+003 0.000E+000
node 45 9.000E+003 7.000E+003 0.000E+000
node 46 0.000E+000 0.000E+000 1.550E+004
node 47 0.000E+000 4.000E+003 1.550E+004
node 48 0.000E+000 7.000E+003 1.550E+004
node 49 5.000E+003 0.000E+000 1.550E+004
node 50 5.000E+003 4.000E+003 1.550E+004
node 51 5.000E+003 7.000E+003 1.550E+004
node 52 9.000E+003 0.000E+000 1.550E+004
node 53 9.000E+003 4.000E+003 1.550E+004
node 54 9.000E+003 7.000E+003 1.550E+004
node 55 0.000E+000 0.000E+000 1.850E+004
node 56 0.000E+000 4.000E+003 1.850E+004
node 57 0.000E+000 7.000E+003 1.850E+004
node 58 5.000E+003 0.000E+000 1.850E+004
node 59 5.000E+003 4.000E+003 1.850E+004
node 60 5.000E+003 7.000E+003 1.850E+004
node 61 9.000E+003 0.000E+000 1.850E+004
node 62 9.000E+003 4.000E+003 1.850E+004
node 63 9.000E+003 7.000E+003 1.850E+004
puts "rigidDiaphragm"
puts "mass"
mass 1 7.609E+000 7.609E+000 7.609E+000 0.000E+000 0.000E+000 0.000E+000
mass 2 7.609E+000 7.609E+000 7.609E+000 0.000E+000 0.000E+000 0.000E+000
mass 3 1.004E+001 1.004E+001 1.004E+001 0.000E+000 0.000E+000 0.000E+000
mass 4 1.004E+001 1.004E+001 1.004E+001 0.000E+000 0.000E+000 0.000E+000
mass 5 6.781E+000 6.781E+000 6.781E+000 0.000E+000 0.000E+000 0.000E+000
mass 6 6.781E+000 6.781E+000 6.781E+000 0.000E+000 0.000E+000 0.000E+000
mass 7 1.031E+001 1.031E+001 1.031E+001 0.000E+000 0.000E+000 0.000E+000
mass 8 1.031E+001 1.031E+001 1.031E+001 0.000E+000 0.000E+000 0.000E+000
mass 9 1.443E+001 1.443E+001 1.443E+001 0.000E+000 0.000E+000 0.000E+000
mass 10 1.443E+001 1.443E+001 1.443E+001 0.000E+000 0.000E+000 0.000E+000
mass 11 8.922E+000 8.922E+000 8.922E+000 0.000E+000 0.000E+000 0.000E+000
mass 12 8.922E+000 8.922E+000 8.922E+000 0.000E+000 0.000E+000 0.000E+000
mass 13 6.921E+000 6.921E+000 6.921E+000 0.000E+000 0.000E+000 0.000E+000
mass 14 6.921E+000 6.921E+000 6.921E+000 0.000E+000 0.000E+000 0.000E+000
mass 15 8.935E+000 8.935E+000 8.935E+000 0.000E+000 0.000E+000 0.000E+000
mass 16 8.935E+000 8.935E+000 8.935E+000 0.000E+000 0.000E+000 0.000E+000
mass 17 6.233E+000 6.233E+000 6.233E+000 0.000E+000 0.000E+000 0.000E+000
mass 18 6.233E+000 6.233E+000 6.233E+000 0.000E+000 0.000E+000 0.000E+000
mass 19 7.609E+000 7.609E+000 7.609E+000 0.000E+000 0.000E+000 0.000E+000
mass 20 1.004E+001 1.004E+001 1.004E+001 0.000E+000 0.000E+000 0.000E+000
mass 21 6.781E+000 6.781E+000 6.781E+000 0.000E+000 0.000E+000 0.000E+000
mass 22 1.031E+001 1.031E+001 1.031E+001 0.000E+000 0.000E+000 0.000E+000
mass 23 1.443E+001 1.443E+001 1.443E+001 0.000E+000 0.000E+000 0.000E+000
mass 24 8.922E+000 8.922E+000 8.922E+000 0.000E+000 0.000E+000 0.000E+000
mass 25 6.921E+000 6.921E+000 6.921E+000 0.000E+000 0.000E+000 0.000E+000
mass 26 8.935E+000 8.935E+000 8.935E+000 0.000E+000 0.000E+000 0.000E+000
mass 27 6.233E+000 6.233E+000 6.233E+000 0.000E+000 0.000E+000 0.000E+000
mass 28 7.923E+000 7.923E+000 7.923E+000 0.000E+000 0.000E+000 0.000E+000
mass 29 1.036E+001 1.036E+001 1.036E+001 0.000E+000 0.000E+000 0.000E+000
mass 30 7.094E+000 7.094E+000 7.094E+000 0.000E+000 0.000E+000 0.000E+000
mass 31 1.063E+001 1.063E+001 1.063E+001 0.000E+000 0.000E+000 0.000E+000
mass 32 1.474E+001 1.474E+001 1.474E+001 0.000E+000 0.000E+000 0.000E+000
mass 33 9.236E+000 9.236E+000 9.236E+000 0.000E+000 0.000E+000 0.000E+000
mass 34 7.235E+000 7.235E+000 7.235E+000 0.000E+000 0.000E+000 0.000E+000
mass 35 9.248E+000 9.248E+000 9.248E+000 0.000E+000 0.000E+000 0.000E+000
mass 36 6.546E+000 6.546E+000 6.546E+000 0.000E+000 0.000E+000 0.000E+000
mass 37 2.193E+000 2.193E+000 2.193E+000 0.000E+000 0.000E+000 0.000E+000
mass 38 2.193E+000 2.193E+000 2.193E+000 0.000E+000 0.000E+000 0.000E+000
mass 39 2.193E+000 2.193E+000 2.193E+000 0.000E+000 0.000E+000 0.000E+000
mass 40 2.193E+000 2.193E+000 2.193E+000 0.000E+000 0.000E+000 0.000E+000
mass 41 2.193E+000 2.193E+000 2.193E+000 0.000E+000 0.000E+000 0.000E+000
mass 42 2.193E+000 2.193E+000 2.193E+000 0.000E+000 0.000E+000 0.000E+000
mass 43 2.193E+000 2.193E+000 2.193E+000 0.000E+000 0.000E+000 0.000E+000
mass 44 2.193E+000 2.193E+000 2.193E+000 0.000E+000 0.000E+000 0.000E+000
mass 45 2.193E+000 2.193E+000 2.193E+000 0.000E+000 0.000E+000 0.000E+000
mass 46 7.609E+000 7.609E+000 7.609E+000 0.000E+000 0.000E+000 0.000E+000
mass 47 1.004E+001 1.004E+001 1.004E+001 0.000E+000 0.000E+000 0.000E+000
mass 48 6.781E+000 6.781E+000 6.781E+000 0.000E+000 0.000E+000 0.000E+000
mass 49 1.031E+001 1.031E+001 1.031E+001 0.000E+000 0.000E+000 0.000E+000
mass 50 1.443E+001 1.443E+001 1.443E+001 0.000E+000 0.000E+000 0.000E+000
mass 51 8.922E+000 8.922E+000 8.922E+000 0.000E+000 0.000E+000 0.000E+000
mass 52 6.921E+000 6.921E+000 6.921E+000 0.000E+000 0.000E+000 0.000E+000
mass 53 8.935E+000 8.935E+000 8.935E+000 0.000E+000 0.000E+000 0.000E+000
mass 54 6.233E+000 6.233E+000 6.233E+000 0.000E+000 0.000E+000 0.000E+000
mass 55 5.729E+000 5.729E+000 5.729E+000 0.000E+000 0.000E+000 0.000E+000
mass 56 8.164E+000 8.164E+000 8.164E+000 0.000E+000 0.000E+000 0.000E+000
mass 57 4.901E+000 4.901E+000 4.901E+000 0.000E+000 0.000E+000 0.000E+000
mass 58 8.432E+000 8.432E+000 8.432E+000 0.000E+000 0.000E+000 0.000E+000
mass 59 1.255E+001 1.255E+001 1.255E+001 0.000E+000 0.000E+000 0.000E+000
mass 60 7.042E+000 7.042E+000 7.042E+000 0.000E+000 0.000E+000 0.000E+000
mass 61 5.041E+000 5.041E+000 5.041E+000 0.000E+000 0.000E+000 0.000E+000
mass 62 7.055E+000 7.055E+000 7.055E+000 0.000E+000 0.000E+000 0.000E+000
mass 63 4.353E+000 4.353E+000 4.353E+000 0.000E+000 0.000E+000 0.000E+000
puts "node"
fix 37 1 1 1 1 1 1;
fix 38 1 1 1 1 1 1;
fix 39 1 1 1 1 1 1;
fix 40 1 1 1 1 1 1;
fix 41 1 1 1 1 1 1;
fix 42 1 1 1 1 1 1;
fix 43 1 1 1 1 1 1;
fix 44 1 1 1 1 1 1;
fix 45 1 1 1 1 1 1;
puts "material"

uniaxialMaterial Steel01 1 400 206000 0.01 
uniaxialMaterial Concrete02 2 -26.8 -0.0015 -10 -0.0033 0.1 2.2 1100

uniaxialMaterial Elastic 3 1.999E+005
uniaxialMaterial Elastic 201 1.056E+010
uniaxialMaterial Elastic 301 1.056E+010
uniaxialMaterial Elastic 401 2.857E+014
uniaxialMaterial Elastic 202 1.094E+009
uniaxialMaterial Elastic 302 1.094E+009
uniaxialMaterial Elastic 402 1.310E+013
##NC400X400 
section Fiber 1 {
fiber -1.600E+002 -1.600E+002 6.400E+003 1
fiber -8.000E+001 -1.600E+002 6.400E+003 1
fiber 0.000E+000 -1.600E+002 6.400E+003 1
fiber 8.000E+001 -1.600E+002 6.400E+003 1
fiber 1.600E+002 -1.600E+002 6.400E+003 1
fiber -1.600E+002 -8.000E+001 6.400E+003 1
fiber -8.000E+001 -8.000E+001 6.400E+003 1
fiber 0.000E+000 -8.000E+001 6.400E+003 1
fiber 8.000E+001 -8.000E+001 6.400E+003 1
fiber 1.600E+002 -8.000E+001 6.400E+003 1
fiber -1.600E+002 0.000E+000 6.400E+003 1
fiber -8.000E+001 0.000E+000 6.400E+003 1
fiber 0.000E+000 0.000E+000 6.400E+003 1
fiber 8.000E+001 0.000E+000 6.400E+003 1
fiber 1.600E+002 0.000E+000 6.400E+003 1
fiber -1.600E+002 8.000E+001 6.400E+003 1
fiber -8.000E+001 8.000E+001 6.400E+003 1
fiber 0.000E+000 8.000E+001 6.400E+003 1
fiber 8.000E+001 8.000E+001 6.400E+003 1
fiber 1.600E+002 8.000E+001 6.400E+003 1
fiber -1.600E+002 1.600E+002 6.400E+003 1
fiber -8.000E+001 1.600E+002 6.400E+003 1
fiber 0.000E+000 1.600E+002 6.400E+003 1
fiber 8.000E+001 1.600E+002 6.400E+003 1
fiber 1.600E+002 1.600E+002 6.400E+003 1
fiber -1.650E+002 -1.650E+002 1.960E+002 1
fiber -8.250E+001 -1.650E+002 1.960E+002 1
fiber 0.000E+000 -1.650E+002 1.960E+002 1
fiber 8.250E+001 -1.650E+002 1.960E+002 1
fiber 1.650E+002 -1.650E+002 1.960E+002 1
fiber -1.650E+002 1.650E+002 1.960E+002 1
fiber -8.250E+001 1.650E+002 1.960E+002 1
fiber 0.000E+000 1.650E+002 1.960E+002 1
fiber 8.250E+001 1.650E+002 1.960E+002 1
fiber 1.650E+002 1.650E+002 1.960E+002 1
fiber -1.650E+002 -1.100E+002 1.960E+002 1
fiber -1.650E+002 -5.500E+001 1.960E+002 1
fiber -1.650E+002 0.000E+000 1.960E+002 1
fiber -1.650E+002 5.500E+001 1.960E+002 1
fiber -1.650E+002 1.100E+002 1.960E+002 1
fiber 1.650E+002 -1.100E+002 1.960E+002 1
fiber 1.650E+002 -5.500E+001 1.960E+002 1
fiber 1.650E+002 0.000E+000 1.960E+002 1
fiber 1.650E+002 5.500E+001 1.960E+002 1
fiber 1.650E+002 1.100E+002 1.960E+002 1
}
##NB200X500 
section Fiber 2 {
fiber -8.000E+001 -2.000E+002 4.000E+003 2
fiber -4.000E+001 -2.000E+002 4.000E+003 2
fiber 0.000E+000 -2.000E+002 4.000E+003 2
fiber 4.000E+001 -2.000E+002 4.000E+003 2
fiber 8.000E+001 -2.000E+002 4.000E+003 2
fiber -8.000E+001 -1.000E+002 4.000E+003 2
fiber -4.000E+001 -1.000E+002 4.000E+003 2
fiber 0.000E+000 -1.000E+002 4.000E+003 2
fiber 4.000E+001 -1.000E+002 4.000E+003 2
fiber 8.000E+001 -1.000E+002 4.000E+003 2
fiber -8.000E+001 0.000E+000 4.000E+003 2
fiber -4.000E+001 0.000E+000 4.000E+003 2
fiber 0.000E+000 0.000E+000 4.000E+003 2
fiber 4.000E+001 0.000E+000 4.000E+003 2
fiber 8.000E+001 0.000E+000 4.000E+003 2
fiber -8.000E+001 1.000E+002 4.000E+003 2
fiber -4.000E+001 1.000E+002 4.000E+003 2
fiber 0.000E+000 1.000E+002 4.000E+003 2
fiber 4.000E+001 1.000E+002 4.000E+003 2
fiber 8.000E+001 1.000E+002 4.000E+003 2
fiber -8.000E+001 2.000E+002 4.000E+003 2
fiber -4.000E+001 2.000E+002 4.000E+003 2
fiber 0.000E+000 2.000E+002 4.000E+003 2
fiber 4.000E+001 2.000E+002 4.000E+003 2
fiber 8.000E+001 2.000E+002 4.000E+003 2
fiber -6.500E+001 2.150E+002 1.256E+002 1
fiber -3.250E+001 2.150E+002 1.256E+002 1
fiber 0.000E+000 2.150E+002 1.256E+002 1
fiber 3.250E+001 2.150E+002 1.256E+002 1
fiber 6.500E+001 2.150E+002 1.256E+002 1
fiber -6.500E+001 -2.150E+002 1.256E+002 1
fiber -3.250E+001 -2.150E+002 1.256E+002 1
fiber 0.000E+000 -2.150E+002 1.256E+002 1
fiber 3.250E+001 -2.150E+002 1.256E+002 1
fiber 6.500E+001 -2.150E+002 1.256E+002 1
}
section Aggregator 1001 201 Vy 301 Vz 401 T -section 1
section Aggregator 1002 202 Vy 302 Vz 402 T -section 2
puts "transformation"
geomTransf Linear 1 1.000 0.000 0.000 
geomTransf Linear 2 1.000 0.000 0.000 
geomTransf Linear 3 1.000 0.000 0.000 
geomTransf Linear 4 1.000 0.000 0.000 
geomTransf Linear 5 1.000 0.000 0.000 
geomTransf Linear 6 1.000 0.000 0.000 
geomTransf Linear 7 1.000 0.000 0.000 
geomTransf Linear 8 1.000 0.000 0.000 
geomTransf Linear 9 1.000 0.000 0.000 
geomTransf Linear 10 0.000 0.000 1.000 
geomTransf Linear 11 0.000 0.000 1.000 
geomTransf Linear 12 0.000 0.000 1.000 
geomTransf Linear 13 0.000 0.000 1.000 
geomTransf Linear 14 0.000 0.000 1.000 
geomTransf Linear 15 0.000 0.000 1.000 
geomTransf Linear 16 0.000 0.000 1.000 
geomTransf Linear 17 0.000 0.000 1.000 
geomTransf Linear 18 0.000 0.000 1.000 
geomTransf Linear 19 0.000 0.000 1.000 
geomTransf Linear 20 0.000 0.000 1.000 
geomTransf Linear 21 0.000 0.000 1.000 
geomTransf Linear 22 1.000 0.000 0.000 
geomTransf Linear 23 1.000 0.000 0.000 
geomTransf Linear 24 1.000 0.000 0.000 
geomTransf Linear 25 1.000 0.000 0.000 
geomTransf Linear 26 1.000 0.000 0.000 
geomTransf Linear 27 1.000 0.000 0.000 
geomTransf Linear 28 1.000 0.000 0.000 
geomTransf Linear 29 1.000 0.000 0.000 
geomTransf Linear 30 1.000 0.000 0.000 
geomTransf Linear 31 0.000 0.000 1.000 
geomTransf Linear 32 0.000 0.000 1.000 
geomTransf Linear 33 0.000 0.000 1.000 
geomTransf Linear 34 0.000 0.000 1.000 
geomTransf Linear 35 0.000 0.000 1.000 
geomTransf Linear 36 0.000 0.000 1.000 
geomTransf Linear 37 0.000 0.000 1.000 
geomTransf Linear 38 0.000 0.000 1.000 
geomTransf Linear 39 0.000 0.000 1.000 
geomTransf Linear 40 0.000 0.000 1.000 
geomTransf Linear 41 0.000 0.000 1.000 
geomTransf Linear 42 0.000 0.000 1.000 
geomTransf Linear 43 1.000 0.000 0.000 
geomTransf Linear 44 1.000 0.000 0.000 
geomTransf Linear 45 1.000 0.000 0.000 
geomTransf Linear 46 1.000 0.000 0.000 
geomTransf Linear 47 1.000 0.000 0.000 
geomTransf Linear 48 1.000 0.000 0.000 
geomTransf Linear 49 1.000 0.000 0.000 
geomTransf Linear 50 1.000 0.000 0.000 
geomTransf Linear 51 1.000 0.000 0.000 
geomTransf Linear 52 0.000 0.000 1.000 
geomTransf Linear 53 0.000 0.000 1.000 
geomTransf Linear 54 0.000 0.000 1.000 
geomTransf Linear 55 0.000 0.000 1.000 
geomTransf Linear 56 0.000 0.000 1.000 
geomTransf Linear 57 0.000 0.000 1.000 
geomTransf Linear 58 0.000 0.000 1.000 
geomTransf Linear 59 0.000 0.000 1.000 
geomTransf Linear 60 0.000 0.000 1.000 
geomTransf Linear 61 0.000 0.000 1.000 
geomTransf Linear 62 0.000 0.000 1.000 
geomTransf Linear 63 0.000 0.000 1.000 
geomTransf Linear 64 1.000 0.000 0.000 
geomTransf Linear 65 1.000 0.000 0.000 
geomTransf Linear 66 1.000 0.000 0.000 
geomTransf Linear 67 1.000 0.000 0.000 
geomTransf Linear 68 1.000 0.000 0.000 
geomTransf Linear 69 1.000 0.000 0.000 
geomTransf Linear 70 1.000 0.000 0.000 
geomTransf Linear 71 1.000 0.000 0.000 
geomTransf Linear 72 1.000 0.000 0.000 
geomTransf Linear 73 0.000 0.000 1.000 
geomTransf Linear 74 0.000 0.000 1.000 
geomTransf Linear 75 0.000 0.000 1.000 
geomTransf Linear 76 0.000 0.000 1.000 
geomTransf Linear 77 0.000 0.000 1.000 
geomTransf Linear 78 0.000 0.000 1.000 
geomTransf Linear 79 0.000 0.000 1.000 
geomTransf Linear 80 0.000 0.000 1.000 
geomTransf Linear 81 0.000 0.000 1.000 
geomTransf Linear 82 0.000 0.000 1.000 
geomTransf Linear 83 0.000 0.000 1.000 
geomTransf Linear 84 0.000 0.000 1.000 
geomTransf Linear 85 1.000 0.000 0.000 
geomTransf Linear 86 1.000 0.000 0.000 
geomTransf Linear 87 1.000 0.000 0.000 
geomTransf Linear 88 1.000 0.000 0.000 
geomTransf Linear 89 1.000 0.000 0.000 
geomTransf Linear 90 1.000 0.000 0.000 
geomTransf Linear 91 1.000 0.000 0.000 
geomTransf Linear 92 1.000 0.000 0.000 
geomTransf Linear 93 1.000 0.000 0.000 
geomTransf Linear 94 0.000 0.000 1.000 
geomTransf Linear 95 0.000 0.000 1.000 
geomTransf Linear 96 0.000 0.000 1.000 
geomTransf Linear 97 0.000 0.000 1.000 
geomTransf Linear 98 0.000 0.000 1.000 
geomTransf Linear 99 0.000 0.000 1.000 
geomTransf Linear 100 0.000 0.000 1.000 
geomTransf Linear 101 0.000 0.000 1.000 
geomTransf Linear 102 0.000 0.000 1.000 
geomTransf Linear 103 0.000 0.000 1.000 
geomTransf Linear 104 0.000 0.000 1.000 
geomTransf Linear 105 0.000 0.000 1.000 
geomTransf Linear 106 1.000 0.000 0.000 
geomTransf Linear 107 1.000 0.000 0.000 
geomTransf Linear 108 1.000 0.000 0.000 
geomTransf Linear 109 1.000 0.000 0.000 
geomTransf Linear 110 1.000 0.000 0.000 
geomTransf Linear 111 1.000 0.000 0.000 
geomTransf Linear 112 1.000 0.000 0.000 
geomTransf Linear 113 1.000 0.000 0.000 
geomTransf Linear 114 1.000 0.000 0.000 
geomTransf Linear 115 0.000 0.000 1.000 
geomTransf Linear 116 0.000 0.000 1.000 
geomTransf Linear 117 0.000 0.000 1.000 
geomTransf Linear 118 0.000 0.000 1.000 
geomTransf Linear 119 0.000 0.000 1.000 
geomTransf Linear 120 0.000 0.000 1.000 
geomTransf Linear 121 0.000 0.000 1.000 
geomTransf Linear 122 0.000 0.000 1.000 
geomTransf Linear 123 0.000 0.000 1.000 
geomTransf Linear 124 0.000 0.000 1.000 
geomTransf Linear 125 0.000 0.000 1.000 
geomTransf Linear 126 0.000 0.000 1.000 
puts "element"
element nonlinearBeamColumn 1 46 55 3 1001 1
element nonlinearBeamColumn 2 47 56 3 1001 2
element nonlinearBeamColumn 3 48 57 3 1001 3
element nonlinearBeamColumn 4 49 58 3 1001 4
element nonlinearBeamColumn 5 50 59 3 1001 5
element nonlinearBeamColumn 6 51 60 3 1001 6
element nonlinearBeamColumn 7 52 61 3 1001 7
element nonlinearBeamColumn 8 53 62 3 1001 8
element nonlinearBeamColumn 9 54 63 3 1001 9
element nonlinearBeamColumn 10 55 56 3 1002 10
element nonlinearBeamColumn 11 56 57 3 1002 11
element nonlinearBeamColumn 12 58 59 3 1002 12
element nonlinearBeamColumn 13 59 60 3 1002 13
element nonlinearBeamColumn 14 61 62 3 1002 14
element nonlinearBeamColumn 15 62 63 3 1002 15
element nonlinearBeamColumn 16 55 58 3 1002 16
element nonlinearBeamColumn 17 58 61 3 1002 17
element nonlinearBeamColumn 18 56 59 3 1002 18
element nonlinearBeamColumn 19 59 62 3 1002 19
element nonlinearBeamColumn 20 57 60 3 1002 20
element nonlinearBeamColumn 21 60 63 3 1002 21
element nonlinearBeamColumn 22 2 46 3 1001 22
element nonlinearBeamColumn 23 4 47 3 1001 23
element nonlinearBeamColumn 24 6 48 3 1001 24
element nonlinearBeamColumn 25 8 49 3 1001 25
element nonlinearBeamColumn 26 10 50 3 1001 26
element nonlinearBeamColumn 27 12 51 3 1001 27
element nonlinearBeamColumn 28 14 52 3 1001 28
element nonlinearBeamColumn 29 16 53 3 1001 29
element nonlinearBeamColumn 30 18 54 3 1001 30
element nonlinearBeamColumn 31 46 47 3 1002 31
element nonlinearBeamColumn 32 47 48 3 1002 32
element nonlinearBeamColumn 33 49 50 3 1002 33
element nonlinearBeamColumn 34 50 51 3 1002 34
element nonlinearBeamColumn 35 52 53 3 1002 35
element nonlinearBeamColumn 36 53 54 3 1002 36
element nonlinearBeamColumn 37 46 49 3 1002 37
element nonlinearBeamColumn 38 49 52 3 1002 38
element nonlinearBeamColumn 39 47 50 3 1002 39
element nonlinearBeamColumn 40 50 53 3 1002 40
element nonlinearBeamColumn 41 48 51 3 1002 41
element nonlinearBeamColumn 42 51 54 3 1002 42
element nonlinearBeamColumn 43 1 2 3 1001 43
element nonlinearBeamColumn 44 3 4 3 1001 44
element nonlinearBeamColumn 45 5 6 3 1001 45
element nonlinearBeamColumn 46 7 8 3 1001 46
element nonlinearBeamColumn 47 9 10 3 1001 47
element nonlinearBeamColumn 48 11 12 3 1001 48
element nonlinearBeamColumn 49 13 14 3 1001 49
element nonlinearBeamColumn 50 15 16 3 1001 50
element nonlinearBeamColumn 51 17 18 3 1001 51
element nonlinearBeamColumn 52 2 4 3 1002 52
element nonlinearBeamColumn 53 4 6 3 1002 53
element nonlinearBeamColumn 54 8 10 3 1002 54
element nonlinearBeamColumn 55 10 12 3 1002 55
element nonlinearBeamColumn 56 14 16 3 1002 56
element nonlinearBeamColumn 57 16 18 3 1002 57
element nonlinearBeamColumn 58 2 8 3 1002 58
element nonlinearBeamColumn 59 8 14 3 1002 59
element nonlinearBeamColumn 60 4 10 3 1002 60
element nonlinearBeamColumn 61 10 16 3 1002 61
element nonlinearBeamColumn 62 6 12 3 1002 62
element nonlinearBeamColumn 63 12 18 3 1002 63
element nonlinearBeamColumn 64 19 1 3 1001 64
element nonlinearBeamColumn 65 20 3 3 1001 65
element nonlinearBeamColumn 66 21 5 3 1001 66
element nonlinearBeamColumn 67 22 7 3 1001 67
element nonlinearBeamColumn 68 23 9 3 1001 68
element nonlinearBeamColumn 69 24 11 3 1001 69
element nonlinearBeamColumn 70 25 13 3 1001 70
element nonlinearBeamColumn 71 26 15 3 1001 71
element nonlinearBeamColumn 72 27 17 3 1001 72
element nonlinearBeamColumn 73 1 3 3 1002 73
element nonlinearBeamColumn 74 3 5 3 1002 74
element nonlinearBeamColumn 75 7 9 3 1002 75
element nonlinearBeamColumn 76 9 11 3 1002 76
element nonlinearBeamColumn 77 13 15 3 1002 77
element nonlinearBeamColumn 78 15 17 3 1002 78
element nonlinearBeamColumn 79 1 7 3 1002 79
element nonlinearBeamColumn 80 7 13 3 1002 80
element nonlinearBeamColumn 81 3 9 3 1002 81
element nonlinearBeamColumn 82 9 15 3 1002 82
element nonlinearBeamColumn 83 5 11 3 1002 83
element nonlinearBeamColumn 84 11 17 3 1002 84
element nonlinearBeamColumn 85 28 19 3 1001 85
element nonlinearBeamColumn 86 29 20 3 1001 86
element nonlinearBeamColumn 87 30 21 3 1001 87
element nonlinearBeamColumn 88 31 22 3 1001 88
element nonlinearBeamColumn 89 32 23 3 1001 89
element nonlinearBeamColumn 90 33 24 3 1001 90
element nonlinearBeamColumn 91 34 25 3 1001 91
element nonlinearBeamColumn 92 35 26 3 1001 92
element nonlinearBeamColumn 93 36 27 3 1001 93
element nonlinearBeamColumn 94 19 20 3 1002 94
element nonlinearBeamColumn 95 20 21 3 1002 95
element nonlinearBeamColumn 96 22 23 3 1002 96
element nonlinearBeamColumn 97 23 24 3 1002 97
element nonlinearBeamColumn 98 25 26 3 1002 98
element nonlinearBeamColumn 99 26 27 3 1002 99
element nonlinearBeamColumn 100 19 22 3 1002 100
element nonlinearBeamColumn 101 22 25 3 1002 101
element nonlinearBeamColumn 102 20 23 3 1002 102
element nonlinearBeamColumn 103 23 26 3 1002 103
element nonlinearBeamColumn 104 21 24 3 1002 104
element nonlinearBeamColumn 105 24 27 3 1002 105
element nonlinearBeamColumn 106 37 28 3 1001 106
element nonlinearBeamColumn 107 38 29 3 1001 107
element nonlinearBeamColumn 108 39 30 3 1001 108
element nonlinearBeamColumn 109 40 31 3 1001 109
element nonlinearBeamColumn 110 41 32 3 1001 110
element nonlinearBeamColumn 111 42 33 3 1001 111
element nonlinearBeamColumn 112 43 34 3 1001 112
element nonlinearBeamColumn 113 44 35 3 1001 113
element nonlinearBeamColumn 114 45 36 3 1001 114
element nonlinearBeamColumn 115 28 29 3 1002 115
element nonlinearBeamColumn 116 29 30 3 1002 116
element nonlinearBeamColumn 117 31 32 3 1002 117
element nonlinearBeamColumn 118 32 33 3 1002 118
element nonlinearBeamColumn 119 34 35 3 1002 119
element nonlinearBeamColumn 120 35 36 3 1002 120
element nonlinearBeamColumn 121 28 31 3 1002 121
element nonlinearBeamColumn 122 31 34 3 1002 122
element nonlinearBeamColumn 123 29 32 3 1002 123
element nonlinearBeamColumn 124 32 35 3 1002 124
element nonlinearBeamColumn 125 30 33 3 1002 125
element nonlinearBeamColumn 126 33 36 3 1002 126
puts "recorder"
recorder Node -file node59.out -time -node 59 -dof 1 disp
recorder Node -file node0.out -time -nodeRange 1 63 -dof 1 2 3 disp
recorder Element -file shear.out -time -eleRange 106 114 localForce
puts "gravity"
## Load Case = DEAD
pattern Plain 1 Linear {
eleLoad -ele 10 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 10 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 16 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 16 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 16 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 12 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 12 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 18 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 18 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 18 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 11 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 11 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 18 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 18 -type -beamUniform 0 -1.800E+000 0
eleLoad -ele 18 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 13 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 13 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 20 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 20 -type -beamUniform 0 -1.800E+000 0
eleLoad -ele 20 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 13 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 13 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 19 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 19 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 19 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 15 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 15 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 21 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 21 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 21 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 12 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 12 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 17 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 17 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 14 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 14 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 19 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 19 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 31 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 31 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 37 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 37 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 37 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 33 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 33 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 39 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 39 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 39 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 32 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 32 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 39 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 39 -type -beamUniform 0 -1.800E+000 0
eleLoad -ele 39 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 34 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 34 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 41 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 41 -type -beamUniform 0 -1.800E+000 0
eleLoad -ele 41 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 34 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 34 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 40 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 40 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 40 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 36 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 36 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 42 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 42 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 42 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 33 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 33 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 38 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 38 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 35 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 35 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 40 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 40 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 52 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 52 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 58 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 58 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 58 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 54 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 54 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 60 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 60 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 60 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 53 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 53 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 60 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 60 -type -beamUniform 0 -1.800E+000 0
eleLoad -ele 60 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 55 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 55 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 62 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 62 -type -beamUniform 0 -1.800E+000 0
eleLoad -ele 62 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 55 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 55 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 61 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 61 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 61 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 57 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 57 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 63 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 63 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 63 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 54 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 54 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 59 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 59 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 56 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 56 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 61 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 61 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 73 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 73 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 79 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 79 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 79 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 75 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 75 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 81 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 81 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 81 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 74 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 74 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 81 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 81 -type -beamUniform 0 -1.800E+000 0
eleLoad -ele 81 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 76 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 76 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 83 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 83 -type -beamUniform 0 -1.800E+000 0
eleLoad -ele 83 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 76 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 76 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 82 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 82 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 82 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 78 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 78 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 84 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 84 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 84 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 75 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 75 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 80 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 80 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 77 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 77 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 82 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 82 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 94 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 94 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 100 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 100 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 100 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 96 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 96 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 102 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 102 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 102 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 95 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 95 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 102 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 102 -type -beamUniform 0 -1.800E+000 0
eleLoad -ele 102 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 97 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 97 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 104 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 104 -type -beamUniform 0 -1.800E+000 0
eleLoad -ele 104 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 97 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 97 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 103 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 103 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 103 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 99 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 99 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 105 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 105 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 105 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 96 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 96 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 101 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 101 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 98 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 98 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 103 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 103 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 115 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 115 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 121 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 121 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 121 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 117 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 117 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 123 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 123 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 123 -type -beamUniform 0 -1.200E+000 0
eleLoad -ele 116 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 116 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 123 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 123 -type -beamUniform 0 -1.800E+000 0
eleLoad -ele 123 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 118 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 118 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 125 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 125 -type -beamUniform 0 -1.800E+000 0
eleLoad -ele 125 -type -beamUniform 0 -6.750E-001 0
eleLoad -ele 118 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 118 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 124 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 124 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 124 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 120 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 120 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 126 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 126 -type -beamUniform 0 -1.125E+000 0
eleLoad -ele 126 -type -beamUniform 0 -8.438E-001 0
eleLoad -ele 117 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 117 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 122 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 122 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 119 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 119 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 124 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 124 -type -beamUniform 0 -1.500E+000 0
eleLoad -ele 10 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 10 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 16 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 16 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 16 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 12 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 12 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 18 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 18 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 18 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 11 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 11 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 18 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 18 -type -beamUniform 0 -9.000E-001 0
eleLoad -ele 18 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 13 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 13 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 20 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 20 -type -beamUniform 0 -9.000E-001 0
eleLoad -ele 20 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 13 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 13 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 19 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 19 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 19 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 15 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 15 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 21 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 21 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 21 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 12 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 12 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 17 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 17 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 14 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 14 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 19 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 19 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 31 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 31 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 37 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 37 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 37 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 33 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 33 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 39 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 39 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 39 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 32 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 32 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 39 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 39 -type -beamUniform 0 -9.000E-001 0
eleLoad -ele 39 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 34 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 34 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 41 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 41 -type -beamUniform 0 -9.000E-001 0
eleLoad -ele 41 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 34 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 34 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 40 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 40 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 40 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 36 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 36 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 42 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 42 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 42 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 33 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 33 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 38 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 38 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 35 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 35 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 40 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 40 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 52 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 52 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 58 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 58 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 58 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 54 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 54 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 60 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 60 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 60 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 53 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 53 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 60 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 60 -type -beamUniform 0 -9.000E-001 0
eleLoad -ele 60 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 55 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 55 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 62 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 62 -type -beamUniform 0 -9.000E-001 0
eleLoad -ele 62 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 55 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 55 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 61 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 61 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 61 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 57 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 57 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 63 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 63 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 63 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 54 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 54 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 59 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 59 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 56 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 56 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 61 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 61 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 73 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 73 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 79 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 79 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 79 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 75 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 75 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 81 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 81 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 81 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 74 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 74 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 81 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 81 -type -beamUniform 0 -9.000E-001 0
eleLoad -ele 81 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 76 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 76 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 83 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 83 -type -beamUniform 0 -9.000E-001 0
eleLoad -ele 83 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 76 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 76 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 82 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 82 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 82 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 78 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 78 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 84 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 84 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 84 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 75 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 75 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 80 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 80 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 77 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 77 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 82 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 82 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 94 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 94 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 100 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 100 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 100 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 96 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 96 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 102 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 102 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 102 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 95 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 95 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 102 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 102 -type -beamUniform 0 -9.000E-001 0
eleLoad -ele 102 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 97 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 97 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 104 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 104 -type -beamUniform 0 -9.000E-001 0
eleLoad -ele 104 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 97 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 97 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 103 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 103 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 103 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 99 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 99 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 105 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 105 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 105 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 96 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 96 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 101 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 101 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 98 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 98 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 103 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 103 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 115 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 115 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 121 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 121 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 121 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 117 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 117 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 123 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 123 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 123 -type -beamUniform 0 -6.000E-001 0
eleLoad -ele 116 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 116 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 123 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 123 -type -beamUniform 0 -9.000E-001 0
eleLoad -ele 123 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 118 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 118 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 125 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 125 -type -beamUniform 0 -9.000E-001 0
eleLoad -ele 125 -type -beamUniform 0 -3.375E-001 0
eleLoad -ele 118 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 118 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 124 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 124 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 124 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 120 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 120 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 126 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 126 -type -beamUniform 0 -5.625E-001 0
eleLoad -ele 126 -type -beamUniform 0 -4.219E-001 0
eleLoad -ele 117 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 117 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 122 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 122 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 119 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 119 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 124 -type -beamUniform 0 -7.500E-001 0
eleLoad -ele 124 -type -beamUniform 0 -7.500E-001 0
}

puts "analysis"
constraints Plain
numberer Plain
system BandGeneral
test EnergyIncr 1.0e-6 200
algorithm Newton
integrator LoadControl 0.1
analysis Static
analyze 10
loadConst -time 0.0
 
set xDamp 0.05;
set nEigenI 1;
set nEigenJ 2;
set lambdaN [eigen [expr $nEigenJ]];
set lambdaI [lindex $lambdaN [expr $nEigenI-1]];
set lambdaJ [lindex $lambdaN [expr $nEigenJ-1]];
set omegaI [expr pow($lambdaI,0.5)]; 
set omegaJ [expr pow($lambdaJ,0.5)];
set alphaM [expr $xDamp*(2*$omegaI*$omegaJ)/($omegaI+$omegaJ)]; 
set betaKcurr [expr 2.*$xDamp/($omegaI+$omegaJ)];   
rayleigh $alphaM $betaKcurr 0 0  
  
set IDloadTag 1001;
set iGMfile "GM1X.txt";
set iGMdirection "1"; 
set iGMfact "0.6072";  
set dt 0.02;   
foreach GMdirection $iGMdirection GMfile $iGMfile GMfact $iGMfact { 
incr IDloadTag; 
set GMfatt [expr 1*$GMfact];  
set AccelSeries "Series -dt $dt -filePath $iGMfile -factor  $GMfatt";
pattern UniformExcitation  $IDloadTag  $GMdirection -accel  $AccelSeries; 
}  
  
constraints Transformation; 
numberer Plain;  
system UmfPack; 
test NormDispIncr  1.0e-1 1000; 
algorithm Newton 
integrator Newmark 0.5 0.25 
analysis Transient
analyze 3000 0.005
