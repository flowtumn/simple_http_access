#include "generator.h"
#include "generator_of_decrypt.h"
#include "decrypt.h"

int main() {
	// please a enter password to this application.
	flowtumn::HttpReqeust v{
		"http://wwwwww",
		{
			{flowTumn::GeneratorNoProcessingImpl <std::string> {"param-name"}},
			{flowTumn::GeneratorOfDecrypt <std::string, flowTumn::DecryptAES256> {"key", "@@@@"}},
		},
	};
}
