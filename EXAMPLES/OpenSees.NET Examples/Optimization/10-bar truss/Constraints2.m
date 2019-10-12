function [ c,ceq ] = Constraints2(A)
l=360;e=3000.0;p=100;ceq = [];ndm = 2;respId = 2;
NET.addAssembly('System');NET.addAssembly('System.IO');
NET.addAssembly(strcat(pwd,'\OpenSees.NET.X64.dll'));
theDomain = OpenSees.Components.DomainWrapper();
import OpenSees.Components.*;import OpenSees.Elements.*;
import OpenSees.Components.Constraints.*;
import  OpenSees.Components.Loads.*;
nodes = [l*2,l;2*l,0;l*1,l;l*1,0;0,l;0,0];
for i=1:6
    theDomain.AddNode(NodeWrapper(i,2,nodes(i,1),nodes(i,2)));
end
theMaterial = OpenSees.Materials.Uniaxials.ElasticMaterialWrapper(1, e,0);
eles = [5, 3;3, 1;6, 4;4, 2;3, 4; 1, 2;5, 4;6, 3;3, 2;4, 1];
for i=1:10
    theDomain.AddElement(TrussWrapper(i, ndm, eles(i,1), eles(i,2), ...
        theMaterial, A(i), 0, 0, 0));
end
for i=5:6
    for j=0:1
        theDomain.AddSP_Constraint(SP_ConstraintWrapper(i, j, 0.0, true));
    end
end
theSeries = OpenSees.Components.Timeseries.LinearSeriesWrapper();
theLoadPattern = OpenSees.Components.LoadPatterns.LoadPatternWrapper(1);
theLoadPattern.SetTimeSeries(theSeries);
theDomain.AddLoadPattern(theLoadPattern);
theLoadValues = OpenSees.VectorWrapper([0;-p]);
theDomain.AddNodalLoad(NodalLoadWrapper(2, 2, theLoadValues, false), 1);
theDomain.AddNodalLoad(NodalLoadWrapper(1, 4, theLoadValues, false), 1);
theSolver =  OpenSees.Systems.Linears.BandSPDLinLapackSolverWrapper();
theAnalysis =  OpenSees.Analysis.StaticAnalysisWrapper(...
    theDomain,...
    OpenSees.Handlers.PlainHandlerWrapper(),...
    OpenSees.Numberers.PlainNumbererWrapper(),...
    OpenSees.AnalysisModelWrapper(),...
    OpenSees.Algorithms.LinearWrapper(),...
    OpenSees.Systems.Linears.BandSPDLinSOEWrapper(theSolver),...
    OpenSees.Integrators.Static.LoadControlWrapper(1.0, 1, 1.0, 1.0),...
    OpenSees.ConvergenceTests.CTestNormDispIncrWrapper(1e-8, 6, 2, 2, 1.0e10)...
);
theAnalysis.Analyze(1);
c = [-25,-25,-25,-25,-25,-25,-25,-25,-75,-25, ...
    0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1];
vec = OpenSees.VectorWrapper([0;0]);
for i=1:10
    theDomain.GetElement(i).GetVectorResponse(respId, vec);
    c(i) =c(i)+abs(vec.Get(0)/A(i));
    c(i+10)=c(i+10)-A(i);
end
end

