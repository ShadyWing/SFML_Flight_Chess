#include "Animation.h"
#include "Game.h"


// 传入纹理数组，数组长度
void Animation::bindFrames(Texture tFrames[], int length) 
{
    // 让内置的纹理数组等于
    frames = new Texture[length];

    // 给动态定义长度
    for (int i = 0; i < length; i++)
    {
        frames[i] = tFrames[i];
    }
    frameLength = length;
}

void Animation::play() 
{
    if (turn == 2)
        turn = 0;
    // 设定当前帧的纹理
    setTexture(frames[frameNo]);
    // 下一帧
    frameNo += 1;
    if (frameNo == frameLength) 
    {            //重新开始播放
        frameNo = 0;
        turn++;
    }
  
}

void Animation::stop(int _num) 
{
    setTexture(frames[_num]);
}