#pragma once

#include "ofMain.h"
#include "Particles.h"
#include "ofxGui.h"
#include "ofxSimpleScreenRecorder.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
        void guiSetups();
		void update();
		void draw();
        void spectrumView();
		void keyPressed(int key);
        void exit();
		void dragEvent(ofDragInfo dragInfo);
    
    ofShader shader;
    ofFbo fbo;
    ofEasyCam cam;
    //audio  staff  new try
    vector<ofSoundPlayer> songs;
    string songName;
    bool showData;
    bool recordData;
    ofLight light;


    float affect;
    ofPolyline circle;
    
    //Gui staff ------------------------------
    ofxPanel ui;
    ofxPanel audctr;
    ofxPanel prtctr;
    ofxPanel colores;
    
    ofParameter<float>lineaSize;
    ofParameter<float>radius;
    ofParameter<int>resolution;
    ofParameter<float>fadeAmnt;
    ofParameter<float>camRotate;
    
    ofxToggle fullScreen;
    ofxToggle shaderOn;
    ofxLabel t;
    ofxButton reset;
    
    ofxToggle record;
    ofTrueTypeFont basic;
    
    
    
  
    ofParameter<ofColor>c;
    
    ofParameter<int>numPtrs;
    //saving to video
    ofxSimpleScreenRecorder mRender;

    
    
    
    
    
    //call Particles  master call
    //Particle p;
    vector<ParticleRef>mParticle;

    
    
    
};
