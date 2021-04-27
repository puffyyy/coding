function dy = vdp(t,x)

r1=1;r2=0.5;r3=0.6;
lambda1 = 0.1;lambda2=0.02;lambda3=0.06;
mu=0.1;
dy = [x(1)*(r1-lambda1*x(2));x(2)*(-r2+lambda2*x(1)-mu*x(3));x(3)*(-r3+lambda3*x(2))];
end

