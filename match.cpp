//
//  match.cpp
//  opencvtest
//
//  Created by 聂鹏举 on 2019/10/25.
//  Copyright © 2019 聂鹏举. All rights reserved.
//

#include "match.hpp"

vector<int> match(vector<vector<int>> & tmpfeature, vector<Mat> & dst)
{
    vector<int> isbnnum;
    vector<vector<int>> dstfeature;
    for (int j = 0; j < dst.size(); ++j)
    {
        Mat tempimg = dst[j];
        Mat element5(3, 3, CV_8U, Scalar(1));
        blur(tempimg, tempimg, Size(3,3));
        thresholding(tempimg, tempimg);
        morphologyEx(tempimg, tempimg, MORPH_DILATE, element5);
        resize(tempimg, tempimg, Size(32,40));
        dstfeature.push_back(featextract(tempimg));
    }
    
    double dist = 0;                                        //欧氏距离
    int num = 0;
    for (int u = 0; u < dst.size(); ++u)                    //逐个识别
    {
        double mindist = DBL_MAX;
        for (int v = 0; v < tmpfeature.size(); ++v)         //与每个模板进行匹配
        {
            dist = 0;
            for (int w = 0; w < tmpfeature[v].size(); ++w)  //计算每个模板与要识别数字的欧氏距离
            {
                dist += pow((tmpfeature[v][w] - dstfeature[u][w]), 2);
            }
            if (dist < mindist)
            {
                mindist = dist;
                num = v;
            }
        }
        isbnnum.push_back(num);
    }
    
    return isbnnum;
}
