function sta = right(pos)
%DOWN 此处显示有关此函数的摘要
sta = -1;
if rem(pos, 3)~=0 
    sta = pos+1;
end
end

