#include "ofxLetterTextObject.h"

//class ofxLetterTextObjectLetter 
//ofxLetterTextObjectLetter::ofxLetterTextObjectLetter(ofxSosoTrueTypeFont *iFont, char iChar, float iX, float iY, float iScaleFactor)
ofxLetterTextObjectLetter::ofxLetterTextObjectLetter(ofxSosoTrueTypeFont *iFont, char *iChar, float iX, float iY, float iScaleFactor)   //eg 0701412
{
	//character = iChar;
    if(iChar) character = iChar[0]; //If iChar is a mapped sequence, then this is irrelevant.
    else character = 0;
	//charPointer = new char[2];
	//charPointer[0] = iChar;
	//charPointer[1] = 0;
    randChar = NULL;
    originalChar = charPointer = iChar;    //eg 0701412
	scaleFactor = iScaleFactor;

	home.set(iX, iY, 0);
	letterWidth = iFont->getCharWidth( *iChar) * iScaleFactor;
    letterHeight = iFont->getCharWidth( *iChar) * iScaleFactor;
    setReg(letterWidth/2, 0, 0); //what could possibly go wrong?
	font = iFont;
	
	hasSpecialTransparency = true;	

}

void ofxLetterTextObjectLetter::setToRandomCharacter(){
    if( randChar != NULL) delete randChar;
    if ( *originalChar >= 33 && *originalChar < 48   )
        randChar = new char( round(ofRandom(33,48) ));
    else if ( *originalChar >= 48 && *originalChar < 58   ){
        randChar = new char( round(ofRandom(48,58) ));
    }
    else if ( *originalChar >= 65 && *originalChar < 90   ){
        randChar = new char( round(ofRandom(65,90) ));
    }
    else if ( *originalChar >= 97 && *originalChar < 122   ){
        randChar = new char( round(ofRandom(97,122) ));
    }
    else{
        randChar = new char( *originalChar );
    }
    
        charPointer = randChar;
}

void ofxLetterTextObjectLetter::setToRandomCap(){
    if( randChar != NULL) delete randChar;
    randChar = new char( round(ofRandom(65,90) ));
    charPointer = randChar;
}

void ofxLetterTextObjectLetter::setToRandomLower(){
    if( randChar != NULL) delete randChar;
    randChar = new char( round(ofRandom(97,122) ));
    charPointer = randChar;
}

void ofxLetterTextObjectLetter::setToOriginal(){
    charPointer = originalChar;
}

ofxLetterTextObjectLetter::~ofxLetterTextObjectLetter()
{
    if(charPointer) delete(charPointer);    //eg 0701412
	//if(font) delete(font); //LM 070612
}

void ofxLetterTextObjectLetter::render()
{	    
	glPushMatrix();
    glScalef(scaleFactor, scaleFactor, 1.0);
	font->drawString(charPointer,0,0);	
	glPopMatrix();
}






//class ofxLetterTextObject
ofxLetterTextObject::ofxLetterTextObject(ofxSosoTrueTypeFont *iFont, char *iString):ofxTextObject(iFont, iString)
{	
	//Format the text with a call to drawText(). Note last arg is false, which says format, but do not draw.
	//drawText(0,0,false);		
	//Reconstruct the letter objects based on the updated formatting.
	rebuildLetters();
}

ofxLetterTextObject::~ofxLetterTextObject(){

    for ( int i = 0; i < letters.size(); i++ )
    {
        delete letters[i];
    }
    
    letters.clear();
    
}



void ofxLetterTextObject::cleanupLetters()
{
	for(unsigned int i=0; i < letters.size(); i++){
		removeChild(letters[i]);
		delete(letters[i]); 
	}
	letters.clear();
	
	/*while (letters.size() > 0) {
		removeChild(letters[0]);
		delete(letters[0]);
		letters.erase(letters.begin()); //LM 070612
	}*/
}

void ofxLetterTextObject::rebuildLetters()
{	
	int     currentWordID;

	cleanupLetters();

	if (words.size() > 0) {

		for(int a=0; a < lines.size(); a++)
		{
			for(int w=0; w < lines[a].wordsID.size(); w++)
			{
				currentWordID = lines[a].wordsID[w];
				//Make letters.
				for(int p=0; p < words[currentWordID].charPositions.size(); p++){
					//Add word position to char position.
                    
                    
                    float xLocation = (words[currentWordID].pos.x + words[currentWordID].charPositions[p].x) * scaleFactor;
                    float yLocation = (words[currentWordID].pos.y + words[currentWordID].charPositions[p].y) * scaleFactor;
                    
                    
					ofVec3f pos( xLocation,	yLocation, 0);
					
                    //Check for special unicode sequences, as defined in buildMappedChars() //eg 0701412
                    char *cSeq = NULL; //getFont()->getMappedCharSequence(words[currentWordID].rawWord, p);
                    if(cSeq==NULL){    //If, not a mapped char sequence, just grab character straight from word.
                        cSeq = new char[2];
                        cSeq[0] = words[currentWordID].rawWord.c_str()[p];
                        cSeq[1] = 0;
                    }
                    
					//Create letter text letter and pass position and char to it.
					//ofxLetterTextObjectLetter *letter = new ofxLetterTextObjectLetter(font, words[currentWordID].rawWord.c_str()[p], pos.x, pos.y, scaleFactor); 					
                    ofxLetterTextObjectLetter *letter = new ofxLetterTextObjectLetter(font, cSeq, pos.x, pos.y, scaleFactor);       //eg 070412
					letter->setTrans(pos.x, pos.y, pos.z);
					letter->setColor(words[currentWordID].color.r, words[currentWordID].color.g, words[currentWordID].color.b, words[currentWordID].color.a);	//Gotta grab word color or else it gets reset to white.					
					letters.push_back(letter);
                    letter->letterWidth =
					addChild(letter);								
				}
			}
		}
	}
}

/*
void ofxLetterTextObject::predraw()
{
	ofxObject::predraw();

	glPushMatrix();
    glScalef(scaleFactor, scaleFactor, 1.0);
}

void ofxLetterTextObject::postdraw()
{
	glPopMatrix();    
	ofxObject::postdraw();
}
*/

void ofxLetterTextObject::setWordColor(int iIndex, float iR, float iG, float iB, float iA)
{
    ofxTextObject::setWordColor(iIndex, iR, iG, iB, iA);
    rebuildLetters();
}

void ofxLetterTextObject::setWordColor(string iWord, float iR, float iG, float iB, float iA, bool iExactMatch)
{
    ofxTextObject::setWordColor(iWord, iR, iG, iB, iA, iExactMatch);
    rebuildLetters();
    
}

//Empty render() because the letter objects handle all of the drawing.
void ofxLetterTextObject::render(){}


void ofxLetterTextObject::setString(char *iString)
{	
	ofxTextObject::setString(iString);
	//drawText(0,0,false);	
	rebuildLetters();	
}

void ofxLetterTextObject::setString(string iString) //JM 080513
{
	setString((char*)iString.c_str());
}

void ofxLetterTextObject::setColumnWidth(float iWidth)
{
	ofxTextObject::setColumnWidth(iWidth);
	//drawText(0,0,false);	
	rebuildLetters();		
}

void ofxLetterTextObject::setPointSize(float iPointSize)
{
	ofxTextObject::setPointSize(iPointSize);
	//drawText(0,0,false);	
	rebuildLetters();		
}

void ofxLetterTextObject::setLeading(float iLeading)
{
	ofxTextObject::setLeading(iLeading);
	//drawText(0,0,false);	
	rebuildLetters();		
}

void ofxLetterTextObject::setSpaceWidth(float iWidth)
{
	ofxTextObject::setSpaceWidth(iWidth);
	//drawText(0,0,false);	
	rebuildLetters();		
}

void ofxLetterTextObject::setAlignment(TextObjectAlignment iAlignment)
{
	ofxTextObject::setAlignment(iAlignment);
	rebuildLetters();
}

void ofxLetterTextObject::setFont(ofxSosoTrueTypeFont *iFont)
{
	ofxTextObject::setFont(iFont);
	//drawText(0,0,false);	
	rebuildLetters();			
}


void ofxLetterTextObject::setColor(float iR, float iG, float iB, float iA)
{ 
    ofxTextObject::setColor(iR, iG, iB, iA);
    for (int i=0; i < letters.size(); i++)
        letters[i]->setColor(iR, iG, iB, iA);
}

void ofxLetterTextObject::setColor(ofVec4f iColor)
{ 
    ofxTextObject::setColor(iColor);
    for (int i=0; i < letters.size(); i++)
        letters[i]->setColor(iColor);
}

void ofxLetterTextObject::setColor(ofColor iColor)
{
    ofxTextObject::setColor(iColor);
    for (int i=0; i < letters.size(); i++)
        letters[i]->setColor(iColor);
}



/*
void ofxLetterTextObject::normalizeScale()
{       
    float textScale = getScale()[0];

    //scale words + home positions
    for(unsigned int i=0; i < letters.size(); i++){
        letters[i]->setScale(textScale/getPointSize());       
        //mBaselinePositions[i] *= textScale;      
		letters[i]->home *= (textScale/getPointSize());
        //mQuads[i]->setTrans(*mBaselinePositions[i]);
		letters[i]->setTrans(letters[i]->home);
    }
   
    setScale(getPointSize());   
}
*/