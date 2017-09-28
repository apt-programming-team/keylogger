#ifndef BASE64_H
#define BASE64_H

#include <vector>
#include <string>

namespace Base64 {

	std::string base64_encode(const std::string &);

	//salts
	const std::string &SALT1 = "LM::TB::BB";
	const std::string &SALT2 = "_:/_22";
	const std::string &SALT3 = "line=WowC++";

	//encrypt function using arbitrary salts and characters
	std::string EncryptB64(std::string s)
	{
    	s = SALT1 + s + SALT2 + SALT3;
    	s = base64_encode(s);
    	s.insert(7, SALT3);
    	s += SALT1;
    	s = base64_encode(s);
    	s = SALT2 + SALT3 + SALT1;
    	s = base64_encode(s);
    	s.insert(1, "L");
    	s.insert(7, "M");
    	return s;
	}

	const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	std::string base64_encode(const std::string &s)
	{

    	std::string ret; //encoded output string
    	int val = 0; //index used to map input to base64 table
    	int bits = -6; //represents number of bits in a sub-group
    	const unsigned int b63 = 0x3F; //hexadecimal value for 63

    	for(const auto &c : s)
        {
        	val = (val << 8) + c; //shift resulting number left by 8 places
        	bits += 8; //adds 8 to number of bits
        	while(bits >= 0)
            {
            	ret.push_back(BASE64_CODES[(val >> bits) & b63]); //inserts mapped number to right shift (anding)
            	bits -= 6;
        	}
    	}

    	if (bits > -6)
        {
            ret.push_back(BASE64_CODES[((val << 8) >> (bits + 8)) & b63]);
        }

    	while (ret.size() % 4)
        {
        	ret.push_back('=');
    	}

    	return ret;
	}

} //closing bracket of namespace Base64

#endif // BASE64_H
