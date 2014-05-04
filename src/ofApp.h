#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "oscClient.h"

#define HUB_IP "127.0.0.1"
#define PORT 8000
#define PULSE_INTERVAL 1000

class ofApp : public ofBaseApp {

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void sendHeartbeat();
    void registerClient(ofxOscMessage *m);
    
    ofxOscReceiver oscReceiver;
    ofxOscSender oscSender;
    
    set<string> clientIps;
    map<string, oscClient> clients;
    int lastPulseTime;
		
};
