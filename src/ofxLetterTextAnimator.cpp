//
//  ofxLetterTextAnimator.cpp
//  textTest
//
//  Created by Michael Manh on 4/21/14.
//
//

#include "ofxLetterTextAnimator.h"
#include "ofxMessage.h"

ofxLetterTextAnimator::ofxLetterTextAnimator( ofxSosoTrueTypeFont *iFont, char *iString ): ofxLetterTextObject(iFont, iString){
    
}

void ofxLetterTextAnimator::addAlphaFlickerAcross(float inWait, float inDelay, float inFlickerTime, float inAlpha){
    for( int i = 0; i < letters.size(); i++ ){
        
        ofxLetterTextObjectLetter* curLetter = letters[i];
        
        curLetter->doMessage1f( OF_SETALPHA, inWait + i*inDelay, inFlickerTime/2, OF_LINEAR, inAlpha * 255 );
        curLetter->doMessage1f( OF_SETALPHA, inWait + i*inDelay+inFlickerTime/2, inFlickerTime/2, OF_LINEAR, 255 );
    }
    
}



void ofxLetterTextAnimator::addFlickerAcross(float inWait, float inDelay, float inFlickerTime){
    for( int i = 0; i < letters.size(); i++ ){
        
        ofxLetterTextObjectLetter* curLetter = letters[i];
        
        curLetter->doMessage0f( OF_HIDE, inWait + i*inDelay );
        curLetter->doMessage0f( OF_SHOW, inWait + i*inDelay +inFlickerTime);

    }
    
}


float scramble(void *letter ){
    //cout << "testFunc:" << pointer<< endl;
    ((ofxLetterTextObjectLetter*)(letter))->setToRandomCharacter();
    return 0.f;
}


float unscramble(void *letter ){
    //cout << "testFunc:" << pointer<< endl;
    ((ofxLetterTextObjectLetter*)(letter))->setToOriginal();
    return 0.f;
}

void ofxLetterTextAnimator::scrambleAcross(float inWait, float inDelay){
    
    cout << "scrambleAcross" <<endl;
    for( int i = 0; i < letters.size(); i++ ){
        
        ofxLetterTextObjectLetter* curLetter = letters[i];
        ofxMessage* scrambleMessage = new ofxMessage(OF_FUNCTION, &scramble, curLetter, inWait + i*inDelay, OF_ONE_TIME_PLAY);
        curLetter->doMessage(scrambleMessage);
        
    }
}

void ofxLetterTextAnimator::unscrambleAcross(float inWait, float inDelay){
    
    cout << "scrambleAcross" <<endl;
    for( int i = 0; i < letters.size(); i++ ){
        
        ofxLetterTextObjectLetter* curLetter = letters[i];
        ofxMessage* scrambleMessage = new ofxMessage(OF_FUNCTION, &unscramble, curLetter, inWait + i*inDelay, OF_ONE_TIME_PLAY);
        curLetter->doMessage(scrambleMessage);
        
    }
}