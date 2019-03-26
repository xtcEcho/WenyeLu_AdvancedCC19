#include "ofApp.h"



//how we define our Ball constructor
Ball::Ball(){
    ofLogNotice()<<"construced a Ball instance"<< endl;
}

Ball::~Ball(){
    ofLogNotice()<<"destroyed a Ball instance"<< endl;
}

void Ball::saySomething(){
    ofLogNotice("Ball") <<"Something!"<< endl;
}
//--------------------------------------------------------------
void ofApp::setup(){
    myBall = make_shared<Ball>();//stack memory
    //shared_ptr<Ball> myBall = make_shared<Ball>();//heap memory
    
    memberBall.saySomething();
    
//    for (int i = 0; i <100; i++){
//        shared_ptr<Ball> ball = make_shared<Ball>();
//        mBalls.push_back(ball);
//        ball->saySomething();
//    }
    int sum = mCustom.add(8, 8);
    ofLogNotice() << sum << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
