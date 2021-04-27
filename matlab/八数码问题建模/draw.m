function  draw(str)

for i=1:9
    if mod(i,3)
        fprintf('%s ',str(i));
    else
        fprintf('%s\n',str(i));
    end
end
fprintf('\n');;
end

