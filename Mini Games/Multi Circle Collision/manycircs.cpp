//Christine Garcia
//Made for PC & Console Game Development I class
//Developed in groups of 3

//Manipulate values as desired in: playerInput.txt
//Use WASD to move player circle

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <ctime>

#define FPS 60
#define circ_speed 1
#define timestep 1.0f / FPS
#define force 10000.0f * timestep
#define ELASTICITY 1

using namespace std;

int main( void ) {
	//Read from file segment
	int wheight = 0; int wwidth = 0;
	int CircNo = 0;
	float acceleration = 0.0f;
	float inputRadius = 0.0f;
	
	ifstream file_reader;
	file_reader.open("playerInput.txt");

	string line1;
	string line2;
	string line3;
	string line4;
	getline(file_reader, line1, ':'); 
	file_reader >> wheight >> wwidth;	
	getline(file_reader, line2, ':'); 
	file_reader >> CircNo;
	getline(file_reader, line3, ':');
	file_reader >> inputRadius;
	getline(file_reader, line4, ':'); 
	file_reader >> acceleration;
	
	//bools for friction
	bool movingUps[CircNo];
	bool movingDowns[CircNo];
	bool movingRights[CircNo];
	bool movingLefts[CircNo];
	bool movingStops[CircNo];
		
    sf::RenderWindow window( sf::VideoMode( wheight, wwidth ), "Multi Circles colliding" );
	window.setFramerateLimit( FPS );
    
	sf::CircleShape circ( inputRadius );
    circ.setPosition(wheight/2, wwidth/2);
    circ.setFillColor( sf::Color::Green );
    float radius = circ.getRadius();
	
	sf::CircleShape circs[CircNo];
	sf::Vector2f velocities[CircNo];
	float radii[CircNo];
	float masses[CircNo];
	for(int i = 0; i < CircNo; i++) {
		circs[i].setRadius( inputRadius );
		circs[i].setPosition(rand() % wheight - 1, rand() % wwidth-1);
		circs[i].setFillColor( sf::Color::Red );
		radii[i] = circs[i].getRadius();
		
		velocities[i].x = 0;
		velocities[i].y = 0;
		masses[i] = 10;
		
		movingUps[i] = false;
		movingDowns[i] = false;
		movingRights[i] = false;
		movingLefts[i] = false;
		movingStops[i] = false;
	}

	bool moveUp = false;
	bool moveDown = false;
	bool moveRight = false;
	bool moveLeft = false;

	bool triggerMe = false;

	bool movingUp = false;
	bool movingDown = false;
	bool movingRight = false;
	bool movingLeft = false;
	bool movingStop = false;

	sf::Vector2f velocity(0, 0); 
	float friction = 0.2f;
	float mass = 10;
	sf::Vector2f overlap (0,0);
	sf::Vector2f distance (0,0);
	float distanceDiag = 0; 

	srand(time(NULL));
	sf::Clock clock;
	int step = 5;

    while( window.isOpen() ) {
		sf::Time elapsed = clock.restart();
        sf::Event event;
        while( window.pollEvent( event ) ) {
        	float elapsed;

            switch( event.type ) {
				case sf::Event::Closed:
	                window.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code) {
						case sf::Keyboard::Escape: {
							window.close();
							break;
						}
						case sf::Keyboard::R: {
							circ.setPosition((wheight/2) -circ.getRadius(), (wwidth/2) - circ.getRadius());
							for(int i = 0; i < CircNo; i++) {
								circs[i].setPosition(rand() % wheight - 1, rand() % wwidth-1);
							}
							break;
						}
						case sf::Keyboard::W: {
							moveUp = true;
							break;
						}
						case sf::Keyboard::A: {
							moveLeft = true;
							break;
						}
						case sf::Keyboard::S: {
							moveDown = true;
							break;
						}
						case sf::Keyboard::D: {
							moveRight = true;
							break;
						}
						
						//Friction on (F) and off (G)
						case sf::Keyboard::F: {
							triggerMe = true;
							circ.setFillColor(sf::Color::Blue);
							for(int i = 0; i < CircNo; i++){
								circs[i].setFillColor(sf::Color::White);
							}
							break;
						}
						case sf::Keyboard::G: {
							triggerMe = false;
							circ.setFillColor(sf::Color::Green);
							for(int i = 0; i < CircNo; i++){
								circs[i].setFillColor(sf::Color::Red);
							}
							break;
						}	
					} 
					break;

				case sf::Event::KeyReleased:
					switch (event.key.code) {
						case sf::Keyboard::W: {
							moveUp = false;
							break;
						}
						case sf::Keyboard::A: {
							moveLeft = false;
							break;
						}
						case sf::Keyboard::S: {
							moveDown = false;
							break;
						}
						case sf::Keyboard::D: {
							moveRight = false;
							break;
						}
						default:
							break;
					}
				}
			}

		if(moveUp && moveRight) {
        	velocity.y += (-acceleration*timestep/mass)/sqrt(2);
        	velocity.x += (acceleration*timestep/mass)/sqrt(2);
		}
		if(moveUp && moveLeft) {
        	velocity.y += (-acceleration*timestep/mass)/sqrt(2);
       		velocity.x += (-acceleration*timestep/mass)/sqrt(2);			
		}
		if(moveDown && moveRight) {
        	velocity.y += (acceleration*timestep/mass)/sqrt(2);
        	velocity.x += (acceleration*timestep/mass)/sqrt(2);
		}
		if(moveDown && moveLeft) {
       		velocity.x += (-acceleration*timestep/mass)/sqrt(2);
        	velocity.y += (acceleration*timestep/mass)/sqrt(2);			
		}
        if (moveUp)
        	velocity.y += -acceleration*timestep/mass;
        if (moveLeft)
       		velocity.x += -acceleration*timestep/mass;
        if (moveDown)
        	velocity.y += acceleration*timestep/mass;
        if (moveRight)
        	velocity.x += acceleration*timestep/mass;

        //Player's Borders
        if(circ.getPosition().y < 0 ){
        	circ.setPosition(circ.getPosition().x, 0);
        	velocity.y *= -ELASTICITY;
        } 
        if(circ.getPosition().y + (2*radius) > wwidth  ){
        	circ.setPosition(circ.getPosition().x, wwidth-2*radius);
        	velocity.y *= -ELASTICITY;
        }
		if(circ.getPosition().x < 0 ){
        	circ.setPosition(0,circ.getPosition().y);
        	velocity.x *= -ELASTICITY;
        }
        if(circ.getPosition().x + (2*radius) > wheight){
        	circ.setPosition(wheight-2*radius, circ.getPosition().y);
        	velocity.x *= -ELASTICITY;
        }
		//Others' Borders
		for(int i= 0; i < CircNo; i++){
			if(circs[i].getPosition().y < 0 ){
				circs[i].setPosition(circs[i].getPosition().x, 0);
				velocities[i].y *= -ELASTICITY;
			} 
			if(circs[i].getPosition().y + (2*radius) > wwidth  ){
				circs[i].setPosition(circs[i].getPosition().x, wwidth-2*radius);
				velocities[i].y *= -ELASTICITY;
			}
			if(circs[i].getPosition().x < 0 ){
				circs[i].setPosition(0,circs[i].getPosition().y);
				velocities[i].x *= -ELASTICITY;
			}
			if(circs[i].getPosition().x + (2*radius) > wheight){
				circs[i].setPosition(wheight-2*radius, circs[i].getPosition().y);
				velocities[i].x *= -ELASTICITY;
			}
		}
		
		//Velocity Checks
		if(velocity.y < 0) {
			movingUp = true;
			movingDown = false;
			movingStop = false;
		}
		if(velocity.y > 0) {
			movingDown = true;
			movingUp = false;
			movingStop = false;
		}
		if(velocity.x > 0) {
			movingRight = true;
			movingLeft = false;
			movingStop = false;
		}
		if(velocity.x < 0) {
			movingLeft = true;
			movingRight = false;
			movingStop = false;
		}
		if(velocity.x == 0 && velocity.y ==0) {
			movingStop = true;
		}

		for(int i =0; i < CircNo; i++){
			if(velocities[i].y < 0) {
				movingUps[i] = true;
				movingDowns[i] = false;
				movingStops[i] = false;
			}
			if(velocities[i].y > 0) {
				movingDowns[i] = true;
				movingUps[i] = false;
				movingStops[i] = false;
			}
			if(velocities[i].x > 0) {
				movingRights[i] = true;
				movingLefts[i] = false;
				movingStops[i] = false;
			}
			if(velocities[i].x < 0) {
				movingLefts[i] = true;
				movingRights[i] = false;
				movingStops[i] = false;
			}
			if(velocities[i].x == 0 && velocities[i].y == 0) {
				movingStops[i] = true;
			}
		}
		
		//COLLISION

		//Player vs. Other Circles
		for(int i =0; i < CircNo; i++){
			distance.x = circ.getPosition().x - circs[i].getPosition().x;
			distance.y = circ.getPosition().y - circs[i].getPosition().y;
			distanceDiag = sqrt((distance.x*distance.x) + (distance.y*distance.y));
			
			if(radius + radii[i] > distanceDiag){
				overlap.x = distanceDiag - (radius+radii[i]);
				overlap.y = distanceDiag - (radius+radii[i]);
				
				float nx = (circs[i].getPosition().x - circ.getPosition().x)/ distanceDiag;
				float ny = (circs[i].getPosition().y - circ.getPosition().y)/ distanceDiag;
				
				float tx = -ny;
				float ty = nx;
				
				float dpTan1 = velocity.x * tx + velocity.y *ty;
				float dpTan2 = velocities[i].x * tx + velocities[i].y *ty;
				
				float dpNorm1 = velocity.x * nx + velocity.y * ny;
				float dpNorm2 = velocities[i].x * nx + velocities[i].y *ty;
				
				float m1 = (dpNorm1 * (mass - masses[i]) +  masses[i] *dpNorm2)/(mass + masses[i]);
				float m2 = (dpNorm2 * (masses[i]- mass) +  mass *dpNorm1)/(mass + masses[i]);
				
				if(circ.getPosition().x < circs[i].getPosition().x){
					circ.move(overlap.x/2,0);
					circs[i].move(-overlap.x/2,0);

					velocity.x = (tx * dpTan1 + nx * m1);
					velocity.y = (ty * dpTan1 + ny * m1);
					velocities[i].x = (tx * dpTan2 + nx * m2); 
					velocities[i].y = (ty * dpTan2 + ny * m2);
				}
				if(circ.getPosition().x > circs[i].getPosition().x){
					circ.move(-overlap.x/2,0);
					circs[i].move(overlap.x/2,0);
					
					velocity.x = (tx * dpTan1 + nx * m1);
					velocity.y = (ty * dpTan1 + ny * m1);
					velocities[i].x = (tx * dpTan2 + nx * m2); 
					velocities[i].y = (ty * dpTan2 + ny * m2);
				}
				if(circ.getPosition().y > circs[i].getPosition().y){
					circ.move(0,-overlap.x/2);
					circs[i].move(0,overlap.x/2);
					
					velocity.x = (tx * dpTan1 + nx * m1);
					velocity.y = (ty * dpTan1 + ny * m1);
					velocities[i].x = (tx * dpTan2 + nx * m2); 
					velocities[i].y = (ty * dpTan2 + ny * m2);
				}
				if(circ.getPosition().y < circs[i].getPosition().y){
					circ.move(0,overlap.x/2);
					circs[i].move(0,-overlap.x/2);
					
					velocity.x = (tx * dpTan1 + nx * m1);
					velocity.y = (ty * dpTan1 + ny * m1);
					velocities[i].x = (tx * dpTan2 + nx * m2); 
					velocities[i].y = (ty * dpTan2 + ny * m2);
				}
			}
		}
		//Other Circles vs. Each Other
		for(int i = 0; i < CircNo; i++){
			for(int j = i; j < CircNo; j++){
				distance.x = circs[i].getPosition().x - circs[j].getPosition().x;
				distance.y = circs[i].getPosition().y - circs[j].getPosition().y;
				distanceDiag = sqrt((distance.x*distance.x) + (distance.y*distance.y));
				
				if(radii[i] + radii[j] > distanceDiag){
					overlap.x = distanceDiag - (radii[i]+radii[j]);
					overlap.y = distanceDiag - (radii[i]+radii[j]);
					
					float nx = (circs[i].getPosition().x - circs[j].getPosition().x)/ distanceDiag;
					float ny = (circs[i].getPosition().y - circs[j].getPosition().y)/ distanceDiag;
					
					float tx = -ny;
					float ty = nx;
					
					float dpTan1 = velocities[i].x * tx + velocities[i].y *ty;
					float dpTan2 = velocities[j].x * tx + velocities[j].y *ty;
					
					float dpNorm1 = velocities[i].x * nx + velocities[i].y * ny;
					float dpNorm2 = velocities[j].x * nx + velocities[j].y *ty;
					
					float m1 = (dpNorm1 * (masses[i] - masses[j]) +  masses[j] *dpNorm2)/(masses[i] + masses[j]);
					float m2 = (dpNorm2 * (masses[j]- masses[i]) + masses[i] *dpNorm1)/(masses[i] + masses[j]);
					
					if(circs[i].getPosition().x < circs[j].getPosition().x){
						circs[i].move(overlap.x/2,0);
						circs[j].move(-overlap.x/2,0);
						
						velocities[i].x = (tx * dpTan1 + nx * m1);
						velocities[i].y = (ty * dpTan1 + ny * m1);
						velocities[j].x = (tx * dpTan2 + nx * m2); 
						velocities[j].y = (ty * dpTan2 + ny * m2);
					}
					if(circs[i].getPosition().x > circs[j].getPosition().x){
						circs[i].move(-overlap.x/2,0);
						circs[j].move(overlap.x/2,0);
						
						velocities[i].x = (tx * dpTan1 + nx * m1);
						velocities[i].y = (ty * dpTan1 + ny * m1);
						velocities[j].x = (tx * dpTan2 + nx * m2); 
						velocities[j].y = (ty * dpTan2 + ny * m2);
					}
					if(circs[i].getPosition().y > circs[j].getPosition().y){
						circs[i].move(0,-overlap.x/2);
						circs[j].move(0,overlap.x/2);
						
						velocities[i].x = (tx * dpTan1 + nx * m1);
						velocities[i].y = (ty * dpTan1 + ny * m1);
						velocities[j].x = (tx * dpTan2 + nx * m2); 
						velocities[j].y = (ty * dpTan2 + ny * m2);
					}
					if(circs[i].getPosition().y < circs[j].getPosition().y){
						circs[i].move(0,overlap.x/2);
						circs[j].move(0,-overlap.x/2);
						
						velocities[i].x = (tx * dpTan1 + nx * m1);
						velocities[i].y = (ty * dpTan1 + ny * m1);
						velocities[j].x = (tx * dpTan2 + nx * m2); 
						velocities[j].y = (ty * dpTan2 + ny * m2);
					}
			}

		}
	}
		//Player Friction
		if(triggerMe && !movingStop) {
			if(movingUp)
				velocity.y -= velocity.y*friction*timestep/mass;
			if(movingDown)
				velocity.y -= velocity.y*friction*timestep/mass;
			if(movingRight)
				velocity.x -= velocity.x*friction*timestep/mass;
			if(movingLeft)
				velocity.x -= velocity.x*friction*timestep/mass;
		}
		//Others' Friction		
		for(int i = 0; i< CircNo; i++){
			if(triggerMe && !movingStops[i]){
				if(movingUps[i])
					velocities[i].y -= velocities[i].y*friction*timestep/masses[i];
				if(movingDowns[i])
					velocities[i].y -= velocities[i].y*friction*timestep/masses[i];
				if(movingRights[i])
					velocities[i].x -= velocities[i].x*friction*timestep/masses[i];
				if(movingLefts[i])
					velocities[i].x -= velocities[i].x*friction*timestep/masses[i];
			}
		}
		
		circ.move(velocity);
		for(int i=0; i< CircNo; i++){
			circs[i].move(velocities[i]);
		}

        window.clear();

        window.draw(circ);
		for(int i=0; i < CircNo; i++){
			window.draw(circs[i]);
		}
        window.display();
    }
    return 0;
}