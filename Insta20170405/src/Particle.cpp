#include "Particle.h"

Particle::Particle()
{
	this->location = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
	//this->location = ofVec2f(0, 0);
	this->velocity = ofVec2f(0, 0);
	this->acceleration = ofVec2f(0, 0);

	this->max_speed = 5;
	this->max_force = 2;
	this->radius = 30;
	this->angle = ofRandom(360);

	this->body_color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
	this->body_size = 20;
}

Particle::~Particle()
{

}

void Particle::applyForce(ofVec2f force)
{
	this->acceleration += force;
}

void Particle::seek(ofVec2f target)
{
	ofVec2f desired = this->location - target;
	float distance = desired.length();
	desired.normalize();
	if (distance < this->radius)
	{
		float m = ofMap(distance, 0, this->radius, 0, this->max_speed);
		desired *= m;
	}
	else
	{
		desired *= this->max_speed;
	}

	ofVec2f steer = this->velocity - desired;
	steer.limit(this->max_force);
	applyForce(steer);
}

void Particle::update()
{
	this->future.set(this->velocity);
	this->future.normalize();
	this->future *= 60;
	this->future += this->location;

	this->angle = ofRandom(0, 360);
	float x = 60 * cos(this->angle * DEG_TO_RAD) + future.x;
	float y = 60 * sin(this->angle * DEG_TO_RAD) + future.y;
	this->target = ofVec2f(x, y);

	this->seek(this->target);

	this->velocity += this->acceleration;
	this->velocity.limit(max_speed);
	this->location += this->velocity;
	
	this->acceleration *= 0;
	this->velocity *= 0.98;

}

void Particle::draw()
{
	ofSetColor(this->body_color);
	ofEllipse(this->location.x, this->location.y, this->body_size, this->body_size);
	ofSetLineWidth(0.1);
	ofLine(this->location, this->future);
	ofSetColor(255);
	ofEllipse(this->future.x, this->future.y, this->body_size / 2, this->body_size / 2);
	ofSetColor(0, 0, 255);
	ofEllipse(this->target.x, this->target.y, this->body_size / 2, this->body_size / 2);

}