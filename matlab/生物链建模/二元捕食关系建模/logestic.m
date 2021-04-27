function dy = vdp(t,x)
% rx-axy
% -dy+bxy
r=1;
a=0.1;
d=0.5;
b=0.02;
% N1 3000 N2 400 
% r1 1    r2 0.3
% sigma1 2 sigma2 6
dy=[x(1).*(1-x(1)./3000-2*x(2)./400);0.3.*x(2).*(-1+6.*x(1)./3000-x(2)./400)];
end

