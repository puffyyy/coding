import random
import numpy as np
import time
import cv2  # 图像处理

try:
    # import sounddevice as sd
    import pygame
    from .sound import get_sound_list, SF
except ImportError:
    pygame = None


# def Input():
#     data = [int(n) for n in input().split()]


class DataSeq:  # 定义一个类
    WHITE = (255, 255, 255)
    RED = (0, 0, 255)
    BLACK = (0, 0, 0)
    YELLOW = (0, 127, 255)

    MAX_IM_SIZE = 500

    def __init__(self,
                 Length=14, time_interval=100,
                 sort_title="Figure",
                 is_resampling=False,
                 is_sparse=False,
                 record=False,
                 sound=False, sound_interval=16,
                 fps=25):
        # self.data = data
        # self.data = [x for x in range(Length)]
        in_list = input().strip().split(" ")
        self.data = [int(n) for n in in_list]
        # if is_resampling:
        #     self.data = random.choices(self.data, k=Length)
        # else:
        #     self.Shuffle()
        # if is_sparse:
        #     self.data = [x if random.random() < 0.3 else 0 for x in self.data]
        # self.Input()
        self.length = len(self.data)
        # print(type(time_interval))
        # print("请选择生成数据的方式\n")
        # print("键入 1 : 自己输入数据（要求数字之间以一个空格分格，换行则结束输入）\n")
        # print("键入 2 : 采用系统随机生成数据\n")
        # od = input()
        # od = int(od)
        # if od == 1:
        #     self.data = [int(n) for n in input().split()]
        #     Length = len(self.data)
        #     self.length = Length
        # print("\n\n\n\n")
        # print("请输入演示速度（数值范围：1-1000）\n")
        # inter = input()
        # time_interval = int(inter)
        self.SetTimeInterval(time_interval)
        self.SetSortType(sort_title)
        self.Getfigure()
        self.InitTime()

        self.record = record
        if record:
            fourcc = cv2.VideoWriter_fourcc(*'XVID')
            self.vdo_wtr = cv2.VideoWriter(
                "%s.avi" % self.sort_title, fourcc, fps, (self.im_size, self.im_size), True)

        self.sound = sound
        if sound and pygame is not None:
            self.SetSoundInterval(sound_interval)
            self.GetSoundArray()

        self.Visualize()

    def Input(self):
        # ds1 = []
        # ds2 = []
        # for i in range(10):
        #     a = input()
        #     a = int(a)
        #     ds2.append(a)
        # ds1.append(ds2)
        self.data = list(map(int, input().strip().split()))
        print("fa")
        # self.data = ds1
        # aa = [1, 3, 12, 43, 3, 31, 65, 3, 2, 65, 1, 1, 1]
        # ds = [12, 43, 3, 31, 65, 3, 2, 65, 1, 23, 66, 1, 76, 34, 1]
        # print("fas")
        # self.data = ds
        # self.data = [int(n) for n in input().split()]
# 时间部分，显示算法执行效率

    def InitTime(self):  # 初始化时间
        self.start = time.time()
        self.time = 0
        self.StopTimer()

    def StartTimer(self):  # 开始时间
        self.start_flag = True
        self.start = time.time()

    def StopTimer(self):  # 结束时间
        self.start_flag = False

    def GetTime(self):  # 获取时间（差）
        if self.start_flag:
            self.time = time.time()-self.start

    def SetTimeInterval(self, time_interval):
        self.time_interval = time_interval

    def SetSoundInterval(self, sound_interval):
        self.sound_interval = sound_interval

    def SetSortType(self, sort_title):
        self.sort_title = sort_title

    def Shuffle(self):
        random.shuffle(self.data)

    def Getfigure(self):  # 获取显示图像
        _bar_width = 5
        figure = np.full((self.length*_bar_width, self.length *
                          _bar_width, 3), 255, dtype=np.uint8)
        for i in range(self.length):
            val = self.data[i]
            figure[-1-val*_bar_width:, i*_bar_width:i*_bar_width +
                   _bar_width] = self.GetColor(val, self.length)
        self._bar_width = _bar_width
        self.figure = figure
        size = _bar_width*self.length
        self.im_size = size if size < self.MAX_IM_SIZE else self.MAX_IM_SIZE

    @staticmethod
    def GetColor(val, TOTAL):
        return (120+val*255//(2*TOTAL), 255-val*255//(2*TOTAL), 0)

    def _set_figure(self, idx, val):
        min_col = idx*self._bar_width
        max_col = min_col+self._bar_width
        min_row = -1-val*self._bar_width
        self.figure[:, min_col:max_col] = self.WHITE
        self.figure[min_row:, min_col:max_col] = self.GetColor(
            val, self.length)

    def SetColor(self, img, marks, color):
        for idx in marks:
            min_col = idx*self._bar_width
            max_col = min_col+self._bar_width
            min_row = -1-self.data[idx]*self._bar_width
            img[min_row:, min_col:max_col] = color

    def Mark(self, img, marks, color):
        self.SetColor(img, marks, color)

    def GetSoundArray(self):
        pygame.mixer.init(SF, -16, 1, 2048)
        self.sound_list = get_sound_list(
            self.length, time_delay=self.sound_interval)
        self.sound_mixer = list(
            map(pygame.sndarray.make_sound, self.sound_list))

    def PlaySound(self, marks):
        # sd.play(self.sound_array[marks[0]], SF)
        self.sound_mixer[self.data[marks[0]]].play()
        pygame.time.wait(self.sound_interval)

    def SetVal(self, idx, val):
        self.data[idx] = val
        self._set_figure(idx, val)

        self.Visualize((idx,))

    def Swap(self, idx1, idx2):
        self.data[idx1], self.data[idx2] = self.data[idx2], self.data[idx1]
        self._set_figure(idx1, self.data[idx1])
        self._set_figure(idx2, self.data[idx2])

        self.Visualize((idx1, idx2))

    def Visualize(self, mark1=None, mark2=None):  # 可视化函数
        img = self.figure.copy()
        if mark2:
            self.Mark(img, mark2, self.YELLOW)
        if mark1:
            self.Mark(img, mark1, self.RED)

        img = cv2.resize(img, (self.im_size, self.im_size))

        self.GetTime()
        cv2.putText(img, self.sort_title+" Time:%02.2fs" % self.time,
                    (20, 20), cv2.FONT_HERSHEY_PLAIN, 1, self.YELLOW, 1)

        if self.record:
            self.vdo_wtr.write(img)

        cv2.imshow(self.sort_title, img)

        if self.sound and mark1:
            self.PlaySound(mark1)
            pass

        cv2.waitKey(self.time_interval)

    def Hold(self):
        for idx in range(self.length):
            self.SetVal(idx, self.data[idx])

        self.SetTimeInterval(0)
        self.Visualize()


if __name__ == "__main__":
    ds = DataSeq(64, is_sparse=True)
    ds.Visualize()
