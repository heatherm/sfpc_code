#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    img.load("cheetah.png");
    img.setImageType(OF_IMAGE_GRAYSCALE);
    

}

//--------------------------------------------------------------
void ofApp::update(){
//    tv noise
//    img.allocate(500, 500, OF_IMAGE_GRAYSCALE);
//    for (int i =0; i< 500; i++) {
//        for (int j = 0; j< 500; j++) {
//            img.setColor(i,j,ofColor(ofRandom(255)));
//        }
//    }
//    img.update();
    
//        gradient
//        img.allocate(500, 500, OF_IMAGE_GRAYSCALE);
//        for (int i =0; i< 500; i++) {
//            for (int j = 0; j< 500; j++) {
//                img.setColor(i,j,ofColor(i));
//            }
//        }
//        img.update();
    
//    weird fan
//    img.allocate(500, 500, OF_IMAGE_GRAYSCALE);
//    for (int i =0; i< 500; i++) {
//        for (int j = 0; j< 500; j++) {
//            img.setColor(i,j,ofColor(i*100/(float)j+1));
//        }
//    }
//    img.update();
    
//    radiating gradient circles
//    img.allocate(500, 500, OF_IMAGE_GRAYSCALE);
//    for (int i =0; i< 500; i++) {
//        for (int j = 0; j< 500; j++) {
//            float dist = ofDist(mouseX, mouseY, i,j);
//            img.setColor(i,j,ofColor(sin(i*.01+dist)));
//        }
//    }
//    img.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
//    img.draw(0,0);
    
    for(int i=0; i<img.getWidth(); i+=10) {
        for(int j=0; j<img.getHeight(); j+=10){
            ofColor c  = img.getColor(i,j);
            float brightness = c.getBrightness();
//            cheetah as circles
//            float radius = ofMap(brightness, 0, 255, 0, 5);
//            ofDrawCircle(i,j,radius);
            
//            cheetah as rotating lines
            ofPushMatrix();
            ofTranslate(i, j);
            ofRotateZ(ofMap(brightness,0,255,0,mouseX/5));
            ofLine(-5,0,5,0);
            ofPopMatrix();
            
        }
    }
    
//    unsigned char * data = img.getPixels().getData();
//
//    for(int i=0; i<img.getWidth(); i+=10) {
//        for(int j=0; j<img.getHeight(); j+=10){
//            int index = j* img.getWidth() + i;
//            int brightness = data[index];
//            ofDrawCircle(i,j,ofMap(brightness, 0, 255, 0, 5));
//
//        }
//    }
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
