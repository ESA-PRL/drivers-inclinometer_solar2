#include <boost/test/unit_test.hpp>
#include <inclinometer_solar2/Dummy.hpp>

using namespace inclinometer_solar2;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    inclinometer_solar2::DummyClass dummy;
    dummy.welcome();
}
