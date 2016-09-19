#ifndef HTTP_REQEUST_H__
#define HTTP_REQEUST_H__

#include <string>
#include <unorder_map>

#include "generator.h"

namespace flowtumn {
	struct HttpReqeust {
		using type = flowTumn::IGenerator <std::string>;

		std::string url_;
		std::unorder_map <std::string, std::string> parameter_;
		std::unorder_map <type::value_type, type::value_type> params_;
	};
};

#endif // HTTP_REQEUST_H__