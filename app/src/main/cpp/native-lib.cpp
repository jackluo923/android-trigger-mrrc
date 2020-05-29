#include <jni.h>
#include <string>
#include <chrono>

extern "C"
JNIEXPORT jstring JNICALL
Java_ca_utoronto_dsrg_trigger_1mrrc_MainActivity_testMrrc(JNIEnv *env, jobject thiz) {
    uint64_t generic_timer_count = 0L;
    uint32_t t1, t2;
    auto start = std::chrono::steady_clock::now();
    int iterations = 100000000;
    for (int i = 0; i < iterations; i++) {
        asm volatile("mrrc p15, 1, %0, %1, c14" : "=r"(t1), "=r"(t2));
        generic_timer_count = t1;
        generic_timer_count = generic_timer_count << 32 | t2;
    }
    auto finish = std::chrono::steady_clock::now();

    double elapsed_seconds = std::chrono::duration_cast<
            std::chrono::duration<double> >(finish - start).count();
    std::string elapsed_milliseconds_string = std::to_string(elapsed_seconds * 1000);
    std::string output_str;
    output_str += std::to_string(iterations);
    output_str += " iterations in ";
    output_str += elapsed_milliseconds_string;
    output_str += "ms,\n ";
    output_str += std::to_string((elapsed_seconds * 1000000000)/ iterations);
    output_str += "ns per iteration";

    return env->NewStringUTF(output_str.c_str());
}