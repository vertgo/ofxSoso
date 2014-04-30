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
    void addAlphaFlickerAcross(float inWait, float inDelay, float inFlickerTime, float inAlpha, bool inRandom = false );
    
    void addFlickerAcross(float inWait, float inDelay, float inFlickerTime, bool inRandom = false );
    //void
    
    void scrambleAcross(float inWait, float inDelay, bool inRandom = false );
    void unscrambleAcross(float inWait, float inDelay, bool inRandom = false );
    
    void randomScrambleThenUnscramble( int inScrambles, float inWait, float inDelay, float inScrambleDelay , bool inRandom = true, bool blink = false, float blinkTime = 0 );
    //TODO delete this
    float setToRandomCharacter( void* );
    
    
    void bounceUp();
private:
    
};
#endif /* defined(__textTest__ofxLetterTextAnimator__) */
