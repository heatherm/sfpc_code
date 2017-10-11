#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    bool antiAliased = true;
    bool fullCharSet = true;
    bool makeContours = true;

    
    font.load("lato-light.ttf", 200, antiAliased, fullCharSet, makeContours);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    linesRadiatingOut();
}

//--------------------------------------------------------------
void ofApp::linesRadiatingOut(){    
    ofBackground(0);
    ofTranslate(300, 300);
    vector <ofPolyline> lines;
    ofSeedRandom(mouseX);
    vector<ofPath> chars = font.getStringAsPoints("hello");
    
    for (int i = 0; i < chars.size(); i++) {
        for (int j = 0; j < chars[i].getOutline().size(); j++) {
            ofPolyline temp = chars[i].getOutline()[j];
            temp = temp.getResampledBySpacing(5);
            lines.push_back(temp);
        }
    }
    
    for (int i = 0; i < lines.size(); i++) {
        for (int j=0; j < lines[i].size(); j++) {
            
            ofPoint a = lines[i][j] + ofPoint(mouseX,mouseY).getNormalized() * 0.1;
            ofPoint b = lines[i][j] + ofPoint(mouseX,mouseY);
            
            for (int k = 0; k < lines.size(); k++) {
                for (int l = 0; l < lines[k].size(); l++) {
                    ofPoint c = lines[k][l];
                    ofPoint d = lines[k][(l+1) % lines[k].size()];
                    
                    ofPoint intersection;
                    if(ofLineSegmentIntersection(a, b, c, d, intersection)){
                        b = intersection;
                    }
                }
            }
            ofDrawLine(a,b);
        }
    }
}


//--------------------------------------------------------------
void ofApp::rotateTextWithTimeCurves(){
    ofBackground(0);
    ofTranslate(300, 300);
    vector <ofPolyline> lines;
    
    vector<ofPath> chars = font.getStringAsPoints("hello");
    
    
    for (int i = 0; i < chars.size(); i++) {
        for (int j = 0; j < chars[i].getOutline().size(); j++) {
            lines.push_back(chars[i].getOutline()[j]);
        }
    }
    
    
    ofPoint center;
    int count = 0;
    
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            center += lines[i][j];
            count++;
        }
    }
    
    center /= (float)count;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            lines[i][j] -= center;
        }
    }
    
    for (int i = 0; i < lines.size(); i++) {
        for (int j=0; j < lines[i].size(); j++) {
            float y = lines[i][j].y;
            
            ofMatrix4x4 m;
            m.makeRotationMatrix(
                                 ofGetElapsedTimef()*50 + sin(y*.01 + ofGetElapsedTimef())*mouseX,
                                 ofPoint(0,1,0)
                                 );
            lines[i][j] = m * lines[i][j];
        }
        lines[i].draw();
    }
   
}

//--------------------------------------------------------------
void ofApp::rotateTextOutlines(){
    ofBackground(0);
    ofTranslate(300, 300);
    vector <ofPolyline> lines;
    
    vector<ofPath> chars = font.getStringAsPoints("hello");
    
    
    for (int i = 0; i < chars.size(); i++) {
        for (int j = 0; j < chars[i].getOutline().size(); j++) {
            lines.push_back(chars[i].getOutline()[j]);
        }
    }
    
    
    ofPoint center;
    int count = 0;
    
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            center += lines[i][j];
            count++;
        }
    }
    
    center /= (float)count;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            lines[i][j] -= center;
        }
    }
    
    ofRotateY(ofGetElapsedTimef()*50);
    for (int i = 0; i < lines.size(); i++) {
        lines[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::scaleText(){
    ofBackground(0);
    ofTranslate(300, 300);
    vector <ofPolyline> lines;
    
    vector<ofPath> chars = font.getStringAsPoints("hello");
    
    
    for (int i = 0; i < chars.size(); i++) {
        for (int j = 0; j < chars[i].getOutline().size(); j++) {
            lines.push_back(chars[i].getOutline()[j]);
        }
    }
    
    
    
    for (int i = 0; i < lines.size(); i++) {
        lines[i].draw();
        //        for (int j = 0; j < lines[i].size(); j++) {
        //            ofCircle(lines[i][j], 3);
        //        }
        
        ofPoint center;
        for (int j =0; j< lines[i].size(); j++) {
            center += lines[i][j];
        }
        center/= (float)lines[i].size();
        
        //not sure what he was going for here?
        //        for (int j =0; j< lines[i].size(); j++) {
        //            lines[i][j] = ofPoint(mouseX, mouseY)  + (lines[i][j]-ofPoint(mouseX,mouseY))*1.1;
        //        }
        
        lines[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::draw3DFont(){
    string s ="Hello";
    ofBackground(0);
    
    ofRectangle rect = font.getStringBoundingBox(s, 0, 0);
    // ortho makes it not get bigger when closer to you
    cam.enableOrtho();
    
    // top-left is 0,0, so it's easier to use the center as 0,0
    
    //rotates around 0,0. double click to get back
    cam.begin();
    // puts object at center -rect.width*.5, -rect.height*.05
    // two fingers zoom
    for (int i=0; i< 10; i++) {
        ofPushMatrix();
        ofTranslate(0, 0, i*10);
        font.drawString(s, -rect.width*.5, -rect.height*.05);
        ofPopMatrix();
    }
    cam.end();
}

//--------------------------------------------------------------
void ofApp::drawSeveralAndRotate(){
    // enabling depth tests will drop pixels and not blend them
    //    ofEnableDepthTest();
    
    // pixels always get brighter (not really sure what this does?)
    //    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    string s ="This stands as a \nsketch blah blah";
    
    ofBackground(0);
    
    // Basic rotation
    //    ofRotateY(ofGetElapsedTimef()*30);
    //    font.drawString(s, 200, 200);
    //    ofRotateX(ofGetElapsedTimef()*30);
    //    font.drawString("FOO FOO", 200, 200);
    
    ofRectangle rect = font.getStringBoundingBox(s, 200, 200);
    
    for (int i =0; i<20; i++) {
        ofPushMatrix();
        ofTranslate(200,200);
        // rotates off of baseline
        ofRotateY(ofGetElapsedTimef()*30 + i*20);
        font.drawString(s, 0, 0);
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::drawTextAndBoundsAndSubline(){
    ofBackground(0);
    ofSetColor(255);
    font.drawString("orange", 200, 200);
    ofSetColor(255, 0, 0);
    ofDrawLine(200,200, 1000,200);
    
    ofRectangle rect = font.getStringBoundingBox("orange", 200, 200);
    ofNoFill();
    ofDrawRectangle(rect);
    
    cout << rect << endl;
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
