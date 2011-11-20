/** Tests the wittyPlus::base::URLs object **/

#include <string>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <wittyPlus/base/URLs.hpp>
#include <Wt/WObject>

namespace wittyPlus {
namespace unittests {

class SignalDetector : public Wt::WObject {
public:
   std::string state;
   SignalDetector() : state("") {}
   void slash() { state = "/"; }
   void pa() { state = "/pa"; }
   void page() { state = "/page"; }
};

BOOST_AUTO_TEST_SUITE( url_suite );

BOOST_AUTO_TEST_CASE( find_handlers ) {
    wittyPlus::base::URLs urls;
    SignalDetector detector;
    BOOST_REQUIRE_EQUAL(detector.state, "");
    urls.urlSignal("/").connect(&detector, &SignalDetector::slash);
    urls.urlSignal("/pa").connect(&detector, &SignalDetector::pa);
    urls.urlSignal("/page").connect(&detector, &SignalDetector::page);
    urls.run("/page/54/edit");
    BOOST_CHECK_EQUAL(detector.state, "/page");
    urls.run("/pays/54/edit");
    BOOST_CHECK_EQUAL(detector.state, "/pa");
    urls.run("/pays/54/edit?x=1&y=2");
    BOOST_CHECK_EQUAL(detector.state, "/pa");
    urls.run("/zed/54/edit?x=1&y=2");
    BOOST_CHECK_EQUAL(detector.state, "/");
    urls.run("/pageywagey/54/edit?x=1&y=2");
    BOOST_CHECK_EQUAL(detector.state, "/page");
    urls.run("/page?x=4&y=1");
    BOOST_CHECK_EQUAL(detector.state, "/page");
    urls.run("/?x=4&y=1");
    BOOST_CHECK_EQUAL(detector.state, "/");
}

BOOST_AUTO_TEST_SUITE_END() // url_suite

} // namespace unittests
} // namespace my_app
