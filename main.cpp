#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include "camera.cpp"
#include "IOReader.cpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace cv;

BinocularCamera binoCamera;
IOReader ioreader;

void matchAlgoCompare(int argc, char **argv)
{
    //参数处理
    cout<<"\n Start compare BM and SGBM\n"<<endl;
    string dataSetName = "../training" + string(argv[1]) + "/";     //训练集名字,ex: Q
    string objectName = argv[2];                                                            //ex: Recycle
    string dataAddr = dataSetName + argv[2];
    string left_Photo =dataAddr +"/im0.png";
    string right_Photo = dataAddr + "/im1.png";
    //数据读取
    std::pair<Mat,Mat> pairImg=ioreader.getPairImgGrey(left_Photo.c_str(),right_Photo.c_str());
    binoCamera.setPairImg(pairImg);
    string calibFileAddr = dataAddr + "/calib.txt";
    std::pair<Mat,Mat> pairK=ioreader.getPairK(calibFileAddr.c_str());
    binoCamera.setPairK(pairK);
    binoCamera.AlgoWithTime("BM", dataAddr.c_str());
    binoCamera.AlgoWithTime("SGBM", dataAddr.c_str());

}

int main(int argc,char** argv){
    matchAlgoCompare(argc,argv);
}