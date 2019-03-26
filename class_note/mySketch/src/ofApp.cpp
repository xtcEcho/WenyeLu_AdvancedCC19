#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'a') {
        mStrings.push_back(ofToString(key));
    }
    ofImage image;
    if(image.load("https://www.google.com/url?sa=i&rct=j&q=&esrc=s&source=images&cd=&ved=2ahUKEwj05M7tj8ngAhURd98KHahTA6wQjRx6BAgBEAU&url=https%3A%2F%2Frateyourmusic.com%2Fartist%2F%25E6%25A4%258E%25E5%2590%258D%25E6%259E%2597%25E6%25AA%258E&psig=AOvVaw0xQJ0EH5Xr_QcnAeUWkge9&ust=1550711283410822")){
        mImages.push_back(image);
    }
    ofLogNotice() << mImages.size() <<endl;
    
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
    mFloatingNums.push_back(ofRandom(100.0));
    ofLogNotice() << "mFloatingNums has" << mFloatingNums.size() << endl;
    ofLogNotice() << mFloatingNums.back() << endl;
    
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
