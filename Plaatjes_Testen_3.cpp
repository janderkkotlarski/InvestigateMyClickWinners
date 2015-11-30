#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

void beweegset(const double speed, const double theta,
				sf::Vector2f &omhoog, sf::Vector2f &omlaag,
				sf::Vector2f &rechts, sf::Vector2f &links)
{
	
	const double PI = 4*atan(1);
	
	const double deg_to_rad = PI/180;
	
	omhoog.x = speed*sin(theta*deg_to_rad);
	omhoog.y = -speed*cos(theta*deg_to_rad);
	
	omlaag.x = -omhoog.x;
	omlaag.y = -omhoog.y;
	
	rechts.x = -omhoog.y;
	rechts.y = omhoog.x;
	
	links.x = omhoog.y;
	links.y = -omhoog.x;
	
}


//    void beweegt_ie(


int main()
{
	
	std::wstring euro = L"€";
	
	assert(euro == L"€");
		
	const double PI = 4*atan(1);
	
	const double delta_var = 0.001;
	
	const double micro_var = 0.000001;
	
	assert(delta_var > 0);
	
	const int delaz = 50;
	
	assert(delaz > 0);
	
	const std::chrono::milliseconds delay(delaz);
	
	const double window_x = 640;
	
	const double window_y = 640;
	
	assert(window_x > 0);
	
	assert(window_y > 0);
	
	
	
	const std::string programma_naam = "Plaatjes_Testen_3";
	assert(programma_naam != "");
	
	
	const std::string font_naam = "Ipanema_Secco.ttf";
	assert(font_naam != "");
	
	sf::Font font;
	if (!font.loadFromFile(font_naam ))
	{
		
		std::cout << font_naam << " not found!\n";
		
		return -1;
		
	}
	
	sf::Text text;
	
	text.setFont(font);
	
	const std::wstring getal = L" 100,-";
	
	assert(getal != L"");

	text.setString(euro + getal);

	text.setCharacterSize(40);

	text.setColor(sf::Color(127, 255, 255));
	
	const sf::FloatRect text_rechthoek = text.getLocalBounds();
	
	const double text_breedte = text_rechthoek.width;	
	const double text_hoogte = text_rechthoek.height;
	
	text.setOrigin(text_breedte/2.0, text_hoogte/1.1);
	text.setPosition(window_x/2.0, window_y/2.0);
	
	const std::string plaatje_naam = "Driehoek.png";
	
	assert(plaatje_naam != "");
	
	sf::Texture plaatje_tex;
	
	if (!plaatje_tex.loadFromFile(plaatje_naam))
	{
			
		std::cout << plaatje_naam << " not found!\n";
		
		return - 2;
			
	}
	
	const double plaatje_breedte = plaatje_tex.getSize().x;	
	const double plaatje_hoogte = plaatje_tex.getSize().y;
	
	sf::Sprite plaatje_sprite;
	
	plaatje_sprite.setTexture(plaatje_tex);	
	plaatje_sprite.setColor(sf::Color(255, 127, 0));

	assert(plaatje_breedte > 0);	
	assert(plaatje_hoogte > 0);
	
	plaatje_sprite.setOrigin(plaatje_breedte/2.0, plaatje_hoogte/2.0);	
	plaatje_sprite.setPosition(window_x/2.0, window_y/2.0);
	
	sf::Vector2f plaatje_pos;
	
	const sf::Vector2f rel_pos_1(0.25*window_x, 0.75*window_y);
	
	const sf::Vector2f rel_pos_2(0.5*window_x, 0.75*window_y);
	
	plaatje_sprite.setPosition(rel_pos_1);	
	text.setPosition(rel_pos_1);
	
	const int steps = 100;
	
	const sf::Vector2f delta_pos(rel_pos_2.x/steps - rel_pos_1.x/steps, rel_pos_2.y/steps - rel_pos_1.y/steps);
	
	assert(steps > 0);
	
	double speed = 5;
		
	assert(speed > 0);
	
	const double delta_speed = 0.5;
	
	assert(delta_speed > 0);
	
	double theta = 0;
	
	assert(theta == 0);
	
	if (delta_pos.y != 0)
	{
		
		theta = -atan(delta_pos.x/delta_pos.y)*180/PI;
		
		if (delta_pos.y > 0)
		{
			
			theta += 180;
			
			if (theta > 180)
			{
				
				theta -= 360;
				
			}
			
		}
		
	}
	else
	{
		
		theta = 90;
		
		if (delta_pos.x < 0)
		{
					
			theta = -90;
			
		}
		
	}
	
	std::cout << theta << "\n";
	
	// theta = -180;
		
	plaatje_sprite.setRotation(theta);
	
	
	
	const double delta_theta = 5;
	
	assert(delta_theta > 0);

	sf::Vector2f omhoog;
	
	sf::Vector2f omlaag;
	
	sf::Vector2f rechts;
	
	sf::Vector2f links;
	
	beweegset(speed, theta, omhoog, omlaag, rechts, links);
	
	sf::RenderWindow window(sf::VideoMode(window_x, window_y), programma_naam, sf::Style::Default);
	
	while (window.isOpen())
	{
		
		sf::Event event;
		
		window.clear(sf::Color(0, 0, 0));
		
		window.draw(plaatje_sprite);
		
		window.draw(text);
		
		window.display();
		
		std::this_thread::sleep_for(delay);
		
		
		
		plaatje_pos = plaatje_sprite.getPosition();
		
		if (!((plaatje_pos.x > rel_pos_2.x - micro_var*abs(rel_pos_2.x) - delta_var*abs(delta_pos.x)) &&
			(plaatje_pos.x < rel_pos_2.x + micro_var*abs(rel_pos_2.x) + delta_var*abs(delta_pos.x)) &&
			(plaatje_pos.y > rel_pos_2.y - micro_var*abs(rel_pos_2.y) - delta_var*abs(delta_pos.y)) &&
			(plaatje_pos.y < rel_pos_2.y + micro_var*abs(rel_pos_2.y) + delta_var*abs(delta_pos.y))))
			
		{
			
			plaatje_sprite.move(delta_pos);
			text.move(delta_pos);
			
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			
			window.close();
					
			return 1;
					
		}
		
		
		
		while (window.pollEvent(event))
		{
			
			if (event.type == sf::Event::Closed)
            {
				
				window.close();
				
				return 2;
				
			}
		
		}
		
	}
	
	return 0;
	
}
