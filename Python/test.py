wi = [
    0, 422.88, 282.88, 268.36, 277.70, 332.29, 603.06, 714.72, 435.84, 343.08,
    641.45, 667.21, 472.30, 340.51, 476.60, 471.25
]
li = [
    0, 44351.13, 39229.01, 54787.74, 45284.39, 53479.79, 897.32, 896.09,
    1096.33, 890.53, 752.61, 970.16, 998.29, 1024.87, 621.91, 1243.03
]

Li = [
    0, 148623.91, 32960.49, 75508.72, 14091.52, 75040.31, 138570.39, 98641.28,
    114074.27, 104637.72, 58023.82
]
Wi = [
    0, 1519.91, 999.35, 1232.32, 920.62, 1573.71, 844.99, 1184.54, 879.02,
    969.02, 1785.45
]
sorder = [0] * len(li)
for i in range(len(li)):
    sorder[i] = li[i] * wi[i]
sraw = [0] * len(li)
for i in range(len(Li)):
    sraw[i] = Li[i] * Wi[i]
remain7 = 75457144.09
remain8 = 33712378.22
map_r = []
with open("r.txt", "r") as f:
    f.readline()
    for i in range(13):
        line = f.readline().strip('\n').strip(' ')
        map_r.append(list(map(lambda x: int(x), line.split('	'))))
# print(map_r)
ans = [0] * 15
cnt = 0
sum = 0
used = 0
for line in map_r:
    cnt += 1
    # print(line[16])
    tmp = 0
    for i in range(2, 17):
        tmp += sorder[i - 1] * line[i]
    if cnt == 12:
        tmp += remain7
    if cnt == 13:
        tmp += remain8
    ans[cnt] = tmp / sraw[line[0]]
    sum += sraw[line[0]]
    used += tmp

for i in range(1, 14):
    print(ans[i])
print(used, sum, used / sum)
