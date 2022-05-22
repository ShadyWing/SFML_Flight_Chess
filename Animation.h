#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;


class Animation :public Sprite 
{
public:
    Texture* frames;                    //��������
    int frameLength;                    //������
    int frameNo = 0;                    //��ǰ����֡
    int turn = 0;
    void bindFrames(Texture[], int);    //������
    void play();                        //���Ŷ���
    void stop(int _num);                //���Ŷ���
};