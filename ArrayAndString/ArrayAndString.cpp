// ArrayAndString.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>


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
};


int main()
{
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
