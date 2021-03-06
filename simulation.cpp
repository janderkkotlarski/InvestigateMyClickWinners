#include "simulation.h"

#include <algorithm>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "bank.h"
#include "calendar.h"

ribi::imcw::simulation::simulation(
  const simulation_parameters& parameters
)
  : m_bank{},
    m_calendar(parameters.get_start()),
    m_company{},
    m_focal_person{parameters.get_focal_person()},
    m_others{parameters.get_others()},
    m_parameters{parameters}
{
  #ifndef NDEBUG
  test();
  #endif
  //focal_person buy his/her membership
  m_company.buy_winner_package(
    m_focal_person,
    winner_package_name::starter,
    m_focal_person.get_balance(),
    m_bank,
    m_calendar
  );

  //add others
  std::for_each(
    std::begin(m_others),
    std::end(m_others),
    [this](person& p)
    {

      m_company.add(p);
      p.add_click_card(
        click_card(
          m_calendar.get_today()
          - boost::gregorian::days(std::rand() % 355)
        )
      );
      p.add_winner(
        winner(p.get_name())
      );
    }
  );

}

void ribi::imcw::simulation::do_timestep() noexcept
{
  std::cout << "today: " << m_calendar.get_today() << std::endl;
  //Will customers buy a new ClickCard?
  if (m_focal_person.will_buy_click_card(m_calendar.get_today())) {
    m_focal_person.buy_click_card(m_bank,m_calendar,m_company);
  }
  for (auto& p: m_others) {
    if (p.will_buy_click_card(m_calendar.get_today())) {
      p.buy_click_card(m_bank,m_calendar,m_company);
    }
  }


  //Website
  if (m_calendar.transfer_profit_website_today()) {
    balance website_net_profit(
      "Monthly website profit",
      m_parameters.get_profit_website_per_month()
    );
    m_company.transfer(website_net_profit,m_bank,m_calendar);
  }
  //Webshop
  if (m_calendar.transfer_profit_webshop_today()) {
    balance webshop_net_profit(
      "Yearly webshop profit",
      m_parameters.get_profit_webshop_per_year()
    );
    m_company.transfer(webshop_net_profit,m_bank,m_calendar);
  }
  //Winners
  //No transfer, all Winner money is already on the undistributed balance

  //Distribute profit
  if (m_calendar.distribute_profit_today()) {
    std::cout << "***************************" << std::endl;
    std::cout << "Distributing profit" << std::endl;
    std::cout << "***************************" << std::endl;
    m_company.distribute_net_profit(
      m_bank,
      m_calendar
    );
    std::cout << m_company << std::endl;
    std::cout << "***************************" << std::endl;
  }

  //Make persons transfer money from BankWallet to personal
  //bank account
  if (m_focal_person.will_tranfer(m_calendar.get_today())) {
    m_focal_person.transfer(m_bank,m_calendar);
  }
  for (auto& p: m_others) {
    if (p.will_tranfer(m_calendar.get_today())) {
      p.transfer(m_bank,m_calendar);
    }
  }

  m_calendar.go_to_next_day();
}

std::string ribi::imcw::simulation::get_version() const noexcept
{
  return "0.4";
}

std::vector<std::string> ribi::imcw::simulation::get_version_history() const noexcept
{
  return {
    "2015-11-01: Version 0.1: initial version",
    "2015-11-10: Version 0.2: got simulation and visualization working",
    "2014-11-14: Version 0.3: correct behavior after ending membership",
    "2014-11-15: Version 0.4: start of compensation plan implementation"
  };
}

bool ribi::imcw::simulation::is_done() const noexcept
{
  return m_calendar.get_today() >= m_parameters.get_end();
}

#ifndef NDEBUG
void ribi::imcw::simulation::test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const boost::gregorian::date today = boost::gregorian::day_clock::local_day();
  //If a member wants to be member for a year,
  //then after a year, the ClickCard is not valid any more
  //and the balance will be -100 euro
  {
    const auto membership_end = today + boost::gregorian::years(1);
    const auto simulation_end = today + boost::gregorian::months(13);
    const simulation_parameters parameters(
      person("Mister X",membership_end),
      {},
      today,
      simulation_end,
      money(0.0),
      money(0.0)
    );
    simulation s(parameters);
    while (!s.is_done()) { s.do_timestep(); }
    const auto p = s.get_focal_person();
    assert(!p.has_valid_click_card(
      s.get_calendar().get_today()
      )
    );
    assert(p.get_balance().get_value() == money(-100.0));
  }
}
#endif
