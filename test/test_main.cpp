#include <algorithm>
#include <cassert>
#include <iterator>
#include <string>
#include "encrypt/base64.h"

template <typename R, typename T>
R toValue(T&& v) {
    R r{};

    using TT = std::remove_reference <T&&>::type;

    std::transform(
        std::begin(v),
        std::end(v),
        std::back_inserter(r),
        [](TT::value_type each) {
            return static_cast <R::value_type> (each);
        }
    );

    return r;
}

std::vector <byte> toBytes(const std::string& v) {
    return toValue <std::vector <byte>>(v);
}

std::string toString(const std::vector <byte>& v) {
    return toValue <std::string>(v);
}

int main() {
    std::string source{ "hello base64." };

    {
        auto r = flowTumn::base64::encode(toBytes(source));
        assert(r == "aGVsbG8gYmFzZTY0Lg==");
        auto rr = toString(flowTumn::base64::decode(r));
        assert(source == rr);
    }
}
