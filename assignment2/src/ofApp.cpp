#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    kennedyVideo.load("kennedy1.mp4");
    ofSetRectMode(OF_RECTMODE_CENTER);
    kennedyVideo.setLoopState(OF_LOOP_NORMAL);
    kennedyVideo.play();
    cam1.load("1.mp4");
    cam2.load("2.mp4");
    cam3.load("3.mp4");
    cam4.load("4.mp4");
    cams.push_back(cam1);
    cams.push_back(cam2);
    cams.push_back(cam3);
    cams.push_back(cam4);
    for (int i = 0; i < 4; i++){
        cams[i].setLoopState(OF_LOOP_NORMAL);
        cams[i].play();
        
    }
    vSpeed = 1.0;
    
    //stopControl = 0;
    }

//--------------------------------------------------------------
void ofApp::update(){
    
    kennedyVideo.update();
    for (int i = 0; i < 4; i++){
        cams[i].update();
    }
  
}

//--------------------------------------------------------------
void ofApp::draw(){
    echo1();
    kennedyVideo.setSpeed(vSpeed);
    kennedyVideo.draw(ofGetWidth()/2, ofGetHeight()/2);
    for (int i = 0; i < 4; i++){
        
        if (camSwitch[i] == true){
            if (i == 0){
                cams[i].draw(ofGetWidth()/2 - kennedyVideo.getWidth()/4, ofGetHeight()/2 - kennedyVideo.getHeight()/4);
                //std::cout << "worked" << endl;
            } else if (i == 1){
                cams[i].draw(ofGetWidth()/2 + kennedyVideo.getWidth()/4, ofGetHeight()/2 - kennedyVideo.getHeight()/4);
            } else if (i ==2){
                cams[i].draw(ofGetWidth()/2 - kennedyVideo.getWidth()/4, ofGetHeight()/2 + kennedyVideo.getHeight()/4);
            } else if (i ==3){
                cams[i].draw(ofGetWidth()/2 + kennedyVideo.getWidth()/4, ofGetHeight()/2 + kennedyVideo.getHeight()/4);
            }

        }
    }
    

}

//--------------------------------------------------------------
//function echo is implemented by Echo
//the function enables speed change of the video according to the speed of the mouse move
void ofApp::echo1(){
    //video speed only change with the mosue when mouse is being dragged
    if (mMove >= 0){
        
        if (mMove >= 80){
            mMove = 80;
        }
        //the only apply new vspeed 4 times per second so that the video is smoother
        int dragNow = ofGetElapsedTimeMillis();
        if ((dragNow - dragStart)%250 == 0){
            vSpeed = ofMap(mMove, 0, 80.1, 0.0, 4.0);
            //round up vspeed leaving only one digit after decimal point to make it look smoother
            vSpeed = roundf(vSpeed*10)/10;
            
            
        }
       
    }
    else {
        vSpeed = 1.0;
        
    }
}
//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1' || key == '2' || key == '3' || key == '4'){
        cam = true;
        if (key == '1'){
            cams[0].setSpeed(vSpeed);
            camSwitch[0] = true;
        } else if (key == '2'){
            cams[1].setSpeed(vSpeed);
            camSwitch[1] = true;
        } else if (key == '3'){
            cams[2].setSpeed(vSpeed);
            camSwitch[2] = true;
        }else if (key == '4'){
            cams[3].setSpeed(vSpeed);
            camSwitch[3] = true;
        }
        
        
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
    dragStart = ofGetElapsedTimeMillis();
    ofVec2f m1(mouseX, mouseY);
    ofVec2f m2(ofGetPreviousMouseX(), ofGetPreviousMouseY());
    mMove = m1.squareDistance(m2);
    //std::cout << "distance: " << sqrt(mMove) << endl;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    mMove = -1;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
