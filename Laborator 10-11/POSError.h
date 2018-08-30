#pragma once
#include <string>

class POSError {
public:
	POSError(std::string message) :
		message(message) {
	}
	const std::string& getMessage() const noexcept{
		return message;
	}
private:
	std::string message;
};
