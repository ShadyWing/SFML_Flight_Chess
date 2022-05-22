#include "Animation.h"
#include "Game.h"


// �����������飬���鳤��
void Animation::bindFrames(Texture tFrames[], int length) 
{
    // �����õ������������
    frames = new Texture[length];

    // ����̬���峤��
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
    // �趨��ǰ֡������
    setTexture(frames[frameNo]);
    // ��һ֡
    frameNo += 1;
    if (frameNo == frameLength) 
    {            //���¿�ʼ����
        frameNo = 0;
        turn++;
    }
  
}

void Animation::stop(int _num) 
{
    setTexture(frames[_num]);
}