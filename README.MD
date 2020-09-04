S-MSCKF去除ROS版本

在ubuntu系统下可运行，需要提前安装此系统；
使用了boost，eigen, opencv库，方便交叉编译，故需要提前安装这些库。

一 运行

1、修改main中euroc数据集路径，如果使用其他的数据集，修改getFiles()

2、如果使用其他数据集修改loadParameters()中相机参数


二 要点

1.去除ROS环境

2.增加了相机和IMU的数据同步，

3.去除了SuiteSparse(交叉编译起来很麻烦)

4.注意typedef long long int FeatureIDType类型，arm下编译会有问题
