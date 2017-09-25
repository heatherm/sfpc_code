#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    float sinVal = sin(ofGetElapsedTimef());
    ofBackground(0);
    
// circle moves from left to right
//    ofDrawCircle(
//        ofMap(sinVal, -1, 1, 0, ofGetWidth()),
//                 ofGetHeight()/2,
//                 100
//                 );
// cirle grows from center
//    ofDrawCircle(ofGetWidth()/2,
//                 ofGetHeight()/2,
//                 ofMap(sinVal, -1, 1, 1, 200)
//                 );
// frequency (multiply)
//    
//    ofDrawCircle(ofMap(sinVal, -1, 1, 200, 600),
//                 100,
//                 20
//                 );
//    
//    float sinVal2 = sin(ofGetElapsedTimef()*2);
//    ofDrawCircle(ofMap(sinVal2, -1, 1, 200, 600),
//                 150,
//                 20
//                 );
//
//    float sinVal3 = sin(ofGetElapsedTimef()*3);
//    ofDrawCircle(ofMap(sinVal3, -1, 1, 200, 600),
//                 200,
//                 20
//                 );
// phase (add)
//    for(int i = 0; i < 10; i++) {
//        float sinVal = sin(ofGetElapsedTimef()+i*.1);
//        ofDrawCircle(ofMap(sinVal, -1, 1, 200, 600),
//                     50*i,
//                     20
//                     );
//
//    }
// move around a mouse point
//    float x = mouseX + 100 * cos(ofGetElapsedTimef());
//    float y = mouseY + 100 * sin(ofGetElapsedTimef());
//    
//    ofDrawCircle(x,y, 10);
// of polyline
//    float radius = ofMap(sin(ofGetElapsedTimef()*20), -1,1,100,300);
//        float x = mouseX + 100 * cos(ofGetElapsedTimef());
//        float y = mouseY + 100 * sin(ofGetElapsedTimef());
//    
//    myLine.addVertex(x,y);
//    
//    if(myLine.size() > 50) {
//        myLine.getVertices().erase(myLine.getVertices().begin());
//    }
//    myLine.draw();
//    
//}
// lissajous figure
//            float x = ofGetWidth()/2 + 200 * cos(ofGetElapsedTimef()*3.7);
//            float y = ofGetHeight()/2 + 200 * sin(ofGetElapsedTimef()*2.1);
//    
//    myLine.addVertex(x,y);
//    
//        if(myLine.size() > 2200) {
//            myLine.getVertices().erase(myLine.getVertices().begin());
//        }
//        myLine.draw();
//    ofSetCircleResolution(100);
//    for (int i =0 ; i< 700; i++){
//        ofDrawCircle(200+i, ofGetHeight()/2, 100);
//    }
    
    float time = ofGetElapsedTimef();
    ofSetCircleResolution(100);
    for (int i =0 ; i< 700; i++){
        ofSetColor(
                   127+127*sin(i*0.01),
                   127+127*sin(i*0.011),
                   127+127*sin(i*0.012)
                   );
        ofDrawCircle(200+i, ofGetHeight()/2 + mouseX *sin(i*.03+time*1.4), 60+40*sin(i*0.01 + time));
    }
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
