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

 Particle::Particle(float m, float x, float y, float z)
{
    mMass = m;
//    pos =glm::vec3(x+30,y,z);
//    acc += 0;
    pos.x = ofRandom(-100,100);
    pos.y = ofRandom(-100,100);
    pos.z = ofRandom(-200,200);
    vel.x = ofRandom(-0.3,0.3);
    vel.y = ofRandom(-1, 1);
    
    //pos+=acc;
}

void Particle::update(float dt)
{
   
//    pos += 0.3 ;
    //acc *= 0;
     //vel +=acc+dt;
    pos = pos + vel;
}

void Particle::draw()
{

    ofDrawRectangle(0, 0, 700, 700);
    ofPushStyle();
    ofSetColor(255);
    ofFill();
    ofDrawSphere(pos, 10);
    ofPopStyle();

    
}

void Particle::applyForce( glm::vec3 force){
    glm::vec3 f = force;
    acc +=f;
}

void Particle::checkborders(float x,float y){
    
    float borderX = x;
    float borderY = y;
    
    if (pos.x >x) {
        vel.x*=-1;
        pos.x= 0;
        
    }else if (pos.x <0){
        vel.x *=-1;
        pos.x =0;
    }
    
    if (pos.y >y) {
        vel.y*=-1;
        pos.y= 0;
        
    }else if (pos.y <0){
        vel.y *=-1;
        pos.y =0;
    }
    
    if (pos.z >20) {
        vel.z*=-1;
        pos.z= 20;
        
    }else if (pos.z <0){
        vel.z *=-1;
        pos.z =-1;
    }


}