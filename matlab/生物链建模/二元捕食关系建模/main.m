x0=[50,6];
ts=0:0.1:100;

[t,x]=ode45('odefun',ts,x0);
subplot(2,1,1);
grid;
plot(t,x);
title("种群数量随时间变化");
legend('x(t)','y(t)');
xlabel("时间");
ylabel("种群数量");

subplot(2,1,2);
plot(x(:,1),x(:,2));
title("相轨线");
xlabel("x");
ylabel("y");