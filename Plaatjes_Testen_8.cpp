#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

const std::wstring getal_naar_wstring(double getal)
{
	
	std::wstringstream stringer;
	stringer << L" " << getal;
	return stringer.str();
	
}

sf::Texture texture_from_image(std::string image_name)
{
	
	sf::Texture image_tex;
	
	if (!image_tex.loadFromFile(image_name))
	{
			
		std::cout << image_name << " not found!\n";
		
		std::cout << "Error -2\n";
		
		exit (EXIT_FAILURE);
			
	}
	
	return image_tex;
	
}

sf::Sprite make_sprite(const std::string& image_name)
{
	
	assert(image_name != "");
	
	sf::Texture image_tex = texture_from_image(image_name);
	
			
	sf::Sprite image_sprite;
	
	image_sprite.setTexture(image_tex);	
	image_sprite.setColor(sf::Color(255, 255, 255));
	
	return image_sprite;
	
}

std::vector <sf::Sprite> vectorized_sprites(const int vector_number,
											const std::string vector_name,
											const sf::Vector2f& vector_pos,
											const sf::Vector2f& vector_shift,
											const std::vector <double>& vector_worth)
{
	
	std::vector <sf::Sprite> vector_sprites;
	
	sf::Sprite vectorized_sprite{make_sprite(vector_name)};
	
	sf::FloatRect vectorized_rect = vectorized_sprite.getLocalBounds();
	
	const double vector_width = vectorized_rect.width;	
	const double vector_height = vectorized_rect.height;
	
	for (int count = 0; count != vector_number; ++count)
	{
		
		const float counted = count;
		
		vector_sprites.push_back(vectorized_sprite);
				
		vector_sprites[count].setColor(sf::Color(127, 0, 255));
		vector_sprites[count].setOrigin(vector_width/2.0, vector_height/2.0);
		vector_sprites[count].setPosition(vector_pos + counted*vector_shift);
		vector_sprites[count].setScale(vector_worth[count], vector_worth[count]);
		
	}
	
	return vector_sprites;
	
}

struct dosh_flow
{
	
	
	
	
};

double theta_bepaling(const sf::Vector2f& delta_pos)
{
	
	const double PI = 4*atan(1);
	
	double theta = 0;
	
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

	return theta;
	
}


void beweegset(const double speed, const double theta,
				sf::Vector2f &omhoog, sf::Vector2f &omlaag,
				sf::Vector2f &rechts, sf::Vector2f &links)
{
	
	//const double PI = 4*atan(1);
	const double PI = M_PI;
	
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


void will_it_move(sf::Sprite& plaatje_sprite, sf::Text& text, const sf::Vector2f& end_pos, const sf::Vector2f& delta_pos)
{
	const double milli_var = 0.001;
	
	const double micro_var = 0.00001;

	const sf::Vector2f plaatje_pos = plaatje_sprite.getPosition();

	if (!((plaatje_pos.x > end_pos.x - micro_var*abs(end_pos.x) - milli_var*abs(delta_pos.x)) &&
		(plaatje_pos.x < end_pos.x + micro_var*abs(end_pos.x) + milli_var*abs(delta_pos.x)) &&
		(plaatje_pos.y > end_pos.y - micro_var*abs(end_pos.y) - milli_var*abs(delta_pos.y)) &&
		(plaatje_pos.y < end_pos.y + micro_var*abs(end_pos.y) + milli_var*abs(delta_pos.y))))
		
	{
		
		plaatje_sprite.move(delta_pos);
		text.move(delta_pos);
		
	}
	
}

int main()
{
	
	std::wstring euro_string = L"€";
	
	assert(euro_string == L"€");
		
	const double delta_var = 0.001;

	assert(delta_var > 0);
	
	const int delaz = 50;
	
	assert(delaz > 0);
	
	const std::chrono::milliseconds delay(delaz);
	
	const double window_x = 640;
	
	const double window_y = 640;
	
	assert(window_x > 0);
	
	assert(window_y > 0);
	
	
	
	const std::string programma_naam = "Plaatjes_Testen_8";
	assert(programma_naam != "");
	
	const std::string circle_name = "cirkel.png";
	
	assert(circle_name != "");
	
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
	
	std::vector <sf::Text> tech;
	
	const double normaal_waarde = 100;
	
	const double driehoek_waarde = 50;
	
	const std::wstring getal_string = getal_naar_wstring(driehoek_waarde);
	
	assert(getal_string != L"");

	text.setString(euro_string + getal_string);

	text.setCharacterSize(40);

	text.setColor(sf::Color(127, 255, 255));
	
	const sf::FloatRect text_rechthoek = text.getLocalBounds();
	
	const double text_breedte = text_rechthoek.width;	
	const double text_hoogte = text_rechthoek.height;
	
	text.setOrigin(text_breedte/2.0, text_hoogte/1.1);
	text.setPosition(window_x/2.0, window_y/2.0);
	
	const std::string driehoek_naam = "Driehoek.png";
	
	assert(driehoek_naam != "");
	
	sf::Texture driehoek_tex = texture_from_image(driehoek_naam);
	
			
	sf::Sprite driehoek_sprite;
	
	driehoek_sprite.setTexture(driehoek_tex);	
	driehoek_sprite.setColor(sf::Color(255, 127, 0));
	
	driehoek_sprite.setOrigin(driehoek_tex.getSize().x/2.0, driehoek_tex.getSize().y/2.0);	
	driehoek_sprite.setPosition(window_x/2.0, window_y/2.0);
	
	const double driehoek_schaal = sqrt(driehoek_waarde/normaal_waarde);
	
	
	driehoek_sprite.setScale(driehoek_schaal, driehoek_schaal);
	
	
	
	
	
	sf::Texture cirkel_tex = texture_from_image(circle_name);
	

	const sf::Vector2f begin_pos{sf::Vector2f(0.25*window_x, 0.25*window_y)};
	
	const sf::Vector2f circle_spacing{sf::Vector2f(0.15*window_x, 0.15*window_y)};
	
	const sf::Vector2f end_pos{begin_pos + circle_spacing};
	
	std::vector <double> cirkel_waarde;
	
	cirkel_waarde.push_back(sqrt(70.0/normaal_waarde));
	cirkel_waarde.push_back(sqrt(140.0/normaal_waarde));
	
	const int cirkel_getal = 2;
			
	
	std::vector <sf::Sprite> circle_sprite{vectorized_sprites(cirkel_getal, circle_name,
															begin_pos, circle_spacing,
															cirkel_waarde)};
		
	
	sf::Vector2f driehoek_pos;
		
	
	driehoek_sprite.setPosition(begin_pos);	
	text.setPosition(begin_pos);
	
	const int steps = 100;
	
	const float stepped{static_cast<int>(steps)};
	
	const sf::Vector2f delta_pos(circle_spacing/stepped);
	
	assert(steps > 0);
	
	double speed = 5;
		
	assert(speed > 0);
	
	const double delta_speed = 0.5;
	
	assert(delta_speed > 0);
	
	const double theta = theta_bepaling(delta_pos);
	

	std::cout << theta << "\n";

	driehoek_sprite.setRotation(theta);
	
	
	
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
		
		for (int teller = 0; teller != cirkel_getal; ++teller)
		{
			
			window.draw(circle_sprite[teller]);
			
		}
		
		window.draw(driehoek_sprite);
		
		window.draw(text);
		
		window.display();
		
		std::this_thread::sleep_for(delay);
		
		will_it_move(driehoek_sprite, text, end_pos, delta_pos);
			
		
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
