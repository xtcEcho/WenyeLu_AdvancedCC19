#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(120);
    //audio part- ------------------------------------------------------
    // 0 output channels,
    // 2 input channels
    // 44100 samples per second
    // BUFFER_SIZE samples per buffer
    // 4 num buffers (latency)
    
    ofSoundStreamSetup(0,2,this, 44100,BUFFER_SIZE, 4);
    left = new float[BUFFER_SIZE];
    right = new float[BUFFER_SIZE];
    
    for (int i = 0; i < NUM_WINDOWS; i++)
    {
        for (int j = 0; j < BUFFER_SIZE/2; j++)
        {
            freq[i][j] = 0;
        }
    }
    
 

}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(ofColor::black);
    cam.begin();
    //audio part - ----------------------------------------------------------
    static int index=0;
    float avg_power = 0.0f;
    
    if(index < 80)
        index += 1;
    else
        index = 0;
    
    /* do the FFT    */
    myfft.powerSpectrum(0,(int)BUFFER_SIZE/2, left,BUFFER_SIZE,&magnitude[0],&phase[0],&power[0],&avg_power);
    
    /* start from 1 because mag[0] = DC component */
    /* and discard the upper half of the buffer */
    for(int j=1; j < BUFFER_SIZE/2; j++) {
        freq[index][j] = magnitude[j];
    }
    
    /* draw the FFT */
    for (int i = 1; i < (int)(BUFFER_SIZE/2); i++){
        //ofDrawLine(200+(i*8),400,200+(i*8),400-magnitude[i]*10.0f);
    }
    
    if(echoTxt.size() != 0){
        stringDimension();
        ofTranslate(ofGetWidth()/2 - stringWidth/2 , ofGetHeight()/2 - stringHeight/2);
        //ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        
        for (int i = 0; i < echoTxt.size(); i++){
            
            //want to change spacing but seems not working
            //so i have to change it manually by giving a estimate value
            if (i >= 1){
              
                ofTranslate(echoTxt[i - 1].charWidth -20 , 0);
            }
            EchoFont tempChar = echoTxt[i];
//            vector<float> charMap = assignMagnitude(tempChar);
//            ofLogNotice() << charMap[0]<< endl;
            for (int j = 0; j < tempChar.triangleNum; j++){
             
                //ofNoFill();
                ofSetColor(ofColor::green);
                ofPushMatrix();
                //meshTriangle tempTri = echoTxt[i].charTriangles[j];
                int tempIndex = txtMap[i][j];
                float tempAngle = magnitude[tempIndex];
                tempAngle *=30.0f;
                if (tempAngle <2){
                    tempAngle = 0;
                }
                ofRotateYDeg(tempAngle);
                echoTxt[i].drawTriangle(j);
                ofPopMatrix();
            }
        }
    }
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_DEL || key == OF_KEY_BACKSPACE){
        if (echoTxt.size() != 0) {
            echoTxt.pop_back();
            txtMap.pop_back();
        }
    }else{
        EchoFont tempEchoFont;
        string inputString = "";
        ofUTF8Append(inputString,key);
        tempEchoFont.setup(inputString[0]);
        
        echoTxt.push_back(tempEchoFont);
        txtMap.push_back(assignMagnitude(tempEchoFont));
        ofLogNotice() << echoTxt.size()<< endl;
        ofLogNotice() << tempEchoFont.inputCharOutput<< endl;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
//void ofApp::windowResized(int w, int h)

//}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------
void ofApp::audioReceived     (float * input, int bufferSize, int nChannels){
     //samples are "interleaved"
    for (int i = 0; i < bufferSize; i++){
        left[i] = input[i*2];
        right[i] = input[i*2+1];
    }
    bufferCounter++;
    
}

//---------------------------------------------------------------
//calculate the dimension of of the whole string with spacing
void ofApp::stringDimension(){
    stringWidth = 0;
    for (int i = 0; i < echoTxt.size(); i++){
        stringWidth += echoTxt[i].charWidth;
    }
    stringWidth += spacing*(echoTxt.size() - 1);
    stringHeight = echoTxt[0].charHeight;
}
//---------------------------------------------------------------
//based on the mag, assign each value in the array on to a trianle on each letter, assign from mag[0] to a random triangle and start from there.
map<int, int> ofApp::assignMagnitude(EchoFont singleChar){
    vector<int> indexList;
    for (int i = 0; i < 256; i++){
        indexList.push_back(i);
    }
    ofRandomize(indexList);
    map<int, int> magMap;
        if (singleChar.triangleNum <= 256){
            for (int i = 0; i < singleChar.triangleNum; i++){
                magMap[i] = indexList[i];
            }
        } else {      //when the number of triangles is more than 256
            for (int i = 0; i< singleChar.triangleNum; i++){
                if (i <= 255){
                    magMap[i] = indexList[i];
                } else{
                    magMap[i] = indexList[i - 256];
                }
            }
            
        }
    return magMap;

}
