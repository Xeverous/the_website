#include <string>

struct request_result
{
	std::string data = {};
	bool is_error = false;
};

// This function is mine and libcurl calls it multiple times during the download.
// The received data is passed as an array of bytes: the classic "pointer + size" convention.
// nmemb is the size, the unused parameter is always 1 to match C standard library fwrite function.
// userdata parameter is mine too, it is set earlier in https://curl.se/libcurl/c/CURLOPT_WRITEDATA.html
std::size_t write_callback(char* data, std::size_t /* size */, std::size_t nmemb, void* userdata) noexcept
{
	// I have given an address of the request_result struct earlier, now I obtain it back.
	// curl uses void* because it doesn't understand external types but can take any address.
	auto& result = *reinterpret_cast<request_result*>(userdata);

	try {
		result.data.append(data, nmemb); // may throw on allocation failure
		return nmemb; // return number of bytes accepted
	}
	catch (const std::exception& e) {
		result.is_error = true;
		result.data = e.what();
	}
	catch (...) {
		result.is_error = true;
		result.data = "(unknown error)";
	}

	// If control flow gets here, it means that result.data threw an exception.
	// This means memory allocation failed and I want to stop the transfer.
	return 0; // error: accepted 0 bytes
}
