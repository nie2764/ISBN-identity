//
//  tmpmatch.hpp
//  opencvtest
//
//  Created by 聂鹏举 on 2019/10/22.
//  Copyright © 2019 聂鹏举. All rights reserved.
//

#ifndef tmpmatch_hpp
#define tmpmatch_hpp

#include <stdio.h>

#endif /* tmpmatch_hpp */

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include "thresholding.hpp"

using namespace cv;
using namespace std;

vector<int> tmpmatch(vector<Mat> & tmp, vector<Mat> & dst);
