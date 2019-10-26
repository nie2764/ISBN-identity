//
//  segment.cpp
//  opencvtest
//
//  Created by 聂鹏举 on 2019/10/22.
//  Copyright © 2019 聂鹏举. All rights reserved.
//

#include "segment.hpp"

void segment(Mat src, Mat & dst)
{
    int rows = src.rows;
    int cols = src.cols;
    int firstrow = 0;
    int lastrow = 0;
    int count;
    
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
        if (count > 10)
        {
            firstrow = i;
            break;
        }
    }                                                   //找出ISBN号的上边界
    for (int i = firstrow; i < rows; ++i)
    {
        count = 0;
        for (int j = 0; j < cols; ++j)
        {
            if (src.at<uchar>(i,j) == 0)
            {
                count++;
            }
        }
        if (count < 10)
        {
            lastrow = i - 1;
            break;
        }
    }                                                   //找出ISBN号的下边界
    Rect rect(0, firstrow, cols, lastrow-firstrow);
    src(rect).copyTo(dst);
    if (dst.empty())
    {
        src.copyTo(dst);
    }
}
