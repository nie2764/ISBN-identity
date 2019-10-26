//
//  load_images.cpp
//  opencvtest
//
//  Created by 聂鹏举 on 2019/10/22.
//  Copyright © 2019 聂鹏举. All rights reserved.
//

#include "load_images.hpp"

void load_images(const String & dirname, vector<Mat> & images)
{
    vector<String> files;   //存储文件名
    glob(dirname, files);   //读取图片文件
    
    for (int i = 0; i < files.size(); ++i)
    {   //将图片存储到向量中
        Mat img = imread(files[i]);
        if (img.empty())
        {
            cout << files[i] << " is invalid!" << endl;
        }
        images.push_back(img);
    }
}
