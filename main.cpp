//
//  main.cpp
//  opencvtest
//
//  Created by 聂鹏举 on 2019/10/22.
//  Copyright © 2019 聂鹏举. All rights reserved.
//

#include "thresholding.hpp"
#include "load_images.hpp"
#include "segment.hpp"
#include "rectify.hpp"
#include "charseg.hpp"
#include "tmpmatch.hpp"
#include "match.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main() {
    String filename = "/Users/niepengju/Documents/三级项目ISBN号数据集/*.jpg";
    vector<Mat> images;                                 //存储要处理的图片
    load_images(filename, images);                      //读取图片
    images.push_back(imread("/Users/niepengju/Documents/三级项目ISBN号数据集/ISBN978-7-5594-1211-9.JPG"));
    vector<string> files;                               //存储图片文件名以便与识别出的数字进行比对
    glob(filename, files);
    files.push_back("/Users/niepengju/Documents/三级项目ISBN号数据集/ISBN978-7-5594-1211-9.JPG");
    
    String tmpname = "/Users/niepengju/Documents/template/*.png";
    vector<Mat> tmp;
    load_images(tmpname, tmp);                          //读入模板图像
    vector<vector<int>> tmpfeature;

    float correctness = 0;                          //计算识别准确度

    for (int i = 0; i < tmp.size(); ++i)                //提取模板特征向量
    {
        Mat temp = tmp[i];
        cvtColor(temp, temp, COLOR_RGB2GRAY);
        thresholding(temp, temp);
        resize(temp, temp, Size(32,40));
        tmpfeature.push_back(featextract(temp));
    }

    for (int i = 0; i < images.size(); ++i)
    {
        Mat src = images[i];
        Mat grayImg, blurImg, bImg, isbnImg, numImg, rectifiedImg;

        cvtColor(src, grayImg, COLOR_RGB2GRAY);         //将图像转化为灰度图
        GaussianBlur(grayImg, grayImg, Size(3,3), 1);
        thresholding(grayImg, bImg);                    //阈值分割将图像转化为二值图
//        rectify(bImg, rectifiedImg);
//        imshow("rectifiedImg", rectifiedImg);
        segment(bImg, isbnImg);                         //分离ISBN号区域

        Mat element5(3, 3, CV_8U, Scalar(1));
        blur(isbnImg, isbnImg, Size(3,3));
        thresholding(isbnImg, isbnImg);
        morphologyEx(isbnImg, isbnImg, MORPH_ERODE, element5);
//        morphologyEx(isbnImg, isbnImg, MORPH_CLOSE, element5);
//
        vector<Mat> chars;
        charseg(isbnImg, chars);                        //分割字符
//        imshow("isbnImg", isbnImg);
//        waitKey();
//        rectify(isbnImg, rectifiedImg);
//        imshow("rectifiedImg", rectifiedImg);
//        for (int i = 0; i < chars.size(); ++i)
//        {
//            imshow("isbnImg", chars[i]);
//
//            waitKey();
//        }
//        waitKey();
        vector<int> isbnnum;
//        isbnnum = tmpmatch(tmp, chars);               //进行模板匹配
        isbnnum = match(tmpfeature, chars);             //根据字符特征与模板匹配
        string identino;
        for (int i = 0; i < isbnnum.size(); ++i)        //将识别到的数字转化为字符串
        {
            identino.append(to_string(isbnnum[i]));
        }
        string isbnno;                                  //提取文件名中的数字以进行比对
        for (int j = 0; j < files[i].size(); ++j)
        {
            if (files[i][j] >= '0' && files[i][j] <= '9')
            {
                isbnno.push_back(files[i][j]);
            }
        }
        float precision = 0;                            //计算识别精确度        for (int k = 0; k < identino.size(); ++k)
        for (int k = 0; k < identino.size(); ++k)
        {
            if (identino[k] == isbnno[k])
            {
                precision++;
            }
        }
        precision /= isbnno.size();
        if (identino == isbnno)
        {
            correctness += 1;
        }
        cout << identino << "|" << isbnno <<"|" << precision << endl;
    }
    correctness /= images.size();
    cout << correctness << endl;
    return 0;
}
