#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(2);
    ofSetWindowShape(1220, 800);
    ofSetWindowTitle("UES -v0.1");
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    basic.load("InputMono-Regular.ttf", 12,true);
    
    //fbo
    ofFbo::Settings s;
    s.width = 700;
    s.height = 700;
    s.useDepth =true;
    s.depthStencilAsTexture = true;
    s.internalformat = GL_RGBA32F_ARB;
    fbo.allocate(s);

    fbo.begin();
    ofClear(255, 255, 255,0);
    fbo.end();
    guiSetups();
    
    light.setParent(cam);
    //light.dolly(39);
    shader.load("shaders/noise.vert", "shaders/noise.frag");
    

    
}
void ofApp::guiSetups(){
    
    //GUI CONTROLS PRINCIPALES
    showData = false;
    ui.loadFromFile("settings.xml");
    ui.setup("View Ctrls");
    ui.setPosition(800,0);
    ui.add(fullScreen.setup("FullScreen on/off",false));
    ui.add(camRotate.set("Cam rotate Y",0,10,360));
    ui.add(reset.setup("Reset Cam"));
    ui.add(record.setup("Capture Screen ",false));
    ui.add(resetAll.setup("RESET ALL TODITO"));
    
    //Wave Controls
    audctr.loadFromFile("WaveControlsSet.xml");
    audctr.setup("Wave Ctrls");
    audctr.setPosition(800,150);
    audctr.add(lineaSize.set("Tmno Linea",1.3,0.1,10.5));
    audctr.add(radius.set("Radio",100,10,300));
    audctr.add(resolution.set("C- Resolution",100,3,150));
    audctr.add(fadeAmnt.set("Fade V",15,5,170));
    audctr.add(luzX.set("Luz X",0,-2000,2000));
    audctr.add(luzY.set("Luz Y",0,-2000,2000));
    audctr.add(luzZ.set("Luz Z",0,-2000,2000));
    audctr.add(shaderOn.setup("Shader Effect",false));
    audctr.add(fillWave.setup("Wave FIll OFF ",true));
    audctr.add(c.set("RGBA -Waves-controls",ofColor(255),ofColor(255),ofColor(255)));
    //GUI Particles
    prtctr.setup("Particle Ctrls");
    prtctr.setPosition(1010, 0);
    prtctr.add(numPtrs.set("size",10,50,100));
    
    
    //saving to video setup
    
    mRender.setup(ofGetWidth(),ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
   
    light.orbitRad(50, 50, 50);
    ofSoundUpdate();
    float *spectrum = ofSoundGetSpectrum(128);
    double level = 0;
    for (int i = 0 ; i<128; i++) {
        level+=spectrum[i] * spectrum[i];
    }
    level =sqrt(level/128);
    //this is key
    affect =ofMap(level, 0, 1, 0.3, 200);

    ofEnableAlphaBlending();
    
    fbo.begin();
    spectrumView();
    fbo.end();
    
    
    
    glm::vec3 g = glm::vec3(0.1,0.10,0);
    for(auto particle:mParticle){
        particle->update(affect);
        particle->applyForce(g);
       
        
    }
      //cout<<"this is "<<mParticle.size()<<endl;
    
}

//--------------------------------------------------------------
void ofApp::spectrumView(){
    ofEnableAlphaBlending();
    ofEnableLighting();
    light.enable();
    light.setPosition(luzX, luzY, luzZ);
    if (reset) {
        cam.reset();
    }
    
    
    ofFill();
    ofSetColor(255,255,255, fadeAmnt);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofDrawRectangle(ofGetWindowWidth()/2,ofGetWindowHeight()/2,ofGetWindowWidth(),ofGetWindowHeight());
    
    float offset = affect;
    ofSetLineWidth(lineaSize);
    ofSetColor(c);
    ofEnableSmoothing();
    
    ofNoFill();
    glm::vec3 ori;
  
    
    
    ori= glm::vec3(0,0,0);
    //if push matrix use always put camera after that  if is camera  by  mouse
    cam.begin();
    //light.enable();
    ofPushStyle();
    if (!fillWave) {
        ofFill();
    }else{
        ofNoFill();
    }
    ofBeginShape();
    
    float noiseHeight = 0.0 + affect;
    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    for (int i = 0; i < resolution; i++) {
        
        float angle = ofMap(i, 0, resolution, 0, PI * 2);
        
        float x = cos(angle) * (radius + ofNoise(i, offset) * noiseHeight);
        float y = sin(angle) * (radius + ofNoise(i, offset) * noiseHeight);
        
        ofVertex(x , y);
        circle.addVertex(x + 200, y);
    }
    

          //calidad del noise height define el numero de planetas q nace
        //cout<<noiseHeight<<endl;
    ofEndShape(true);
    ofPopStyle();
    float pmaker = ofMap(noiseHeight, 0.0, 50.0, 0.0, 10.0);
    //this hace q las particulas nascan de forma regular con la musica
     //convirtiendo el valor de noise 0.0 float to  int
    int test = int(pmaker);
    
    if(noiseHeight>50 ){
        int numParticle =pmaker;
        for(int i = 0; i<numParticle; i++){
            auto m = ParticleRef(new Particle(5,ofRandom(fbo.getWidth()),fbo.getHeight(),-400,c));
            mParticle.push_back(m);
    
            if (mParticle.size()==50) {
                m.reset();
                mParticle.erase(mParticle.begin(),mParticle.begin()+45);
                cout<<"yap Borre 45"<<endl;
               
            }
            
            ///clear TODO cn el boto reset all
            if (resetAll== true) {
                m.reset();
                mParticle.clear();
            }


            
        }
        
        
        
    }

    
    

    for (auto particle:mParticle) {
        if (shaderOn ==true) {
              shader.begin();
            //we want to pass in some varrying values to animate our type / color
            shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1 );
            shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.4 );
            
            //we also pass in the mouse position
            //we have to transform the coords to what the shader is expecting which is 0,0 in the center and y axis flipped.
            shader.setUniform2f("mouse", noiseHeight - ofGetWidth()/2, ofGetHeight()/2-affect);
            particle->draw();
            shader.end();

        }else {
            particle->draw();
          

        }
      
        
    }
    
    
    light.disable();
    cam.end();
    ofDisableLighting();
}
//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableAntiAliasing();
    //mRender.begin();
    
    fbo.draw(30,20);
    
    ofSetColor(ofColor::white);
    //ofNoFill();
    ofFill();
    ofDrawRectangle(5, 740,basic.stringWidth(songName)+210, 50);

    
    
    
    ofSetColor(ofColor::black);
    if(showData ==false){
        
//        ofSetColor(ofColor::black);
        basic.drawString("Drop the song here!!", 10, 780);
 
    } else{
        basic.drawString("Playing ..."+songName, 10, 780);
    }

    //guide  drop song  draw
    ofSetColor(255, 255, 255);
    //GuiS DRAwn
    ui.draw();
//    colores.draw();
    audctr.draw();
    prtctr.draw();
    //end guis
    //recoreded end//
    //mRender.end();
    
    //esta parte toca verificar
     //algo esta raro con el 
    
    if(record ==false){
        mRender.stop();
    } else{
        mRender.start();
        //basic.drawString("Playing ..."+songName, 10, 780);
    }
    
    if(fullScreen==true){
        ofSetFullscreen(true);
        
    }else {
        ofSetFullscreen(false);
    }
}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
    if (dragInfo.files.size() >0) {
        showData = true;
        ofLogNotice("song loaded");
        songs.assign(dragInfo.files.size(), ofSoundPlayer());
        for ( unsigned int k =0 ; k<dragInfo.files.size(); k++) {
            
            
            songs[k].load(dragInfo.files[k]);
             ofFile files (dragInfo.files[k]);
            songName = ofToString(files.getFileName());
        }
    }
 
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofImage imgpreview;
    switch (key) {
        case 'p':
            songs[0].play();
            break;

        case 's':
            songs[0].stop();
            break;
        case'c':
            fbo.begin();
            ofClear(255,255,255, 0);
            fbo.end();
            break;
        case 'i':
            imgpreview.grabScreen(30, 20, fbo.getWidth(), fbo.getHeight());
            imgpreview.save("preview/screenshot"+ofToString(ofRandom(0,1000),0)+".jpg",OF_IMAGE_QUALITY_HIGH);
            break;
        case 'o':
            int numParticle =5;
            for(int i = 0; i<numParticle; i++){
                auto m = ParticleRef(new Particle(5,ofRandom(fbo.getWidth()),fbo.getHeight(),-400,c));
                mParticle.push_back(m);
            }

            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    ui.saveToFile("settings.xml");
    audctr.saveToFile("WaveControlsSet.xml");
}

