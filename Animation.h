#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;


class Animation :public Sprite 
{
public:
    Texture* frames;                    //纹理序列
    int frameLength;                    //序列量
    int frameNo = 0;                    //当前播放帧
    int turn = 0;
    void bindFrames(Texture[], int);    //绑定序列
    void play();                        //播放动画
    void stop(int _num);                //播放动画
};