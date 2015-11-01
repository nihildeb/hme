#include "test.hpp"
#include "SimpleSignal.h"

static int float_callback(float, int i, std::string) { return i; }
static int call_count = 0;

void cb(void)
{
    ++call_count;
}

BOOST_AUTO_TEST_CASE(SimpleSignals)
{
    Simple::Signal<int(float, int, std::string)> sig;
    sig.connect(float_callback);
    auto ret = sig.emit(1.0f, 123, "asd");
    //DCHECK(ret == 123);
    BOOST_REQUIRE(ret == 123);

    call_count = 0;
    Simple::Signal<void(void)> sig2;
    auto id1 = sig2.connect(cb);
    BOOST_REQUIRE(call_count == 0);
    sig2.emit();
    BOOST_REQUIRE(call_count == 1);
    sig2.emit();
    BOOST_REQUIRE(call_count == 2);
    // reset, connect twice, emit once
    call_count = 0;
    auto id2 = sig2.connect(cb);
    BOOST_REQUIRE(call_count == 0);
    sig2.emit();
    BOOST_REQUIRE(call_count == 2);
    // reset, disconnect 1, emit once
    call_count = 0;
    sig2.disconnect(id1);
    BOOST_REQUIRE(call_count == 0);
    sig2.emit();
    BOOST_REQUIRE(call_count == 1);
    // reset, disconnect last, emit once
    call_count = 0;
    sig2.disconnect(id2);
    BOOST_REQUIRE(call_count == 0);
    sig2.emit();
    BOOST_REQUIRE(call_count == 0);
}


struct TestCounter {
    static uint64_t get();
    static void     set(uint64_t);
    static void     add2(void*, uint64_t);
};

namespace { // Anon
    void(*test_counter_add2) (void*, uint64_t) = TestCounter::add2; // external symbol to prevent easy inlining
    static uint64_t test_counter_var = 0;
} // Anon

uint64_t
TestCounter::get()
{
    return test_counter_var;
}

void
TestCounter::set(uint64_t v)
{
    test_counter_var = v;
}

void
TestCounter::add2(void*, uint64_t v)
{
    test_counter_var += v;
}

static uint64_t
timestamp_benchmark()
{
    auto now = std::clock();
    auto cast = static_cast<uint64_t>(1.0e9 / CLOCKS_PER_SEC * now);
    return cast;
}

BOOST_AUTO_TEST_CASE(SimpleSignalBenchmark)
{
    Simple::Signal<void(void*, uint64_t)> sig_increment;
    sig_increment.connect(test_counter_add2);
    const auto start_counter = TestCounter::get();
    const auto benchstart = timestamp_benchmark();
    uint64_t i;
    for (i = 0; i < 999999; i++)
    {
        sig_increment.emit(nullptr, 1);
    }
    const auto benchdone = timestamp_benchmark();
    const auto end_counter = TestCounter::get();
    BOOST_REQUIRE(end_counter - start_counter == i);
    std::cout << "OK\n  Benchmark: Simple::Signal: " << (size_t(benchdone - benchstart) * 1.0 / size_t(i)) <<
        "ns per emission (size=" << sizeof(sig_increment) << ")\n";
}

BOOST_AUTO_TEST_CASE(SimpleSignalCallbackBenchmark)
{
    auto counter_increment = test_counter_add2;
    const auto start_counter = TestCounter::get();
    const auto benchstart = timestamp_benchmark();
    uint64_t i;
    for (i = 0; i < 999999; i++)
    {
        counter_increment(nullptr, 1);
    }
    const auto benchdone = timestamp_benchmark();
    const auto end_counter = TestCounter::get();
    BOOST_REQUIRE(end_counter - start_counter == i);
    std::cout << "OK\n  Benchmark: callback loop: " << (size_t(benchdone - benchstart) * 1.0 / size_t(i)) << "ns per round\n";
}