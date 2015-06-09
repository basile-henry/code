#ifndef INEXOR_RPC_SHARED_VAR_PARSER_HEADER
#define INEXOR_RPC_SHARED_VAR_PARSER_HEADER

#include <boost/preprocessor.hpp>

/// Concatenate all the given arguments
///
/// ```INEXOR_PP_VCAT(h,e,l,l,o) // hello ```
#define INEXOR_PP_VCAT(...) \
    BOOST_PP_SEQ_CAT(       \
        BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define INEXOR_PP_BRACE_OPENING() {
#define INEXOR_PP_BRACE_CLOSING() }

/// Extract the last element from a tuple
///
/// ```INEXOR_PP_TUPLE_LAST((1,2,3,4,5)) // 5```
#define INEXOR_PP_TUPLE_LAST(tup)                  \
    BOOST_PP_TUPLE_ELEM(                           \
        BOOST_PP_SUB(BOOST_PP_TUPLE_SIZE(tup), 1), \
        tup)

/// Extract the first element from a tuple
///
/// ```INEXOR_PP_TUPLE_HEAD((1,2,3,4,5)) // 1```
#define INEXOR_PP_TUPLE_HEAD(tup) \
    BOOST_PP_TUPLE_ELEM(0, tup)

/// Join a sequence with a specific separator
///
/// ```INEXOR_PP_SEQ_JOIN((a)(b)(c), _) // a_b_c ```
///
/// @param seq The sequence to join
/// @param sep The separator to put between each element
#define INEXOR_PP_SEQ_JOIN(seq, sep)      \
    BOOST_PP_SEQ_ELEM(1,                  \
      BOOST_PP_SEQ_FOLD_LEFT(             \
          BOOST_PP_SEQ_FOLD_LEFT_OP,      \
          (sep)(BOOST_PP_SEQ_HEAD(seq)),  \
          BOOST_PP_SEQ_TAIL(seq)))
/// Basically a catenation operator (A cat B), but we need
/// to store the seperator somehow, so we use the
/// accumulation variable (which is the result which is set
/// to A) to store the separator, so what we're actually
/// doing is more like `[A[0], cat(A[1], A[0], B)]`
///
/// The caller needs to make sure to pack the accumulator
/// correctly and then to unpack the result again.
///
/// ```
/// INEXOR_PP_SEQ_JOIN_OPNPACK(_, (::)(helloworld), foo)
/// // -> (::)(helloworldfoo)
/// ```
///
/// @param A sequence that contains (seperator)(accumulator)
/// @param B The next element to append to the accumulator
#define INEXOR_PP_SEQ_JOIN_OP(s, A, B) \
    (BOOST_PP_SEQ_ELEM(0, A))\
    (INEXOR_PP_VCAT(BOOST_PP_SEQ_ELEM(1, A), BOOST_PP_SEQ_ELEM(2), B))

/// Join the elements of a tuple with the given separator
///
/// ```INEXOR_PP_TUPLE_JOIN((foo,bar)) // foobar```
///
/// @param tup The tuple to join
/// @param sep The seperator to divide the elements with
#define INEXOR_PP_TUPLE_JOIN(tup, sep) \
    INEXOR_PP_SEQ_JOIN(BOOST_PP_TUPLE_TO_SEQ(tup), sep)

/// Extract the plain name from a tuple-style variable path
///
/// ```INEXOR_PP_NSP_NAME((inexor,util,myvar)) // myvar```
#define INEXOR_PP_NSP_NAME INEXOR_PP_TUPLE_LAST

/// Create the canonical name from a tuple style variable
/// path
///
/// ```
/// INEXOR_PP_NSP_CANONICAL_NAME((inexor,util,myvar))
/// // -> inexor::util::myvar
/// ```
#define INEXOR_PP_NSP_CANONICAL_NAME(nsp) \
    INEXOR_PP_TUPLE_JOIN(nsp, ::)

/// Create a namespace declaration from a tuple style
/// variable path; this assumes that the last element in the
/// path is a variable and skips it therefor
///
/// ```
/// INEXOR_PP_NSP_NSDEC((inexor,util,myvar))
/// // -> namespace inexor { namespace util {
/// ```
#define INEXOR_PP_NSP_NSDEC(nsp) \
    NEXOR_PP_NSP_NSDEC_FULL(BOOST_PP_TUPLE_POP_BACK(nsp))

/// Like INEXOR_PP_NSP_NSDEC, but does not skip the last
/// element in the tuple
///
/// ```
/// INEXOR_PP_NSP_NSDEC((inexor,util,myns))
/// // -> namespace inexor { namespace util { namespace myns {
/// ```
#define INEXOR_PP_NSP_NSDEC_FULL(nsp) \
    INEXOR_PP_NSP_NSDEC_FULLSEQ(BOOST_PP_TUPLE_TO_SEQ(nsp))

/// Like INEXOR_PP_NSP_NSDEC_FULL but takes a sequence
///
/// ```
/// INEXOR_PP_NSP_NSDEC((inexor)(util)(myns))
/// // -> namespace inexor { namespace util { namespace myns {
/// ```
#define INEXOR_PP_NSP_NSDEC_FULLSEQ(nsp)    \
    BOOST_PP_SEQ_CAT(                       \
        BOOST_PP_SEQ_TRANSFORM(             \
            INEXOR_PP_NSP_NSDEC_FULLSEQ_OP, \
            BOOST_PP_NULL,                  \
            nsp))
#define INEXOR_PP_NSP_NSDEC_FULLSEQ_OP(s, dat, X) \
    namespace X {

/// Creates appropriate closing braces for a declaration
/// with INEXOR_PP_NSP_NSDEC
///
/// ```
/// INEXOR_PP_NSP_NSDEC((inexor,util,myvar))
/// INEXOR_PP_NSP_NSCLOSE((inexor,util,myvar))
/// // namespace inexor { namespace util {
/// // }}
/// ```
#define INEXOR_PP_NSP_NSCLOSE(nsp) \
    INEXOR_PP_NSP_NSCLOSE_I(       \
        BOOST_PP_SUB(BOOST_PP_TUPLE_SIZE(nsp), 1))
/// Like INEXOR_PP_NSP_NSCLOSE but creates one brace more
///
/// Creates appropriate closing braces for a declaration
/// with INEXOR_PP_NSP_NSDEC
///
/// ```
/// INEXOR_PP_NSP_NSDEC((inexor,util,myns))
/// INEXOR_PP_NSP_NSCLOSE_FULL((inexor,util,myns))
/// // namespace inexor { namespace util { namespace myns {
/// // }}}
/// ```
#define INEXOR_PP_NSP_NSCLOSE_FULL(nsp) \
    INEXOR_PP_NSP_NSCLOSE_I(BOOST_PP_TUPLE_SIZE(nsp))
/// Generates N consecutive closing braces
///
/// ```INEXOR_PP_NSP_NSCLOSE_I(4) // }}}}```
#define INEXOR_PP_NSP_NSCLOSE_I(N) \
    BOOST_PP_REPEAT(N, INEXOR_PP_BRACE_CLOSING, BOOST_PP_NULL)

/// Declares a variable of the given type in the given
/// namespace
///
/// ```
/// INEXOR_PP_NSP_DECLARE(int, (inexor,util,mavar))
/// // namespace inexor {namespace util {
/// // int myvar;
/// // }}
/// ```
#define INEXOR_PP_NSP_DECLARE(type, nsp) \
    INEXOR_PP_NSP_NSDEC(nsp)             \
    type INEXOR_PP_NSP_NAME(nsp);        \
    INEXOR_PP_NSP_NSCLOSE(nsp)

#endif
