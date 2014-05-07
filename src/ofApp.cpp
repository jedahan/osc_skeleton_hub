#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    oscReceiver.setup(PORT);
    
    lastPulseTime = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    int time = ofGetElapsedTimeMillis();
    
    if (time - lastPulseTime > PULSE_INTERVAL) {
        lastPulseTime = time;
        sendPulse();
    }
    
    while(oscReceiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		oscReceiver.getNextMessage(&m);
        
        // handle heartbeat
        if(m.getAddress() == "/call/home"){
			registerClient(&m);
		}
    }

}

void ofApp::registerClient(ofxOscMessage *m) {
    // we use the client's IP address as an ID - this has limitations, but will work in
    // many cases.
    string clientIp = m->getRemoteIp();
    
    cout << "received call home from " << clientIp << endl;
    
    // Check to see if this IP already is registered as a client
    map<string, ofxOscSender>::const_iterator it = clients.find(clientIp);

    if(it == clients.end()) {
        // no client found for this IP, add it to the map of clients.
        cout << "registering new client" << endl;
        ofxOscSender _sender;
        _sender.setup(clientIp, PORT);
        clients[clientIp] = _sender;
    }

}

/**
 * Send a heartbeat pulse to all registered clients.
 */
void ofApp::sendPulse() {
    cout << "sending pulse to IPs:" << endl;
    
    // first, we add all of registered client IPs to the message
    ofxOscMessage m;
    m.setAddress("/pulse");
    for(map<string, ofxOscSender>::iterator i = clients.begin(); i != clients.end(); i++) {
        // iterator->first = key (string ip)
        // iterator->second = value (ofxOscSender sender)
        string ip = i->first;
        cout << ip << endl;
        m.addStringArg(ip);
    }
    
    // then we iterate through the registered clients, sending the heartbeat message to them all.
    for(map<string, ofxOscSender>::iterator i = clients.begin(); i != clients.end(); i++) {
        // iterator->first = key (string ip)
        // iterator->second = value (ofxOscSender sender)
        ofxOscSender & _sender = i->second;
        _sender.sendMessage(m);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
