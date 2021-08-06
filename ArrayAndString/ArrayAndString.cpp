// ArrayAndString.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <algorithm>


class Solution 
{

public:
   
    //双指针 双index 二分法的写法？
    static  int searchInsert(std::vector<int>& nums, int target) 
    {
        int nLeftIndex = 0; 
        int nRightIndex = nums.size() - 1;
        bool bFindTarget = false;
        while (nLeftIndex < nRightIndex)
        {
            int nMidIndex = (nLeftIndex + nRightIndex) / 2;
            if (nums[nMidIndex] == target)
            {
                bFindTarget = true;
                return nMidIndex;
            }
            else if (nums[nMidIndex] < target)
            {
                nLeftIndex = nMidIndex + 1;
            }
            else
            { 
                nRightIndex = nMidIndex - 1;
            }
        }
        if (!bFindTarget)
        {
            if (target > nums[nLeftIndex])
            {
                return nLeftIndex + 1;
            }
        }

        return nLeftIndex;
    }
    //数组之间merge
    /*
     *输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
     *                  [1,6], [2,6], [8,10],[15,18] => i = 2; j = 0;
     *输出：[[1,6],[8,10],[15,18]]
     *解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
     * 只要有重合就需要合并，什么是重合， j[1] > j+1[0]时，就需要替换 j[1] 和 j+1[1];
     */
    static std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) 
    {
        int n = intervals.size();
        if (n == 1)
            return intervals;

        std::sort(intervals.begin(), intervals.end());
        std::vector<std::vector<int>> vec;
        vec.push_back(intervals[0]);
        int j = 0;
        //j 这里是放进vec的index
        //每次比较的是当前放进vec的最后一个元素
        for (int i = j + 1;i < n;i++) 
        {
            if (intervals[i][0] <= vec[j][1])
            {
                vec[j][1] = std::max(vec[j][1], intervals[i][1]);
            }    
            else 
            {
                vec.push_back(intervals[i]);
                j++;
            }
        }
        return vec;
    }
    /* 旋转矩阵，尽量用矩阵自己的内存
        matrix =
        [
            [1, 2, 3],
            [4, 5, 6],
            [7, 8, 9]
        ],

        原地旋转输入矩阵，使其变为:
        [
            [7, 4, 1],
            [8, 5, 2],
            [9, 6, 3]
        ]
    */
    static void rotate(std::vector<std::vector<int>>& matrix) 
    {
        //1. 对角翻转
        for (auto row = 0;row < matrix.size();row++)
        {
            for (auto column = 0;column <= row;column++) {
                std::swap(matrix[row][column], matrix[column][row]);
            }
        }
        // 2. 镜像翻转
        for (int row = 0; row < matrix.size(); row++)
        {
            //4/2 = 2 
            // 主要是 matrix.size() / 2 是不用遍历翻转的
            for (int column = 0; column < matrix.size() / 2; column++) 
            {
                std::swap(matrix[row][column], matrix[row][matrix.size() - column - 1]);
            }
        }
        return;

    }

    /*输入：
        [
            [0, 1, 2, 0],
            [3, 4, 5, 2],
            [1, 3, 1, 5]
        ]
    输出：
        [
            [0, 0, 0, 0],
            [0, 4, 5, 0],
            [0, 3, 1, 0]
        ]*/

    static void setZeroes(std::vector<std::vector<int>>& matrix) {

    }
    static std::vector<std::vector<int>> MakeMatrix()
    {
        
    }
};


int main()
{
    //[[1, 3], [2, 6], [8, 10], [15, 18]]
    std::vector<std::vector<int>> intervals;
    std::vector<int> vecTemp;
    intervals.push_back(vecTemp);
    intervals[0].push_back(1);
    intervals[0].push_back(3);

    intervals.push_back(vecTemp);
    intervals[1].push_back(2);
    intervals[1].push_back(6);

    intervals.push_back(vecTemp);
    intervals[2].push_back(8);
    intervals[2].push_back(10);

    intervals.push_back(vecTemp);
    intervals[3].push_back(15);
    intervals[3].push_back(18);

    intervals = Solution::merge(intervals);

    std::vector<int> vecNums;//[1, 3, 5, 6]
    vecNums.push_back(1);
    vecNums.push_back(3);
    vecNums.push_back(5);
    vecNums.push_back(6);
    int index = Solution::searchInsert(vecNums, 2);
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
