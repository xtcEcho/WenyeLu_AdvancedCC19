//
//  EchoFont.h
//  finalProject
//
//  Created by 文野 卢 on 5/5/19.
//

#ifndef EchoFont_h
#define EchoFont_h

#include "ofMain.h"
#include "ofxTriangleMesh.h"

class EchoFont {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    void setup();    // setup method, use this to setup your object's initial state
    void update();  // update method, used to refresh your objects properties
    void draw();    // draw method, this where you'll do the object's drawing
    void drawTriangle(int triIndex);
    void getTriNum();
    void getOutputPts();
    void getTriangles();
    
    void keyPressed(int key);
    
    
    //variables
    ofTrueTypeFont baseFont;
    //Echofont is built based on char input instead of string, so that there are more control over each letter
    char inputChar;
    ofPath inputCharContour;
    ofPolyline line;
    ofxTriangleMesh charMesh;
    
    int triangleNum;
    vector <glm::vec3> charOutputPts;
    vector <meshTriangle> charTriangles;
    
    EchoFont();
    

}; // don't forget the semicolon!

#endif /* EchoFont_h */
