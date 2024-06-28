#pragma once

class color{
private:
    int R,G,B;
    float H,S,V;

    void RGBtoHSV();
    void HSVtoRGB();

public:  
    color();
    void setRGB(int _r,int _g, int _b);
    void setHSV(float _h, float _s, float _v);

    int getR();
    int getG();
    int getB();

    float getH();
    float getS();
    float getV();
};