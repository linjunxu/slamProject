#include "IOReader.h"
std::pair<Mat, Mat> IOReader::getPairImgGrey(const char *addrL, const char *addrR)
{
    cout << "start read image" << endl;
    Mat leftImg = imread(addrL, IMREAD_GRAYSCALE);
    Mat rightImg = imread(addrR, IMREAD_GRAYSCALE);
    if (leftImg.empty())
    {
        cout << addrL << " is not exist，please check it" << endl;
        exit(1);
    }
    if (rightImg.empty())
    {
        cout << addrR << " is not exist，please check it" << endl;
        exit(1);
    }
    cout << "read image success" << endl;
    return std::make_pair(leftImg, rightImg);
}

vector<string> IOReader::split(const string &s, const string &sep)
{
    vector<string> v;
    string::size_type pos1, pos2;
    pos2 = s.find(sep);
    pos1 = 0;
    while (string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + sep.size();
        pos2 = s.find(sep, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
    return v;
}
Mat IOReader::getK(const char *line)
{
    string newLine = line;
    vector<string> sv;
    sv = split(newLine, "=");
    sv[1] = sv[1].substr(1, sv[1].length() - 2);
    newLine = sv[1];
    sv = split(newLine, "; ");
    float k[3][3] = {0};
    for (int i = 0; i < 3; i++)
    {
        vector<string> sv_temp = split(sv[i], " ");

        for (int j = 0; j < 3; j++)
        {
            //cout << sv_temp[j] << "  ";
            k[i][j] = atof(sv_temp[j].c_str());
        }
        //cout << endl;
    }
    return Mat(3, 3, CV_64F, k);
}
std::pair<Mat, Mat> IOReader::getPairK(const char *addr)
{
    cout << "start read calib.txt" << endl;
    std::ifstream infile;
    string file = addr, line;
    infile.open(file.data());
    getline(infile, line);
    Mat LK = getK(line.c_str());
    getline(infile, line);
    Mat RK = getK(line.c_str());
    infile.close();
    cout << "read calib.txt success" << endl;
    return std::make_pair(LK, RK);
}