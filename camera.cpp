#include "camera.h"
void BinocularCamera::AlgoWithTime(const char* algoName, const char* addr){
    cout<<"start run algo of "<<algoName<<endl;
    clock_t startTime = clock();
    if(algoName=="BM")  BM();
    else if(algoName=="SGBM") SGBM();
    else {
        cout<<"we haven't define algo of"<<algoName<<", place check code"<<endl;
    }
    clock_t endTime = clock();
    double cost = (double)(endTime - startTime) / CLOCKS_PER_SEC * 1000;
    std::ofstream outfile;
    string timeAddr = string(addr) + "/time.txt";
    string dispAddr = string(addr) + "/" + algoName + ".jpg";
    outfile.open(timeAddr, std::ios::out | std::ios::app);
    outfile << algoName<<" cost time of " << cost << " ms" << endl;
    outfile.close();
    normalize(_disp, _vdisp, 0, 256, NORM_MINMAX, CV_8U);
    imshow("disparity", _vdisp);
    waitKey(0);
    imwrite(dispAddr, _vdisp);
    cout<<"run "<< algoName << " success"<<endl;
}
void BinocularCamera::SGBM(){
    Ptr<StereoSGBM> stereo = StereoSGBM::create(-64, 128, 11, 100, 1000, 32, 0, 15, 1000, 16, StereoSGBM::MODE_HH);
    stereo->compute(_pairImg.first, _pairImg.second, _disp);
}
void BinocularCamera::BM(){
    //48对于小图是个好数字
    Ptr<StereoBM> stereo = StereoBM::create(48);
    stereo->compute(_pairImg.first, _pairImg.second, _disp);
}