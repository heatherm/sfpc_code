#include "ofApp.h"
#include "ofTrueTypeFont.h"

//--------------------------------------------------------------
void ofApp::setup(){
    bool antiAliased = true;
    bool fullCharSet = true;
    bool makeContours = true;
    
    font.load("lato-bold.ttf", 60, antiAliased, fullCharSet, makeContours);
    
    vector<string> word_choices = {"his", "first", "film", "studio", "auspicious", "space", "ship", "commander", "science", "fiction", "classic", "forbidden", "planet", "found", "best", "dramatic", "role", "captain", "overturned", "ocean", "liner", "serious", "actor", "camera", "prankster", "personality", "exploited", "Airplane", "huge", "hit", "doctor", "plane", "pilots", "passengers", "hospital", "flight", "attendant", "big", "building", "patients", "important", "deadpans", "fly", "serious", "call", "me", "shirley", "cast", "type","comedy", "career", "appearing", "such", "comedies", "takeoff", "demonic", "possession", "movies", "exorcist", "mr.", "magoo", "played", "title", "role", "good", "natured", "bumbler"};
    
vector<ofColor> color_choices = {ofColor(157,157,157,180), ofColor(157,157,157,180), ofColor(239,178,156,180), ofColor(157,157,157,180), ofColor(239,178,156,180), ofColor(157,157,157,180), ofColor(239,178,156,180), ofColor(157,157,157,180), ofColor(239,178,156,180), ofColor(157,157,157,180), ofColor(157,157,157,180), ofColor(239,178,156,180), ofColor(239,178,156,180), ofColor(157,157,157,180), ofColor(157,157,157,180), ofColor(239,178,156,180), ofColor(239,178,156,180), ofColor(157,157,157,180), ofColor(239,178,156,180), ofColor(157,157,157,180), ofColor(157,157,157,180), ofColor(157,157,157,180), ofColor(239,178,156,180)};
    
    trunkSize = 40;
    relativeBranchSize = 0.77;
    minSize = 10;
    angleBase = 15;
    bushiness = .96;
    scale = .73;
    
    int count = 0;
    float blamo = trunkSize;
    while (blamo > minSize){
        count++;
        blamo *= relativeBranchSize;
    }
    
    int branches = 4*count;
    
    angles.resize(branches);
    words.resize(branches);
    colors.resize(branches);

    
    for (int i = 0; i < branches; i++){
        int angle = angleBase + (i*bushiness);
        if(i%2 == 0){
            int scaledAngle;
            if (i < 20){
                scaledAngle = angle*2;
            } else if (i < 100) {
                scaledAngle = angle*3;
            } else {
                scaledAngle = angle*4;
            }
            angles[i] = ofRandom(5,scaledAngle);
            angles[i + 1] = ofRandom(-scaledAngle,-5);
            
            words[i] = word_choices[ofRandom(word_choices.size())];
            words[i+1] = word_choices[ofRandom(word_choices.size())];
            
            colors[i] = color_choices[ofRandom(color_choices.size())];
            colors[i+1] = color_choices[ofRandom(color_choices.size())];
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}



//--------------------------------------------------------------
void ofApp::draw(){
    words_copy.clear();
    colors_copy.clear();
    
    for (int j=0; j<words.size()*3; j++){
        for (int i=0; i<words.size(); i++){
            words_copy.push_back(words[i]);
            colors_copy.push_back(colors[i]);
        }
    }
    
    ofBackground(51);
    
    ofTranslate(ofGetWidth()/2, ofGetHeight());
    ofRotate(-90);
    branch(trunkSize, 0, false);
}


//--------------------------------------------------------------
void ofApp::branch(float length, int count, bool left){
    ofScale(scale, scale, 1);
    
    string text = words_copy.back();
    ofSetColor(colors_copy.back());
    words_copy.pop_back();
    colors_copy.pop_back();

    ofEnableAlphaBlending();
    
    float fontWidth = font.stringWidth(text);
    ofTranslate(fontWidth + 50/(count+1), 0);
    ofRotate(180);
    font.drawString(text, -fontWidth, fontWidth);
//    font.drawString(text, 0, 0);
//    ofTranslate(fontWidth + 50/(count+1), 0);
    
    if (length > minSize){
        ofPushMatrix();
        if (false){
//            count % 3 == 0
            ofRotate((angles[count] + 180) % 360);
        } else {
            

            ofRotate(angles[count]);
        }
        
        branch(length*relativeBranchSize, count+1, true);
        ofPopMatrix();
        ofPushMatrix();
        ofRotate(angles[count+1]);
        branch(length*relativeBranchSize, count+1, false);
        ofPopMatrix();
        if (length < minSize*4) {
            ofPushMatrix();
            ofRotate(angles[angles.size()-count]);
            branch(length*relativeBranchSize, count+2, false);
            ofPopMatrix();
        }
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
