import unittest


class MyTest(unittest.TestCase):
    # 编写测试用例，记得要以t开头，例：test
    def testEqual(self):
        # 调用内部的测试方法，如：assertEqual,assertNotEqual等
        # 2 + 3 代表待测试的函数，5代表测试样例的期望输出
        self.assertEqual(2 + 3, 5)


# 运行测试
if __name__ == '__main__':
    unittest.main()
