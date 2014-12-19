#ifndef SEPERATOR_H
#define SEPERATOR_H

#include "common.h"

namespace ullman {

class Seperator {
	public:
		Seperator(const char* token): _m_token(token) {
		};

		uint32_t seperate(const char *file_path, Buffer& stream);

	private:
		const char* _m_token;	
};

}//namespace ullman

#endif //SEPERATOR_H
