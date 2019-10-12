function [c,ceq] = Constraints(A)
respId = 2;ceq =[];
NET.addAssembly(strcat(pwd,'\OpenSees.NET.X64.dll'));
import OpenSees.Tcl.*;
tcl = OpenSees.Tcl.TclWrapper();
tcl.Init();
tclAs = ToTclArray(A);
tcl.Execute("set As "+tclAs+";");
tcl.Execute("source model.tcl");
theDomain = tcl.GetActiveDomain();
c = [-25,-25,-25,-25,-25,-25,-25,-25,-75,-25, ...
    0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1];
vec = OpenSees.VectorWrapper([0;0]);
for i=1:10
    theDomain.GetElement(i).GetVectorResponse(respId, vec);
    response = vec.Get(0)/A(i);
    c(i) =c(i)+abs(response);
    c(i+10)=c(i+10)-A(i);
end
end

