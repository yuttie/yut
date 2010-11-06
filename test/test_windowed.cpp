#include "yut/windowed.hpp"
#define BOOST_TEST_MODULE yut::windowed
#include <boost/test/unit_test.hpp>

#include <string>
#include <boost/typeof/typeof.hpp>


BOOST_AUTO_TEST_CASE(application_to_string) {
    using namespace std;

    string const rng = "The quick brown fox jumps over the lazy dog.";
    BOOST_AUTO(wrng, rng | yut::windowed(24));
    BOOST_AUTO(it, wrng.begin());

    BOOST_CHECK_EQUAL(*it, string("The quick brown fox jump"));  ++it;
    BOOST_CHECK_EQUAL(*it, string("he quick brown fox jumps"));  ++it;
    BOOST_CHECK_EQUAL(*it, string("e quick brown fox jumps "));  ++it;
    BOOST_CHECK_EQUAL(*it, string(" quick brown fox jumps o"));  ++it;
    BOOST_CHECK_EQUAL(*it, string("quick brown fox jumps ov"));  ++it;
    BOOST_CHECK_EQUAL(*it, string("uick brown fox jumps ove"));  ++it;
    BOOST_CHECK_EQUAL(*it, string("ick brown fox jumps over"));  ++it;
    BOOST_CHECK_EQUAL(*it, string("ck brown fox jumps over "));  ++it;
    BOOST_CHECK_EQUAL(*it, string("k brown fox jumps over t"));  ++it;
    BOOST_CHECK_EQUAL(*it, string(" brown fox jumps over th"));  ++it;
    BOOST_CHECK_EQUAL(*it, string("brown fox jumps over the"));  ++it;
    BOOST_CHECK_EQUAL(*it, string("rown fox jumps over the "));  ++it;
    BOOST_CHECK_EQUAL(*it, string("own fox jumps over the l"));  ++it;
    BOOST_CHECK_EQUAL(*it, string("wn fox jumps over the la"));  ++it;
    BOOST_CHECK_EQUAL(*it, string("n fox jumps over the laz"));  ++it;
    BOOST_CHECK_EQUAL(*it, string(" fox jumps over the lazy"));  ++it;
    BOOST_CHECK_EQUAL(*it, string("fox jumps over the lazy "));  ++it;
    BOOST_CHECK_EQUAL(*it, string("ox jumps over the lazy d"));  ++it;
    BOOST_CHECK_EQUAL(*it, string("x jumps over the lazy do"));  ++it;
    BOOST_CHECK_EQUAL(*it, string(" jumps over the lazy dog"));  ++it;
    BOOST_CHECK_EQUAL(*it, string("jumps over the lazy dog."));  ++it;
    BOOST_CHECK(it == wrng.end());  ++it;
    BOOST_CHECK(it == wrng.end());
}
