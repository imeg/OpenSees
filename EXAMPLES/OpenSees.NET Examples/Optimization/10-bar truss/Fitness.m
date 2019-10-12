function weight = Fitness(A)
	l=360; r= 0.1; lp = l*sqrt(2);weight =0;
	L = [l,l,l,l,l,l,lp,lp,lp,lp];
	for i=1:10
	weight = weight + L(i)*A(i)*r;
	end
end

