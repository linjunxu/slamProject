#ifndef CAMERA_LINSLAM_H_
#define CAMERA_LINSLAM_H_

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
//代表单个摄像机镜头
class CameraLens
{
public:
    CameraLens():_K(Mat(3,3,CV_32F)){};
    void setK(Mat K){
        _K=K;
    };
private:
    float _height;
    float _width;
    Size _imageSize;
    Mat _K; //相机内参
};

class BinocularCamera
{
public:
    BinocularCamera():_LLen(new CameraLens), _RLen(new CameraLens){};
    void setPairImg(std::pair<Mat, Mat> pairImg){
        _pairImg=pairImg;
         _imgSize=pairImg.first.size();
    };
    void setPairImg(Mat LImg, Mat RImg){
         _pairImg = std::make_pair(LImg, RImg);
         _imgSize=LImg.size();
    };
    void setPairK(Mat LK, Mat RK){
        _LLen->setK(LK);
        _RLen->setK(RK);
    };
    void setPairK(std::pair<Mat, Mat> pairK){
        _LLen->setK(pairK.first);
        _RLen->setK(pairK.second);
    };

    //算法
    void SGBM();
    void BM();
    void AlgoWithTime(const char* algoName,const char* addr);   //addr:存储数据的地方

private:
    CameraLens *_LLen;            //左镜头
    CameraLens *_RLen;           //右镜头
    Size _imgSize;                        //单镜头大小
    Mat _R;                                       //旋转矩阵
    Mat _T;                                       //平移矩阵
    Mat _disp;                                    //disparity 视差图
    Mat _vdisp;                                  //归一化后的视察图
    std::pair<Mat, Mat> _pairImg;
};


#endif