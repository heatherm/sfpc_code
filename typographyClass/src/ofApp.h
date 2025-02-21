#pragma once

#include "ofMain.h"

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
    
        void drawTextAndBoundsAndSubline();
        void drawSeveralAndRotate();
        void draw3DFont();
   
        void scaleText();
        void rotateTextOutlines();
        void rotateTextWithTimeCurves();
        void linesRadiatingOut();
    
        void branch(float length, int count, bool left);
        void generateAngles();
    
        int trunkSize, minSize, angleBase;
        float relativeBranchSize, bushiness, scale;
        vector<int> angles;
        vector<string> words, words_copy;
        vector<ofColor> colors, colors_copy;

    
        ofTrueTypeFont font;
        ofEasyCam cam;
        ofPolyline line;
    
};
