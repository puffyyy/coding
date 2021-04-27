function dy = vdp(t,x)
% rx-axy
% -dy+bxy
r=1;
a=0.1;
d=0.5;
b=0.02;
dy = [r*x(1)-a*x(1)*x(2);-d*x(2)+b*x(1)*x(2)];
end

