#ifndef _VU_MD5_H
#define _VU_MD5_H


#include <string>
#include <fstream>



/* Type define */
typedef unsigned char byte;
typedef unsigned int uint32;

using std::string;
using std::ifstream;

/* MD5 declaration. */
class MD5
{
public:
	MD5();
	MD5(const void *input, size_t length);
	MD5(const string &str);
	MD5(ifstream &in);
	void update(const void *input, size_t length);
	void update(const string &str);
	void update(ifstream &in);
	const byte* digest();
	string toString();
	void reset();
private:
	void update(const byte *input, size_t length);
	void final();
	void transform(const byte block[64]);
	void encode(const uint32 *input, byte *output, size_t length);
	void decode(const byte *input, uint32 *output, size_t length);
	string bytesToHexString(const byte *input, size_t length);

	/* class uncopyable */
	MD5(const MD5&);
	MD5& operator=(const MD5&);
private:
	uint32 _state[4];	/* state (ABCD) */
	uint32 _count[2];	/* number of bits, modulo 2^64 (low-order word first) */
	byte _buffer[64];	/* input buffer */
	byte _digest[16];	/* message digest */
	bool _finished;		/* calculate finished ? */

	static const byte MD5_PADDING[64];	/* padding for calculate */
	static const char MD5_HEX[16];
	static const size_t MD5_BUFFER_SIZE = 1024;
};

#endif/*_VU_MD5_H*/
