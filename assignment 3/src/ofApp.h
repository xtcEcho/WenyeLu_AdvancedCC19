#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxBox2d.h"
#include "ofxCvHaarFinder.h"



class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void resized(int w, int h);
    
    
    //box2d world
    ofxBox2d box2d;
    
    ofPolyline firstLine;
    ofPolyline secondLine;
    
    //implement a hand shape edge
    vector <shared_ptr<ofxBox2dEdge>> edges;
//    ofxBox2dEdge first;
//    ofxBox2dEdge second;
    
    vector    <shared_ptr<ofxBox2dCircle> > circles;         // default box2d circles
    
    //set ball radius
    float r;
    
    
    //a timer for dropping balls
    int initTime;
    int realTime;
    
    
    
    //    ofImage crop(ofImage* sImg, int x1, int y1, int w, int h);
    //    ofImage img;
    //    ofTexture cropTexture;
    //    ofPixels pixels;
    //    ofImage im;
    //    ofImage cropped;
    
    ofVideoGrabber  mVidGrabber;
    int camWidth = 1280;
    int camHeight = 720;
    
    ofxCvColorImage colorImage;
    ofxCvColorImage mHand;
    
    ofImage                mImage;
    
    ofxCvGrayscaleImage     grayImage;
    ofxCvGrayscaleImage     grayhandImage;
    ofxCvGrayscaleImage     grayBg;
    ofxCvGrayscaleImage     grayDiff;
    
    ofxCvContourFinder     contourFinder;
    
    int                 threshold;
    bool            bLearnBakground;
    
    ofFbo    mFbo1;
};
