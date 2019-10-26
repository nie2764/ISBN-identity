//
//  featextract.cpp
//  opencvtest
//
//  Created by 聂鹏举 on 2019/10/25.
//  Copyright © 2019 聂鹏举. All rights reserved.
//

#include "featextract.hpp"

vector<int> featextract(Mat & src)
{
    vector<int> cross;
    int rows = src.rows;
    int cols = src.cols;
    int count = 0;
    int max = 0;
    for (int i = 0; i < rows; ++i)
    {
        count = 0;
        for (int j = 0; j < cols; ++j)
        {
            if (src.at<uchar>(i,j) == 0)
            {
                count++;
            }
        }
        if (max < count)
        {
            max = count;
        }
        if ((i+1) % 4 == 0)                     //将字符从上至下分为8段，每段中扫描线上黑色像素最多的，记录像素点个数，记为该段的特征值
        {
            cross.push_back(max);
            max = 0;
        }
    }
    max = 0;
    for (int i = 0; i < cols; ++i)
    {
        count = 0;
        for (int j = 0; j < rows; ++j)
        {
            if (src.at<uchar>(j,i) == 0)
            {
                count ++;
            }
        }
        if (max < count)
        {
            max = count;
        }
        if ((i+1) % 5 == 0)                     //将字符从左至右分为8段，计算特征值
        {
            cross.push_back(max);
            max = 0;
        }
    }
    return cross;                               //返回每个字符的特征向量
}
