//
//  ofxLetterTextAnimator.h
//  textTest
//
//  Created by Michael Manh on 4/21/14.
//
//

#ifndef __textTest__ofxLetterTextAnimator__
#define __textTest__ofxLetterTextAnimator__

#include <iostream>
#include "ofxLetterTextObject.h"
class ofxLetterTextAnimator :public ofxLetterTextObject {
public:
    ofxLetterTextAnimator(ofxSosoTrueTypeFont *iFont, char *iString=NULL);
    void addTotalFlicker( float inWait, float inFlickerTime, float inAlpha );
    void addFlickerAcross(float inWait, float inDelay, float inFlickerTime, float inAlpha );
    void bounceUp();
private:
    
};
#endif /* defined(__textTest__ofxLetterTextAnimator__) */
