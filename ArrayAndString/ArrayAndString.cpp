// ArrayAndString.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>


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

    static void setZeroes(std::vector<std::vector<int>>& matrix) 
    {
        //首先是便利，将遇到0的元素的行号和列号记录下来。
        //最后去掉行号和列号上的元素。
        std::set<int> setRowNums;
        std::set<int> setColNums;
        for (int nRowIndex = 0; nRowIndex < matrix.size(); ++nRowIndex)
        {
            for (int nColIndex = 0; nColIndex < matrix[nRowIndex].size(); ++nColIndex)
            {
                if (matrix[nRowIndex][nColIndex] == 0)
                {
                    setRowNums.insert(nRowIndex);
                    setColNums.insert(nColIndex);
                }
            }
        }

        for (int nRowIndex = 0; nRowIndex < matrix.size(); ++nRowIndex)
        {
            if (setRowNums.find(nRowIndex) != setRowNums.end())
            {
                for (int nColIndex = 0; nColIndex < matrix[nRowIndex].size(); ++nColIndex)
                {
                    matrix[nRowIndex][nColIndex] = 0;
                }
            }
        }

        //矩阵怎么列遍历
        for (int nRowIndex = 0; nRowIndex < matrix.size(); ++nRowIndex)
        {

            for (int nColIndex = 0; nColIndex < matrix[nRowIndex].size(); ++nColIndex)
            {
                if (setColNums.find(nColIndex) != setColNums.end())
                {
                    matrix[nRowIndex][nColIndex] = 0;
                }
            }

        }
        return;

    }
    
    //判断所有字符串的固定长度前缀。
    static bool isPrefix(std::vector<std::string> vecStrs, int nLength)
    {
        std::string strHead = vecStrs[0].substr(0, nLength);
        for (unsigned long ulIndex = 0; ulIndex < vecStrs.size();++ulIndex)
        {
            std::string strTemp = vecStrs[ulIndex];
            std::string strSubTemp = strTemp.substr(0, nLength);
            if (strHead != strSubTemp)
            {
                return false;
            }
        }
        return true;
    }
    static std::string longestCommonPrefix(std::vector<std::string> vecStr) 
    {
        if (0 == vecStr.size()) 
        {
            return "";
        }
        // 二分查找
        // 最短字符串的字符数 minLength
        //int minLength = Integer.MAX_VALUE;
        unsigned long ulMinLength = std::numeric_limits<unsigned long>::max();
        for (unsigned long  ulIndex = 0; ulIndex < vecStr.size(); ulIndex++) 
        {
            ulMinLength = std::min(ulMinLength, (unsigned long)vecStr[ulIndex].length());
        }
        // 在 0 - ulMinLength 区间内进行二分查找
        unsigned long ulStart = 0, ulEnd = ulMinLength;
        while (ulStart < ulEnd) 
        {
            //二分查找 ulMid该怎么取？ (ulEnd + ulStart) / 2有什么不一样的？
            //这里ulMid怎么取不重要，无非是你定义的中间位置不一样，差别一个位置。
            unsigned long ulMid = (ulEnd - ulStart + 1) / 2 + ulStart;
            if (isPrefix(vecStr, ulMid)) 
            {
                ulStart = ulMid;
            }
            else 
            {
                ulEnd = ulMid - 1;
            }
        }
        return vecStr[0].substr(0, ulStart);

    }
    std::vector<int> findDiagonalOrder(std::vector<std::vector<int>>& mat) 
    {
        
    }

    static std::vector<std::vector<int>> MakeMatrix()
    {
        
    }
};


int main()
{
    //["flower", "flow", "flight"]
    std::vector<std::string> vecStr;
    vecStr.push_back("flower");
    vecStr.push_back("flow");
    vecStr.push_back("flight");

    std::string strTTTTT =  Solution::longestCommonPrefix(vecStr);
    int ii = 0;
    /* [0, 1, 2, 0] ,
        [3, 4, 5, 2],
        [1, 3, 1, 5]*/
    std::vector<std::vector<int>> intervals222;
    std::vector<int> vecTemp;
    intervals222.push_back(vecTemp);
    intervals222[0].push_back(0);
    intervals222[0].push_back(1);
    intervals222[0].push_back(2);
    intervals222[0].push_back(0);

    intervals222.push_back(vecTemp);
    intervals222[1].push_back(3);
    intervals222[1].push_back(4);
    intervals222[1].push_back(5);
    intervals222[1].push_back(2);

    intervals222.push_back(vecTemp);
    intervals222[2].push_back(1);
    intervals222[2].push_back(3);
    intervals222[2].push_back(1);
    intervals222[2].push_back(5);
    Solution::setZeroes(intervals222);


    //[[1, 3], [2, 6], [8, 10], [15, 18]]
    std::vector<std::vector<int>> intervals;
    
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
