#ifndef IOREADER_LINSLAM_H_
#define IOREADER_LINSLAM_H_

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace cv;

//处理IO之类的脏活，不应该传入具体类型，尽可能使用通用类型
class IOReader
{
public:
    std::pair<Mat, Mat> getPairK(const char *addr);
    Mat *getImg(const char *addr);
    vector<string> split(const string &s, const string &sep);
    Mat getK(const char* line);
    //读取双图
    std::pair<Mat, Mat> getPairImgGrey(const char *addrL, const char *addrR);
};
#endif