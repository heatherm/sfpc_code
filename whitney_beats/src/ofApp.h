#pragma once

#include "ofMain.h"
#include "ofxGui.h"

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
    
    //triangles
    //The number of trianglesint nVert; //The number of the vertices equals nTri * 3
    vector<ofPoint> vertices;
    vector<ofColor> colors;
    vector<int> beatBuckets;
    int nTri;
    int nVert;
    
    
    //audio
    ofSoundPlayer player;
    float * fftSmooth;
    int bands;
    bool beatDetected;
        
    // gui
    ofxPanel gui;
    ofxFloatSlider vertScale;
    ofxFloatSlider smoothScale;
    ofxFloatSlider range;

		
};
