inf = 0x7fffffff


class dist(object):
    def __init__(self, n):
        self.lenth = (n + 1)
        self.matrix = [[inf] * self.lenth for i in range(self.lenth)]
        self.dist = [0] * self.lenth
        self.path = [0] * self.lenth
        for i in range(1, self.lenth):
            self.matrix[i][i] = 0

    def read_edge(self, m):
        f = []
        for i in range(m):
            f = input().strip().split(" ")
            f = list(map(int, f))
            self.matrix[f[0]][f[1]] = f[2]

    def ppath(self, s, t):
        if (s == t):
            print(s, end=" ")
            return None
        self.ppath(s, self.path[t])
        print(t, end=" ")

    def print_mat(self, s, t):
        # print(self.path)
        self.ppath(s, t)
        print()
        print(self.dist[t])

    def dij(self, s, t):
        vis = [0] * self.lenth
        nplus1 = self.lenth
        for i in range(1, nplus1):
            self.dist[i] = self.matrix[s][i]
            self.path[i] = s
        vis[s] = 1
        for i in range(nplus1 - 2):
            v = 0
            min = inf
            for j in range(1, nplus1):
                if ((not vis[j]) and (min > self.dist[j])):
                    min = self.dist[j]
                    v = j
            vis[v] = 1
            for j in range(1, nplus1):
                if ((not vis[j]) and (self.matrix[v][j] != inf)
                        and (min + self.matrix[v][j] < self.dist[j])):
                    self.dist[j] = min + self.matrix[v][j]
                    self.path[j] = v


if __name__ == "__main__":
    read_4 = input().strip().split(" ")
    (size, edges, start, terminal) = map(int, read_4)
    D = dist(size)
    D.read_edge(edges)
    D.dij(start, terminal)
    D.print_mat(start, terminal)
