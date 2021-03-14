/* mumps_int_def.h will define either MUMPS_INTSIZE32 (default)
   or MUMPS_INTSIZE64 (if compilation is with -DINTSIZE64 to
   match Fortran -i8 or equivalent option). This allows one to
   test from an external code whether MUMPS_INT is 64bits or not */

// #define MUMPS_INTSIZE32
#define MUMPS_INTSIZE64