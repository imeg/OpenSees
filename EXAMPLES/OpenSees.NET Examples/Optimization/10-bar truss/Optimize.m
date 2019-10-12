clc;
a0 = [0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1];
nonlcon = @Constraints;
func = @Fitness;
options = optimoptions('fmincon','Display','iter','Algorithm','sqp');
[x,fval,exitflag] = fmincon(func,a0,[],[],[],[],[],[],nonlcon, options);
