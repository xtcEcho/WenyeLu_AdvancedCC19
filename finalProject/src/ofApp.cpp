#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
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
    ofBackgroundGradient(ofColor::black, ofColor(200,200,200), OF_GRADIENT_LINEAR);
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
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        ofLogNotice() << echoTxt[0].inputChar<< endl;
        
        for (int i = 0; i < echoTxt.size(); i++){
            EchoFont tempChar = echoTxt[i];
            //ofLogNotice() << tempChar.triangleNum<< endl;
            for (int j = 0; j < tempChar.triangleNum; j++){
                //ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
                ofNoFill();
                ofSetColor(ofColor::white);
                tempChar.drawTriangle(j);
                
            }
        }
    }
//
//    //EchoFont tryout
//    ofBackgroundGradient(ofColor::black, ofColor(200,200,200), OF_GRADIENT_LINEAR);
//    if (echoTxt.size() != 0){
//        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
//
//        ofNoFill();
//        ofSetColor(ofColor::white);
//        echoTxt[0].charMesh.draw();
//    }
    //txt part -------------------------------------------------------
//    ofBackgroundGradient(ofColor::black, ofColor(200,200,200), OF_GRADIENT_LINEAR);
//    ofPushMatrix();
//    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
//    if (echoTxt.size() != 0){
//        for (int i = 0; i < echoTxt.size(); i++){
//            //ofxTriangleMesh tempMesh = echoTxt[i].charMesh;
//            for (int j = 0; j <echoTxt[i].triangleNum; j++){
//                ofNoFill();
//                ofVec3f temp1 = echoTxt[i].charOutputPts[echoTxt[i].charTriangles[j].index[0]];
//                ofVec3f temp2 = echoTxt[i].charOutputPts[echoTxt[i].charTriangles[j].index[1]];
//                ofVec3f temp3 = echoTxt[i].charOutputPts[echoTxt[i].charTriangles[j].index[2]];
//                ofDrawTriangle(temp1, temp2, temp3);
//                //    ofDrawTriangle( tempIndex0,mesh.outputPts[mesh.triangles[i].index[1]],mesh.outputPts[mesh.triangles[i].index[2]]);
//
//            }
//        }
//    }
    
    
//    ofTranslate(100,ofGetWidth()/2);
//    //line.draw();
//
//
//    //mesh.draw();
//
//    outputPtsFC = mesh.outputPts;
//    trianglesFC = mesh.triangles;
//
//
//
////
//
//    for (int i=0; i<mesh.nTriangles; i++){
//
//        //ofFill();
//        //ofSetColor( triangles[i].randomColor);
//        ofNoFill();
//    float tempx = mesh.outputPts[mesh.triangles[i].index[0]].x - magnitude[i]*3.0f;
//    float tempy = mesh.outputPts[mesh.triangles[i].index[0]].y;
//    float tempz = mesh.outputPts[mesh.triangles[i].index[0]].z;
//    glm::vec3 tempIndex0(tempx, tempy, tempz);
//    ofDrawTriangle( tempIndex0,mesh.outputPts[mesh.triangles[i].index[1]],mesh.outputPts[mesh.triangles[i].index[2]]);
//
//
//        ofLogNotice() << tempx<< endl;
//    }
//
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    EchoFont tempEchoFont;
    tempEchoFont.setup();
    echoTxt.push_back(tempEchoFont);
    //ofLogNotice() << echoTxt.size()<< endl;
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
//based on the mag, assign each value in the array on to a trianle on each letter, assign from mag[0] to a random triangle and start from there. 
void ofApp::assignMagnitude(){
    
}
