package test;

import java.util.Stack;

public class Test {
    public static void main(String[] args) {
        System.out.println(trap(new int[]{4,2,0,3,2,5}));
    }
    
    public static int trap(int[] height) {
        int res = 0;
        Stack<Integer> stack = new Stack<Integer>();
        stack.push(0);
        for (int i = 1; i < height.length; i++) {
            while (!stack.isEmpty() && height[stack.peek()] <= height[i]) {
                int cur = stack.pop();
                if (!stack.isEmpty()) {
                    int h = Math.min(height[stack.peek()], height[i]) - height[cur];
                    res += h * (i - stack.peek() - 1);
                }
            }
            stack.push(i);
        }
        
        return res;
    }
    
}
