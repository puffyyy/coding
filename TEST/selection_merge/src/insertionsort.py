from data import DataSeq
# from data import Input


def InsertionSort(ds):
    assert isinstance(ds, DataSeq), "Type Error"

    Length = ds.length
    for i in range(Length):
        tmp = ds.data[i]
        j = i
        while j >= 1 and ds.data[j-1] > tmp:
            ds.SetVal(j, ds.data[j-1])
            j -= 1
        ds.SetVal(j, tmp)


if __name__ == "__main__":
    # print(type(time_interval))
    # print("请选择生成数据的方式\n")
    # print("键入 1 : 自己输入数据（要求数字之间以一个空格分格，换行则结束输入）\n")
    # print("键入 2 : 采用系统随机生成数据\n")
    # od = input()
    # od = int(od)3
    # if od == 1:
    # data = [int(n) for n in input().split()]
    # print("\n\n\n\n")
    # print("请输入演示速度（数值范围：1-1000）\n")
    # inter = input()
    # time_interval = int(inter)
    # data=[12, 43 ,3 ,31, 65 ,3, 2 ,65 ,1, 23, 66, 1, 76 ,34 ,1]
    # ds = DataSeq(data)

    ds = DataSeq()
    ds.Visualize()
    ds.StartTimer()
    InsertionSort(ds)
    ds.StopTimer()
    ds.SetTimeInterval(0)
    ds.Visualize()
