x0=[100,20,6];
ts=0:0.1:40;

[t,x]=ode45('fun3',ts,x0);
subplot(1,2,1);

plot(t,x);
legend('x_1(t)','x_2(t)','x_3(t)');
grid
subplot(1,2,2);
plot3(x(:,1),x(:,2),x(:,3));
xlabel('x_1'),ylabel('x_2'),zlabel('x_3');
grid on;