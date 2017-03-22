#ifndef ALGOHUB_JUDGE_RESULT_H
#define ALGOHUB_JUDGE_RESULT_H

#include <signal.h>
#include "serialize.h"


enum class StatusCode {
    RUNTIME_ERROR =3,
    ACCEPTED = 4,
    WRONG_ANSWER = 5,
    TIME_LIMIT_EXCEEDED = 6,
    MEMORY_LIMIT_EXCEEDED = 7,
    OUTPUT_LIMIT_EXCEEDED = 8,
    RESTRICTED_CALL = 9,
};

static inline int status_code_to_int(StatusCode code) {
    return static_cast<int>(code);
}

class JudgeResult {
public:
    StatusCode status_code;
    std::string error_message;
    rapidjson::Value input;
    rapidjson::Value output;
    rapidjson::Value expected_output;
    int testcase_passed_count;
    int testcase_total_count;
    int64_t elapsed_time;
    int64_t consumed_memory;

    JudgeResult() {
        status_code = StatusCode::ACCEPTED ;
        error_message = "";
        testcase_passed_count = 0;
        testcase_total_count = 0;
        elapsed_time = 0;
        consumed_memory = 0;
    }

    std::string to_string() const {
        rapidjson::Document d;
        auto& allocator = d.GetAllocator();
        rapidjson::Value result = rapidjson::Value(rapidjson::kObjectType);
        result.AddMember("status_code", status_code_to_int(this->status_code), allocator);
        if(!error_message.empty()) {
            result.AddMember("error_message", rapidjson::Value(error_message, allocator).Move(), allocator);
        }
        if(!input.IsNull()) {
            result.AddMember("input", rapidjson::Value(input, allocator).Move(), allocator);
        }
        if(!output.IsNull()) {
            result.AddMember("output", rapidjson::Value(output, allocator).Move(), allocator);
        }
        if(!expected_output.IsNull()) {
            result.AddMember("expected_output", rapidjson::Value(expected_output, allocator).Move(), allocator);
        }
        if(testcase_passed_count > 0) {
            result.AddMember("testcase_passed_count", testcase_passed_count, allocator);
        }
        if(testcase_total_count > 0) {
            result.AddMember("testcase_total_count", testcase_total_count, allocator);
        }
        if(elapsed_time > 0) {
            result.AddMember("elapsed_time", elapsed_time, allocator);
        }
        if(consumed_memory > 0) {
            result.AddMember("consumed_memory", consumed_memory, allocator);
        }
        return json_value_to_string(result);
    }
};


static JudgeResult judge_result;

static void sigsegv_handler(int sig) {
    judge_result.status_code = StatusCode::RUNTIME_ERROR;
    judge_result.error_message = "Segmentation fault";
    std::cerr << judge_result.to_string() << std::endl;
    exit(sig);
}

static void sigabrt_handler(int sig) {
    judge_result.status_code = StatusCode::RUNTIME_ERROR;
    judge_result.error_message = "Aborted";
    std::cerr << judge_result.to_string() << std::endl;
    exit(sig);
}

#endif //ALGOHUB_JUDGE_RESULT_H
