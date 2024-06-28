#include <cmath>
#include "color.h"

color::color(): R(0),G(0),B(0),H(0.0F),S(0.0F),V(0.0F){
}

void color::setRGB(int _r, int _g, int _b){
    if(_r < 0){
        R = 0;
    } else if (_r > 255){
        R = 255;
    } else {
        R = _r;
    }

    if(_g < 0){
        G = 0;
    } else if (_g > 255){
        G = 255;
    } else {
        G = _g;
    }

    if(_b < 0){
        B = 0;
    } else if (_b > 255){
        B = 255;
    } else {
        B = _b;
    }

    RGBtoHSV();
}


void color::setHSV(float _h, float _s, float _v){
    H = _h - 360.0f * std::floor(_h/360.0F);

    if(_s < 0){
        S = 0.0F;
    } else if (_s > 1.0){
        S = 1.0;
    } else {
        S = _s;
    }

    if(_v < 0){
        V = 0.0F;
    } else if (_v > 1.0){
        V = 1.0;
    } else {
        V = _v;
    }

    HSVtoRGB();
}

int color::getR(){
    return R;
}

int color::getG(){
    return G;
}

int color::getB(){
    return B;
}

float color::getH(){
    return H;
}

float color::getS(){
    return S;
}

float color::getV(){
    return V;
}

void color::RGBtoHSV(){
    int max,min;

    if(R==G && R==B){
        H = 0.0f;
        S = 0.0f;
        V = (float)R / 255;
    } else {
        if(R>=G && R>=B){
            max = R;
            if(G<B){
                min = G;
            } else {
                min = B;
            }
            H = 60.0f * ((float)(G - B) / (max - min));

        } else if(G>=R && G>=B){
            max = G;
            if(R<B){
                min = R;
            } else {
                min = B;
            }
            H = 60.0f * ((float)(B - R) / (max - min)) + 120.0f;
            S = (float)(max - min) / max;

        } else if(B>=R && B>=G){
            max = B;
            if(R<G){
                min = R;
            } else {
                min = G;
            }
            H = 60.0f * ((float)(R - G) / (max - min)) + 240.0f;
        }
        H = H - 360.0f * std::floor(H / 360.0f);
        S = (float)(max - min) / max;
        V = (float)max / 255;
    }
}

void color::HSVtoRGB(){
    int max,min;
    int Hrank = std::floor(H / 60.0f);

    max = V * 255;
    min = max * (1 - S);
    switch(Hrank){
    case 0:
        R = max;
        G = (H / 60.0f) * (max - min) + min;
        B = min;
        break;
    case 1:
        R = ((120.0f - H) / 60.0f) * (max - min) + min;
        G = max;
        B = min;
        break;
    case 2:
        R = min;
        G = max;
        B = ((H - 120.0f) / 60.0f) * (max - min) + min;
        break;
    case 3:
        R = min;
        G = ((240.0f - H) / 60.0f) * (max - min) + min;
        B = max;
        break;
    case 4:
        R = ((H - 240.0f) / 60.0f) * (max - min) + min;
        G = min;
        B = max;
        break;
    case 5:
        R = max;
        G = min;
        B = ((360.0f - H) / 60.0f) * (max - min) + min;
        break;
    default:
        R = 0;
        G = 0;
        B = 0;
        break;
    
    }
}

