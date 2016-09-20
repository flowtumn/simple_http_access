#ifndef HTTP_METHOD_H_INCLUDE__
#define HTTP_METHOD_H_INCLUDE__

#include <string>

namespace flowTumn {
    namespace Http {
        enum struct Method {
            Get,
            Post,
            Put,
            Delete,
        };
    };

    std::string toStr(flowTumn::Http::Method method);
};

#endif // HTTP_METHOD_H_INCLUDE__
