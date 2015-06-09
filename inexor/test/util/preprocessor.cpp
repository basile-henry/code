#include <regex>

#include <boost/preprocessor.hpp>

#include "inexor/util/preprocessor.h"

#include "gtest/gtest.h"
#include "inexor/test/helpers.h"

using namespace std;

#define expectNStringEq(ref, mc) \
    expectEq(string(ref), string(#mc))

#define expectMacro_RES(res, ref, macro, ...)                 \
    expectNStringEq(ref, macro(__VA_ARGS__)) << "Expected "   \
        << "macro `" << #macro                                \
        << "(" << #__VA_ARGS__ << ")` "                       \
        << "to evaluate to \"" << #res << "\", but it turned " \
        << "out as \"" << #res << "\"."
#define expectMacro(ref, macro, ...) \
    expectMacro_RES(macro(__VA_ARGS__), ref, macro, __VA_ARGS__)

#define expectIMacro(ref, macro, ...) \
    expectMacro(ref, INEXOR_PP_ ## macro, __VA_ARGS__)

#define TT(sub) TEST(preprocessor, sub)

TT(VCAT) {
    expectIMacro("hello world", VCAT, h, e, l, l o, i, w, o, r, l, d);
}

TT(TUPLE_LAST) {
    expectIMacro("99", TUPLE_LAST, (a,2,w,x,r,99));
    expectIMacro("2",  TUPLE_LAST, (2));
}

TT(TUPLE_HEAD) {
    expectIMacro("a",  TUPLE_HEAD, (a,2,w,x,r,99));
    expectIMacro("99", TUPLE_HEAD, (99));
}

TT(SEQ_JOIN) {
    expectIMacro("inexor::util", SEQ_JOIN, (inexor)(util), ::);
    expectIMacro("/foo/bar/baz", SEQ_JOIN, ()(foo)(bar)(baz), /);
    expectIMacro("hello world",  SEQ_JOIN, (hello)(world), );
    expectIMacro("hello",        SEQ_JOIN, (hello), aosidjaos);
}

TT(TUPLE_JOIN) {
    expectIMacro("inexor::util", TUPLE_JOIN, (inexor, util), ::);
    expectIMacro("/foo/bar/baz", TUPLE_JOIN, ( , foo, bar, baz), /);
    expectIMacro("hello world",  TUPLE_JOIN, (hello, world), );
    expectIMacro("hello",        TUPLE_JOIN, (hello), aosidjaos);
}

TT(NSP_NAME) {
    expectIMacro("foobar", NSP_NAME, (inexor, util, foobar));
    expectIMacro("bang", NSP_NAME, (bang));
}

TT(CANONICAL_NAME) {
    expectIMacro("inexor::util::foobar", NSP_CANONICAL_NAME,
        (inexor, util, foobar));
    expectIMacro("bang", NSP_CANONICAL_NAME, (bang));
}


//TT(NSP_DECLARE) {
//    string code, ex;
//    regex exc;
//    std::smatch sm;
//
//    exc = ex = "^//s*namespace//s*inexor//s*{//s*"
//      "namespace//s*game//*{//s*"
//        "int//s*millis//s*"
//        "//s*}//s*}//s*$";
//    code = BOOST_PP_STRIINGIZE(INEXOR_PP_NSP_DECLARE(
//          int, (inexor, game, millis));
//    expect(regex_match(code, exc, sm)) << "Expected "
//      << "`INEXOR_PP_NSP_DECLARE(int, (inexor, game, millis))`"
//      << " to match " << ex << ", but it turned out as `"
//      << code << "`.";
//
//    exc = ex = "^//s*namespace//s*inexor//s*{//s*"
//      "namespace//s*game//*{//s*"
//        "extern//s*inexor::util::Observe<string>//s*botnum//s*;"
//        "//s*}//s*}//s*$";
//    code = BOOST_PP_STRIINGIZE(INEXOR_PP_NSP_DECLARE(
//          extern inexor::util::Observe<string>, (inexor::game::botnum));
//    expect(regex_match(code, exc, sm)) << "Expected "
//      << "`INEXOR_PP_NSP_DECLARE(int, (inexor, game, millis))`"
//      << " to match " << ex << ", but it turned out as `"
//      << code << "`.";
//    exc = ex = "^\s*const\s*char[]\s*foo\s*;\s*$%"
//    code = BOOST_PP_STRIINGIZE(INEXOR_PP_NSP_DECLARE(
//          const char[], (foo));
//    expect(regex_match(code, exc, sm)) << "Expected "
//}
