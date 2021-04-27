function flag = judge(vec,terminal_vec)
%terminal_vec=[1,2,3,4,5,6,7,8,0];
ori_cnt = 0;
ter_cnt = 0;
for i=1:9
    for j =1:i
    if vec(j) > vec(i) && vec(j)~= 9
        ori_cnt = ori_cnt + 1;
    end
    end
end
for i=1:9
    for j =1:i
    if terminal_vec(j) > terminal_vec(i) && terminal_vec(j)~= 9
        ori_cnt = ori_cnt + 1;
    end
    end
    %ter_cnt=ter_cnt+sum(terminal_vec(1:i-1)<terminal_vec(i));
end
flag = (mod(ori_cnt,2)==mod(ter_cnt,2));
end

