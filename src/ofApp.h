#pragma once

#include "ofMain.h"
#include "Particles.h"
#include "Squares.hpp"
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

    
    ofParameter<float>lineaSize;
    ofParameter<float>radius;
    ofParameter<int>resolution;
    ofParameter<float>fadeAmnt;
    ofParameter<float>camRotate;
    ofParameter<float>luzX;
    ofParameter<float>luzY;
    ofParameter<float>luzZ;
    //ofParameter<glm::vec3>luzPos;
    
    
    ofxToggle fullScreen;
    ofxToggle shaderOn;
    ofxToggle fillWave;
    ofxLabel t;
    ofxButton reset;
    ofxButton resetAll;
    
    ofxToggle record;
    ofTrueTypeFont basic;
    
    
    
  
    ofParameter<ofColor>c;
    //audio
    ofParameter<int>numPtrs;
    
    
    
    //saving to video
    ofxSimpleScreenRecorder mRender;

    
    
    
    
    
    //call Particles  master call
    //Particle p;
    vector<ParticleRef>mParticle;

    
    
    
};
