import random
from copy import deepcopy
import numpy as np

popsize = 160  # 种群大小 200
mutprob = 0.4  # 新种群由变异得来的概率
transprob = 0.8
elite = 0.4  # 种群中是优解，且被允许遗传给下一代的部分
maxiter = 20  # 需运行多少代
material = 2

Li = [
    0, 148623.91, 32960.49, 75508.72, 14091.52, 75040.31, 138570.39, 98641.28,
    114074.27, 104637.72, 58023.82
]
Wi = [
    0, 1519.91, 999.35, 1232.32, 920.62, 1573.71, 844.99, 1184.54, 879.02,
    969.02, 1785.45
]

W = Wi[material]
L = Li[material]

# 自变量维数
# [卷还是板，各列是哪个订单]*col
row = min(int(W / 268.36), 5) + 1
col = int(L / 621.91)
print('row', row)

dimen_x = row * col

wi = [
    0, 422.88, 282.88, 268.36, 277.70, 332.29, 603.06, 714.72, 435.84, 343.08,
    641.45, 667.21, 472.30, 340.51, 476.60, 471.25
]
li = [
    0, 44351.13, 39229.01, 54787.74, 45284.39, 53479.79, 897.32, 896.09,
    1096.33, 890.53, 752.61, 970.16, 998.29, 1024.87, 621.91, 1243.03
]
si = []
for i in range(16):
    si.append(wi[i] * li[i])


def abstract_feature(optvec):
    order = [0] * 16
    for i_col in range(col):
        for i_row in range(row - 1):
            order[optvec[i_col * row + i_row + 1]] += 1
    w_spare = [0] * col
    for i_col in range(col):
        sum_w = 0
        for i_row in range(row - 1):
            sum_w += wi[optvec[i_col * row + i_row + 1]]
        w_spare[i_col] = W - sum_w

    l_col = [0] * col
    for i_col in range(col):
        max_l = 0
        for i_row in range(row - 1):
            if max_l < li[optvec[i_col * row + i_row + 1]]:
                max_l = li[optvec[i_col * row + i_row + 1]]
        l_col[i_col] = max_l

    l_spare = L - sum(l_col)

    sums = 0
    for i_col in range(col):
        # print('i_col', i_col)
        for i_row in range(row - 1):
            sums += si[optvec[i_col * row + i_row + 1]]
    yita = sums / W / L

    print(optvec)
    print(w_spare)
    print(l_col)
    print('材料剩余长度', l_spare)
    print('成材率', yita, '订单面积', sums)
    print(order)


# Mutation Operation
def mutate(vec1):
    mut_col = random.randint(0, col - 1)  # 变异点所处col
    mut_row = random.randint(1, row - 1)  # 变异点所处row
    if random.random() < 0.8:
        if vec1[row * mut_col] == 0:
            vec1[row * mut_col + mut_row] = random.randint(0, 5)
        if vec1[row * mut_col] == 1:
            vec1[row * mut_col + mut_row] = random.randint(6, 15)
            judge = random.randint(0, 8)
            if judge == 0:
                vec1[row * mut_col + mut_row] = 0
        return vec1
    else:
        return vec1


# Crossover Operation
def crossover(r1, r2):
    col_cross = random.randint(1, col - 2)
    new = r1[0:(col_cross * row)] + r2[(col_cross * row):]
    return new


def transfer(t1, t2):
    col_cross = random.randint(1, col - 2)
    newt = t1[0:(col_cross * row)] + t2[(col_cross * row):(
        col_cross * row + row)] + t1[(col_cross * row + row):]
    return newt


def aimfunc(vec):
    sum = 0

    for i_col in range(col):
        #print('i_col', i_col)
        for i_row in range(row - 1):
            sum += si[vec[i_col * row + i_row + 1]]
            #print('s', i_col*row+i_row+1, vec[i_col*row+i_row+1], si[vec[i_col*row+i_row+1]])
    yita = sum / W / L

    weight = np.array([
        0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2,
        0.2, 0.2
    ])
    num_order = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

    for i_col in range(col):
        for i_row in range(row - 1):
            num_order[vec[i_col * row + i_row + 1]] += 1
    num_order = np.array(num_order).T
    result = np.dot(weight, num_order)
    #print(result)
    return 0 - 3 * yita - 0.01 * result


def constraint(vec):
    if len(vec) != dimen_x:
        print('vec长度不对')
        return 0

    for i_col in range(col):
        if vec[i_col * row] == 0:
            for i_row in range(row - 1):
                if vec[i_col * row + i_row + 1] > 5:
                    return 0
        if vec[i_col * row] == 1:
            for i_row in range(row - 1):
                if vec[i_col * row + i_row + 1] < 6 and vec[i_col * row +
                                                            i_row + 1] > 0:
                    return 0

    sum_l = 0
    for i_col in range(col):
        max_l = 0
        for i_row in range(row - 1):
            if max_l < li[vec[i_col * row + i_row + 1]]:
                max_l = li[vec[i_col * row + i_row + 1]]
        sum_l += max_l
        if sum_l > L:
            #print('不满足长度约束')
            return 0

    for i_col in range(col):
        sum_w = 0
        for i_row in range(row - 1):
            sum_w += wi[vec[i_col * row + i_row + 1]]
        if sum_w > W:
            #print('不满足宽度约束')
            return 0

    return 1


# Build the initial population
pop = []

while (len(pop) < popsize):
    print('len_pop', len(pop))
    # 初始化染色体
    vec = [0] * dimen_x
    sum_l = 0
    for i_col in range(col):

        vec[i_col * row] = random.randint(0, 1)
        if vec[i_col * row] == 0:  # 卷料
            sum_w = 0
            for i_row in range(row - 1):
                vec[i_col * row + i_row + 1] = random.randint(0, 5)
                sum_w += wi[vec[i_col * row + i_row + 1]]
                if sum_w > W:
                    vec[i_col * row + i_row + 1] = 0
                    break
        elif vec[i_col * row] == 1:  # 板料
            sum_w = 0
            for i_row in range(row - 1):
                vec[i_col * row + i_row + 1] = random.randint(6, 15)
                judge = random.randint(0, 9)
                if judge == 0:
                    vec[i_col * row + i_row + 1] = 0
                sum_w += wi[vec[i_col * row + i_row + 1]]
                if sum_w > W:
                    vec[i_col * row + i_row + 1] = 0
                    break

        max_l = 0
        for i_row in range(row - 1):
            if max_l < li[vec[i_col * row + i_row + 1]]:
                max_l = li[vec[i_col * row + i_row + 1]]
        sum_l += max_l
        if sum_l > L and max_l > 30000:
            sum_l -= max_l
            sum_w = 0
            for i_row in range(row - 1):
                vec[i_col * row + i_row + 1] = random.randint(6, 15)
                judge = random.randint(0, 9)
                if judge == 0:
                    vec[i_col * row + i_row + 1] = 0
                sum_w += wi[vec[i_col * row + i_row + 1]]
                if sum_w > W:
                    vec[i_col * row + i_row + 1] = 0
                    break
            max_l = 0
            for i_row in range(row - 1):
                if max_l < li[vec[i_col * row + i_row + 1]]:
                    max_l = li[vec[i_col * row + i_row + 1]]
            sum_l += max_l

        else:
            for i_row in range(row - 1):
                vec[i_col * row + i_row + 1] = 0
            break

    if constraint(vec) == 1:
        pop.append(vec)

# How many winners from each generation?
topelite = int(elite * popsize)

for i in range(maxiter):

    print('iter', i)
    scores = [(aimfunc(v), v) for v in pop]
    scores.sort()
    ranked = [v for (s, v) in scores]

    print(scores[0])

    # Start with the pure winners
    pop = deepcopy(ranked[0:topelite])

    # Add mutated and bred forms of the winners
    cnt = 0
    while len(pop) < popsize:
        # print('len_pop', len(pop))
        cnt += 1
        #print(cnt, '###############################')
        if random.random() < mutprob:

            # Mutation
            c = random.randint(0, topelite)
            vec_new = mutate(ranked[c])
            #print(constraint(vec_new))
            if constraint(vec_new) == 1:
                vec_ = vec_new[0:]
                pop.append(vec_)
                #print('加入pop')

        else:
            # Crossover
            c1 = random.randint(0, topelite)
            c2 = random.randint(0, topelite)
            vec_new = crossover(ranked[c1], ranked[c2])
            #print(constraint(vec_new))
            if constraint(vec_new) == 1:
                pop.append(vec_new)
                #print('加入pop')
        if random.random() < transprob:
            c1 = random.randint(0, topelite)
            c2 = random.randint(0, topelite)
            vec_new = transfer(ranked[c1], ranked[c2])
            if constraint(vec_new) == 1:
                pop.append(vec_new)

optpop = pop[0:-1]
opt_scores = [(aimfunc(v), v) for v in optpop]
opt_scores.sort()
opt_scores2 = []
for i in range(len(opt_scores)):
    if i == 0:
        opt_scores2.append(opt_scores[i])
    if i > 0 and opt_scores[i][0] != opt_scores2[-1][0]:
        opt_scores2.append(opt_scores[i])

optpop2 = []
for i in range(len(opt_scores2)):
    optpop2.append(opt_scores2[i][1])

for i in range(len(optpop2)):
    print('优解', i)
    abstract_feature(optpop2[i])
