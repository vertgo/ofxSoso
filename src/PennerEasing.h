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
    
    static float backEaseIn (float t,float b , float c, float d) {
        float s = 1.70158f;
        float postFix = t/=d;
        return c*(postFix)*t*((s+1)*t - s) + b;
    }
    static float backEaseOut(float t,float b , float c, float d) {
        float s = 1.70158f;
        return c*((t=t/d-1)*t*((s+1)*t + s) + 1) + b;
    }
    
    static float backEaseInOut(float t,float b , float c, float d) {
        float s = 1.70158f;
        if ((t/=d/2) < 1) return c/2*(t*t*(((s*=(1.525f))+1)*t - s)) + b;
        float postFix = t-=2;
        return c/2*((postFix)*t*(((s*=(1.525f))+1)*t + s) + 2) + b;
    }
    
    static float quintEaseIn (float t,float b , float c, float d) {
        return c*(t/=d)*t*t*t*t + b;
    }
    static float quintEaseOut(float t,float b , float c, float d) {
        return c*((t=t/d-1)*t*t*t*t + 1) + b;
    }
    
    static float quintEaseInOut(float t,float b , float c, float d) {
        if ((t/=d/2) < 1) return c/2*t*t*t*t*t + b;
        return c/2*((t-=2)*t*t*t*t + 2) + b;
    }
    
    
    static float quadEaseIn (float t,float b , float c, float d) {
        return c*(t/=d)*t + b;
    }
    static float quadEaseOut(float t,float b , float c, float d) {
        return -c *(t/=d)*(t-2) + b;
    }
    
    static float quadEaseInOut(float t,float b , float c, float d) {
        if ((t/=d/2) < 1) return ((c/2)*(t*t)) + b;
        return -c/2 * (((t-2)*(--t)) - 1) + b;
        
    }
    
    static float quartEaseIn (float t,float b , float c, float d) {
        return c*(t/=d)*t*t*t + b;
    }
    static float quartEaseOut(float t,float b , float c, float d) {
        return -c * ((t=t/d-1)*t*t*t - 1) + b;
    }
    
    static float quartEaseInOut(float t,float b , float c, float d) {
        if ((t/=d/2) < 1) return c/2*t*t*t*t + b;
        return -c/2 * ((t-=2)*t*t*t - 2) + b;
    }
    
    static float expoEaseIn (float t,float b , float c, float d) {
        return (t==0) ? b : c * pow(2, 10 * (t/d - 1)) + b;
    }
    static float expoEaseOut(float t,float b , float c, float d) {
        return (t==d) ? b+c : c * (-pow(2, -10 * t/d) + 1) + b;
    }
    
    static float expoEaseInOut(float t,float b , float c, float d) {
        if (t==0) return b;
        if (t==d) return b+c;
        if ((t/=d/2) < 1) return c/2 * pow(2, 10 * (t - 1)) + b;
        return c/2 * (-pow(2, -10 * --t) + 2) + b;
    }
    
    static float sineEaseIn (float t,float b , float c, float d) {
        return -c * cos(t/d * (PI/2)) + c + b;
    }
    static float sineEaseOut(float t,float b , float c, float d) {
        return c * sin(t/d * (PI/2)) + b;
    }
    
    static float sineEaseInOut(float t,float b , float c, float d) {
        return -c/2 * (cos(PI*t/d) - 1) + b;
    }
    
    static float cubicEaseIn (float t,float b , float c, float d) {
        return c*(t/=d)*t*t + b;
    }
    static float cubicEaseOut(float t,float b , float c, float d) {
        return c*((t=t/d-1)*t*t + 1) + b;
    }
    
    static float cubicEaseInOut(float t,float b , float c, float d) {
        if ((t/=d/2) < 1) return c/2*t*t*t + b;
        return c/2*((t-=2)*t*t + 2) + b;	
    }
    
    static float circEaseIn (float t,float b , float c, float d) {
        return -c * (sqrt(1 - (t/=d)*t) - 1) + b;
    }
    static float circEaseOut(float t,float b , float c, float d) {
        return c * sqrt(1 - (t=t/d-1)*t) + b;
    }
    
    static float circEaseInOut(float t,float b , float c, float d) {
        if ((t/=d/2) < 1) return -c/2 * (sqrt(1 - t*t) - 1) + b;
        return c/2 * (sqrt(1 - t*(t-=2)) + 1) + b;
    }
    
    static float bounceEaseIn (float t,float b , float c, float d) {
        return c - bounceEaseOut (d-t, 0, c, d) + b;
    }
    static float bounceEaseOut(float t,float b , float c, float d) {
        if ((t/=d) < (1/2.75f)) {
            return c*(7.5625f*t*t) + b;
        } else if (t < (2/2.75f)) {
            float postFix = t-=(1.5f/2.75f);
            return c*(7.5625f*(postFix)*t + .75f) + b;
        } else if (t < (2.5/2.75)) {
			float postFix = t-=(2.25f/2.75f);
            return c*(7.5625f*(postFix)*t + .9375f) + b;
        } else {
            float postFix = t-=(2.625f/2.75f);
            return c*(7.5625f*(postFix)*t + .984375f) + b;
        }
    }
    
    static float bounceEaseInOut(float t,float b , float c, float d) {
        if (t < d/2) return bounceEaseIn (t*2, 0, c, d) * .5f + b;
        else return bounceEaseOut (t*2-d, 0, c, d) * .5f + c*.5f + b;
    }
};


#endif /* defined(__textTest__PennerEasing__) */
