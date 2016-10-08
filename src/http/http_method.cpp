#include "http/http_method.h"

#include <stdexcept>

namespace flowTumn {
    std::string toStr(flowTumn::Http::Method method) {
        using L = flowTumn::Http::Method;

        switch (method) {
        default:
            throw std::invalid_argument("unsupport http method.");
        case L::Get:
            return "GET";
        case L::Post:
            return "POST";
        case L::Put:
            return "PUT";
        case L::Delete:
            return "DELETE";
        }
    }
};
