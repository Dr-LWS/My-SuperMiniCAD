# My-SuperMiniCAD
Final project for 3D modeling in CAD, the course of ZJU.

三维CAD建模期末大作业

## 介绍
本次大程要求完成以下目标：

1）定义半边数据结构。

2）基于半边数据结构，实现五个基本欧拉操作。

3）基于欧拉操作，实现扫掠操作（允许二维区域带多个内环），并将基于扫掠操作构建的实体模型进行真实感图形显示。

本项目在Visual Studio 2019中完成，采用了OpenGL进行图形显示，同时使用了 GLFW, GLAD 和 GLM 库。
源代码在src文件夹内。

## 程序使用说明
编译完成后生成 `cad.exe`，双击开启程序。

程序内预先设置了三个实体模型：正方体、长方体隧道、三棱锥。键盘输入`N`进行模型间的切换。

使用键盘上的 `W` `S` `A` `D` `Q` `E` 按键进行视角的切换。其中 `W` `S` ，`A` `D` ，`Q` `E` 分别控制三个不同轴向的旋转。
以下是程序运行效果图：

![运行图](运行图.jpg)

## 编译说明
将OpenGL, GLFW, GLAD, GLM安装在正确的路径中。

使用Visual Studio 2019或更高版本打开cad.sln，进行项目环境配置，添加各类路径和依赖。

完成环境配置后生成解决方案得到可执行文件。

## 心得体会
本次大程让我学到许多。

在编写数据结构以及欧拉算法的过程中，我对B-rep表示及其建模方式有了更加深刻的了解。在深入地学习了五种欧拉操作以及扫掠操作具体的实现方式之后，我感受到实体建模操作精妙的秩序感与逻辑闭环。

而为了实现真实感绘制，我也从零开始学习了不少OpenGL和三个库的操作方法，游玩图形库总是能带给我很大的乐趣。
