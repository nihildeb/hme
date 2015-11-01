#include "test.hpp"

BOOST_AUTO_TEST_CASE(EasyLogging)
{
    LOG(INFO) << "some log message";
    //LOG_IF(false, ERROR) << "never see this";
    //LOG_IF(true, INFO) << "do see this";
    for (int i = 1; i <= 10; ++i) {
        LOG_EVERY_N(2, INFO) << "Logged every second iter";
    }
    for (int i = 1; i <= 10; ++i) {
        LOG_AFTER_N(2, INFO) << "Log after 2 hits; " << i;
    }
    //DCHECK(1 == 1);
    BOOST_REQUIRE(1 == 1);
}
