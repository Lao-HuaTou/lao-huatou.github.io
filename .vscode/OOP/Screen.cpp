#include<bits/stdc++.h>
using namespace std;

class Screen{
public:
    typedef string::size_type pos;
    Screen() = default;
    Screen(pos ht,pos wd,char c):height(ht),width(wd),contents(ht*wd,c){}
    char get(){                         //隐式内联
        return contents[cursor];        //显示内联
    }
    inline char get(pos ht, pos wd) const;
    Screen &move(pos r, pos c);         //可在后续声明设为内联

private:
    pos cursor;
    pos height;
    pos width;
    string contents;
};

inline Screen &Screen::move(pos r,pos c){
    pos row = r * width;
    cursor = row + c;
    return *this;
}
char Screen::get(pos r,pos c)const{
    pos row = r * width;
    return contents[row + c];
}