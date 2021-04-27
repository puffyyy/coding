s = ["1,2,3", "4,5,6", "7,8,9"]
ls = []
for line in s:
    ls.append((line.split(",")))
    # print(ls[-1])
for i in range(len(ls)):
    li = ls.pop()
    ll = reversed(li)
    ll = list(ll)
    print(ll)
