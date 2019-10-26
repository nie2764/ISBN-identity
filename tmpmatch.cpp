//
//  tmpmatch.cpp
//  opencvtest
//
//  Created by 聂鹏举 on 2019/10/22.
//  Copyright © 2019 聂鹏举. All rights reserved.
//

#include "tmpmatch.hpp"

vector<int> tmpmatch(vector<Mat> & tmp, vector<Mat> & dst)
{
    vector<int> isbnnum;
    isbnnum.resize(dst.size());
    for (int u = 0; u < dst.size(); ++u)
    {
//        Mat element3(3, 3, CV_8U, Scalar(1));
        Mat dstimg;
        resize(dst[u], dstimg, Size(40,50), 0, 0, INTER_LINEAR);
//        morphologyEx(dst[u], dst[u], MORPH_CLOSE, element3);
//        imshow("0", dst[u]);
//        waitKey();
        int mindif = INT_MAX;
        for (int k = 0; k < tmp.size(); ++k)
        {
            Mat temp;
            resize(tmp[k], temp, Size(40,50), 0, 0, INTER_LINEAR);
            cvtColor(temp, temp, COLOR_RGB2GRAY);
            thresholding(temp, temp);
            int rows = temp.rows;
            int cols = temp.cols;
            int dif = 0;                                //
            
            Mat difimg;
            absdiff(dstimg, temp, difimg);
            
            
            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < cols; ++j)
                {
//                    dif += abs(dst[u].at<uchar>(i,j) - temp.at<uchar>(i,j));
                    dif += difimg.at<uchar>(i,j);
                }
            }
//
//
            if (dif < mindif)
            {
                mindif = dif;
                isbnnum[u] = k;
            }
        }
    }
    return isbnnum;
}
