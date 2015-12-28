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

void init_posits(const int tent_x, const int tent_y, std::vector <sf::Vector2f>& tent_posits,
				const sf::Vector2f& tent_posit, const sf::Vector2f& tent_jump)
{

	int counter_y{0};
	assert(counter_y == 0);
	
	while (counter_y < tent_y)
	{
		
		int counter_x{0};
		assert(counter_x == 0);
		
		while (counter_x < tent_x)
		{
			
			const sf::Vector2f posit{tent_posit.x + static_cast<float>(counter_x)*tent_jump.x,
									tent_posit.y + static_cast<float>(counter_y)*tent_jump.y};
			
			tent_posits.push_back(posit);
			
			++counter_x;
			
		}
		
		++counter_y;
		
	}
		
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

void init_circlents(const int tent_x, const int tent_y, std::vector <circle_entity>& circlents,
				const std::vector <sf::Vector2f>& circlent_posits, const std::vector <double>& circlent_values,
				const sf::Color& circlent_color, const double circlent_radius)
{

	int counter_y{0};
	assert(counter_y == 0);
	
	while (counter_y < tent_y)
	{
		
		int counter_x{0};
		assert(counter_x == 0);
		
		while (counter_x < tent_x)
		{
			
			const circle_entity circlent(circlent_values[tent_x*counter_y + counter_x], circlent_radius,
										circlent_posits[tent_x*counter_y + counter_x], circlent_color);
						
			circlents.push_back(circlent);
			
			++counter_x;
			
		}
		
		++counter_y;
		
	}
		
}

struct rect_entity
{
	
	sf::Vector2f posit{0, 0};	
	
	const sf::Vector2f sizes{300, 300};
	
	sf::RectangleShape rectangle{sizes};
	
	const sf::Color rect_color{0, 127, 0};
	
	const sf::Color circlent_color{0, 0, 127};
	
	std::vector <double> values;
	
	const double normal_radius{0.1*sizes.y};
	
	std::vector <circle_entity> circlents;
	
	const int circlent_amount{0};
	
	rect_entity(const sf::Vector2f& pozit, const sf::Vector2f& zisez, const int kirkle_amount,
				const sf::Color rekt_kolor, const sf::Color& kirkle_kolor, const std::vector <double>& walues);
	
	~rect_entity();
			
};

rect_entity::rect_entity(const sf::Vector2f& pozit, const sf::Vector2f& zisez, const int kirklent_amount,
						const sf::Color rekt_kolor, const sf::Color& kirklent_kolor, const std::vector <double>& walues)
	:posit(pozit), sizes(zisez), rectangle(sizes), rect_color(rekt_kolor), circlent_color(kirklent_kolor),
	 values(walues), normal_radius(0.1*sizes.y), circlents(), circlent_amount(kirklent_amount)
{
	
	assert(circlent_amount > 0);
	
	assert(sizes.x > 0);
	assert(sizes.y > 0);
	
	const int amount_x{2};
	
	const int amount_y{2};
		
	rectangle.setPosition(posit);
	
	rectangle.setFillColor(rect_color);
	
	const float posit_part{0.25f};
	
	const sf::Vector2f first_posit{posit_part*sizes};
	
	const sf::Vector2f jump_posit{0.5f*sizes};	
	
	sf::Vector2f circlent_posit{posit + first_posit};
	
	std::vector <sf::Vector2f> circlent_posits;
	
	init_posits(amount_x, amount_x, circlent_posits, circlent_posit, jump_posit);
	
	init_circlents(amount_x, amount_y, circlents, circlent_posits, values, circlent_color, normal_radius);
	
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
	
	
	
	const std::string program_name{"Rectangle Circles V0.4"};
	
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
	
	
	const float window_x{800};
	const float window_y{600};	
		
	assert(window_x > 0);	
	assert(window_y > 0);
	
	const sf::Vector2f window_sizes{window_x, window_y};
	
	const float rect_part{0.3};
	const float moat_part{0.5*(0.5 - rect_part)};
	assert(rect_part > 0);
	assert(rect_part < 0.5);
	
	const sf::Vector2f rectent_sizes{rect_part*window_sizes};
	const sf::Vector2f rectent_posit{moat_part*window_sizes};
	const sf::Vector2f rectent_jump{0.5f*window_sizes};

	const int rectent_x{2};
	assert(rectent_x > 0);
	
	const int rectent_y{2};
	assert(rectent_y > 0);
	
	const int rectent_amount{rectent_x*rectent_y};
	
	std::vector <sf::Vector2f> rectent_posits;
	
	init_posits(rectent_x, rectent_y, rectent_posits, rectent_posit, rectent_jump);
	
	
	
	std::vector <int> rectent_circlent_amounts;
	
	rectent_circlent_amounts.push_back(4);
	rectent_circlent_amounts.push_back(2);
	rectent_circlent_amounts.push_back(4);
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
