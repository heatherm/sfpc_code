#include "ofApp.h"
#include "ofTrueTypeFont.h"

//--------------------------------------------------------------
void ofApp::setup(){
    bool antiAliased = true;
    bool fullCharSet = true;
    bool makeContours = true;
    
    font.load("lato-light.ttf", 60, antiAliased, fullCharSet, makeContours);
    
    vector<string> word_choices = {"His", "first", "film", "studio", "auspicious", "space", "ship", "commander", "science", "fiction", "classic", "Forbidden", "Planet", "found", "best", "dramatic", "role", "captain", "overturned", "ocean", "liner", "disaster", "movie"};
    
    trunkSize = 250;
    relativeBranchSize = 0.67;
    minSize = 7;
    angleBase = 30;
    bushiness = .96;
    scale = 1.0;
    
    int count = 0;
    float blamo = trunkSize;
    while (blamo > minSize){
        count++;
        blamo *= relativeBranchSize;
    }
    
    int branches = 4*count;
    
    angles.resize(branches);
    words.resize(branches);
    
    for (int i = 0; i < branches; i++){
        int angle = 30 + (i*.96);
        if(i%2 == 0){
            angles[i] = ofRandom(10,angle);
            angles[i + 1] = ofRandom(-angle,-10);
            
            words[i] = word_choices[ofRandom(23)];
            words[i+1] = word_choices[ofRandom(23)];
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
}



//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(51);
    
    ofTranslate(ofGetWidth()/2, ofGetHeight());
    ofRotate(-90);
    branch(trunkSize, 0);
}


//--------------------------------------------------------------
void ofApp::branch(float length, int count){
    ofSetColor(255);
    ofScale(.9, .9, 1);
    string text = words[count];
    float fontWidth = font.stringWidth(text);
    font.drawString(text, 0, 0);
    ofTranslate(fontWidth, 0);

    
    if (length > minSize){
        ofPushMatrix();
        ofRotate(angles[count]);
        branch(length*relativeBranchSize, count+1);
        ofPopMatrix();
        ofPushMatrix();
        ofRotate(angles[count+1]);
        branch(length*relativeBranchSize, count+1);
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::linesRadiatingOut(){    
    ofBackground(0);
    ofTranslate(300, 300);
    vector <ofPolyline> lines;
    ofSeedRandom(mouseX);
    vector<ofPath> chars = font.getStringAsPoints("nice!");
    
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
    
    vector<ofPath> chars = font.getStringAsPoints("nice!!");
    
    
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
                                 ofGetElapsedTimef()*mouseX + sin(y*.01 + ofGetElapsedTimef())*mouseY,
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
    ofTranslate(500, 500);
    vector <ofPolyline> lines;
    
    vector<ofPath> chars = font.getStringAsPoints("NICE!!");
    
    
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
