#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

struct Pirate_Captain
{
	
	const std::string pirate_call{"YAAAAAAAAAAAAAAAAAAAARRRRRRRRRRRRRRRRRRRR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"};
	
	const std::string pirate_question{"IS ZER SUM RUM?!\n"};
	
	Pirate_Captain();
	
	~Pirate_Captain();
	
	void pirate_sez_wut()
	{
		
		std::cout << pirate_call;
		
	}
	
	void pirate_axe_wut()
	{
		
		std::cout << pirate_question;
		
	}
	
};

Pirate_Captain::Pirate_Captain()
{
	
}

Pirate_Captain::~Pirate_Captain()
{
	
}

double value_to_radius(const double value, const double normal_radius)
{
	
	const double normal_value{100};
	
	return sqrt(abs(value)/normal_value)*normal_radius;
	
}

struct circle_entity
{
	
	double value{0};
		
	const double normal_radius{100};
	
	double radius{value_to_radius(value, normal_radius)};
	
	sf::Vector2f posit{0, 0};
		
	sf::CircleShape circle{static_cast<float>(radius)};
	
	sf::Color color{0, 0, 0};
	
	circle_entity(const double walue, const double normal_radiuz,
				const sf::Vector2f& pozit, const sf::Color& kolor);
				
	~circle_entity();
	
};

circle_entity::circle_entity(const double walue, const double normal_radiuz,
							const sf::Vector2f& pozit, const sf::Color& kolor)
	:value(walue), normal_radius(normal_radiuz), radius(value_to_radius(value, normal_radius)),
	posit(pozit), circle(static_cast<float>(radius)), color(kolor)
{
	
	circle.setOrigin(radius, radius);
	
	circle.setPosition(posit);
	
	circle.setFillColor(color);
	
}

circle_entity::~circle_entity()
{
		
}

void reposit_circlent(circle_entity& circlent, const sf::Vector2f& posit)
{
	
	circlent.circle.setPosition(posit);
	
}

void reorigin_circlent(circle_entity& circlent)
{
	
	circlent.circle.setOrigin(circlent.radius, circlent.radius);
	
}

void reshape_circlent(circle_entity& circlent, const double value)
{
	
	circlent.circle.setRadius(value_to_radius(value, circlent.normal_radius));
	
}

void recolor_circlent(circle_entity& circlent, const sf::Color& color)
{
	
	circlent.circle.setFillColor(color);
	
}

void show_circlent(sf::RenderWindow& window, const circle_entity& circlent)
{
	
	window.draw(circlent.circle);
	
}

struct rect_entity
{
	
	sf::Vector2f posit{0, 0};	
	
	const sf::Vector2f sizes{300, 75};
	
	sf::RectangleShape rectangle{sizes};
	
	const sf::Color rect_color{0, 127, 0};
	
	const sf::Color circlent_color{0, 0, 127};
	
	std::vector <double> values;
	
	const double normal_radius{0.4*sizes.y};
	
	std::vector <circle_entity> circlents;
	
	const int circlent_amount{0};
	
	rect_entity(const sf::Vector2f& pozit, const sf::Vector2f& zisez, const int kirkle_amount,
				const sf::Color rekt_kolor, const sf::Color& kirkle_kolor, const std::vector <double>& walues);
	
	~rect_entity();
			
};

rect_entity::rect_entity(const sf::Vector2f& pozit, const sf::Vector2f& zisez, const int kirklent_amount,
						const sf::Color rekt_kolor, const sf::Color& kirklent_kolor, const std::vector <double>& walues)
	:posit(pozit), sizes(zisez), rectangle(sizes), rect_color(rekt_kolor), circlent_color(kirklent_kolor),
	 values(walues), normal_radius(0.4*sizes.y), circlents(), circlent_amount(kirklent_amount)
{
	
	assert(circlent_amount > 0);
	
	assert(sizes.x > 0);
	assert(sizes.y > 0);
		
	rectangle.setPosition(posit);
	
	rectangle.setFillColor(rect_color);
	
	int counter{0};
	
	assert(counter == 0);
	
	const float half_y{static_cast<float>(0.5*sizes.y)};
	
	const sf::Vector2f first_posit{half_y, half_y};
	
	const sf::Vector2f jump_posit{2*half_y, 0};
	
	sf::Vector2f circlent_posit{posit + first_posit};	
		
	while (counter < circlent_amount)
	{
		
		const circle_entity circlent(values[counter], normal_radius, circlent_posit, circlent_color);
		
		circlents.push_back(circlent);	
		
		reposit_circlent(circlents[counter], circlent_posit + static_cast<float>(counter)*jump_posit);
			
		++counter;
		
		assert(counter > 0);	
			
	}
	
}

rect_entity::~rect_entity()
{
			
}

void show_rectent(sf::RenderWindow& window, const rect_entity& rectent)
{
	
	assert(rectent.circlent_amount > 0);
	
	window.draw(rectent.rectangle);
	
	int counter{0};
	assert(counter == 0);
	
	while (counter < rectent.circlent_amount)
	{
		
		show_circlent(window, rectent.circlents[counter]);
			
		++counter;
		
		assert(counter > 0);
		
	}
	
}

int main()
{
	
	Pirate_Captain Blackbeard;
	
	Blackbeard.pirate_sez_wut();
	
	const int delaz{50};	
	assert(delaz > 0);
	
	const std::chrono::milliseconds delay(delaz);
	
	const double window_x{1000};
	const double window_y{700};	
	
	assert(window_x > 0);	
	assert(window_y > 0);
	
	const std::string program_name{"Rectangle Circles V0.2"};
	
	assert(program_name != "");
	
	const sf::Color white{sf::Color(255, 255, 255)};	
	const sf::Color black{sf::Color(0, 0, 0)};	
	const sf::Color orange{sf::Color(255, 127, 0)};	
	const sf::Color purple{sf::Color(127, 0, 255)};	
	const sf::Color cyan{sf::Color(127, 255, 255)};
	const sf::Color red{sf::Color(255, 0, 0)};
	const sf::Color yellow{sf::Color(255, 255, 0)};
	const sf::Color green{sf::Color(0, 255, 0)};
	const sf::Color blue{sf::Color(0, 0, 255)};
	
	const int rectent_x{2};
	assert(rectent_x > 0);
	
	const int rectent_y{2};
	assert(rectent_y > 0);
	
	const float rectent_posit_x{50};
	assert(rectent_posit_x > 0);
	
	const float rectent_posit_y{50};
	assert(rectent_posit_y > 0);
	
	const float rectent_jump_x{500};
	assert(rectent_jump_x > 0);
	
	const float rectent_jump_y{150};
	assert(rectent_jump_y > 0);
	
	const float rectent_size_x{300};
	assert(rectent_size_x > 0);
	
	const float rectent_size_y{0.25f*rectent_size_x};
	assert(rectent_size_y > 0);
	
	const sf::Vector2f rectent_sizes{rectent_size_x, rectent_size_y};
	
	const int rectent_amount{rectent_x*rectent_y};
	
	std::vector <sf::Vector2f> rectent_posits;
	
	int counter_y{0};
	assert(counter_y == 0);
	
	while (counter_y < rectent_y)
	{
		
		int counter_x{0};
		assert(counter_x == 0);
		
		while (counter_x < rectent_x)
		{
			
			const sf::Vector2f posit{rectent_posit_x + static_cast<float>(counter_x)*rectent_jump_x,
									rectent_posit_y + static_cast<float>(counter_y)*rectent_jump_y};
			
			rectent_posits.push_back(posit);
			
			++counter_x;
			
		}
		
		++counter_y;
		
	}
	
	std::vector <int> rectent_circlent_amounts;
	
	rectent_circlent_amounts.push_back(4);
	rectent_circlent_amounts.push_back(4);
	rectent_circlent_amounts.push_back(2);
	rectent_circlent_amounts.push_back(4);
	
	std::vector <sf::Color> rectent_colors;
	
	rectent_colors.push_back(purple);
	rectent_colors.push_back(yellow);
	rectent_colors.push_back(green);
	rectent_colors.push_back(orange);
	
	std::vector <sf::Color> circlent_colors;
	
	circlent_colors.push_back(red);
	circlent_colors.push_back(cyan);
	
	std::vector <double> circlent_values;
	
	circlent_values.push_back(100);
	circlent_values.push_back(30);
	circlent_values.push_back(160);
	circlent_values.push_back(80);
	
	std::vector <rect_entity> rectents;
	
	int counter{0};
	assert(counter == 0);
	
	while (counter < rectent_amount)
	{
			
		const rect_entity rectent(rectent_posits[counter], rectent_sizes, rectent_circlent_amounts[counter],
							rectent_colors[counter], circlent_colors[0], circlent_values);
							
		rectents.push_back(rectent);
		
		++counter;
			
	}
	
	sf::RenderWindow window(sf::VideoMode(window_x, window_y), program_name, sf::Style::Default);
	
	while (window.isOpen())
	{

		sf::Event event;
		
		window.clear(black);
		
		counter = 0;
		assert(counter == 0);
		
		while (counter < 4)
		{
			
			show_rectent(window, rectents[counter]);
			
			++counter;
			
		}
		
		window.display();
				
		std::this_thread::sleep_for(delay);
		
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
	
	Blackbeard.pirate_axe_wut();
	
	return 0;
	
}
