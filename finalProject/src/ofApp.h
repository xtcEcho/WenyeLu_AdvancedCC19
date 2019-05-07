#pragma once

#include "fft.h"
#include "ofMain.h"
#include "ofxTriangleMesh.h"
#include "EchoFont.h"

#define BUFFER_SIZE 256
#define NUM_WINDOWS 80

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
		//void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        //a function to calculate string dimensions
        void stringDimension();
       //first int is the index of triangles, second is index of Magnitude
        map<int, int> assignMagnitude(EchoFont singleChar);
    
    //audio part -----------------------------------------------------------
        void audioReceived     (float * input, int bufferSize, int nChannels);
    
        
        float * left;
        float * right;
        int     bufferCounter;
        fft        myfft;
    
        float magnitude[BUFFER_SIZE];
        float phase[BUFFER_SIZE];
        float power[BUFFER_SIZE];
    
        float freq[NUM_WINDOWS][BUFFER_SIZE/2];
        float freq_phase[NUM_WINDOWS][BUFFER_SIZE/2];
    
    //add on the echoFont class
        vector<EchoFont> echoTxt;
        vector<map<int, int>> txtMap;
    
    vector<int> magIndex;
    
    //string dimensions
    float stringWidth;
    float stringHeight;
    int spacing = 0;
    
    ofEasyCam cam;
};
