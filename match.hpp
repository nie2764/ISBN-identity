//
//  match.hpp
//  opencvtest
//
//  Created by 聂鹏举 on 2019/10/25.
//  Copyright © 2019 聂鹏举. All rights reserved.
//

#ifndef match_hpp
#define match_hpp

#include <stdio.h>

#endif /* match_hpp */

#include "featextract.hpp"
#include "thresholding.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


vector<int> match(vector<vector<int>> & tmpfeature, vector<Mat> & dst);
