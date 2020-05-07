运行代码

```bash
cd build
#独立运算
#程序名  训练集名  内部Teddy文件夹
./AlgoCompare Q Teddy
```

修改代码后重新编译：

```bash
rm -r build
mkdir build && cd build && cmake ..
make
```

notice:
本机使用的opencv版本为3.2.0

可用 pkg-config opencv --modversion 查看电脑中的opencv版本

训练集下载地址：http://vision.middlebury.edu/stereo/submit3/

