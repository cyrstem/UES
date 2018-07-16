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
    pos = glm::vec3(0,0,0);
    vel=  glm::vec3(0,0,0);
    acc = glm::vec3(0,0,0);
}

 Particle::Particle(float s, float x, float y, float z)
{
    s = 10;
    acc +=1;
    pos = glm::vec3(x,y,z);
    pos+=acc;
}

void Particle::update(float dt)
{
    vel +=0.01 ;
    pos += vel * dt;
    
}

void Particle::draw()
{
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

void Particle::checkborders(float radioAudio){
    
    float border = radioAudio;
    if (pos.x >radioAudio) {
        vel.x*=-1;
        pos.x= border;
        
    }else if (pos.x <0){
        vel.x *=-1;
        pos.x =0;
    }
    
    if (pos.y >radioAudio) {
        vel.y*=-1;
        pos.y= border;
        
    }else if (pos.y <0){
        vel.y *=-1;
        pos.y =0;
    }
    
    if (pos.z >radioAudio) {
        vel.z*=-1;
        pos.z= border;
        
    }else if (pos.z <0){
        vel.z *=-1;
        pos.z =-1;
    }


}