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

void ofxLetterTextAnimator::addAlphaFlickerAcross(float inWait, float inDelay, float inFlickerTime, float inAlpha, bool inRandom ){
    for( int i = 0; i < letters.size(); i++ ){
        
        ofxLetterTextObjectLetter* curLetter = letters[i];
        
        curLetter->doMessage1f( OF_SETALPHA, inWait + i*inDelay, inFlickerTime/2, OF_LINEAR, inAlpha * 255 );
        curLetter->doMessage1f( OF_SETALPHA, inWait + i*inDelay+inFlickerTime/2, inFlickerTime/2, OF_LINEAR, 255 );
    }
    
}



void ofxLetterTextAnimator::addFlickerAcross(float inWait, float inDelay, float inFlickerTime, bool inRandom ){
    vector<ofxLetterTextObjectLetter*>	lettersCopy = letters;
    if ( inRandom )
        random_shuffle( lettersCopy.begin(), lettersCopy.end() );
    
    for( int i = 0; i < lettersCopy.size(); i++ ){
        
        ofxLetterTextObjectLetter* curLetter = lettersCopy[i];
        
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

void ofxLetterTextAnimator::scrambleAcross(float inWait, float inDelay, bool inRandom){
    
    vector<ofxLetterTextObjectLetter*>	lettersCopy = letters;
    if ( inRandom )
        random_shuffle( lettersCopy.begin(), lettersCopy.end() );
    
    cout << "scrambleAcross" <<endl;
    for( int i = 0; i < lettersCopy.size(); i++ ){
        
        ofxLetterTextObjectLetter* curLetter = lettersCopy[i];
        ofxMessage* scrambleMessage = new ofxMessage(OF_FUNCTION, &scramble, curLetter, inWait + i*inDelay, OF_ONE_TIME_PLAY);
        curLetter->doMessage(scrambleMessage);
        
    }
}


void ofxLetterTextAnimator::unscrambleAcross(float inWait, float inDelay, bool inRandom){
    
    vector<ofxLetterTextObjectLetter*>	lettersCopy = letters;
    if ( inRandom )
        random_shuffle( lettersCopy.begin(), lettersCopy.end() );
    
    cout << "scrambleAcross" <<endl;
    for( int i = 0; i < lettersCopy.size(); i++ ){
        
        ofxLetterTextObjectLetter* curLetter = lettersCopy[i];
        ofxMessage* scrambleMessage = new ofxMessage(OF_FUNCTION, &unscramble, curLetter, inWait + i*inDelay, OF_ONE_TIME_PLAY);
        curLetter->doMessage(scrambleMessage);
        
    }
}

void ofxLetterTextAnimator::randomScrambleThenUnscramble( int inScrambles, float inWait, float inDelay, float inScrambleDelay , bool inRandom, bool blink, float blinkTime ){
    
    if ( blinkTime == 0){
        blinkTime = inScrambleDelay/2;
    }
    
    vector<ofxLetterTextObjectLetter*>	lettersCopy = letters;
    if ( inRandom )
        random_shuffle( lettersCopy.begin(), lettersCopy.end() );
    
    
    cout << "randomScrambleThenUnscramble" <<endl;
    float waitTime;
    
    for( int i = 0; i < lettersCopy.size(); i++ ){
        
        ofxMessage* scrambleMessage;
        ofxLetterTextObjectLetter* curLetter = lettersCopy[i];
        for( int j = 0; j < inScrambles; j++){
            cout << "scramble:" << j;
            waitTime = inWait + i*inDelay + j*inScrambleDelay;
            if ( blink ){
                curLetter->doMessage0f(OF_HIDE, waitTime-blinkTime);
                curLetter->doMessage0f(OF_SHOW, waitTime);
                cout <<", blink off:" << waitTime-blinkTime*2;
                cout <<", blink on:" << waitTime-blinkTime;
            }
            cout << endl;
            scrambleMessage = new ofxMessage(OF_FUNCTION, &scramble, curLetter, waitTime, OF_ONE_TIME_PLAY);
            
            curLetter->doMessage(scrambleMessage);
        }
        
        //then unscramble it once you're out of that loop
        waitTime = inWait + i*inDelay + inScrambles * inScrambleDelay;
        if ( blink ){
            curLetter->doMessage0f(OF_HIDE, waitTime-blinkTime);
            curLetter->doMessage0f(OF_SHOW, waitTime);
        }
        
            cout <<", unscramble:" << waitTime <<endl;
            scrambleMessage = new ofxMessage(OF_FUNCTION, &unscramble, curLetter, waitTime, OF_ONE_TIME_PLAY);
            curLetter->doMessage(scrambleMessage);
        
        
    }
}