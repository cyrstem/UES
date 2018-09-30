//
//  Particles.cpp
//  UES
//
//  Created by Jacobo Heredia on 7/2/18.
//
//

#include "Particles.h"
Particle::Particle()
{
    mMass =1.0f;
    pos = glm::vec3(0,0,0);
    vel=  glm::vec3(0,0,0);
    acc = glm::vec3(0,0,0);

}

 Particle::Particle(float m, float x, float y, float z,ofColor _color)
{
    mMass = m;
    pos.x = ofRandom(-100,100);
    pos.y = ofRandom(-100,100);
    pos.z = ofRandom(-200,200);
    vel.x = ofRandom(-0.3,0.3);
    vel.y = ofRandom(-1, 1);

    color =_color;

}

void Particle::update(float dt)
{
   
    pos = pos + vel;
    history.push_back(pos);
    if (history.size() > 20) {
        history.erase(history.begin()+5);
    }

    

}

void Particle::draw()
{

     ofDrawBox(0, 0, 100, 700, 700, 700);
    ofPushStyle();
    
    for (int i=0; i < history.size(); i=i+10) {
        //ofPushMatrix();
        ofPushStyle();
        ofSetLineWidth(0.1);
        ofSetColor(255,255,255);

        ofRotateRad(360, pos.x, pos.y, pos.z);
        ofDrawCircle(pos.x, pos.y,pos.z,5+i);
        ofPopStyle();
        //ofPopMatrix();
    }
    ofSetColor(color);
    ofFill();
    ofDrawSphere(pos, 9);
    ofPopStyle();

    
}
void Particle::applyForce( glm::vec3 force){
    glm::vec3 f = force;
    acc +=f;


}

void Particle::timetoDie(){

}