#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>

#include <SFML/Graphics.hpp> 



struct money_flow
{
	
	const double money_inside = 0;
	
	const double scaling = 0.0;
	
	const std::string triangle_image = "Triangle.png";
	
	sf::Texture triangle_tex;	
	
	sf::Sprite triangle_sprite;
	
	
	money_flow();
	
	money_flow(const double money_amount);
	
};

money_flow::money_flow()
	:money_inside(0), scaling(0), triangle_tex(), triangle_sprite()
{

	assert(money_inside == 0);
	
	assert(scaling == 0);
	
	triangle_tex.loadFromFile(triangle_image);
	
	triangle_sprite.setTexture(triangle_tex);
	
	
}

money_flow::money_flow(const double money_amount)
	:money_inside(money_amount), scaling(sqrt(money_inside)), triangle_tex(), triangle_sprite()
{
	
	assert(money_inside > 0);
	
	assert(scaling > 0);
	
	triangle_tex.loadFromFile(triangle_image);
	
	triangle_sprite.setTexture(triangle_tex);
	
}

struct money_vault
{
	
	
	double money_inside = 0;
	
	double scaling = 0.0;
	
	const std::string circle_image = "Circle.png";
	
	sf::Texture circle_tex;	
	
	sf::Sprite circle_sprite;
	
	
	money_vault();
	
	money_vault(const double money_amount);
	
	void money_plus(const money_flow &transfer)
	{
		
		money_inside += transfer.money_inside;
		
		scaling = sqrt(money_inside);
		
	}
	
	void money_minus(const money_flow &transfer)
	{
		
		money_inside -= transfer.money_inside;
		
		scaling = sqrt(money_inside);
		
	}
	
};

money_vault::money_vault()
	:money_inside(0), scaling(0), circle_tex(), circle_sprite()
{

	assert(money_inside == 0);
	
	assert(scaling == 0);
	
	circle_tex.loadFromFile(circle_image);
	
	circle_sprite.setTexture(circle_tex);
	
	
}

money_vault::money_vault(const double money_amount)
	:money_inside(money_amount), scaling(sqrt(money_inside)), circle_tex(), circle_sprite()
{

	assert(money_inside > 0);
	
	assert(scaling > 0);
	
	circle_tex.loadFromFile(circle_image);
	
	circle_sprite.setTexture(circle_tex);
	
	
}

void money_transfer(money_vault &sender, const money_flow &transfer, money_vault &receiver)
{
	
	sender.money_minus(transfer);
	
	receiver.money_plus(transfer);
	
}

struct profit_sphere
{
	
	money_vault monthly_website_profit;
	
	money_vault yearly_webshop_profit;
	
};

struct company_sphere
{
	
	money_vault undistributed;
	
	money_vault compensation_plan;
	
	money_vault holding;
	
	money_vault reserves;
		
};

struct mister_sphere
{
	
	money_vault winner;
	
	money_vault shopwallet;
	
	money_vault bankwallet;
	
	money_vault personal_balance;
		
};

struct investors_sphere
{
	
	money_vault winner;
	
	money_vault shopwallet;
	
	money_vault bankwallet;
	
	money_vault personal_balance;
		
};

int main()
{
	
	sf::CircleShape money_circle(100);
	
	return 0;
	
} 
