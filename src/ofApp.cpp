#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    receiver.setup(PORT);
    mouseButtonState = "";
}

//--------------------------------------------------------------
void ofApp::update(){
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if (m.getAddress() == "/mouse/position") {
            remoteMouse.x = m.getArgAsInt32(0);
            remoteMouse.y = m.getArgAsInt32(1);
        } else if (m.getAddress() == "/mouse/button") {
            mouseButtonState = m.getArgAsString(0);
        } else if (m.getAddress() == "/play2") {
            tidalCyclesState = m.getArgAsString(21);
        }
        dumpOsc(m);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    int radius;
    
    if (mouseButtonState == "down") {
        radius = 20;
        ofSetColor(255, 127, 0);
    } else if (tidalCyclesState == "bd") {
        radius = 30;
        ofSetColor(127, 255, 0);
    } else {
        tidalCyclesState = "";
        radius = 10;
        ofSetColor(0, 127, 255);
    }
    ofDrawCircle(remoteMouse.x, remoteMouse.y, radius);
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

//--------------------------------------------------------------
void ofApp::dumpOsc(ofxOscMessage m){
    string msg_string;
    msg_string = m.getAddress();
    
    for (int i=0; i<m.getNumArgs(); i++) {
        msg_string += " ";
        
        if (m.getArgType(i) == OFXOSC_TYPE_INT32) {
            msg_string += ofToString(m.getArgAsInt32(i));
        } else if (m.getArgType(i) == OFXOSC_TYPE_FLOAT) {
            msg_string += ofToString(m.getArgAsFloat(i));
        } else if (m.getArgType(i) == OFXOSC_TYPE_STRING) {
            msg_string += m.getArgAsString(i);
        }
    }
    cout << msg_string << endl;
}
