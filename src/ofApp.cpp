#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(5);
    ofSetWindowShape(1200, 800);
    ofSetWindowTitle("UES -v0.1");
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    basic.load("Hack-Regular.ttf", 12,true);
    
    
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
    
    
    
#ifdef TARGET_OPENGLES
    shader.load("shaders_gles/noise.vert","shaders_gles/noise.frag");
#else
    if(ofIsGLProgrammableRenderer()){
        shader.load("shaders_gl3/noise.vert", "shaders_gl3/noise.frag");
    }else{
        shader.load("shaders/noise.vert", "shaders/noise.frag");
    }
#endif
    

    
}
void ofApp::guiSetups(){
    
    //GUI CONTROLS PRINCIPALES
    showData = false;
    ui.loadFromFile("settings.xml");
    ui.setup("View Ctrls");
    ui.setPosition(800,0);
    ui.add(fullScreen.setup("FullScreen on/off",false));
    ui.add(camRotate.set("Cam rotate Y",0,10,360));
    ui.add(reset.setup("Reset"));
    ui.add(record.setup("Capture Screen ",false));
    
    //audio Visualisation  Controlsss
    audctr.setup("Wave Ctrls");
    audctr.loadFromFile("audioWSettings.xml");
    audctr.setPosition(800,200);
    audctr.add(lineaSize.set("Tmno Linea",1.3,0.1,10.5));
    audctr.add(radius.set("Radio",100,10,300));
    audctr.add(resolution.set("C- Resolution",100,3,150));
    audctr.add(fadeAmnt.set("Fade V",15,5,45));
    audctr.add(shaderOn.setup("Shader Effect",false));
    //color  for audio  Wave controls
    //GUI CONTROLES COLOREs
    colores.loadFromFile("colorsSettings.xml");
    colores.setup("Colores");
    colores.setPosition(800,500);
    c.set("RGB -A?",ofColor(255),ofColor(255,1),ofColor(255));
    colores.add(c);
    
    //gui Particles
    prtctr.setup("Particle Ctrls");
    prtctr.setPosition(800, 400);
    prtctr.add(numPtrs.set("size",10,5,100));
    
    //saving to video setup
    
    mRender.setup(ofGetWidth(),ofGetHeight());
    
//    int numParticle =5;
//    for(int i = 0; i<numParticle; i++){
//        auto m = ParticleRef(new Particle(5,0,0,0));
//        mParticle.push_back(m);
//    }


}

//--------------------------------------------------------------
void ofApp::update(){
    light.setPosition(ofGetWindowWidth()/2, ofGetWindowHeight()/2, 300);
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
    
    
    
    glm::vec3 g = glm::vec3(0,0.8,0);
    for(auto particle:mParticle){
        particle->update(affect);
        particle->applyForce(g);
       
        
    }
      cout<<"this is "<<mParticle.size()<<endl;
    
}

//--------------------------------------------------------------
void ofApp::spectrumView(){
    ofEnableAlphaBlending();
    ofEnableAntiAliasing();
    //ofEnableDepthTest();
    ofEnableLighting();
    light.enable();
    //light.
    //fadeAmnt =15;
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
    
    
    ofEndShape(true);

    for (auto particle:mParticle) {
        if (shaderOn ==true) {
              shader.begin();
            //we want to pass in some varrying values to animate our type / color
            shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1 );
            shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18 );
            
            //we also pass in the mouse position
            //we have to transform the coords to what the shader is expecting which is 0,0 in the center and y axis flipped.
            shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );
            particle->draw();
            shader.end();

        }else {
            particle->draw();
          

        }
      
        
    }
    
    
    light.disable();
    cam.end();
    ofDisableLighting();
   // ofDisableDepthTest();
}
//--------------------------------------------------------------
void ofApp::draw(){
    mRender.begin();
    fbo.draw(30,20);
    if(showData ==false){
        basic.drawString("Drop the song here!!", 10, 780);
    } else{
        basic.drawString("Playing ..."+songName, 10, 780);
    }
    
    //guide  drop song  draw
    ofPushStyle();
    ofSetColor(ofColor::white,255);
    ofNoFill();
    ofSetLineWidth(1);
    ofDrawRectangle(5, 740,basic.stringWidth(songName)+210, 50);
    ofPopStyle();
    //GuiS DRAwn
    ui.draw();
    colores.draw();
    audctr.draw();
    prtctr.draw();
    //end guis
    //recoreded end//
    mRender.end();
    
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
            songName = ofToString(dragInfo.files[k]);
            songs[k].load(dragInfo.files[k]);
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
    colores.saveToFile("colorsSettings.xml");
}

