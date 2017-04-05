#pragma once

#include "ofMain.h"

class Particle
{
public:
	Particle();
	~Particle();
	
	void applyForce(ofVec2f force);
	void seek(ofVec2f target);

	void update();
	void draw();

private:
	ofVec2f location;
	ofVec2f velocity;
	ofVec2f acceleration;
	ofVec2f future;
	ofVec2f target;
	float max_speed;
	float max_force;
	float radius;
	float angle;
	
	ofColor body_color;
	float body_size;
};