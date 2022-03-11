///
/// \note 功能：OpenGL+GLUT开发代码模板
///

#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <unistd.h> //延时

using namespace std;

#define ESCAPE 27 //esc键ASCII码值

int window; //glut窗口标识号

//初始化函数，设置所有初始化值
void initGL(int width, int height)
{
    glClearColor(1.0f, 1.0f, 0.0f, 0.0f); //将界面背景清空为红绿蓝alpha值对应的颜色
    glClearDepth(1.0);                    //设置清空深度缓冲区（depth buffer）
    glDepthFunc(GL_LESS);                 //设置深度测试的类型
    glEnable(GL_DEPTH_TEST);              //设置进行深度测试（depth test）
    glShadeModel(GL_SMOOTH);              //栅格化模式为平滑，只有平滑和两种模式

    glMatrixMode(GL_PROJECTION); //矩阵模式为投影模式
    glLoadIdentity();            //重置投影矩阵

    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f); //计算窗口的显示比例

    glMatrixMode(GL_MODELVIEW); //
}

//OpenGL的主要绘图函数，绘制什么显示什么。
void displayGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空界面和depth缓冲区
    glLoadIdentity();                                   //调整视场
    ////////////////下面是实际的绘图函数///////////////////

    ////////////////绘图函数结束/////////////////////////
    //双缓冲技术，交换缓冲区以显示刚刚绘制的图像
    glutSwapBuffers();
}

// 窗口大小变化回调函数
void reshapeGL(int w, int h)
{
    glViewport(0, 0, w, max(h, 1)); //重置当前窗口的视场和角度，防止出现长度为0的情况，尤其是下面还将h用作除数
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, static_cast<GLfloat>(w / h), 0.1f, 100.0f); //设置长宽视景
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//如果有按键按下调用此函数
void keyboard(unsigned char key, int x, int y)
{
    usleep(100); //稍微延时以免干扰

    //根据键值处理
    switch (key)
    {
    case ESCAPE:                   //如果是escape键
        glutDestroyWindow(window); //销毁窗口
        exit(0);                   //正常退出程序
    }
}

int main(int argc, char **argv)
{
    //初始化glut状态，并且接管所有传给程序的参数
    glutInit(&argc, argv);
    //设置显示模式：双缓冲、RGBA颜色、alpha支持、depth缓冲支持
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

    // 初始化窗口
    glutInitWindowSize(640, 480);     //初始界面大小
    glutInitWindowPosition(100, 100); //界面初始位置，相对于屏幕左上角的像素值
    //创建界面，界面标题为argv[0]，即程序名称，也可以以字符串进行指定
    //同时获取创建的窗口ID号，销毁时使用
    window = glutCreateWindow(argv[0]);

    glutIdleFunc(&displayGL);    //即使没有任何事件，也重绘场景
    glutReshapeFunc(&reshapeGL); //注册调整窗口大小回调函数
    glutDisplayFunc(&displayGL); //注册主要绘图回调函数
    glutKeyboardFunc(&keyboard); //注册键盘回调函数

    initGL(640, 480); //初始化窗口

    glutMainLoop(); //开始事件处理引擎

    return 0;
}
