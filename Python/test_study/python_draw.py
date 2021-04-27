s = '''双儿 洪七公 赵敏 赵敏 逍遥子 鳌拜 殷天正 金轮法王 乔峰 杨过 洪七公'''
ls = list(s.split(" "))
dic = {}
for item in ls:
    if (item == ''):
        continue
    elif item == '\n':
        continue
    dic[item] = dic.get(item, 0) + 1
ls = list(dic.items())

ls.sort(key=lambda x: x[1], reverse=True)
print(ls[0][0])
