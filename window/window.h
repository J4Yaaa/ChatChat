#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>
#include <string>
#include <unistd.h>
#include <ncurses.h>
#include <pthread.h>

class window
{
public:
    window();

    WINDOW* create_newwin(int h,int w,int y,int x);

    void create_title();       // 绘制欢迎栏
    void create_output();      // 绘制消息输出栏
    void create_friend_list(); // 绘制好友列表栏
    void create_input();       // 绘制消息输入栏

    void put_str_to_win(WINDOW* w,int y,int x,std::string& msg); // 将消息打印到屏幕上
    void clear_win_line(WINDOW* w,int begin, int lines); // 消去界面中原有的数据
    void welcome_title(); // 打印滚动的title
    void get_str(WINDOW* w,std::string& outString); // 从标准输入读取数据

    ~window();
public:
    WINDOW* title;
    WINDOW* output;
    WINDOW* friend_list;
    WINDOW* input;
    pthread_mutex_t w_lock;
};

#endif
