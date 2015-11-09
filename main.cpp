#include <iostream>

#include "bank.h"
#include "calendar.h"
#include "company.h"
#include "money.h"
#include "person.h"
#include "winner_package.h"
#include "simulation.h"
#include "simulation_parameters.h"

int main()
{
  //using ribi::imcw::bank;
  //using ribi::imcw::calendar;
  //using ribi::imcw::company;
  using ribi::imcw::person;
  using ribi::imcw::simulation;
  using ribi::imcw::simulation_parameters;

  person p("Mister X");
  p.set_auto_buy(false);

  const simulation_parameters parameters(
    p,
    {},
    boost::gregorian::day_clock::local_day(),
    boost::gregorian::day_clock::local_day()
      + boost::gregorian::months(11)
  );
  simulation s(
    parameters
  );

  //Display initial situation
  std::cout << "*****************" << std::endl;
  std::cout << "Initial situation" << '\n';
  std::cout << "*****************" << std::endl;
  std::cout << s.get_company() << std::endl;
  std::cout << "*****************" << std::endl;
  s.run();
}
