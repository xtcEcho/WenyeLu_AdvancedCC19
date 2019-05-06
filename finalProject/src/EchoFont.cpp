//
//  EchoFont.cpp
//  finalProject
//
//  Created by 文野 卢 on 5/5/19.
//

#include "EchoFont.h"

EchoFont::EchoFont(){
    
}

void EchoFont::setup(){
    baseFont.load("SFAlienEncountersSolid-Ital.ttf", 320, true, true, true);
    bool vflip = true;
    bool filled = true;
    
    filled = false;
   
    inputCharContour = baseFont.getCharacterAsPoints(inputChar, vflip, filled);
        //get the outline from our test character
    auto outline = inputCharContour.getOutline();
        //loop through all the polylines of our outline
        //and for every polyline, add its vertices to our line
        //KS TODO: need to add space compensation to each letter so shapes are not drawing on top of eachother.
    for(auto &lins : outline){
        auto pts = lins.getVertices();
        for(auto &pt : pts){
            line.addVertex(glm::vec3(pt.x, pt.y, 0));
            //ofLogNotice() << "added vertex at" << pt.x << " " << pt.y << endl;
        }
            
    }
    
    if (line.size() > 2){
        
        ofPolyline lineRespaced = line;
        
        // add the last point (so when we resample, it's a closed polygon)
        lineRespaced.addVertex(lineRespaced[0]);
        // resample
        lineRespaced = lineRespaced.getResampledBySpacing(20);
        // I want to make sure the first point and the last point are not the same, since triangle is unhappy:
        lineRespaced.getVertices().erase(lineRespaced.getVertices().begin());
        // if we have a proper set of points, mesh them:
        if (lineRespaced.size() > 5){
            
            // angle constraint = 28
            // size constraint = -1 (don't constraint triangles by size);
            
            charMesh.triangulate(lineRespaced, 28, -1);
            
            
            // this is an alternative, constrain on size not angle:
            //mesh.triangulate(lineRespaced, -1, 200);
            // see ofxTriangleMesh.h for info.
            
        }
    }
    getTriNum();
    getOutputPts();
    getTriangles();
    
}

//--------------------------------------------------------------
void EchoFont::update(){
    
}

//--------------------------------------------------------------
void EchoFont::draw(){
    
}

//--------------------------------------------------------------
void EchoFont::drawTriangle(int triIndex){
    ofDrawTriangle(charMesh.outputPts[charMesh.triangles[triIndex].index[0]],charMesh.outputPts[charMesh.triangles[triIndex].index[1]],charMesh.outputPts[charMesh.triangles[triIndex].index[2]]);
    
    //    ofDrawTriangle( tempIndex0,mesh.outputPts[mesh.triangles[i].index[1]],mesh.outputPts[mesh.triangles[i].index[2]]);
}
//--------------------------------------------------------------
void EchoFont::getTriNum(){
    triangleNum = charMesh.nTriangles;
}

//--------------------------------------------------------------
void EchoFont::getOutputPts(){
    charOutputPts = charMesh.outputPts;
}

//--------------------------------------------------------------
void EchoFont::getTriangles(){
    charTriangles = charMesh.triangles;
}
//--------------------------------------------------------------
void EchoFont::keyPressed(int key){
    if (key >=32 && key <=126){
        inputChar = key;
    }
  
    ofLogNotice()<<key<<endl;
}
