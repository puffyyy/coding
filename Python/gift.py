class Friend(object):
    def __init__(self, name=None, money=0):
        self.name = name
        self.sendmoney = money
        self.recmoney = 0


if __name__ == "__main__":
    t = input().strip()
    t = int(t)
    for time in range(t):
        n = int(input().strip())
        arr = [Friend() for i in range(n)]
        dic = {}
        for i in range(n):
            name = input().strip()
            arr[i].name = name
            dic[name] = i
        for i in range(n):
            send_name = input().strip()
            value_2 = input().strip().split(" ")
            (money, div) = map(int, value_2)
            send_pos = dic[send_name]
            arr[send_pos].sendmoney = money
            if div > 0:
                hand_out = int(money / div)
                arr[send_pos].recmoney += money - hand_out * div
            for j in range(div):
                receiver_name = input().strip()
                receiver_pos = dic[receiver_name]
                arr[receiver_pos].recmoney += hand_out
        for i in range(n):
            print(arr[i].name, arr[i].recmoney - arr[i].sendmoney)
        print()
