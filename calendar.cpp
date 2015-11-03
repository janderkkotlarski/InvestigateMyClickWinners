#include "calendar.h"

const boost::gregorian::date calendar::sm_distibute_profit_webshop_day
  = boost::gregorian::date(
    boost::gregorian::greg_year(2015),
    boost::gregorian::greg_month(2),
    boost::gregorian::greg_day(28)
  );

calendar::calendar(
  const boost::gregorian::date& today
) : m_today{today}
{
  #ifndef NDEBUG
  test();
  #endif
}

bool calendar::distibute_profit_winners_today() const noexcept
{
  return m_today == m_today.end_of_month();
}

bool calendar::distibute_profit_webshop_today() const noexcept
{
  return m_today.day() == sm_distibute_profit_webshop_day.day()
    && m_today.month() == sm_distibute_profit_webshop_day.month()
  ;
}

#ifndef NDEBUG
void calendar::test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const bool verbose{false};
  //Distribute Winners money at the end of the month
  {
    boost::gregorian::date today = boost::gregorian::day_clock::local_day();
    calendar c(today);
    for (int i=0; i!=12; ++i)
    {
      boost::gregorian::date next_month = today + boost::gregorian::months(1);
      bool has_distributed_winners{false};
      for ( ; c.get_current_day() != next_month; c.go_to_next_day() ) {
        if (c.distibute_profit_winners_today()) {
          if (verbose) {
            std::cout << "Distribute Winners profit at " << c.get_current_day() << std::endl;
          }
          has_distributed_winners = true;
        }
      }
      assert(has_distributed_winners);
      today = next_month;
    }
  }
  //Distribute profit webshop at Februari/March
  {
    const boost::gregorian::date today = boost::gregorian::day_clock::local_day();
    calendar c(today);
    const boost::gregorian::date next_year = today + boost::gregorian::years(1);
    int n_profit_of_webshop_distributed = 0;
    for ( ; c.get_current_day() != next_year; c.go_to_next_day() ) {
      if (c.distibute_profit_webshop_today()) {
        if (verbose) {
          std::cout << "Distribute webshop profit at " << c.get_current_day() << std::endl;
        }
        ++n_profit_of_webshop_distributed;
      }
    }
    assert(n_profit_of_webshop_distributed == 1);
  }
}
#endif

