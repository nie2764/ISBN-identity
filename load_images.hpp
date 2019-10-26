//
//  load_images.hpp
//  opencvtest
//
//  Created by 聂鹏举 on 2019/10/22.
//  Copyright © 2019 聂鹏举. All rights reserved.
//

#ifndef load_images_hpp
#define load_images_hpp

#include <stdio.h>

#endif /* load_images_hpp */

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void load_images(const String & dirname, vector<Mat> & images);
