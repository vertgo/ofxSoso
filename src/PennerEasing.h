//
//  PennerEasing.h
//  textTest
//
//  Created by Michael Manh on 4/30/14.
//
//

//just an include file of Jesus Gollonet's port of penner's easing equations

#ifndef __textTest__PennerEasing__
#define __textTest__PennerEasing__

#include <iostream>
#include <math.h>

#ifndef PI
#define PI  3.14159265
#endif

typedef float (*EasingFunction)(float, float, float, float);

class PennerEasing{
public:
    //linear easing
    static float easeNone(float t,float b , float c, float d){
        return c*t/d + b;
    }
    
    static float elasticEaseIn(float t,float b , float c, float d){
        if (t==0) return b;  if ((t/=d)==1) return b+c;
        float p=d*.3f;
        float a=c;
        float s=p/4;
        float postFix =a*pow(2,10*(t-=1)); // this is a fix, again, with post-increment operators
        return -(postFix * sin((t*d-s)*(2*PI)/p )) + b;
    }
    
    static float elasticEaseOut(float t,float b , float c, float d){
        if (t==0) return b;  if ((t/=d)==1) return b+c;
        float p=d*.3f;
        float a=c;
        float s=p/4;
        return (a*pow(2,-10*t) * sin( (t*d-s)*(2*PI)/p ) + c + b);
    }
    
    static float elasticEaseInOut(float t,float b , float c, float d) {
        if (t==0) return b;  if ((t/=d/2)==2) return b+c;
        float p=d*(.3f*1.5f);
        float a=c;
        float s=p/4;
        
        if (t < 1) {
            float postFix =a*pow(2,10*(t-=1)); // postIncrement is evil
            return -.5f*(postFix* sin( (t*d-s)*(2*PI)/p )) + b;
        }
        float postFix =  a*pow(2,-10*(t-=1)); // postIncrement is evil
        return postFix * sin( (t*d-s)*(2*PI)/p )*.5f + c + b;
    }
    
    
    
};


#endif /* defined(__textTest__PennerEasing__) */
