//
//  get_threshold.cpp
//  opencvtest
//
//  Created by 聂鹏举 on 2019/10/22.
//  Copyright © 2019 聂鹏举. All rights reserved.
//

#include "get_threshold.hpp"

int get_threshold(Mat image) {
    int threshValue = 0;    //阈值
    double fore_pix = 0;    //前景像素点总数
    double back_pix = 0;    //背景像素点总数
    double maxvar = 0;    //最大类间方差
    double fore_rate = 0;    //前景像素点所占比例
    double back_rate = 0;    //背景像素点所占比例
    double mean_of_fore = 0;    //前景像素点灰度平均值
    double mean_of_back = 0;    //背景像素点灰度平均值
    double mean = 0;    //图像总灰度平均值
    double hist[256] = { 0 };    //存储不同灰度值对应像素点个数的数组，数组下标代表灰度值
    double totalNum = image.rows * image.cols;    //像素点总数
    vector<int> thresh;    //存储类间方差最大时的阈值，求平均值

    for (int i = 0; i < image.rows; i++)    //将图像各灰度值像素点的个数存储到数组中
    {
        for (int j = 0; j < image.cols; j++)
        {
            hist[image.at<uchar>(i, j)]++;    //对应灰度值的像素点个数加1
        }
    }

    for (int i = 1; i < 256; i++)    //每轮循环找出当前灰度值作为阈值时的类间方差，与最大类间方差作比较
    {
        fore_pix = 0;
        fore_rate = 0;
        mean_of_fore = 0;
        mean_of_back = 0;
        for (int j = 0; j <= i; j++)
        {
            fore_pix += hist[j];
            fore_rate += hist[j] / totalNum;
        }
        back_pix = totalNum - fore_pix;
        back_rate = 1 - fore_rate;

        for (int k = 0; k <= i; k++)
        {
            mean_of_fore += k * (hist[k] / totalNum) / fore_rate;
        }

        for (int k = i + 1; k < 256; k++)
        {
            mean_of_back += k * (hist[k] / totalNum) / back_rate;
        }

        mean = mean_of_fore * fore_rate + mean_of_back * back_rate;

        double varience = fore_rate * pow((mean_of_fore - mean), 2) + back_rate * pow((mean_of_back - mean), 2);    //计算类间方差

        if (maxvar < varience)    //判断当前类间方差是否比已记录的类间方差大，是则更新最大类间方差
        {
            thresh.clear();
            thresh.push_back(i);
            maxvar = varience;
        }
        else if (maxvar == varience && threshValue != i)    //若当前类间方差与已记录的类间方差相等，则将对应像素值存入数组
        {
            thresh.push_back(i);
        }

    }

    double var_of_gross = 0;    //全局方差
    for (int i = 0; i < 256; i++)
    {
        var_of_gross += pow((i - mean), 2) * (hist[i] / totalNum);
    }
//    double dif = maxvar / var_of_gross;
//    cout << dif << endl;    //判断阈值分割效果

    int sum = 0;
    for (int i = 0; i < thresh.size(); i++)    //计算相同类间方差所对应的不同阈值的平均值
    {
        sum += thresh[i];
    }
    threshValue = int(sum / (thresh.size()));

    return threshValue;
}
