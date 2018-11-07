#pragma once

#include "ofMain.h"
#include "Particles.h"
#include "Squares.hpp"
#include "ofxFft.h"
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
    
    
    //light new way
    
    ofLight light, spotlight;
    float time;

    float affect;
    ofPolyline circle;
    
    //Gui staff ------------------------------
    ofxPanel ui;
    ofxPanel audctr;
    ofxPanel prtctr;
    ofxPanel luzctr;


    ofParameter<float>lineaSize;
    ofParameter<float>radius;
    ofParameter<int>resolution;
    ofParameter<float>fadeAmnt;
    ofParameter<float>camRotate;
    ofParameter<float>luzX;
    ofParameter<float>luzY;
    ofParameter<float>luzZ;
    ofParameter<float>luzPX;
    ofParameter<float>luzPY;
    ofParameter<float>luzPZ;
    //ofParameter<int>lightOrbit;
    
    
    ofxToggle fullScreen;
    ofxToggle shaderOn;
    ofxToggle fillWave;
    ofxLabel t;
    ofxLabel lp,ls;
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
    
    
    
//----audio analysis
    ofxFft* fft;
    ofMutex soundMutex;
    
    
    
    
    
    
};
