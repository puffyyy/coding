from queue import Queue

inf = 1145141919810114514


class Path(object):
    def __init__(self):
        input_list = input().strip().split(" ")
        (self.vers, self.edges, self.start,
         self.terminal) = map(int, input_list)
        self.size = self.edges + 1
        self.head = [-1] * self.size
        self.to = [0] * self.size
        self.w = [0] * self.size
        self.next = [0] * self.size
        # reverse edge
        self.rhead = [-1] * self.size
        self.rto = [0] * self.size
        self.rnext = [0] * self.size
        self.cnt = 0
        self.in_degree = [0] * self.size
        self.TE = [0] * self.size
        self.TL = [inf] * self.size
        self.access = []
        self.li = []
        self.read_edge()

    def add_edge(self, u, v, wei):
        self.w[self.cnt] = wei
        self.to[self.cnt] = v
        self.next[self.cnt] = self.head[u]
        self.head[u] = self.cnt
        # reverse edge
        self.rto[self.cnt] = u
        self.rnext[self.cnt] = self.rhead[v]
        self.rhead[v] = self.cnt
        self.cnt += 1
        self.in_degree[v] += 1

    def read_edge(self):
        for i in range(self.edges):
            input_list_3 = input().strip().split(" ")
            (u, v, wei) = map(int, input_list_3)
            self.add_edge(u, v, wei)

    def cal_TE_time(self):
        q = Queue(maxsize=0)
        q.put(self.start)
        while (not q.empty()):
            u = q.get()
            j = self.head[u]
            while (j != -1):
                self.TE[self.to[j]] = max(self.TE[self.to[j]],
                                          self.TE[u] + self.w[j])
                self.in_degree[self.to[j]] -= 1
                if (self.in_degree[self.to[j]] == 0):
                    q.put(self.to[j])
                j = self.next[j]

    def cal_TL_time(self):
        q = Queue(maxsize=0)
        q.put(self.terminal)
        self.TL[self.terminal] = self.TE[self.terminal]
        while (not q.empty()):
            u = q.get()
            j = self.rhead[u]
            while (j != -1):
                q.put(self.rto[j])
                j = self.rnext[j]
            j = self.head[u]
            while (j != -1):
                self.TL[u] = min(self.TL[u], self.TL[self.to[j]] - self.w[j])
                j = self.next[j]

    def get_access(self, p):
        if (p == self.terminal):
            self.li.append(p)
            li_copy = list(self.li)
            self.access.append(li_copy)
            return
        self.li.append(p)
        j = self.head[p]
        while (j != -1):
            if self.TE[self.to[j]] == self.TL[self.to[j]] and self.TE[
                    self.to[j]] == self.TE[p] + self.w[j]:
                self.get_access(self.to[j])
                self.li.pop()
            j = self.next[j]

    def print_ans(self):
        print("Dis=", self.TE[self.terminal], sep="")
        for i in range(1, self.vers + 1):
            print("Node", i, end="")
            print(": TE= %3d" % (self.TE[i]), sep="", end=" ")
            print(" TL= %3d" % (self.TL[i]), sep="", end=" ")
            print(" TL-TE= ", self.TL[i] - self.TE[i], sep="")
        self.get_access(self.start)
        self.access.sort()
        self.access.sort(key=len)
        print(self.access)

    def work(self):
        self.cal_TE_time()
        self.cal_TL_time()
        self.print_ans()


if __name__ == "__main__":
    path = Path()
    path.work()
