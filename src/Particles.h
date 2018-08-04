//
//  Particles.h
//  UES
//
//  Created by Jacobo Heredia on 7/2/18.
//
//

#ifndef __UES__Particles__
#define __UES__Particles__

#include "ofMain.h"
typedef std::shared_ptr<class Particle> ParticleRef;

class Particle{
    public:
    Particle();
    Particle(float m, float x, float y, float z);
    void update(float dt);
    void draw();
    void applyForce(glm::vec3 force);
    void checkborders( float x,float y);
    
    glm::vec3 pos;
    glm::vec3 vel;
    glm::vec3 acc;
    
 
    float mMass;
    glm::vec3 ori;
    glm::vec3 angularVel;
    glm::vec3 angularAcc;
    
    
};
#endif /* defined(__UES__Particles__) */
