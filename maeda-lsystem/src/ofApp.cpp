#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    ofSetColor(30, 30,30);

    angle = 90;
    length = 20;

    string axiom = "F";
    
    sentence = axiom;
    
    rule1['a']="F";
    rule1['b']="FNFSFSFNF";
//    rule1['b']="FF+[+F-F-F]-[-F+F+F]";
    
//    rule2['a']="Y";
//    rule2['b']="SFXSY";
    turtle();
}

void ofApp::generate(){
    length *= 0.7;
    string nextSentence = "";
    for (int i=0; i< sentence.size(); i++) {
        std::string str(sentence);
        string current = str.substr(i,1);
        
        if (current == rule1['a']) {
            nextSentence.append(rule1['b']);
        }
//        else if (current == rule2['a']) {
//            nextSentence.append(rule2['b']);
//        }
        else {
            nextSentence.append(current);
        }
    }
    sentence = nextSentence;
    cout << sentence;
}

void ofApp::turtle(){
    buffer.allocate(ofGetWidth(), ofGetHeight());
    buffer.begin();
    
    ofTranslate(ofGetWidth()/2-400, ofGetHeight()/2);
    ofEnableAlphaBlending();
    ofSetLineWidth(2);
    ofRotate(90);
    for(int i =0; i< sentence.size(); i++){
        std::string str(sentence);
        string current = str.substr(i,1);
        
        if (current == "F") {
            ofDrawLine(0, 0, 0, -length);
            ofTranslate(0, -length);
        } else if (current == "N"){
            ofRotate(-angle);
        } else if (current == "S"){
            ofRotate(angle);
        }
//        else if (current == "[") {
//            ofPushMatrix();
//        }
//        else if (current == "]"){
//            ofPopMatrix();
//        }
    }
    buffer.end();
//    buffers.push_back(buffer);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    buffer.draw(0,0);
//    for (int i =0; i < buffers.size(); i++) {
//        buffers[i].draw(0,0);
//    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'g'){
        generate();
        turtle();
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
