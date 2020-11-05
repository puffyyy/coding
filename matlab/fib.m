function res=fib(n)
if n>1
    res = n*fib(n-1);
else 
    res=1;
end