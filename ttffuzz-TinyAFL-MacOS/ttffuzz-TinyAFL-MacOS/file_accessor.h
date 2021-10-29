//
//  file_accessor.h
//  AFL
//
//  Created by System Administrator on 2021/5/8.
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <random>
#include <cassert>
#include <algorithm>
#include <functional>
#include <zlib.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_set>
#include <stdarg.h>
#include <map>
#include <sstream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "formatfuzzer.h"
#include "alloc-inl.h"

extern bool is_big_endian;
extern bool generate_parsedata;
extern bool formatfuzztojc;

void save_outputf(const char* filename);
void assert_cond(bool cond, const char* error_msg);
void swap_bytes(void* b, unsigned size);
bool ttf_tables(std::map<int, long> &get_data);//sunglin
std::map<int, long> decode_table(std::string table, size_t *offset_data, int index_data); //sunglin

template <class Type>
Type stringToNum(const std::string& str);

class file_accessor{
    bool allow_evil_values = true;
    bool dont_be_evil = false;
    unsigned bitfield_size = 0;
    unsigned bitfield_bits = 0;
    bool has_bitmap = false;
    std::vector<bool> bitmap;
    std::string string_buf;
    
    unsigned long long parse_integer(unsigned char* file_buf, unsigned size, unsigned bits);
    void write_file_bits(unsigned long long value, size_t size, unsigned bits);
    std::map<int, long> write_file(const void *buf, size_t size);
    void get_value(std::string value, size_t len);
    bool write_parse_data(std::map<int, long> &get_data);
public:
    
    std::function<bool (unsigned char*)> evil_parse;
    std::function<long long (unsigned char*)> parse;
    
    unsigned char* rand_buffer;
    unsigned rand_pos = 0;
    unsigned rand_size = 0;
    unsigned char *file_buffer;
    unsigned file_pos = 0;
    unsigned file_size = 0;
    unsigned final_file_size = 0;
    unsigned parsed_file_size = 0;
    unsigned rand_prev = 0;
    unsigned rand_last = UINT_MAX;
    bool has_size = false;
    bool generate = true;
    bool lookahead = false;
    bool is_padding = false;
    
    bool Decisiontree = false; //sunglin
    unsigned char * deci_buffer; //sunglin
    unsigned deci_pos = 36; //sunglin 9 * 4 table length
    unsigned deci_size = 36; //sunglin
    
    size_t table_offset[9] = {0};
    //size_t tabledata_offset = 0;
    
    
    long deci_number = 0;//sunglin
    
    char* input_filename[100];
    char* outttf_dir[100];
    
    file_accessor();
    ~file_accessor();
    bool set_evil_bit(bool allow);
    bool evil(std::function<bool (unsigned char*)>& evil_parse);
    long long rand_int(unsigned long long x, std::function<long long (unsigned char*)>& parse);
    void finish();
    std::string rand_bytes(int size);
    void seed(unsigned char* b, unsigned rsize, unsigned fsize);
    int feof();
    
    template<typename T>
    long long file_integer(unsigned size, unsigned bits, std::vector<T>& known);
    template<typename T>
    bool is_compatible_integer(unsigned size, T& v);
    long long file_integer(unsigned size, unsigned bits, int small);
    bool is_compatible_string(std::string& v);
    std::string file_string(std::vector<std::string>& known);
    std::string file_string(int size = 0);
    std::string file_ascii_string(int size = 0);
    std::string file_latin1_string(int size = 0);
    
};
template<typename T>
long long file_accessor::file_integer(unsigned size, unsigned bits, std::vector<T>& known) {
    assert_cond(0 < size && size <= 8, "sizeof integer invalid");
    assert_cond(file_pos + size <= MAX_FILE_SIZE, "file size exceeded MAX_FILE_SIZE");
    std::vector<T> compatible;
    bool match = false;
    if (has_bitmap) {
        for (unsigned i = 0; i < size; ++i) {
            if (bitmap[file_pos + i]) {
                match = true;
                break;
            }
        }
        if (match) {
            assert_cond(bits == 0, "bitfield lookahead not implemented");
            for (T& v : known) {
                if (is_compatible_integer(size, v))
                    compatible.push_back(v);
            }
        }
    }
    std::vector<T>& good = match ? compatible : known;

    if (!generate)
        evil_parse = [&size, &bits, &good, this](unsigned char* file_buf) -> bool {
            T value = (T)parse_integer(file_buf, size, bits);
            return std::find(good.begin(), good.end(), value) == good.end();
        };

    if ((match && compatible.empty()) || evil(evil_parse)) {
        return file_integer(size, bits, 1);
    }

    if (!generate)
        parse = [&size, &bits, &good, this](unsigned char* file_buf) -> long long {
            T value = (T)parse_integer(file_buf, size, bits);
            return std::find(good.begin(), good.end(), value) - good.begin();
        };

    T value = good[rand_int(good.size(), parse)];
    T newvalue = value;
    if (bits) {
        value = (T)((unsigned long long)value & ((1LLU << bits) - 1LLU));
        write_file_bits(value, size, bits);
    } else {
        swap_bytes(&newvalue, size);
        
        //write_file(&newvalue, size);
        std::map<int, long> get_data;
        get_data = write_file(&newvalue, size);
        if(get_data.size() > 0)
        {
            std::map<int, long>::iterator get_data_iter;// 0:D   1:N    2:S   3:X   4:1  5:0
            get_data_iter = get_data.begin();
            if(get_data_iter->first < 4)
            {
                value = get_data_iter->second;
            }
            else if(get_data_iter->first == 5)
            {
                value = 0;
            }
        }
        
        get_value(std::to_string(value), size);
    }

    return value;
}
template<typename T>
bool file_accessor::is_compatible_integer(unsigned size, T& v) {
    unsigned char* p = (unsigned char*) &v;
    for (unsigned i = 0; i < size; ++i) {
        if (bitmap[file_pos + i]) {
            unsigned index = is_big_endian ? size - 1 - i : i;
            if (p[index] != file_buffer[file_pos + i])
                return false;
        }
    }
    return true;
}
//long long rand_int(unsigned long long x, std::function<long long (unsigned char*)>& parse);
// bt


//#include "types.h"
//using namespace std;
//_HAS_STD_BYTE=0

typedef unsigned int UINT;
typedef char byte;
typedef char CHAR;
typedef char BYTE;
typedef unsigned char uchar;
typedef unsigned char ubyte;
typedef unsigned char UCHAR;
typedef unsigned char UBYTE;
typedef short int16;
typedef short SHORT;
typedef short INT16;
typedef unsigned short uint16;
typedef unsigned short ushort;
typedef unsigned short USHORT;
typedef unsigned short UINT16;
typedef unsigned short WORD;
typedef int int32;
typedef int INT;
typedef int INT32;
typedef int LONG;
typedef unsigned int uint;
typedef unsigned int uint32;
typedef unsigned int ulong;
typedef unsigned int UINT;
typedef unsigned int UINT32;
typedef unsigned int ULONG;
typedef unsigned int DWORD;
typedef long long int64;
typedef long long quad;
typedef long long QUAD;
typedef long long INT64;
typedef long long __int64;
typedef unsigned long long uint64;
typedef unsigned long long uquad;
typedef unsigned long long UQUAD;
typedef unsigned long long UINT64;
typedef unsigned long long QWORD;
typedef unsigned long long __uint64;
typedef float FLOAT;
typedef double DOUBLE;
typedef float hfloat;
typedef float HFLOAT;
typedef unsigned long long OLETIME;
typedef long time_t;

const int CHECKSUM_BYTE = 0;
const int CHECKSUM_SHORT_LE = 1;
const int CHECKSUM_SHORT_BE = 2;
const int CHECKSUM_INT_LE = 3;
const int CHECKSUM_INT_BE = 4;
const int CHECKSUM_INT64_LE = 5;
const int CHECKSUM_INT64_BE = 6;
const int CHECKSUM_SUM8 = 7;
const int CHECKSUM_SUM16 = 8;
const int CHECKSUM_SUM32 = 9;
const int CHECKSUM_SUM64 = 10;
const int CHECKSUM_CRC16 = 11;
const int CHECKSUM_CRCCCITT = 12;
const int CHECKSUM_CRC32 = 13;
const int CHECKSUM_ADLER32 = 14;
const int FINDMETHOD_NORMAL = 0;
const int FINDMETHOD_WILDCARDS = 1;
const int FINDMETHOD_REGEX = 2;
const int cBlack = 0x000000;
const int cRed = 0x0000ff;
const int cDkRed = 0x000080;
const int cLtRed = 0x8080ff;
const int cGreen = 0x00ff00;
const int cDkGreen = 0x008000;
const int cLtGreen = 0x80ff80;
const int cBlue = 0xff0000;
const int cDkBlue = 0x800000;
const int cLtBlue = 0xff8080;
const int cPurple = 0xff00ff;
const int cDkPurple = 0x800080;
const int cLtPurple = 0xffe0ff;
const int cAqua = 0xffff00;
const int cDkAqua = 0x808000;
const int cLtAqua = 0xffffe0;
const int cYellow = 0x00ffff;
const int cDkYellow = 0x008080;
const int cLtYellow = 0x80ffff;
const int cDkGray = 0x404040;
const int cGray = 0x808080;
const int cSilver = 0xc0c0c0;
const int cLtGray = 0xe0e0e0;
const int cWhite = 0xffffff;
const int cNone = 0xffffffff;
const int True = 1;
const int TRUE = 1;
const int False = 0;
const int FALSE = 0;

#define GENERATE_VAR(name, value) do { \
    start_generation(#name);       \
    name ## _var = (value);        \
    name ## _exists = true;        \
    end_generation();              \
    } while (0)

#define GENERATE(name, value) do {     \
    start_generation(#name);       \
    (value);                       \
    end_generation();              \
    } while (0)

#define GENERATE_EXISTS(name, value)   \
    name ## _exists = true

#define GENERATE_GVAR(name) \
    name ## _var

unsigned long long STR2INT(std::string s);

constexpr unsigned long long STR2INT(const char * s) {
#ifndef __clang__
    assert(strlen(s) <= 8);
#endif
    unsigned long long result = 0;
    while (*s) {
        result = (result << 8) | *s;
        ++s;
    }
    return result;
}

//extern unsigned char *rand_buffer;
extern file_accessor file_acc;

//extern bool is_big_endian;
//extern bool is_padded_bitfield;

//sunglin
void os_2_table();
void head_table();
void cmap_table();

void save_outttf(size_t filesize);

void write_deci_bytes(bool data, bool stru, bool number , bool xxxx , long xxxxvalue);
void memcpy_decistr(std::string str);
void memcpy_decidata(long data, size_t len);


//void png_generate_file();

double get_validity();
void start_generation(const char* name);
void end_generation();
char* get_bin_name(char* arg);
void set_parser();
void set_generator();
bool setup_input(const char* filename, const char* outdir);
int  save_output(char* filedata, int32_t len, int32_t *temlen);
unsigned copy_rand(unsigned char *dest);
//void png_delete_globals();
//void jpg_delete_globals();
void ttf_generate_file();
void ttf_delete_globals();

void exit_template(int status);
void exit_template(std::string message);
void check_array_length(unsigned& size) ;
void ChangeArrayLength();
void EndChangeArrayLength();
void BigEndian();
void LittleEndian();
int IsBigEndian();
void BitfieldLeftToRight();
void BitfieldRightToLeft();
void BitfieldEnablePadding();
void BitfieldDisablePadding();
void SetBackColor(int color);

void DisplayFormatBinary();
void DisplayFormatDecimal();
void DisplayFormatHex();
void DisplayFormatOctal();

int SetEvilBit(int allow);
uint32 Checksum(int checksum_type, int64 start, int64 size);
void Warning(const std::string fmt, ...);
void Printf(const std::string fmt, ...);
void SPrintf(std::string& s, const char* fmt, ...);
std::string::size_type Strlen(std::string s);

int Strcmp(std::string s1, std::string s2);

int Strncmp(std::string s1, std::string s2, int n);

std::string SubStr(std::string s, int start, int count = -1);

int Memcmp(std::string s1, std::string s2, int n);
void Memcpy(std::string& dest, std::string src, int n, int destOffset = 0, int srcOffset = 0);

int IsParsing();

int FEof();
int64 FTell();
int FSeek(int64 pos, bool print = true);

int FSkip(int64 offset);

int64 FileSize();

unsigned get_file_size();
template<typename T>
int64 FindFirst(T data, int matchcase=true, int wholeword=false, int method=0, double tolerance=0.0, int dir=1, int64 start=0, int64 size=0, int wildcardMatchLength=24) ;

template<typename T>
void VectorRemove(std::vector<T>& vec, std::unordered_set<T> set) ;
extern std::vector<std::string> ReadBytesInitValues;

bool ReadBytes(std::string& s, int64 pos, int n) ;

bool ReadBytes(std::string& s, int64 pos, int n, std::vector<std::string> preferred_values, std::vector<std::string> possible_values = {}, double p = 0.25);
extern std::vector<byte> ReadByteInitValues;

byte ReadByte(int64 pos = FTell(), std::vector<byte> possible_values = {}) ;

extern std::vector<ubyte> ReadUByteInitValues;

ubyte ReadUByte(int64 pos = FTell(), std::vector<ubyte> possible_values = {}) ;

extern std::vector<short> ReadShortInitValues;

short ReadShort(int64 pos = FTell(), std::vector<short> possible_values = {}) ;

extern std::vector<ushort> ReadUShortInitValues;

ushort ReadUShort(int64 pos = FTell(), std::vector<ushort> possible_values = {}) ;

extern std::vector<int> ReadIntInitValues;

int ReadInt(int64 pos = FTell(), std::vector<int> possible_values = {}) ;

extern std::vector<uint> ReadUIntInitValues;

uint ReadUInt(int64 pos = FTell(), std::vector<uint> possible_values = {}) ;

extern std::vector<int64> ReadQuadInitValues;

int64 ReadQuad(int64 pos = FTell(), std::vector<int64> possible_values = {}) ;

extern std::vector<uint64> ReadUQuadInitValues;

uint64 ReadUQuad(int64 pos = FTell(), std::vector<uint64> possible_values = {}) ;

extern std::vector<int64> ReadInt64InitValues;

int64 ReadInt64(int64 pos = FTell(), std::vector<int64> possible_values = {}) ;

extern std::vector<uint64> ReadUInt64InitValues;

uint64 ReadUInt64(int64 pos = FTell(), std::vector<uint64> possible_values = {});
extern std::vector<hfloat> ReadHFloatInitValues;

hfloat ReadHFloat(int64 pos = FTell(), std::vector<hfloat> possible_values = {});

extern std::vector<float> ReadFloatInitValues;

float ReadFloat(int64 pos = FTell(), std::vector<float> possible_values = {});

extern std::vector<double> ReadDoubleInitValues;

double ReadDouble(int64 pos = FTell(), std::vector<double> possible_values = {});


template<typename T>
int64 FindFirst(T data, int matchcase, int wholeword, int method, double tolerance, int dir, int64 start, int64 size, int wildcardMatchLength) {
    // Other configurations not yet handled
    assert(matchcase == true && wholeword == false && method == 0 && tolerance == 0.0 && dir == 1 && size == 0 && wildcardMatchLength == 24);
    T newdata = data;
    swap_bytes(&newdata, sizeof(T));
    file_acc.lookahead = true;
    if (!file_acc.generate)
        file_acc.evil_parse = [&start, &newdata](unsigned char* file_buf) -> bool {
            return memmem(file_acc.file_buffer + start, file_acc.final_file_size - start, &newdata, sizeof(T)) == NULL;
        };
    if (file_acc.evil(file_acc.evil_parse)) {
        file_acc.lookahead = false;
        return -1;
    }
    if (!file_acc.generate)
        file_acc.parse = [&start, &newdata](unsigned char* file_buf) -> long long {
            return (unsigned char *)memmem(file_acc.file_buffer + start, file_acc.final_file_size - start, &newdata, sizeof(T)) - (file_acc.file_buffer + start);
        };
    int64 pos = start + file_acc.rand_int(MAX_FILE_SIZE + 1 - sizeof(T) - start, file_acc.parse);
    int64 original_pos = FTell();
    FSeek(pos);
    std::vector<T> values = { data };
    bool evil = file_acc.set_evil_bit(false);
    file_acc.file_integer(sizeof(T), 0, values);
    file_acc.set_evil_bit(evil);
        file_acc.lookahead = false;
        FSeek(original_pos);
        return pos;

}

template<typename T>
void VectorRemove(std::vector<T>& vec, std::unordered_set<T> set) {
    vec.erase(std::remove_if(vec.begin(), vec.end(), [&set](T s) { return set.find(s) != set.end(); }), vec.end());
}


// bt

