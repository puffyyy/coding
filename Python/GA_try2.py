import random
import numpy as np
'''读入各种分割方法的特性'''
feature = []
f = open('opt2.txt')  # 打开数据文件文件
lines = f.readlines()  # 把全部数据文件读到一个列表lines中
for line in lines:  # 把lines中的数据逐行读取出来
    list = line.strip('\n').split('\t')
    for i in range(len(list) - 1):
        list[i] = int(list[i])
    list[-1] = float(list[-1])
    feature.append(list)

# 各钢板面积
S0 = [
    225894967.048, 93050905.830, 118091686.250, 117090593.846, 116844541.811,
    100273564.815, 101396043.434, 103598629.419
]
S = []
for i in range(len(S0)):
    for j in range(4):
        S.append(S0[i])

# 各订单面积
si = np.array([
    18755205.854399998, 11097102.3488, 14702837.9064, 12575475.103,
    17770799.4191
])

# 订单需求量
need = np.array([36, 29, 42, 32, 18])

# 各原材料个数
store = np.array([5, 10, 8, 2, 3, 10, 12, 9, 3, 10])
'''开始遗传算法'''
popsize = 200  # 种群大小 200
mutprob = 0.5  # 新种群由变异得来的概率
elite = 0.2  # 种群中是优解，且被允许遗传给下一代的部分
maxiter = 300  # 需运行多少代
dimen_x = len(feature)  # 自变量维数

# 目标函数权重
weight = np.array([12, 0.1, 5, 5, 5, 5, 5]).T
'''
p1 = 0.4
p2 = 0.1
p3 = 0.1
p4 = 0.1
p5 = 0.1
p6 = 0.1
p7 = 0.1
'''


# Mutation Operation
def mutate(vec):
    step = random.randint(0, 10)  # 自变量取值即为（0,5）的闭区间
    i = random.randint(0, len(vec) - 1)
    if random.random() < 0.8:
        return vec[0:i] + [step] + vec[i + 1:]
    else:
        return vec


# Crossover Operation
def crossover(r1, r2):
    i = random.randint(1, len(r1) - 2)
    return r1[0:i] + r2[i:]


def aimfunc(vec):

    # 所用钢板数量之和
    total = 0
    for i in range(len(vec)):
        total += vec[i]

    # 成材率
    s_material = 0
    s_order = 0
    s_spare = 0
    for i in range(len(vec)):
        s_material += vec[i] * S[i]
        num_order = feature[i][2:7]
        num_order = np.array(num_order)
        s_order += np.dot(num_order, si.T) * vec[i]
        s_spare += feature[i][7] * vec[i]
    yita = -(s_order + s_spare) / s_material

    # di = 订单i需求数量-现完成订单i数量
    d = [36, 29, 42, 32, 18]
    for i in range(len(vec)):
        for n_order in range(len(d)):
            d[n_order] -= vec[i] * feature[i][n_order + 2]

    z = np.array([total, yita, d[0], d[1], d[2], d[3], d[4]])
    z = np.dot(weight, z.T)

    return z


def constraint(vec):
    '''约束1：订单i需求数量-现完成订单i数量必须大于0'''
    # di = 订单i需求数量-现完成订单i数量
    d = [36, 29, 42, 32, 18]
    for i in range(len(vec)):
        for n_order in range(len(d)):
            d[n_order] -= vec[i] * feature[i][n_order + 2]
    for n_order in range(len(d)):
        if d[n_order] < 0:
            #print('订单', n_order, '不满足约束1:', d[n_order])
            #print(vec)
            #print(d, need)
            return 0
    '''约束2：使用的原材料i个数小于等于库存'''
    use = np.zeros(len(store))
    for i in range(len(vec)):
        use[int(feature[i][0]) - 1] += vec[i]
    for i in range(use.shape[0]):
        if use[i] > store[i]:
            print('不满足约束2')
            return 0

    return 1


def calculate_feature(vec):
    print('vec', vec)
    '''总消耗板数数'''
    total = 0
    for i in range(len(vec)):
        total += vec[i]
    print('总消耗板数数：', total)
    '''成材率'''
    s_material = 0
    s_order = 0
    s_spare = 0
    for i in range(len(vec)):
        s_material += vec[i] * S[i]
        num_order = feature[i][2:7]
        num_order = np.array(num_order)
        s_order += np.dot(num_order, si.T) * vec[i]
        s_spare += feature[i][7] * vec[i]
    yita = (s_order + s_spare) / s_material
    print('总材料面积：', s_material)
    print('订单面积：', s_order)
    print('余料面积：', s_spare)
    print('成材率：', yita)
    '''di'''
    # di = 订单i需求数量-现完成订单i数量
    d = [36, 29, 42, 32, 18]
    need_num = [36, 29, 42, 32, 18]
    for i in range(len(vec)):
        for n_order in range(len(d)):
            d[n_order] -= vec[i] * feature[i][n_order + 2]
    for i in range(len(d)):
        print('订单', i + 1, '已生产：', need_num[i] - d[i], '  还差：', d[i])
    '''原材料剩余板数'''
    use = np.zeros(len(store))
    for i in range(len(vec)):
        use[int(feature[i][0]) - 1] += vec[i]
    for i in range(len(store)):
        print('材料', i + 1, '已用：', use[i], '剩余：', store[i] - use[i])


def result(vec):
    for i in range(len(vec)):

        print(
            i + 1,
            feature[i][0],
            vec[i],
            feature[i][2],
            feature[i][3],
            feature[i][4],
            feature[i][5],
            feature[i][6],
        )


# Build the initial population
pop = []

while (len(pop) < popsize):

    vec = [
        random.randint(0, store[j // 4] // 5)  # 为了满足约束，先设用比较少的块数，所以store[j]整除2
        for j in range(dimen_x)
    ]

    #print('ok')
    if constraint(vec) == 1:
        #print('当前种群数量：', len(pop))
        pop.append(vec)

# How many winners from each generation?
topelite = int(elite * popsize)

for i in range(maxiter):
    print('1迭代：', i)
    scores = [(aimfunc(v), v) for v in pop]
    scores.sort()
    ranked = [v for (s, v) in scores]

    print(scores[0])

    # Start with the pure winners
    pop = ranked[0:topelite]

    # Add mutated and bred forms of the winners
    while len(pop) < popsize:
        if random.random() < mutprob:

            # Mutation
            c = random.randint(0, topelite)
            vec_new = mutate(ranked[c])
            if constraint(vec_new) == 1:
                pop.append(vec_new)
        else:

            # Crossover
            c1 = random.randint(0, topelite)
            c2 = random.randint(0, topelite)
            vec_new = crossover(ranked[c1], ranked[c2])
            if constraint(vec_new) == 1:
                pop.append(vec_new)

print('第一次迭代完成')

for i in range(maxiter):
    print('2迭代：', i)
    scores = [(aimfunc(v), v) for v in pop]
    scores.sort()
    ranked = [v for (s, v) in scores]

    print(scores[0])

    # Start with the pure winners
    pop = ranked[0:topelite]

    # Add mutated and bred forms of the winners
    while len(pop) < popsize:
        if random.random() < mutprob:

            # Mutation
            c = random.randint(0, topelite)
            vec_new = mutate(ranked[c])
            if constraint(vec_new) == 1:
                pop.append(vec_new)
        else:

            # Crossover
            c1 = random.randint(0, topelite)
            c2 = random.randint(0, topelite)
            vec_new = crossover(ranked[c1], ranked[c2])
            if constraint(vec_new) == 1:
                pop.append(vec_new)

v_test = pop[0]
#v_test = [1, 2, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 2, 0, 1, 0, 1, 0]
calculate_feature(v_test)
result(v_test)
