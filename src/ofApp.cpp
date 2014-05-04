#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    oscReceiver.setup(PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    
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
    
    cout << "received heartbeat from " << clientIp << endl;
    
    // Check to see if this IP already is registered as a client
    map<string, oscClient>::iterator it = clients.find(clientIp);
    oscClient cl;
    if(it == clients.end()) {
        // no client found for this IP, add it to the map of clients.
        cout << "registering new client" << endl;
        clientIps.insert(clientIp);
        ofxOscSender & _sender = clients[clientIp].sender;
        _sender.setup(clientIp, PORT);
    }

}

/**
 * Send a heartbeat pulse to all registered clients.
 */
void ofApp::sendHeartbeat() {
    cout << "sending heartbeat to IPs:" << endl;
    
    // first, we add all of registered client IPs to the message
    ofxOscMessage m;
    m.setAddress("/pulse");
    for (set<string>::iterator i = clientIps.begin(); i != clientIps.end(); i++) {
        string ip = *i;
        cout << ip << endl;
        m.addStringArg(ip);
    }
    
    // then we iterate through the registered clients, sending the heartbeat message to them all.
    for(map<string, oscClient>::iterator i = clients.begin(); i != clients.end(); i++) {
        // iterator->first = key
        // iterator->second = value
        ofxOscSender & _sender = i->second.sender;
        _sender.sendMessage(m);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    int time = ofGetElapsedTimeMillis();
    
    if (time - lastPulseTime > PULSE_INTERVAL) {
        lastPulseTime = time;
        sendHeartbeat();
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
