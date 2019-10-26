//
//  thresholding.cpp
//  opencvtest
//
//  Created by 聂鹏举 on 2019/10/22.
//  Copyright © 2019 聂鹏举. All rights reserved.
//

#include "thresholding.hpp"

Mat thresholding(Mat src, Mat & dst)
{
    src.copyTo(dst);

    int thresh = get_threshold(src);

    uchar* grayscale = dst.data;
    for (int i = 0; i < dst.rows; i++)
    {
        for (int j = 0; j < dst.cols; j++)
        {
            if (grayscale[i * dst.step + j] <= thresh)
            {
                grayscale[i * dst.step + j] = 0;
            }
            else
                grayscale[i * dst.step + j] = 255;
        }
    }

    return dst;
}
