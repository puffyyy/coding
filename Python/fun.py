import random

dealremainlist = []


def readcurfile(now):
    if not dealremainlist:
        with open("r" + str(now) + "s4.txt", "r") as f:
            for i in range(10):
                f.readline()
                line = f.readline().strip('\n').strip(' ')
                dealremainlist.append(
                    list(map(lambda x: int(x), line.split(' '))))
    return


def fill_in(now, L, curlen):
    readcurfile(now)
    reW = L - curlen
    reRate = reW / L
    listfill = []
    cat = random.randint(0, 9)
    listfill = (list(map(lambda x: int(x * reRate), dealremainlist[cat])))
    listret = []
    print(listfill)
    for i in range(10):
        while listfill[i]:
            listfill[i] -= 1
            listret.append(i + 6)
    print(listret)

    return listret


if __name__ == "__main__":
    fill_in(3, 15, 10)
