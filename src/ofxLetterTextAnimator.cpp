//
//  ofxLetterTextAnimator.cpp
//  textTest
//
//  Created by Michael Manh on 4/21/14.
//
//

#include "ofxLetterTextAnimator.h"

ofxLetterTextAnimator::ofxLetterTextAnimator( ofxSosoTrueTypeFont *iFont, char *iString ): ofxLetterTextObject(iFont, iString){
    
}

void ofxLetterTextAnimator::addFlickerAcross(float inWait, float inDelay, float inFlickerTime, float inAlpha){
    for( int i = 0; i < letters.size(); i++ ){
        
        ofxLetterTextObjectLetter* curLetter = letters[i];
        
        curLetter->doMessage1f( OF_SETALPHA, inWait + i*inDelay, inFlickerTime/2, OF_LINEAR, inAlpha * 255 );
        curLetter->doMessage1f( OF_SETALPHA, inWait + i*inDelay+inFlickerTime/2, inFlickerTime/2, OF_LINEAR, 255 );
    }

}