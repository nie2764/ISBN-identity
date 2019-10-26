//
//  charseg.cpp
//  opencvtest
//
//  Created by 聂鹏举 on 2019/10/23.
//  Copyright © 2019 聂鹏举. All rights reserved.
//

#include "charseg.hpp"

void charseg(Mat & src, vector<Mat> & dst)
{
    int rows = src.rows;
    int cols = src.cols;
    int line = 0;                                           //竖向扫描线
    int firstrow = 0;
    int lastrow = 0;
    int firstcol = 0;
    int lastcol = 0;
    int count = 0;                                          //记录扫描线上黑色像素点个数
    
    while (line < cols)
    {
        for (int i = line + 1; i < cols; ++i)
        {
            count = 0;
            for (int j = 0; j < rows; ++j)
            {
                if (src.at<uchar>(j,i) == 0)
                {
                    count++;
                }
            }
            if (count > 1)                                  //黑色像素点大于3个记为字符左边界
            {
                firstcol = i;
                break;
            }
        }
        for (int i = firstcol+1; i < cols; ++i)
        {
            count = 0;
            for (int j = 0; j < rows; ++j)
            {
                if (src.at<uchar>(j,i) == 0)
                {
                    count++;
                }
            }
            if (count < 3)                                  //黑色像素点小于3个记为右边界
            {
                lastcol = i - 1;
                break;
            }
        }
        for (int i = 0; i < rows; ++i)
        {
            count = 0;
            for (int j = firstcol; j <= lastcol; ++j)
            {
                if (src.at<uchar>(i,j) == 0)
                {
                    count++;
                }
            }
            if (count > 1)
            {
                firstrow = i;
                break;
            }
        }                                                   //找出字符上边界
        for (int i = firstrow+1; i < rows; ++i)
        {
            count = 0;
            for (int j = firstcol; j <= lastcol; ++j)
            {
                if (src.at<uchar>(i,j) == 0)
                {
                    count++;
                }
            }
            if (count < 3)
            {
                lastrow = i - 1;
                break;
            }
            lastrow = i;
        }                                                   //找出字符下边界
        Rect rect(firstcol, firstrow, lastcol-firstcol, lastrow-firstrow);
        Mat temp;
        src(rect).copyTo(temp);
        dst.push_back(temp);
        if (line < lastcol)
        {
            line = lastcol;                             //扫描线移动至字符右边界
        }
        else{
            break;
        }
    }
    dst.erase(dst.begin(), dst.begin()+4);                  //去除ISBN四个字符
    int k = 0;
    while (k < dst.size())
    {
        int row = dst[k].rows;
        int col = dst[k].cols;
        if (row < col)                                      //移除“-”
        {
            dst.erase(dst.begin()+k);
            continue;
        }
        k++;
    }
    dst.pop_back();
    cout << dst.size() << endl;
}
