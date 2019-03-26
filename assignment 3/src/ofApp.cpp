#include "ofApp.h"

using namespace cv;
using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    initTime = ofGetSeconds();
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    box2d.init();
    box2d.setGravity(0, 10);
    //unable below function to make ball fall off the screen
    //box2d.createGround();
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    
    
    mVidGrabber.setVerbose(true);
    mVidGrabber.setup(camWidth,camHeight);
    
    glm::ivec2 vidGrabberSize = glm::ivec2 (mVidGrabber.getWidth(),mVidGrabber.getHeight());
    
    mImage.allocate(vidGrabberSize.x,vidGrabberSize.y,OF_IMAGE_COLOR);
    mHand.allocate(vidGrabberSize.x,vidGrabberSize.y);
    colorImage.allocate(vidGrabberSize.x,vidGrabberSize.y);
    grayImage.allocate(vidGrabberSize.x,vidGrabberSize.y);
    grayhandImage.allocate(vidGrabberSize.x,vidGrabberSize.y);
    grayBg.allocate(vidGrabberSize.x,vidGrabberSize.y);
    grayDiff.allocate(vidGrabberSize.x,vidGrabberSize.y);
    
    mFbo1.allocate(vidGrabberSize.x,vidGrabberSize.y, GL_RGBA);
    
    bLearnBakground = true;
    threshold = 254;
}

//--------------------------------------------------------------
void ofApp::update(){
    box2d.update();
    if (circles.size() == 0){
        realTime = ofGetSeconds();
        if ((realTime - initTime) == 3){
            r = ofRandom(20, 35);
            circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
            circles.back().get()->setPhysics(3.0, 0.53, 0.1);
            circles.back().get()->setup(box2d.getWorld(), ofRandom(0, ofGetWidth()), -35, r);
        }
    } else {
        if(circles.back()->getPosition().y>(ofGetHeight()+300)){
            r = ofRandom(20, 35);
            circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
            circles.back().get()->setPhysics(3.0, 0.53, 0.1);
            circles.back().get()->setup(box2d.getWorld(), ofRandom(0, ofGetWidth()), -35, r);
        }
    }
    
    bool bNewFrame = false;
    
    mVidGrabber.update();
    bNewFrame = mVidGrabber.isFrameNew();
    
    if (bNewFrame){
        colorImage.setFromPixels(mVidGrabber.getPixels());
        colorImage.mirror(false,true);
        mHand.setFromPixels(mVidGrabber.getPixels());
        mHand.mirror(false,true);
        mImage.setFromPixels(mVidGrabber.getPixels());
        mImage.mirror(false,true);
        mHand.blurGaussian(5);
        mHand.dilate();
        mHand.erode();
        
        //find skin color in input image
        int len = camWidth * camHeight * 3;
        int Max;
        int Min;
        
        for (int i = 0; i < camHeight; i++){
            for (int j = 0; j < camWidth; j++){
                int Red = mHand.getPixels()[camWidth * i * 3 + j * 3];
                int Green = mHand.getPixels()[camWidth * i * 3 + j * 3 + 1];
                int Blue = mHand.getPixels()[camWidth * i * 3 + j * 3 + 2];
                
                if (Red > 95 && Green > 40 && Blue > 20 && Red > Blue && Red > Green && abs(Red - Green) > 15){
                    if (Blue >= Green){
                        Max = Blue;
                        Min = Green;
                    } else {
                        Max = Green;
                        Min = Blue;
                    }
                    if  (Red > Max) {
                        Max = Red;
                    } else if (Red < Min) {
                        Min = Red;
                    }
                    if (Max - Min > 15){
                        mHand.getPixels()[camWidth * i * 3 + j * 3] = 255;
                        mHand.getPixels()[camWidth * i * 3 + j * 3 + 1] = 255;
                        mHand.getPixels()[camWidth * i * 3 + j * 3 + 2] = 255;
                    }
                }
            }
        }
        mHand.flagImageChanged();
        
        grayImage = colorImage;
        grayhandImage = mHand;
        
        grayhandImage.threshold(threshold);
        
        contourFinder.findContours(grayhandImage, (camWidth * camHeight)/30, (camWidth * camHeight)/3, 10, true);
        
        //mImage.getTexture().setAlphaMask(grayhandImage.getTexture());
    }
    
    if (first.size()!=0){
        first.clear();
    }
    if (second.size()!=0){
        second.clear();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    //  finding the largest and the second largest contour
    int largest_area = 0;
    int largest_contour_index = 0;
    int second_largest_area  = 0;
    int second_largest_contour_index = 0;
    ofRectangle largest_bounding_rect;
    ofRectangle second_largest_bounding_rect;
    
    // iterate through each contour.
    for( int i = 0; i< contourFinder.blobs.size(); i++ )
    {
        //  Find the area of contour
        int length_of_contour = contourFinder.blobs[i].pts.size();
        if(length_of_contour > largest_area){
            second_largest_area = largest_area;
            second_largest_contour_index = largest_contour_index;
            largest_area = length_of_contour;
            //Store the index of largest
            largest_contour_index = i;
        }else if(length_of_contour > second_largest_area){
            second_largest_area = length_of_contour;
            //Store the index of largest of the second largest
            second_largest_contour_index = i;
        }
        largest_bounding_rect = contourFinder.blobs[largest_contour_index].boundingRect;
        second_largest_bounding_rect = contourFinder.blobs[second_largest_contour_index].boundingRect;
        
        
        //draw image subsections based on contour area found above
        //    mImage.drawSubsection(largest_bounding_rect.x,largest_bounding_rect.y,largest_bounding_rect.width,largest_bounding_rect.height,largest_bounding_rect.x,largest_bounding_rect.y);
        //    mImage.drawSubsection(second_largest_bounding_rect.x,second_largest_bounding_rect.y,second_largest_bounding_rect.width,second_largest_bounding_rect.height,second_largest_bounding_rect.x,second_largest_bounding_rect.y);
        
        
        //only display hands
        //draw image subsections based on contour area found above
        ofSetHexColor(0xffffff);
        mFbo1.begin();
        ofClear(0,0,0,0);
        ofSetColor(255,255,255,255);
        ofFill();
        for(int j=0; j < contourFinder.blobs[largest_contour_index].pts.size(); j++)
        {
            first.addVertex(contourFinder.blobs[largest_contour_index].pts[j].x, contourFinder.blobs[largest_contour_index].pts[j].y);
        }
        first.setPhysics(0.0, 0.5, 0.5);
        first.create(box2d.getWorld());
        first.draw();
        for(int j=0; j < contourFinder.blobs[second_largest_contour_index].pts.size(); j++)
        {
            second.addVertex(contourFinder.blobs[second_largest_contour_index].pts[j].x, contourFinder.blobs[second_largest_contour_index].pts[j].y);
        }
        second.setPhysics(0.0, 0.5, 0.5);
        second.create(box2d.getWorld());
        second.draw();
        mFbo1.end();
        
        mFbo1.draw(0,0);
        
        mImage.getTexture().setAlphaMask(mFbo1.getTexture());
        
        mImage.draw(0,0);
        
        //draw hand contour shapes
        
        ofNoFill();
        ofSetLineWidth(2);
        ofSetHexColor(0x557dcc);
        //ofDrawRectangle(largest_bounding_rect);
        ofBeginShape();
        for(int j=0; j < contourFinder.blobs[largest_contour_index].pts.size(); j++)
        {
            ofVertex(contourFinder.blobs[largest_contour_index].pts[j].x, contourFinder.blobs[largest_contour_index].pts[j].y);
        }
        ofEndShape();
        
        ofSetHexColor(0xf2e41f);
        //ofDrawRectangle(second_largest_bounding_rect);
        ofBeginShape();
        for(int j=0; j < contourFinder.blobs[second_largest_contour_index].pts.size(); j++)
        {
            ofVertex(contourFinder.blobs[second_largest_contour_index].pts[j].x, contourFinder.blobs[second_largest_contour_index].pts[j].y);
        }
        ofEndShape();
        
    }
    
    if (circles.size()!=0){
        ofFill();
        ofSetHexColor(0x90d4e3);
        circles.back()->draw();
    }
}
//--------------------------------------------------------------

//ofImage ofApp::crop(ofImage* sImg, int x, int y, int w, int h) {
//
//    int sW = sImg->getWidth();
//    int sH = sImg->getHeight();
//
//    ofImage tmpImg;
//    tmpImg.allocate(w, h, OF_IMAGE_COLOR);
//
//    unsigned char subRegion[ w * h * 3  ];
//    ofPixels srcPixels = sImg->getPixels();
//
//    for (int i = 0; i < w; i++){
//        for (int j = 0; j < h; j++){
//            int mainPixelPos = ((j + y) * sW + (i + x)) * 3;
//            int subPixlPos = (j * w + i) * 3;
//
//            subRegion[subPixlPos] = srcPixels[mainPixelPos];   // R
//            subRegion[subPixlPos + 1] = srcPixels[mainPixelPos + 1];  // G
//            subRegion[subPixlPos + 2] = srcPixels[mainPixelPos + 2];  // B
//        }
//    }
//    tmpImg.setFromPixels(subRegion, w, h,  OF_IMAGE_COLOR);
//    return tmpImg;
//}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
            //by pressing s you will start a new game round; the vector will be cleaned up and the timer reset
            //        case 's':
            //            playMode = true;
            //            circles.clear();
            //            initTime = ofGetSeconds();
        case ' ':
            bLearnBakground = true;
            break;
        case '+':
            threshold ++;
            if (threshold > 255) threshold = 255;
            break;
        case '-':
            threshold --;
            if (threshold < 0) threshold = 0;
            break;
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
