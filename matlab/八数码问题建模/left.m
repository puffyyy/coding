function sta = left(pos)
%DOWN �˴���ʾ�йش˺�����ժҪ
sta = -1;
if rem(pos-1, 3) ~= 0
    sta = pos-1;
end
end

