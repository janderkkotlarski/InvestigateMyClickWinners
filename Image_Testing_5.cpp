#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

const std::wstring number_to_wstring(double number)
{
	
	std::wstringstream wstringer;
	wstringer << L" " << number;
	return wstringer.str();
	
}

sf::Texture texture_from_image(std::string image_name)
{
	
	assert(image_name != "");
	
	sf::Texture image_tex;
	
	if (!image_tex.loadFromFile(image_name))
	{
			
		std::cout << image_name << " not found!\n";
		
		std::cout << "Error -2\n";
		
		exit (EXIT_FAILURE);
			
	}
	
	return image_tex;
	
}

sf::Sprite make_sprite(const sf::Color& image_color)
{
		
	sf::Sprite image_sprite;
			
	image_sprite.setColor(image_color);
	
	return image_sprite;
	
}

std::vector <sf::Sprite> vectorized_sprites(const int vector_number,
											const std::string& vector_name,
											const sf::Color& vector_color,
											const sf::Vector2f& vector_pos,
											const sf::Vector2f& vector_shift,
											const std::vector <double>& vector_value)
{
	
	assert(vector_number > 0);
	
	sf::Texture vector_tex{texture_from_image(vector_name)};
		
	sf::Sprite vectorized_sprite{make_sprite(vector_color)};
	
	vectorized_sprite.setTexture(vector_tex);
	
	sf::FloatRect vectorized_rect{vectorized_sprite.getLocalBounds()};
	
	const sf::Vector2f width_height(0.5*vectorized_rect.width, 0.5*vectorized_rect.height);	
	
	std::vector <sf::Sprite> vector_sprites;
	
	for (int count{0}; count != vector_number; ++count)
	{
		
		const float counted{static_cast<float>(count)};
		
		const sf::Vector2f vector_posit{vector_pos + counted*vector_shift};
		
		const double vector_scale{sqrt(abs(vector_value[count])/100.0)};
		
		const sf::Vector2f vector_2_scale(vector_scale, vector_scale);
		
		vector_sprites.push_back(vectorized_sprite);
		
		vector_sprites[count].setTexture(vector_tex);
		vector_sprites[count].setColor(vector_color);
		vector_sprites[count].setOrigin(width_height);
		vector_sprites[count].setPosition(vector_posit);
		vector_sprites[count].setScale(vector_2_scale);
		
	}
	
	return vector_sprites;
	
}

struct dosh_flow
{
	
	
	
	
};

double theta_determine(const sf::Vector2f& delta_pos)
{
	
	const double PI{M_PI};
	
	assert(PI == M_PI);
	
	double theta{0};
	
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

	return theta;
	
}


void move_set(const double speed, const double theta,
				sf::Vector2f &up, sf::Vector2f &down,
				sf::Vector2f &right, sf::Vector2f &left)
{
	
	assert(speed >= 0);

	const double PI{M_PI};
	
	const double deg_to_rad{PI/180};
	
	up.x = speed*sin(theta*deg_to_rad);
	up.y = -speed*cos(theta*deg_to_rad);
	
	down.x = -up.x;
	down.y = -up.y;
	
	right.x = -up.y;
	right.y = up.x;
	
	left.x = up.y;
	left.y = -up.x;
	
}


void will_it_move(sf::Sprite& image_sprite, sf::Text& text, const sf::Vector2f& end_pos, const sf::Vector2f& delta_pos)
{
	const double milli_var{0.001};
	
	assert(milli_var > 0);
	assert(milli_var < 1);
	
	const double micro_var{0.00001};
	
	assert(micro_var > 0);
	assert(micro_var < 1);
	assert(micro_var < milli_var);

	const sf::Vector2f image_pos{image_sprite.getPosition()};

	if (!((image_pos.x > end_pos.x - micro_var*abs(end_pos.x) - milli_var*abs(delta_pos.x)) &&
		(image_pos.x < end_pos.x + micro_var*abs(end_pos.x) + milli_var*abs(delta_pos.x)) &&
		(image_pos.y > end_pos.y - micro_var*abs(end_pos.y) - milli_var*abs(delta_pos.y)) &&
		(image_pos.y < end_pos.y + micro_var*abs(end_pos.y) + milli_var*abs(delta_pos.y))))
		
	{
		
		image_sprite.move(delta_pos);
		text.move(delta_pos);
		
	}
	
}

int main()
{
	
	std::wstring euro_string{L"€"};
	assert(euro_string == L"€");
		
	const double delta_var{0.001};
	assert(delta_var > 0);
	
	const int delaz{50};
	assert(delaz > 0);
	
	const std::chrono::milliseconds delay(delaz);
	
	const double window_x{640};
	assert(window_x > 0);
	
	const double window_y{640};
	assert(window_y > 0);
	
	const sf::Color white{sf::Color(255, 255, 255)};
	
	const sf::Color black{sf::Color(0, 0, 0)};
	
	const sf::Color orange{sf::Color(255, 127, 0)};
	
	const sf::Color purple{sf::Color(127, 0, 255)};
	
	const sf::Color cyan{sf::Color(127, 255, 255)};
	
	const std::string program_name{"Image Testing 5"};
	assert(program_name != "");
	
	const std::string circle_name{"Cirkel.png"};	
	assert(circle_name != "");
	
	const std::string font_name{"Ipanema_Secco.ttf"};
	assert(font_name != "");
	
	sf::Font font;
	if (!font.loadFromFile(font_name ))
	{
		
		std::cout << font_name << " not found!\n";
		
		return -1;
		
	}
	
	sf::Text text;
	
	text.setFont(font);
	
	std::vector <sf::Text> tech;
	
	const double normal_value{100};
	assert(normal_value == 100);
	
	const double triangle_value{-50};
	
	const std::wstring number_string{number_to_wstring(triangle_value)};
	
	assert(number_string != L"");

	text.setString(euro_string + number_string);

	text.setCharacterSize(40);

	text.setColor(cyan);
	
	const sf::FloatRect text_rectangle{text.getLocalBounds()};
	
	const sf::Vector2f width_height(0.5*text_rectangle.width, 0.5*text_rectangle.height);	
	
	text.setOrigin(width_height);
	text.setPosition(window_x/2.0, window_y/2.0);
	
	const std::string triangle_name{"Driehoek.png"};
	
	assert(triangle_name != "");
	
	sf::Texture triangle_tex{texture_from_image(triangle_name)};
	
			
	sf::Sprite triangle_sprite;
	
	triangle_sprite.setTexture(triangle_tex);	
	triangle_sprite.setColor(orange);
	
	triangle_sprite.setOrigin(triangle_tex.getSize().x/2.0, triangle_tex.getSize().y/2.0);	
	triangle_sprite.setPosition(window_x/2.0, window_y/2.0);
	
	const double triangle_scale{sqrt(abs(triangle_value)/normal_value)};	
	
	triangle_sprite.setScale(triangle_scale, triangle_scale);
	
	
	
	const sf::Color circle_color{purple};
	
	sf::Texture cirkel_tex{texture_from_image(circle_name)};
	

	const sf::Vector2f begin_pos{sf::Vector2f(0.25*window_x, 0.25*window_y)};
	
	const sf::Vector2f circle_spacing{sf::Vector2f(0.15*window_x, 0.15*window_y)};
	
	const sf::Vector2f end_pos{begin_pos + circle_spacing};
	
	std::vector <double> circle_value{70, 140};
	
	const int circle_amount = 2;
			
	
	std::vector <sf::Sprite> circle_sprites{vectorized_sprites(circle_amount, circle_name, circle_color,
											begin_pos, circle_spacing, circle_value)};
											
	for (int count{0}; count < circle_amount; ++count)
	{
		
		circle_sprites[count].setTexture(cirkel_tex);
		
	}
		
	
	sf::Vector2f triangle_pos;
		
	
	triangle_sprite.setPosition(begin_pos);	
	text.setPosition(begin_pos);
	
	const int steps{100};
	assert(steps > 0);
	
	const float stepped{static_cast<int>(steps)};
	
	const sf::Vector2f delta_pos(circle_spacing/stepped);
	
	double speed{5};		
	assert(speed > 0);
	
	const double delta_speed{0.5};	
	assert(delta_speed > 0);
	
	const double theta{theta_determine(delta_pos)};	

	std::cout << theta << "\n";

	triangle_sprite.setRotation(theta);	
	
	const double delta_theta{5};	
	assert(delta_theta > 0);

	sf::Vector2f up;	
	sf::Vector2f down;	
	sf::Vector2f right;	
	sf::Vector2f left;
	
	move_set(speed, theta, up, down, right, left);
	
	sf::RenderWindow window(sf::VideoMode(window_x, window_y), program_name, sf::Style::Default);
	
	while (window.isOpen())
	{
		
		// std::cout << "Asuka\n";
		
		sf::Event event;
		
		window.clear(black);
		
		for (int count{0}; count != circle_amount; ++count)
		{
			
			window.draw(circle_sprites[count]);
			
		}
		
		// std::cout << "Chiaki\n";
		
		window.draw(triangle_sprite);		
		window.draw(text);
		
		window.display();		
		
		std::this_thread::sleep_for(delay);
		
		will_it_move(triangle_sprite, text, end_pos, delta_pos);
					
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
