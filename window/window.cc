#include "window.h"
#include <pthread.h>

window::window()
{
    initscr();
    curs_set(0); //消去光标
    pthread_mutex_init(&w_lock,NULL);
}

WINDOW* window::create_newwin(int h,int w,int y,int x)
{
    pthread_mutex_lock(&w_lock);
    WINDOW* win = newwin(h,w,y,x);
    box(win,0,0);
    pthread_mutex_unlock(&w_lock);
    return win;
}

void window::create_title()
{
    int y = 0;
    int x = 0;
    int h = LINES/5;
    int w = COLS;
    title = create_newwin(h,w,y,x);
    wrefresh(title);
}

void window::create_output()
{
    int y = LINES/5;
    int x = 0;
    int h = (LINES*3)/5 - 1;
    int w = (COLS*3)/4;
    output = create_newwin(h,w,y,x);
    wrefresh(output);
}

void window::create_friend_list()
{
    int y = LINES/5;
    int x = (COLS*3)/4;
    int h = (LINES*3)/5 - 1;
    int w = COLS/4;
    friend_list = create_newwin(h,w,y,x);
    wrefresh(friend_list);
}

void window::create_input()
{
    int y = (LINES*4)/5 -1;
    int x = 0;
    int h = LINES/5;
    int w = COLS;
    input = create_newwin(h,w,y,x);
    wrefresh(input);
}

void window::put_str_to_win(WINDOW* w,int y,int x,std::string& msg)
{
    pthread_mutex_lock(&w_lock);
    mvwaddstr(w,y,x,msg.c_str());
    wrefresh(w);
    pthread_mutex_unlock(&w_lock);
}

void window::clear_win_line(WINDOW* w,int begin, int lines)
{
    pthread_mutex_lock(&w_lock);
    while(lines-- > 0)
    {
        wmove(w,begin++,0);
        wclrtoeol(w);
    }
    wrefresh(w);
    box(w,0,0);
    wrefresh(w); // 消行以后最好把窗口和边框都刷新以下
    pthread_mutex_unlock(&w_lock);
}

void window::welcome_title()
{
    int x,y;
    getmaxyx(title,y,x);
    std::string run = "welcome to chat";
    int i = 1;
    int r_to_l = 0;
    while(1)
    {
        mvwaddstr(title,y/2,i,run.c_str());
        wrefresh(title);
        usleep(123456);
        clear_win_line(title,y/2,1);
        create_title(); // 为避免边框也被清除掉,所以重新绘制以下title
        int len = x - run.size();
        if(i == len - 1)
        {
            r_to_l = 1;
        }
        if(i == 1)
        {
            r_to_l = 0;
        }
        if(r_to_l == 1)
        {
            --i;
        }
        if(r_to_l == 0)
        {
            ++i;
        }
    }
}

void window::get_str(WINDOW* w,std::string& outString)
{
    char msg[1024];
    wgetnstr(w,msg,sizeof(msg));
    outString = msg;
}

window::~window()
{
    delwin(title);
    delwin(output);
    delwin(friend_list);
    delwin(input);
    curs_set(1); //重置光标
    endwin();
    pthread_mutex_destroy(&w_lock);
}

#if 0

int main()
{
    window w;
    w.create_title();
    w.create_output();
    w.create_friend_list();
    w.create_input();
    w.welcome_title();
    return 0;
}

#endif
