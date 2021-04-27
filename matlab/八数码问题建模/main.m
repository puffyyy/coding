terminal_vec=[1,2,3,4,5,6,7,8,9,9];
terminal_str = char(terminal_vec + '0');
terminal_num =int64(str2double(terminal_str));
ori_vec =  randperm(9);%[9,1,3,4,2,5,7,8,6];
ori_str = char(ori_vec+'0');
% 寻找9的位置
z=9;
for i = 1:9
    if ori_vec(i) == 9
        z=i;
        break;
    end
end
% 将9的位置保存在ori中
ori_vec(10)=z;
ori_str = strcat (ori_str , '0'+z);
ori_num = int64(str2double(ori_str));

if judge(ori_vec,terminal_vec)
    map = containers.Map(ori_str,int64(0));
    path = containers.Map('0',ori_str);
    %初始化queue
    queue = zeros(30005,1,'int64'); % 提前分好内存
    Q_size = 30000;
    queue(1) = ori_num; % 初值
    queueTop = 1; % 队首
    queueBack = 2; % 队尾，实际指向最后一个数的下一个
    % queue(queueTop)
    % queue(queueTop) = 0; queueTop = mod(queueTop,Q_size) + 1; % 出队
    % queue(queueBack) = insertVal; queueBack = mod(queueBack,Q_size)+1; % 入队
    
    steps = -1;
    
    while(queueTop~=queueBack)
        state_now=queue(queueTop);
        queue(queueTop) = 0;  queueTop = mod(queueTop,Q_size) + 1;
        a = num2str(state_now);
        z=a(10)-'0';
        pos = up(z);
        if pos ~= -1
            b = a;
            [b(z) ,b(pos)]=deal(b(pos),b(z));
            b(10) = pos + '0';
            num_change = int64(str2double(b));
            if ~isKey(map,b)
                map(b) = map(a) + 1;
                queue(queueBack) = num_change;
                queueBack = mod(queueBack,Q_size)+1;
                path(b)=a;
            end
            if (num_change == terminal_num)
                steps =  map(b);
                break;
            end
        end
        
        pos = left(z);
        if pos ~= -1
            b = a;
            [b(z) ,b(pos)]=deal(b(pos),b(z));
            b(10) = pos + '0';
            num_change = int64(str2double(b));
            if ~isKey(map,b)
                map(b) = map(a) + 1;
                queue(queueBack) = num_change;
                queueBack = mod(queueBack,Q_size)+1;
                path(b)=a;
            end
            if (num_change == terminal_num)
                steps =  map(b);
                break;
            end
        end
        
        pos = right(z);
        if pos ~= -1
            b = a;
            [b(z) ,b(pos)]=deal(b(pos),b(z));
            b(10) = pos + '0';
            num_change = int64(str2double(b));
            if ~isKey(map,b)
                map(b) = map(a) + 1;
                queue(queueBack) = num_change;
                queueBack = mod(queueBack,Q_size)+1;
                path(b)=a;
            end
            if (num_change == terminal_num)
                steps =  map(b);
                break;
            end
        end
        
        pos = down(z);
        if pos ~= -1
            b = a;
            [b(z) ,b(pos)]=deal(b(pos),b(z));
            b(10) = pos + '0';
            num_change = int64(str2double(b));
            if ~isKey(map,b)
                map(b) = map(a) + 1;
                queue(queueBack) = num_change;
                queueBack = mod(queueBack,Q_size)+1;
                path(b)=a;
            end
            if (num_change == terminal_num)
                steps =  map(b);
                break;
            end
        end
        
    end
    fprintf('step is %d\n',steps);
    fprintf('Starting state is \n');
    draw(ori_str);
    fprintf('Target state is \n');
    draw(ori_str);
    
    print = containers.Map();
    temp =terminal_str;
    pre = temp;
    while(any(path(temp) ~= ori_str))
        pre = path(temp);ans
        print(pre)=temp;
        temp=pre;
    end
    print(ori_str)=temp;
    temp =ori_str;
    while(any(temp ~= terminal_str))
        draw(temp);
        temp=print(temp);
    end
    draw(terminal_str);
else
    fprintf('no solution\n')
end
