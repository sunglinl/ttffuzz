//
//  file_accessor.cpp
//  AFL
//
//  Created by System Administrator on 2021/5/10.
//

#include <stdio.h>
#include "file_accessor.h"

bool is_big_endian = false;
bool is_bitfield_left_to_right[2] = {false, true};
bool is_bitfield_right_to_left[2] = {true, false};
bool is_padded_bitfield = true;

std::vector<std::vector<InsertionPoint>> insertion_points;
std::vector<std::vector<Chunk>> deletable_chunks;
std::vector<Chunk> optional_chunks;
std::vector<int> optional_index = { 0 };
std::unordered_map<std::string, std::vector<Chunk>> non_optional_chunks;
std::vector<std::vector<NonOptional>> non_optional_index;
std::vector<std::string> rand_names;

bool debug_print = false;
bool print_errors = false;
bool get_parse_tree = false;

bool generate_parsedata = false;

unsigned char *rand_buffer;


unsigned char *following_rand_buffer = NULL;
unsigned following_rand_size = 0;

extern std::vector<std::vector<int>> integer_ranges;
bool change_array_length = false;


bool is_following = false;
bool following_is_optional = false;

const char* chunk_name;
const char* chunk_name2;
int file_index = 0;

bool get_chunk = false;
bool get_all_chunks = false;
bool smart_mutation = false;
bool smart_abstraction = false;
bool smart_swapping = false;
unsigned chunk_start;
unsigned chunk_end;
unsigned rand_start;
unsigned rand_end;
unsigned rand_start2;
unsigned rand_end2;
bool is_optional = false;
bool is_delete = false;

unsigned long long STR2INT(std::string s) {
    assert(s.size() <= 8);
    unsigned long long result = 0;
    for (char& c : s) {
        result = (result << 8) | c;
    }
    return result;
}

file_accessor file_acc;
struct stack_cell {
    const char* name;
    std::unordered_map<std::string, int> counts;
    //std::map<std::string, size_t> values;//sunglin
    std::vector<std::pair<std::string, size_t>> values;//sunglin
    unsigned rand_start = 0;
    unsigned rand_start_real = 0;
    unsigned min = UINT_MAX;
    unsigned max = 0;
    stack_cell(const char* name, unsigned rand_start, unsigned rand_start_real) : name(name), rand_start(rand_start), rand_start_real(rand_start_real) {}
    void clear() {
        counts.clear();
        min = UINT_MAX;
        max = 0;
    }
};
stack_cell root_cell("file", 0, 0);
std::vector<stack_cell> generator_stack = {root_cell};


void swap_bytes(void* b, unsigned size) {
    if (is_big_endian) {
        char* start = (char*) b;
        char* end = start + size;
        
        std::reverse(start, end);
       
    }
}
void swap_bytes2(void* b, unsigned size) {
    //if (is_big_endian) {
        char* start = (char*) b;
        char* end = start + size;
       
        std::reverse(start, end);
      
  //  }
}





void assert_cond(bool cond, const char* error_msg) {
    if (!cond) {
        if (debug_print || print_errors)
            fprintf(stderr, "Error: %s\n", error_msg);
        throw -1;
    }
}



//class file_accessor {
    

    unsigned long long file_accessor::parse_integer(unsigned char* file_buf, unsigned size, unsigned bits) {
       
        unsigned long long value = 0;
        if (bits) {
            unsigned new_pos = 0;
            unsigned new_bitfield_bits = bitfield_bits;
            if (is_padded_bitfield && (bitfield_bits + bits > 8 * bitfield_size || size != bitfield_size)) {
                new_pos += bitfield_size;
                new_bitfield_bits = 0;
            }

            unsigned initial_bitfield_bits = new_bitfield_bits;
            unsigned new_bits = bits;
            while (new_bits) {
                unsigned byte_pos = new_bitfield_bits / 8;
                unsigned bits_pos = new_bitfield_bits % 8;
                unsigned write_bits = 8 - bits_pos;
                if (new_bits < write_bits)
                    write_bits = new_bits;
                unsigned b1;
                unsigned b2;
                if (is_big_endian) {
                    b2 = bits - write_bits - (new_bitfield_bits - initial_bitfield_bits);
                } else {
                    b2 = new_bitfield_bits - initial_bitfield_bits;
                }
                if (is_bitfield_left_to_right[is_big_endian]) {
                    b1 = (8 - bits_pos - write_bits);
                } else {
                    b1 = bits_pos;
                }
                unsigned long long c = file_buf[new_pos + byte_pos] >> b1;
                c &= (1 << write_bits) - 1;
                c <<= b2;
                value |= c;

                new_bits -= write_bits;
                new_bitfield_bits += write_bits;
            }

            return value;
        }
        unsigned start_pos = bitfield_bits ? bitfield_size : 0;
        if (is_big_endian) {
            unsigned char* dest = (unsigned char*) &value;
            for (unsigned i = 0; i < size; ++i)
            {
                //printf("%x ", file_buf[start_pos + size-1-i]);
                dest[i] = file_buf[start_pos + size-1-i];
            }
            //printf("\n");
                
        } else {
            memcpy(&value, file_buf + start_pos, size);
        }
        return value;
    }
    //sunglin
    bool file_accessor::write_parse_data(std::map<int, long> &get_data)
    {
        
        return ttf_tables(get_data);
        
       
        
    }
    void file_accessor::write_file_bits(unsigned long long value, size_t size, unsigned bits) {
        int i = 0;
        if (is_padded_bitfield && bitfield_size && (bitfield_bits + bits > 8 * bitfield_size || size != bitfield_size)) {
            is_padding = true;
            file_integer(bitfield_size, 8 * bitfield_size - bitfield_bits, 0);
            is_padding = false;
        }
        unsigned start_pos = file_pos;
        assert_cond(file_pos + size <= MAX_FILE_SIZE, "file size exceeded MAX_FILE_SIZE");
        assert_cond(!has_size || file_pos + size <= file_size, "file size exceeded known size");
        value &= (1LLU << bits) - 1LLU;
        unsigned new_bits = bits;
        while (new_bits) {
            unsigned byte_pos = bitfield_bits / 8;
            unsigned bits_pos = bitfield_bits % 8;
            unsigned write_bits = 8 - bits_pos;
            if (new_bits < write_bits)
                write_bits = new_bits;
            unsigned char c;
            unsigned char mask = (1 << write_bits) - 1;
            if (is_big_endian) {
                c = value >> (bits - write_bits);
                value <<= write_bits;
                value &= (1LLU << bits) - 1LLU;
            } else {
                c = value & ((1 << write_bits) - 1);
                value >>= write_bits;
            }
            if (is_bitfield_left_to_right[is_big_endian]) {
                c <<= (8 - bits_pos - write_bits);
                mask <<= 8 - bits_pos - write_bits;
            } else {
                c <<= bits_pos;
                mask <<= bits_pos;
            }
            unsigned index = file_pos + byte_pos;
            if (!generate)
                assert_cond(index < final_file_size, "reading past the end of file");
            unsigned char old = file_buffer[index];
            file_buffer[index] &= ~mask;
            file_buffer[index] |= c;
            if (!generate)
                assert_cond(file_buffer[index] == old, "parsed wrong file contents");
            new_bits -= write_bits;
            bitfield_bits += write_bits;
        }
        bitfield_size = size;
        while (bitfield_bits >= bitfield_size * 8) {
            file_pos += bitfield_size;
            bitfield_bits -= bitfield_size * 8;
        }
        if (bitfield_bits == 0)
            bitfield_size = 0;

        if (file_size < file_pos)
            file_size = file_pos;
        if (is_padding)
            return;
        if (!generate && parsed_file_size < file_pos)
            parsed_file_size = file_pos;
        if (!get_parse_tree)
            return;
        if (start_pos < generator_stack.back().min)
            generator_stack.back().min = start_pos;
        unsigned end = bitfield_size ? file_pos + ((bitfield_bits - 1) / 8) : file_pos - 1;
        if (end > generator_stack.back().max)
            generator_stack.back().max = end;
    }
    void file_accessor::get_value(std::string value, size_t len)
    {
        generator_stack.back().values.push_back(std::pair<std::string, size_t>(value, len));
    }
std::map<int, long> file_accessor::write_file(const void *buf, size_t size) {
        int i = 0;
        //long return_data = 0;
        std::map<int, long> get_data;
        if (bitfield_bits) {
            is_padding = true;
            file_integer(bitfield_size, 8 * bitfield_size - bitfield_bits, 0);
            is_padding = false;
        }
        unsigned start_pos = file_pos;
        file_pos += size;
        assert_cond(file_pos <= MAX_FILE_SIZE, "file size exceeded MAX_FILE_SIZE");
        assert_cond(!has_size || file_pos <= file_size, "file size exceeded known size");
        if (generate) {
            if(generate_parsedata)
            {
                bool write_buf = false;
                
                std::map<int, long>::iterator get_data_iter;// 0:D   1:N    2:S   3:X   4:1  5:0
                write_buf = write_parse_data(get_data);
                get_data_iter = get_data.begin();
                if(!write_buf)
                {
                    memcpy(file_buffer + start_pos, buf, size);
                }
                else
                {
                    if(get_data. size() > 0)
                    {
                        switch (get_data_iter->first) {
                            case 0:
                                memcpy(file_buffer + start_pos, &get_data_iter->second, size); //get D:data
                                break;
                            case 1:
                                memcpy(file_buffer + start_pos, &get_data_iter->second, size); //get N:number 数组
                                break;
                            case 2:
                                memcpy(file_buffer + start_pos, &get_data_iter->second, size); //get S:struc 子类结构
                                break;
                            case 3:
                                memcpy(file_buffer + start_pos, &get_data_iter->second, size); //get X:xxxx 固定不可变数据
                                break;
                            case 4:
                                memcpy(file_buffer + start_pos, buf, size); //get 1:此数据存在
                                break;
                                
                            case 5:
                                memset(file_buffer + start_pos, 0, size);  //get 0:此数据不存在
                                break;
                        }
                        if(get_data_iter->first < 4)
                        {
                            swap_bytes2(file_buffer + start_pos, size);
                        }
                            
                        
                    }
                    else
                    {
                        memcpy(file_buffer + start_pos, buf, size);
                    }
                    
                    
                }
            }
            else
            {
                memcpy(file_buffer + start_pos, buf, size);
            }
            
        } else {
          
            assert_cond(file_pos <= final_file_size, "reading past the end of file");
            assert_cond(memcmp(file_buffer + start_pos, buf, size) == 0, "parsed wrong file contents");
        }

        if (file_size < file_pos)
            file_size = file_pos;

        if (lookahead) {
            has_bitmap = true;
            unsigned original_pos = file_pos - size;
            for (unsigned i = 0; i < size; ++i)
                bitmap[original_pos + i] = true;
        }

        if (is_padding || lookahead)
            return get_data;
        if (!generate && parsed_file_size < file_pos)
            parsed_file_size = file_pos;
        if (!get_parse_tree)
            return get_data;
        if (start_pos < generator_stack.back().min)
            generator_stack.back().min = start_pos;
        if (file_pos - 1 > generator_stack.back().max)
            generator_stack.back().max = file_pos - 1;
    return get_data;
    }

//public:
    

file_accessor::file_accessor() : bitmap(MAX_FILE_SIZE) {
        file_buffer = new unsigned char[MAX_FILE_SIZE];
        ::rand_buffer = new unsigned char[MAX_RAND_SIZE];
        deci_buffer = new unsigned char[MAX_DECI_SIZE]; //sunglin
        memset(deci_buffer, 0, MAX_DECI_SIZE);
    
        if (getenv("DONT_BE_EVIL"))
            dont_be_evil = true;
    }
    
file_accessor::~file_accessor() {
        delete[] file_buffer;
        delete[] ::rand_buffer;
        delete[] deci_buffer; //sunglin
    }

    bool file_accessor::set_evil_bit(bool allow) {
        bool old = allow_evil_values;
        allow_evil_values = allow;
        return old;
    }

  
    bool file_accessor::evil(std::function<bool (unsigned char*)>& evil_parse) {
        if (!generate)
            parse = [&evil_parse](unsigned char* file_buf) -> long long { return evil_parse(file_buf) ? 127 : 0; };
        bool is_evil = rand_int(127 + allow_evil_values, parse) == 127;
        assert_cond(!(!generate && !allow_evil_values && rand_buffer[rand_pos-1] == 127), "Evil bit is disabled, but an evil decision is required to parse this file");
        return is_evil;
    }

   

    long long file_accessor::rand_int(unsigned long long x, std::function<long long (unsigned char*)>& parse) {
        unsigned long long max = x-1;
        if (!max)
            return 0;
        if (get_parse_tree) {
            if (lookahead || is_padding) {
                if (rand_last == UINT_MAX)
                    rand_last = rand_pos;
            } else {
                rand_last = UINT_MAX;
            }
            if (is_following && !is_padding) {
                following_is_optional = lookahead;
                is_following = false;
                if (get_all_chunks && lookahead) {
                    deletable_chunks[file_index].emplace_back(file_index, rand_start, rand_end, variable_types[chunk_name].c_str(), chunk_name);
                }
            }
        }
        if (!(max>>8)) {
            assert_cond(rand_pos + 1 <= rand_size, "random size exceeded rand_size");
            unsigned char* p = (unsigned char*) &rand_buffer[rand_pos];
            //printf("p:%x\n", *p);
            //printf("file_buffer:%c\n", file_buffer[file_pos]);
            if (!generate) {
                *p = parse(&file_buffer[file_pos]);
            }
            //printf("parse :%x\n", *p);
            ++rand_pos;
            return (*p) % x;
        }
        if (!(max>>16)) {
            assert_cond(rand_pos + 2 <= rand_size, "random size exceeded rand_size");
            unsigned short* p = (unsigned short*) &rand_buffer[rand_pos];
           // printf("%x\n", *p);
            if (!generate) {
                *p = parse(&file_buffer[file_pos]);
            }
            rand_pos += 2;
            //printf("p %x\n", *p);
            return (*p) % x;
        }
        if (!(max>>32)) {
            assert_cond(rand_pos + 4 <= rand_size, "random size exceeded rand_size");
            unsigned* p = (unsigned*) &rand_buffer[rand_pos];
          //  printf("%x\n", *p);
            if (!generate) {
                *p = parse(&file_buffer[file_pos]);
            }
            rand_pos += 4;
           // printf("p %x\n", *p);
            return (*p) % x;
        }
        assert_cond(rand_pos + 8 <= rand_size, "random size exceeded rand_size");
        unsigned long long* p = (unsigned long long*) &rand_buffer[rand_pos];
        if (!generate) {
            *p = parse(&file_buffer[file_pos]);
        }
        rand_pos += 8;
        if (!x)
            return *p;
        return (*p) % x;
    }

    void file_accessor::finish() {
        if (bitfield_bits) {
            is_padding = true;
            file_integer(bitfield_size, 8 * bitfield_size - bitfield_bits, 0);
            is_padding = false;
        }
        if (!generate) {
            assert_cond(file_size == final_file_size, "unparsed bytes left at the end of file");
            if (parsed_file_size != final_file_size && (debug_print || print_errors))
                fprintf(stderr, "Warning: unparsed (lookahead) bytes left at the end of file\n");

            if (get_parse_tree && get_chunk && chunk_end == UINT_MAX && file_pos == chunk_start && rand_last != UINT_MAX) {
                printf("FILE IS APPENDABLE\n");
                rand_start = rand_last;
                chunk_name = "file";
            }
            if (get_parse_tree && get_all_chunks && rand_last != UINT_MAX) {
                insertion_points[file_index].emplace_back(rand_last, "File", "file");
            }
        }
    }

    std::string file_accessor::rand_bytes(int size) {
        std::string result;
        for (int i = 0; i < size; ++i) {
            unsigned char byte = rand_int(256, parse);
            result += byte;
        }
        return result;
    }

    void file_accessor::seed(unsigned char* b, unsigned rsize, unsigned fsize) {
        rand_buffer = b;
        rand_size = rsize;
        rand_pos = 0;
        file_pos = 0;
        file_size = 0;
        final_file_size = fsize;
        parsed_file_size = 0;
        rand_prev = 0;
        rand_last = UINT_MAX;
        following_is_optional = false;
        is_following = false;

        has_size = false;
        allow_evil_values = !dont_be_evil;
        bitfield_size = 0;
        bitfield_bits = 0;
        lookahead = false;
        is_padding = false;
        if (has_bitmap)
            std::fill(bitmap.begin(), bitmap.end(), false);
        has_bitmap = false;
        is_big_endian = false;
        is_bitfield_left_to_right[0] = false;
        is_bitfield_left_to_right[1] = true;
        is_padded_bitfield = true;
        if (get_parse_tree || generate_parsedata) { //sunglin
            generator_stack.erase(generator_stack.begin() + 1, generator_stack.end());
            generator_stack[0].clear();
        }
    }

    int file_accessor::feof() {
        if (file_pos < file_size)
            return 0;
        if (has_size)
            return 1;
        lookahead = true;
        if (!generate)
            parse = [this](unsigned char* file_buf) -> long long { return file_pos == final_file_size ? 7 : 0; };
        int is_feof = rand_int(8, parse) == 7;
        lookahead = false;
        if (is_feof)
            has_size = true;
        return is_feof;
    }

   

    
    long long file_accessor::file_integer(unsigned size, unsigned bits, int small ) {
        assert_cond(0 < size && size <= 8, "sizeof integer invalid");
        assert_cond(file_pos + size <= MAX_FILE_SIZE, "file size exceeded MAX_FILE_SIZE");

        unsigned long long range = bits ? bits : 8*size;
        range = range == 64 ? 0 : 1LLU << range;
        long long value;

        if (small == 0) {
            if (!generate)
                parse = [&size, &bits, this](unsigned char* file_buf) -> long long {
                    return parse_integer(file_buf, size, bits);
                };
            value = rand_int(range, parse);
        } else if (small == 1 || (small >= 2 && integer_ranges[small-2][1] == INT_MAX)) {
            int min = 0;
            if (small >= 2)
                min = integer_ranges[small-2][0];
            std::function<long long (unsigned char*)> choice_parse;
            if (!generate) {
                choice_parse = [&size, &bits, &min, this](unsigned char* file_buf) -> long long {
                    unsigned long long value = parse_integer(file_buf, size, bits) - min;
                    if (value > 0 && value <= 1<<4)
                        return 0;
                    if (value < 1<<8)
                        return 256 - 32;
                    if (value < 1<<16)
                        return 256 - 8;
                    return 256 - 2;
                };
                parse = [&size, &bits, &min, this](unsigned char* file_buf) -> long long {
                    long long value = parse_integer(file_buf, size, bits);
                    value -= min;
                    return value;
                };
            }
            int s = rand_int(256, choice_parse);
            if (s >= 256 - 2)
                value = rand_int(range, parse);
            else if (s >= 256 - 8)
                value = rand_int(1<<16, parse);
            else if (s >= 256 - 32)
                value = rand_int(1<<8, parse);
            else {
                if (!generate)
                    parse = [&size, &bits, &min, this](unsigned char* file_buf) -> long long {
                        long long value = parse_integer(file_buf, size, bits);
                        value -= min + 1;
                        return value;
                    };
                value = 1+rand_int(1<<4, parse);
            }
            value += min;
        } else {
            int min = integer_ranges[small-2][0];
            int max = integer_ranges[small-2][1];
            if (!generate)
                evil_parse = [&size, &bits, &min, &max, this](unsigned char* file_buf) -> bool {
                    long long value = parse_integer(file_buf, size, bits);
                    if (value >= min && value <= max)
                        return false;
                    return true;
                };

            if (evil(evil_parse)) {
                if (!generate)
                    parse = [&size, &bits, this](unsigned char* file_buf) -> long long {
                        return parse_integer(file_buf, size, bits);
                    };
                value = rand_int(range, parse);
            } else {
                if (!generate)
                    parse = [&size, &bits, &min, this](unsigned char* file_buf) -> long long {
                        long long value = parse_integer(file_buf, size, bits);
                        value -= min;
                        return value;
                    };
                value = min + rand_int(max + 1 - min, parse);
            }
        }
        if (has_bitmap) {
         //   printf("bitmap\n");
            for (unsigned i = 0; i < size; ++i) {
                
                if (bitmap[file_pos + i]) {
                  //  printf("%x ", file_buffer[file_pos + i]);
                    assert_cond(bits == 0, "bitfield lookahead not implemented");
                    unsigned char* p = (unsigned char*) &value;
                    unsigned index = is_big_endian ? size - 1 - i : i;
                    p[index] = file_buffer[file_pos + i];
                }
            }
        }
        long long newvalue = value;
        if (bits) {
            value &= (1LLU << bits) - 1LLU;
            write_file_bits(value, size, bits);
        } else {
            
            swap_bytes(&newvalue, size);
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

    bool file_accessor::is_compatible_string(std::string& v) {
        unsigned char* p = (unsigned char*) v.c_str();
        for (unsigned i = 0; i < v.length(); ++i) {
            if (bitmap[file_pos + i] && p[i] != file_buffer[file_pos + i])
                return false;
        }
        return true;
    }
    
    std::string file_accessor::file_string(std::vector<std::string>& known) {
        int size = known[0].length();
        assert_cond(file_pos + size <= MAX_FILE_SIZE, "file size exceeded MAX_FILE_SIZE");
        std::vector<std::string> compatible;
        bool match = false;
        if (has_bitmap) {
            for (int i = 0; i < size; ++i) {
                if (bitmap[file_pos + i]) {
                    match = true;
                    break;
                }
            }
            if (match) {
                for (std::string& v : known) {
                    if (is_compatible_string(v))
                        compatible.push_back(v);
                }
            }
        }
        std::vector<std::string>& good = match ? compatible : known;

        if (!generate)
            evil_parse = [&good](unsigned char* file_buf) -> bool {
                std::string value((char*) file_buf, good[0].length());
                return std::find(good.begin(), good.end(), value) == good.end();
            };
        if ((match && compatible.empty()) || evil(evil_parse)) {
            assert_cond(size, "empty known string");
            return file_string(size);
        }
        if (!generate)
            parse = [&good](unsigned char* file_buf) -> long long {
                std::string value((char*) file_buf, good[0].length());
                return std::find(good.begin(), good.end(), value) - good.begin();
            };
        std::string value = good[rand_int(good.size(), parse)];
        ssize_t len = value.length();
        
        std::map<int, long> get_data;
        get_data = write_file(value.c_str(), len);
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
                value.clear();
            }
        }
        
        get_value(value, len);
        return value;
    }
    
    std::string file_accessor::file_string(int size ) {
        assert_cond(size >= 0, "negative string length");
        assert_cond(file_pos + size <= MAX_FILE_SIZE, "file size exceeded MAX_FILE_SIZE");
        if (!generate)
            parse = [&size](unsigned char* file_buf) -> long long {
                int len = size ? size : INT_MAX;
                for (int i = 0; i < len && (size || file_buf[i]); ++i)
                    if (file_buf[i] < 32 || file_buf[i] >= 127)
                        return 15;
                return 0;
            };
        int choice = rand_int(16, parse);
        if (choice < 14) {
            return file_ascii_string(size);
        } else if (choice == 14) {
            return file_latin1_string(size);
        }
        ssize_t len = size;
        if (!len) {
            if (!generate)
                parse = [](unsigned char* file_buf) -> long long { return strlen((char*)file_buf); };
            len = rand_int(80, parse);
        }

        string_buf.resize(len + 1);
        for (int i = 0; i < len; ++i) {
            if (size == 0) {
                if (!generate)
                    parse = [&i](unsigned char* file_buf) -> long long { return file_buf[i] - 1; };
                string_buf[i] = rand_int(255, parse) + 1;
            } else {
                if (!generate)
                    parse = [&i](unsigned char* file_buf) -> long long { return file_buf[i]; };
                string_buf[i] = rand_int(256, parse);
            }
        }
        string_buf[len] = '\0';
        if (has_bitmap) {
            for (int i = 0; i < len; ++i) {
                if (bitmap[file_pos + i]) {
                    string_buf[i] = file_buffer[file_pos + i];
                }
            }
        }
        std::string value(string_buf.c_str(), len);
        if (size == 0)
            ++len;
        write_file(value.c_str(), len);
        get_value(value, len);
        return value;
    }

    std::string file_accessor::file_ascii_string(int size ) {
        assert_cond(size >= 0, "negative string length");
        assert_cond(file_pos + size <= MAX_FILE_SIZE, "file size exceeded MAX_FILE_SIZE");
        ssize_t len = size;
        if (!len) {
            if (!generate)
                parse = [](unsigned char* file_buf) -> long long { return strlen((char*)file_buf); };
            len = rand_int(80, parse);
        }

        string_buf.resize(len + 1);
        for (int i = 0; i < len; ++i) {
            if (!generate)
                parse = [&i](unsigned char* file_buf) -> long long { return file_buf[i] - 32; };
            string_buf[i] = rand_int(95, parse) + 32;
        }
        string_buf[len] = '\0';
        if (has_bitmap) {
            for (int i = 0; i < len; ++i) {
                if (bitmap[file_pos + i]) {
                    string_buf[i] = file_buffer[file_pos + i];
                }
            }
        }
        std::string value(string_buf.c_str(), len);
        if (size == 0)
            ++len;
        write_file(value.c_str(), len);
        get_value(value, len);
        return value;
    }

    std::string file_accessor::file_latin1_string(int size) {
        assert_cond(size >= 0, "negative string length");
        assert_cond(file_pos + size <= MAX_FILE_SIZE, "file size exceeded MAX_FILE_SIZE");
        ssize_t len = size;
        if (!len) {
            if (!generate)
                parse = [](unsigned char* file_buf) -> long long { return strlen((char*)file_buf); };
            len = rand_int(80, parse);
        }

        string_buf.resize(len + 1);
        for (int i = 0; i < len; ++i) {
            if (!generate)
                parse = [&i](unsigned char* file_buf) -> long long { return file_buf[i] >= 161 ? file_buf[i] - 66 : file_buf[i] - 32; };
            string_buf[i] = rand_int(190, parse) + 32;
            if (string_buf[i] >= 127)
                string_buf[i] += 34;
        }
        string_buf[len] = '\0';
        if (has_bitmap) {
            for (int i = 0; i < len; ++i) {
                if (bitmap[file_pos + i]) {
                    string_buf[i] = file_buffer[file_pos + i];
                }
            }
        }
        std::string value(string_buf.c_str(), len);
        if (size == 0)
            ++len;
        write_file(value.c_str(), len);
        get_value(value, len);
        return value;
    }
//};
// bt
template <class Type>
Type stringToNum(const std::string& str){
    std::istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}
void memcpy_decistr(std::string str)
{
    memcpy(file_acc.deci_buffer + file_acc.deci_pos, str.c_str(), str.size());
  
    file_acc.deci_size += str.size();
    file_acc.deci_pos += str.size();
}
void memcpy_decidata(long data, size_t len)
{
    memcpy(file_acc.deci_buffer + file_acc.deci_pos, &data, len);
    file_acc.deci_size += len;
    file_acc.deci_pos += len;
}
void deci_writebyte(size_t len)
{
    //file_acc.deci_buffer[file_acc.deci_pos] = len;
    memcpy(file_acc.deci_buffer + file_acc.deci_pos, &len, 1);
    file_acc.deci_size ++;
    file_acc.deci_pos ++;
}
long get_data_value()
{
    long ldata = 0;
    stack_cell& cell = generator_stack.back();
    std::vector<std::pair<std::string, size_t>>::iterator iter;
    for(iter = cell.values.begin(); iter != cell.values.end(); iter++)
    {
        switch (iter->second) {
            case 1:
                ldata = stringToNum<short>(iter->first);
                break;
            case 2:
                ldata = stringToNum<short>(iter->first);
                break;
            case 4:
                ldata = stringToNum<long>(iter->first);
                break;
            default:
                break;
        }
    }
    return ldata;
}
void write_deci_bytes(bool data = false, bool stru = false, bool number = false, bool xxxx = false, long xxxxvalue = 0, bool number_data = false)
{
    stack_cell& cell = generator_stack.back();
    std::vector<std::pair<std::string, size_t>>::iterator iter;
    //byte cdata = 0;
   // short sdata = 0;
    long ldata = 0;
    std::string pf = ":";
    std::string sdata = "D";
    std::string sstru = "S";
    std::string snumb = "N";
    std::string sxxxx = "X";
    //printf("cell size is %lu\n", cell.values.size());
    if(cell.values.size() == 0 && data && xxxxvalue == 0)
    {
        size_t bytedata = 0;
        deci_writebyte(bytedata);
    }
    for(iter = cell.values.begin(); iter != cell.values.end(); iter++)
    {
        switch (iter->second) {
            case 1:
                ldata = stringToNum<short>(iter->first);
                break;
            case 2:
                ldata = stringToNum<short>(iter->first);
                break;
            case 4:
                ldata = stringToNum<long>(iter->first);
                break;
            default:
                break;
        }
        if(!number)
        {
            if(iter->first.compare("0") == 0)
            {
                //memcpy(file_acc.deci_buffer + file_acc.deci_pos, &name, name.size());
                //0
                size_t bytedata = 0;
                deci_writebyte(bytedata);
            }
            else
            {
                size_t bytedata = 1;
                //1
                deci_writebyte(bytedata);
                if(data)
                {
                    memcpy_decistr(pf);//:
                  //  printf("%x ", file_acc.deci_buffer[file_acc.deci_pos - 1]);
                    deci_writebyte(iter->second);//data-length
                    memcpy_decistr(sdata);//data
                   
                    memcpy_decidata(ldata, iter->second);//data
                            
                }
                else if(stru)
                {
                    memcpy_decistr(pf);//:
                    deci_writebyte(iter->second);//data-length
                    memcpy_decistr(sstru);//stru
                    memcpy_decidata(ldata, iter->second);//data
                }
                else if(xxxx)
                {
                    memcpy_decistr(pf);//:
                    deci_writebyte(iter->second);//data-length
                    memcpy_decistr(sxxxx);//sxxxx
                    memcpy_decidata(ldata, iter->second);//data
                }
                
            }
        }
        else
        {

            size_t bytedata = 4;
            deci_writebyte(bytedata);//4
            memcpy_decistr(pf);//:
            deci_writebyte(iter->second);//data-length
            memcpy_decistr(snumb);//numb
            long sizeofnumber = cell.values.size();
            if(xxxxvalue != 0)
            {
                sizeofnumber = xxxxvalue;
            }
            if(number_data)
            {
                memcpy_decidata(ldata, 4);
            }
            else
            {
                memcpy_decidata(sizeofnumber, 4);
                break;
            }
            
            
               
        }
        
    }
    
     
}
void os_2_table()
{
    stack_cell& cell = generator_stack.back();
    if(strcmp(cell.name, "version_tos") == 0)
    {
        std::string name = "OS_2";
        memcpy_decistr(name);
        write_deci_bytes();
        
    }
    else
    {
        write_deci_bytes();
    }
   // printf("os_2_table is os_2 \n");
}
void write_deci_bytess_sw(int num)
{
    switch (num) {
        case 0:
            write_deci_bytes();//0 1
            break;
        case 1:
            write_deci_bytes(true);//data
            break;
        case 2:
            write_deci_bytes(false, true);//stru
            break;
        case 3:
            write_deci_bytes(false, false, true, false, 0, true);//number
            break;
        case 4:
            write_deci_bytes(false, false, false, true);//xxxx
            break;
            
        default:
            break;
    }
}
long maxp_numGlyphs = 0;
long Glyph_numGlyphs = 0;
long g_cmap_index = 0;
long htmx_index = 0;
long name_index = 0;
long post_index = 0;
long tableindex = 0;
long numTables_d = 0;
bool nametodata(std::string nametable, std::string name, std::vector<std::pair<std::string, int>>  struct_name, size_t*offset_data, std::map<int, long> &get_data)
{
   std::vector<std::pair<std::string, int>>::iterator name_iter;
    
    size_t struct_size = struct_name.size();
    int i = 0;
    if(nametable.compare("glyf") == 0)
    {
       
        i = (Glyph_numGlyphs * 7) ;
    }
    
   
    for(name_iter = struct_name.begin(); name_iter != struct_name.end(); name_iter ++)
    {
        if(nametable.compare("loca") == 0)
        {
            i = name_iter->second;
        }
       
        if(name.compare(name_iter->first) == 0)
        {
            if(generate_parsedata)
            {
                if(nametable.compare("cmap") == 0)
                {
                    
                    i = g_cmap_index;
                    g_cmap_index ++;
                }
                if(nametable.compare("hmtx") == 0)
                {
                    i = htmx_index;
                }
                if(nametable.compare("name") == 0)
                {
                    i = name_index;
                    name_index ++;
                }
                if(nametable.compare("post") == 0)
                {
                    i = post_index;
                    post_index ++;
                }
                get_data = decode_table(nametable, offset_data, i);
                return true;
            }
            else
            {
                write_deci_bytess_sw(name_iter->second);
                return false;
            }
        }
      //  if(nametable.compare("cmap") != 0)
       // {
            i ++;
       // }
        
    }
}

bool head_table(std::map<int, long> &get_data)
{
    size_t offset_data = 0;
    offset_data = file_acc.table_offset[0];
    bool get_data_succeful = false;
   
    std::string name = "head";
    std::vector<std::pair<std::string, int>> struct_name;
    
    struct_name.push_back(std::pair<std::string, int>("version", 1));
    struct_name.push_back(std::pair<std::string, int>("fontRevision", 0));
    struct_name.push_back(std::pair<std::string, int>("checkSumAdjustment", 0));
    struct_name.push_back(std::pair<std::string, int>("magicNumber", 0));
    struct_name.push_back(std::pair<std::string, int>("flags", 0));
    struct_name.push_back(std::pair<std::string, int>("unitsPerEm", 0));
    struct_name.push_back(std::pair<std::string, int>("created", 0));
    struct_name.push_back(std::pair<std::string, int>("modified", 0));
    struct_name.push_back(std::pair<std::string, int>("xMin", 0));
    struct_name.push_back(std::pair<std::string, int>("yMin", 0));
    struct_name.push_back(std::pair<std::string, int>("xMax", 0));
    struct_name.push_back(std::pair<std::string, int>("yMax", 0));
    struct_name.push_back(std::pair<std::string, int>("macStyle", 0));
    struct_name.push_back(std::pair<std::string, int>("lowestRecPPEM", 0));
    struct_name.push_back(std::pair<std::string, int>("fontDirectionHint", 0));
    struct_name.push_back(std::pair<std::string, int>("indexToLocFormat", 1));
    struct_name.push_back(std::pair<std::string, int>("glyphDataFormat", 0));
   // std::string version = "version";
    
    stack_cell& cell = generator_stack.back();
    if(strcmp(cell.name, "version") == 0)
    {
        if(!generate_parsedata)
        {
            memcpy_decistr(name);
        }
        
    }
    if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
    {
            get_data_succeful = true;
    }
    
   
  //  printf("head_table head\n");
    return get_data_succeful;
}

bool maxp_table(std::map<int, long> &get_data)
{
    size_t offset_data = 0;
    offset_data = file_acc.table_offset[1];
    bool get_data_succeful = false;
   
    std::string name = "maxp";
    std::vector<std::pair<std::string, int>> struct_name;
    
    struct_name.push_back(std::pair<std::string, int>("version", 1));
    struct_name.push_back(std::pair<std::string, int>("numGlyphs", 2));
    struct_name.push_back(std::pair<std::string, int>("maxPoints", 0));
    struct_name.push_back(std::pair<std::string, int>("maxContours", 0));
    struct_name.push_back(std::pair<std::string, int>("maxCompositePoints", 0));
    struct_name.push_back(std::pair<std::string, int>("maxCompositeContours", 0));
    struct_name.push_back(std::pair<std::string, int>("maxTwilightPoints", 0));
    struct_name.push_back(std::pair<std::string, int>("maxStorage", 0));
    struct_name.push_back(std::pair<std::string, int>("maxFunctionDefs", 0));
    struct_name.push_back(std::pair<std::string, int>("maxInstructionDefs", 0));
    struct_name.push_back(std::pair<std::string, int>("maxStackElements", 0));
    struct_name.push_back(std::pair<std::string, int>("maxSizeOfInstructions", 0));
    struct_name.push_back(std::pair<std::string, int>("maxComponentElements", 0));
    struct_name.push_back(std::pair<std::string, int>("maxComponentDepth", 0));
    
    stack_cell& cell = generator_stack.back();
    if(strcmp(cell.name, "version") == 0)
    {
        if(!generate_parsedata)
        {
            memcpy_decistr(name);
        }
        
    }
    if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
    {
            get_data_succeful = true;
    }
    
    
    
    if(strcmp(cell.name, "numGlyphs") == 0 && !generate_parsedata)
    {
       // write_deci_bytes(false, true, false);//srtuc
        maxp_numGlyphs = get_data_value();
    }
   
    return get_data_succeful;
}
bool loca_table(std::map<int, long> &get_data)
{
    size_t offset_data = 0;
    offset_data = file_acc.table_offset[4]; // 4 loca
    bool get_data_succeful = false;
   
    std::string name = "loca";
    std::vector<std::pair<std::string, int>> struct_name;
    
    struct_name.push_back(std::pair<std::string, int>("offsets", file_acc.deci_number));
    
    stack_cell& cell = generator_stack.back();
    if(!generate_parsedata && !file_acc.deci_number)
    {
        memcpy_decistr(name);
        write_deci_bytes(false, false, false, true, 0, false);//number loca'data decide to glyf's data-length
    }
    else
    {
        if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
        {
                get_data_succeful = true;
        }
    }
    
    file_acc.deci_number ++;
    return get_data_succeful;
   // printf("loca_table loca\n");
}

long numberOfContoursl_gloab = 0;
bool glyf_table(std::map<int, long> &get_data)
{
    size_t offset_data = 0;
    offset_data = file_acc.table_offset[3]; // 4 glyf
    bool get_data_succeful = false;
   
    std::string name = "glyf";
    std::vector<std::pair<std::string, int>> struct_name;
    
    struct_name.push_back(std::pair<std::string, int>("numberOfContoursl", 2));
    struct_name.push_back(std::pair<std::string, int>("xMin", 0));
    struct_name.push_back(std::pair<std::string, int>("yMin", 0));
    struct_name.push_back(std::pair<std::string, int>("xMax", 0));
    struct_name.push_back(std::pair<std::string, int>("yMax", 0));
    
    struct_name.push_back(std::pair<std::string, int>("endPtsOfContoursl", 2));
    struct_name.push_back(std::pair<std::string, int>("instructionLengthl", 2));
    
    stack_cell& cell = generator_stack.back();
    //printf("cell.name:%s\n", cell.name);
    if(strcmp(cell.name, "numberOfContoursl") == 0 && !generate_parsedata)
    {
       // std::string name = "glyf";
        memcpy_decistr(name);
       // write_deci_bytes(false, true);//struc
        numberOfContoursl_gloab = get_data_value();
    }
    if(strcmp(cell.name, "endPtsOfContoursl") != 0)
    {
        if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
        {
                get_data_succeful = true;
        }
        if(strcmp(cell.name, "numberOfContoursl") == 0 && generate_parsedata)
        {
            std::map<int, long>::iterator get_data_iter;//
            
            get_data_iter = get_data.begin();
            numberOfContoursl_gloab = get_data_iter->second;
            //numberOfContoursl_gloab ++;
        }
    }
    else
    {
        numberOfContoursl_gloab --;
        if(numberOfContoursl_gloab == 0)
        {
            if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
            {
                    get_data_succeful = true;
            }
        }
    }
    
    
    if(strcmp(cell.name, "instructionLengthl") == 0 && generate_parsedata)
    {
        Glyph_numGlyphs ++;
    }

    //printf("glyf_table glyf\n");
    return get_data_succeful;
}
USHORT cmap_numTables = 0;
bool cmap_globle = false;
bool cmap_table(std::map<int, long> &get_data)
{
    size_t offset_data = 0;
    offset_data = file_acc.table_offset[8]; // 4 cmap
    bool get_data_succeful = false;
   
    std::string name = "cmap";
    std::vector<std::pair<std::string, int>> struct_name;
    
    struct_name.push_back(std::pair<std::string, int>("version_cmap", 4));
    struct_name.push_back(std::pair<std::string, int>("numTables", 2));
    
    struct_name.push_back(std::pair<std::string, int>("platformID", 1));
    struct_name.push_back(std::pair<std::string, int>("encodingID", 1));
    struct_name.push_back(std::pair<std::string, int>("offset", 0));
    struct_name.push_back(std::pair<std::string, int>("format", 4));
    
    stack_cell& cell = generator_stack.back();
    if(strcmp(cell.name, "version_cmap") == 0 && !generate_parsedata)
    {
      //  std::string name = "cmap";
        memcpy_decistr(name);
        //write_deci_bytes(false, false, false, true);//xxxx
    }
    if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
    {
            get_data_succeful = true;
    }
   // printf("cmap_table cmap\n");
    
    if(strcmp(cell.name, "numTables") == 0)
    {
        cmap_globle = true;
       // write_deci_bytes(false, true);//stru
        if(generate_parsedata)
        {
            std::map<int, long>::iterator get_data_iter;//
            
            get_data_iter = get_data.begin();
            cmap_numTables = get_data_iter->second;
            
        }
        else
        {
            cmap_numTables = get_data_value();
        }
        
       
    }
   
    else if(strcmp(cell.name, "format") == 0)
    {
       // write_deci_bytes(false, false, false, true, 0, false);//xxxx
        if(cmap_numTables != 1)
        {
            cmap_numTables --;
        }
        else
        {
           // cmap_numTables --;
            cmap_globle = false;
        }
    }
    return get_data_succeful;
  
}

bool cmap_table_0(std::map<int, long> &get_data)
{
    size_t offset_data = 0;
    offset_data = file_acc.table_offset[8]; // 4 cmap
    bool get_data_succeful = false;
   
    std::string name = "cmap";
    std::vector<std::pair<std::string, int>> struct_name;
    
    struct_name.push_back(std::pair<std::string, int>("length", 4));
    struct_name.push_back(std::pair<std::string, int>("language", 1));
    //struct_name.push_back(std::pair<std::string, int>("glyphIdArray", 3));
    
    
    stack_cell& cell = generator_stack.back();
    //printf("cmap_table_0 cmap\n");
    if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
    {
            get_data_succeful = true;
    }
    return get_data_succeful;
    
   
}
bool cmap_table_2(std::map<int, long> &get_data)
{
    size_t offset_data = 0;
    offset_data = file_acc.table_offset[8]; // 4 cmap
    bool get_data_succeful = false;
   
    std::string name = "cmap";
    std::vector<std::pair<std::string, int>> struct_name;
    
    struct_name.push_back(std::pair<std::string, int>("length", 4));
    struct_name.push_back(std::pair<std::string, int>("language", 1));
    
    stack_cell& cell = generator_stack.back();
   // printf("cmap_table_2 cmap\n");
    if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
    {
            get_data_succeful = true;
    }
    return get_data_succeful;
   
}
bool cmap4 = false;
bool cmap_table_4(std::map<int, long> &get_data)
{
    size_t offset_data = 0;
    offset_data = file_acc.table_offset[8]; // 4 cmap
    bool get_data_succeful = false;
   
    std::string name = "cmap";
    std::vector<std::pair<std::string, int>> struct_name;
    
    struct_name.push_back(std::pair<std::string, int>("length", 4));
    struct_name.push_back(std::pair<std::string, int>("language", 1));
    struct_name.push_back(std::pair<std::string, int>("segCountX2", 2));
    struct_name.push_back(std::pair<std::string, int>("searchRange", 1));
    struct_name.push_back(std::pair<std::string, int>("entrySelector", 1));
    struct_name.push_back(std::pair<std::string, int>("rangeShift", 4));
    
    stack_cell& cell = generator_stack.back();
    //printf("cmap_table_4 cmap\n");
    if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
    {
            get_data_succeful = true;
    }
    return get_data_succeful;
   
 
}
bool cmap_table_6(std::map<int, long> &get_data)
{
    size_t offset_data = 0;
    offset_data = file_acc.table_offset[8]; // 4 cmap
    bool get_data_succeful = false;
   
    std::string name = "cmap";
    std::vector<std::pair<std::string, int>> struct_name;
    
    struct_name.push_back(std::pair<std::string, int>("length", 4));
    struct_name.push_back(std::pair<std::string, int>("language", 1));
    struct_name.push_back(std::pair<std::string, int>("firstCode", 1));
    struct_name.push_back(std::pair<std::string, int>("entryCount", 2));
    
    stack_cell& cell = generator_stack.back();
    //printf("cmap_table_6 cmap\n");
    if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
    {
            get_data_succeful = true;
    }
    return get_data_succeful;
    
   
}
bool cmap_table_8(std::map<int, long> &get_data)
{
    size_t offset_data = 0;
    offset_data = file_acc.table_offset[8]; // 4 cmap
    bool get_data_succeful = false;
   
    std::string name = "cmap";
    std::vector<std::pair<std::string, int>> struct_name;
    
    struct_name.push_back(std::pair<std::string, int>("length", 4));
    struct_name.push_back(std::pair<std::string, int>("reserved", 1));
    struct_name.push_back(std::pair<std::string, int>("language", 1));
    struct_name.push_back(std::pair<std::string, int>("nGroups", 2));
    
    stack_cell& cell = generator_stack.back();
    //printf("cmap_table_8 cmap\n");
    if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
    {
            get_data_succeful = true;
    }
    return get_data_succeful;
}
bool cmap_table_12(std::map<int, long> &get_data)
{
    size_t offset_data = 0;
    offset_data = file_acc.table_offset[8]; // 4 cmap
    bool get_data_succeful = false;
   
    std::string name = "cmap";
    std::vector<std::pair<std::string, int>> struct_name;
    
    struct_name.push_back(std::pair<std::string, int>("length", 4));
    struct_name.push_back(std::pair<std::string, int>("reserved", 1));
    struct_name.push_back(std::pair<std::string, int>("language", 1));
    struct_name.push_back(std::pair<std::string, int>("nGroups", 2));
    
    stack_cell& cell = generator_stack.back();
   // printf("cmap_table_12 cmap\n");
    if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
    {
            get_data_succeful = true;
    }
    return get_data_succeful;
}

bool hhea_table(std::map<int, long> &get_data)
{
    size_t offset_data = 0;
    offset_data = file_acc.table_offset[6]; // 6 hhea
    bool get_data_succeful = false;
   
    std::string name = "hhea";
    std::vector<std::pair<std::string, int>> struct_name;
    
    struct_name.push_back(std::pair<std::string, int>("version", 4));
    struct_name.push_back(std::pair<std::string, int>("Ascender", 1));
    struct_name.push_back(std::pair<std::string, int>("Descender", 1));
    struct_name.push_back(std::pair<std::string, int>("LineGap", 1));
    struct_name.push_back(std::pair<std::string, int>("advanceWidthMax", 1));
    struct_name.push_back(std::pair<std::string, int>("minLeftSideBearing", 1));
    struct_name.push_back(std::pair<std::string, int>("xMaxExtent", 1));
    struct_name.push_back(std::pair<std::string, int>("caretSlopeRise", 1));
    
    struct_name.push_back(std::pair<std::string, int>("caretSlopeRun", 1));
    struct_name.push_back(std::pair<std::string, int>("caretOffset", 1));
    struct_name.push_back(std::pair<std::string, int>("reserved", 1));
    struct_name.push_back(std::pair<std::string, int>("reserved1", 1));
    struct_name.push_back(std::pair<std::string, int>("reserved2", 1));
    struct_name.push_back(std::pair<std::string, int>("reserved3", 1));
    struct_name.push_back(std::pair<std::string, int>("metricDataFormat", 1));
    struct_name.push_back(std::pair<std::string, int>("numberOfHMetrics", 2));
    
    stack_cell& cell = generator_stack.back();
    
    if(strcmp(cell.name, "version") == 0 && !generate_parsedata)
    {
       // std::string name = "hhea";
        memcpy_decistr(name);
      //  write_deci_bytes(false, false, false, true);//xxxx
    }
    if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
    {
            get_data_succeful = true;
    }
   // if(strcmp(cell.name, "numberOfHMetrics") == 0)
    htmx_index = 0;
    return get_data_succeful;
    
}
bool hmtx_table(std::map<int, long> &get_data)
{
    size_t offset_data = 0;
    offset_data = file_acc.table_offset[5]; // 5 hmtx
    bool get_data_succeful = false;
   
    std::string name = "hmtx";
    std::vector<std::pair<std::string, int>> struct_name;
    
    struct_name.push_back(std::pair<std::string, int>("advanceWidth", 1));
    struct_name.push_back(std::pair<std::string, int>("lsb", 1));
    struct_name.push_back(std::pair<std::string, int>("leftSideBearing", 3));
    
    stack_cell& cell = generator_stack.back();
    if(!generate_parsedata && htmx_index == 0)
    {
        //std::string name = "hmtx";
        memcpy_decistr(name);
       // write_deci_bytes(true);//data
        
    }
    if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
    {
            get_data_succeful = true;
    }
   // if(generate_parsedata)
    //{
        htmx_index ++;
    //}
    return get_data_succeful;
}
bool name_table(std::map<int, long> &get_data)
{
    size_t offset_data = 0;
    offset_data = file_acc.table_offset[2]; // 2 name
    bool get_data_succeful = false;
   
    std::string name = "name";
    std::vector<std::pair<std::string, int>> struct_name;
    
    struct_name.push_back(std::pair<std::string, int>("format", 4));
    struct_name.push_back(std::pair<std::string, int>("count", 2));
    struct_name.push_back(std::pair<std::string, int>("stringOffset", 1));
    
    struct_name.push_back(std::pair<std::string, int>("platformID", 1));
    struct_name.push_back(std::pair<std::string, int>("encodingID", 1));
    struct_name.push_back(std::pair<std::string, int>("languageID", 1));
    struct_name.push_back(std::pair<std::string, int>("nameID", 4));
    struct_name.push_back(std::pair<std::string, int>("length", 2));
    struct_name.push_back(std::pair<std::string, int>("offset", 1));
    
    
    stack_cell& cell = generator_stack.back();
   // printf("cmap_table_2 cmap\n");
    if(strcmp(cell.name, "format") == 0 && !generate_parsedata)
    {
        //std::string name = "name";
        memcpy_decistr(name);
       // write_deci_bytes(false, false, false, true, 0, false);//xxxx
    }
    if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
    {
            get_data_succeful = true;
    }
   
    
    return get_data_succeful;
}
//long post_version = 0;
bool post_table(std::map<int, long> &get_data)
{
    size_t offset_data = 0;
    offset_data = file_acc.table_offset[7]; // 7 post
    bool get_data_succeful = false;
   
    std::string name = "post";
    std::vector<std::pair<std::string, int>> struct_name;
    
    struct_name.push_back(std::pair<std::string, int>("version", 4));
    struct_name.push_back(std::pair<std::string, int>("italicAngle", 1));
    struct_name.push_back(std::pair<std::string, int>("underlinePosition", 1));
    struct_name.push_back(std::pair<std::string, int>("underlineThickness", 1));
    struct_name.push_back(std::pair<std::string, int>("isFixedPitch", 1));
    struct_name.push_back(std::pair<std::string, int>("minMemType42", 1));
    struct_name.push_back(std::pair<std::string, int>("maxMemType42", 1));
    struct_name.push_back(std::pair<std::string, int>("minMemType1", 1));
    struct_name.push_back(std::pair<std::string, int>("maxMemType1", 1));
    
    struct_name.push_back(std::pair<std::string, int>("numberOfGlyphs", 2));
    struct_name.push_back(std::pair<std::string, int>("length", 2));
    
    stack_cell& cell = generator_stack.back();
    if(strcmp(cell.name, "version") == 0 && !generate_parsedata)
    {
        //std::string name = "post";
        memcpy_decistr(name);
        //write_deci_bytes(false, false, false, true);//xxxx
        //post_version = get_data_value();
    }
    if(nametodata(name, std::string(cell.name), struct_name, &offset_data, get_data))
    {
            get_data_succeful = true;
    }
   
   
    return get_data_succeful;
}
void getdeci_typedata(std::string type_name, long data, std::map<int, long> &ret_data)
{
    if(type_name.compare("D") == 0)
    {
        ret_data[0] = data;
    }
    else if(type_name.compare("N") == 0)
    {
        ret_data[1] = data;
    }
    else if(type_name.compare("S") == 0)
    {
        ret_data[2] = data;
    }
    else if(type_name.compare("X") == 0)
    {
        ret_data[3] = data;
    }
}
std::map<int, long> printfdata(size_t *offset_data)
{
    int i = 0;
    long data = 0;
    int type_n;
    std::map<int, long> ret_data;
    std::string type_name;
    switch (file_acc.deci_buffer[*offset_data]) {
        case 1:
           // printf("%0.2x", file_acc.deci_buffer[*offset_data]);
            *offset_data +=1;
          
            if(file_acc.deci_buffer[*offset_data] == 0x3a)
            {
               // printf(":");
                *offset_data +=1;
                //data-length
                //printf("%0.2x", file_acc.deci_buffer[*offset_data]);
                size_t data_length = file_acc.deci_buffer[*offset_data];
                *offset_data +=1;
              
               // printf("%c", file_acc.deci_buffer[*offset_data]);
                type_name = file_acc.deci_buffer[*offset_data];
               
                
                //printf(" ");
                *offset_data +=1;
                //swap_bytes2(&file_acc.deci_buffer[*offset_data], data_length);
               /* for(i = 0; i < data_length; i ++)
                {
                    printf("%0.2x", file_acc.deci_buffer[*offset_data + i]);
                    
                }*/
                if(data_length > 4)
                {
                    return ret_data;
                }
                memcpy(&data, &file_acc.deci_buffer[*offset_data], data_length);
                getdeci_typedata(type_name, data, ret_data);
               // printf(" ");
                *offset_data += data_length;
              
                
            }
            else
            {
               
                ret_data[4] = 1;
               // printf(" ");
            }
            break;
        case 0:
           // printf("%0.2x", file_acc.deci_buffer[*offset_data]);
            *offset_data +=1;
           
            ret_data[5] = 0;
            //printf(" ");
            break;
        case 4:
            //printf("%0.2x", file_acc.deci_buffer[*offset_data]);
            *offset_data +=1;
           // printf(":");
            *offset_data +=1;
           // printf("%0.2x", file_acc.deci_buffer[*offset_data]);
            size_t data_length = file_acc.deci_buffer[*offset_data];
            *offset_data +=1;
           
            //printf("%c", file_acc.deci_buffer[*offset_data]);
            type_name = file_acc.deci_buffer[*offset_data];
           // printf(" ");
            *offset_data +=1;
           // swap_bytes2(&file_acc.deci_buffer[*offset_data], data_length);
            /*for(i = 0; i < 4; i ++)
            {
                printf("%0.2x", file_acc.deci_buffer[*offset_data + i]);
                
            }*/
            memcpy(&data, &file_acc.deci_buffer[*offset_data], data_length);
            getdeci_typedata(type_name, data, ret_data);
           // printf(" ");
            *offset_data += 4;
            break;
            
    
    }
    return ret_data;
    
}
std::map<int, long> decode_head(size_t *offset_data, int index_data)
{
    int i = 0;
    std::map<int, long> data;
    
    for(i = 0; i < 17; i ++)
    {
        data = printfdata(offset_data);
     
        if(i == index_data)
        {
            return data;
        }
    }
   // printf("\n");
    data.clear();
    return data;
    
}
std::map<int, long> decode_maxp(size_t *offset_data, int index_data)
{
    int i = 0;
    std::map<int, long> data;
    std::map<int, long>::iterator data_iter;
    data = printfdata(offset_data);
    if(index_data == 0)
    {
        return data;
    }
    if(maxp_numGlyphs == 0)
    {
        data = printfdata(offset_data);
        data_iter = data.begin();
        maxp_numGlyphs = data_iter->second;
    }
    else
    {
        data = printfdata(offset_data);
    }
    if(index_data == 1)
    {
        return data;
    }
    for(i = 0; i < 13; i ++)
    {
        data = printfdata(offset_data);
    
        if(index_data == (i + 2))
        {
            return data;
        }
    }
    //printf("\n");
    data.clear();
    return data;
        
}
std::map<int, long> decode_loca(size_t *offset_data, int index_data)
{
    int i = 0;
    std::map<int, long> data;
            
    for(i = 0; i < (maxp_numGlyphs + 1); i ++)
    {
        data = printfdata(offset_data);
      
        if(index_data == i)
        {
            return data;
        }
    }
   // printf("\n");
    data.clear();
    return data;
            
}
std::map<int, long> decode_glyf(size_t *offset_data, int index_data)
{
    int i = 0, y = 0;
    std::map<int, long> data;
                
    for(i = 0; i < (maxp_numGlyphs + 1); i ++)
    {
        for(y = 0; y < 7; y ++)
        {
            data = printfdata(offset_data);
           
            if(index_data == (i * 7 + y))
            {
                return data;
            }
        }
        *offset_data += 4;
      //  printf("\n");
    }
    *offset_data -= 4;
   // printf("\n");
    data.clear();
    return data;
    
                
}

std::map<int, long> decode_cmap0(size_t *offset_data, int cmap_index, int index_data)
{
    int i = 0;
    std::map<int, long> data;
    for(i = 0; i < 2; i ++)
    {
        data = printfdata(offset_data);
        if(index_data == cmap_index + i)
        {
            return data;
        }
    }
    data.clear();
    return data;
}
std::map<int, long> decode_cmap2(size_t *offset_data, int cmap_index, int index_data)
{
    int i = 0;
    std::map<int, long> data;
    for(i = 0; i < 2; i ++)
    {
        data = printfdata(offset_data);
        if(index_data == cmap_index + i)
        {
            return data;
        }
    }
    data.clear();
    return data;
}
std::map<int, long> decode_cmap4(size_t *offset_data, int cmap_index, int index_data)
{
    int i = 0;
    std::map<int, long> data;
    for(i = 0; i < 6; i ++)
    {
        data = printfdata(offset_data);
        if(index_data == cmap_index + i)
        {
            return data;
        }
    }
    data.clear();
    return data;
}
std::map<int, long> decode_cmap6(size_t *offset_data, int cmap_index, int index_data)
{
    int i = 0;
    std::map<int, long> data;
    for(i = 0; i < 4; i ++)
    {
        data = printfdata(offset_data);
        if(index_data == cmap_index + i)
        {
            return data;
        }
    }
    data.clear();
    return data;
}
std::map<int, long> decode_cmap8(size_t *offset_data, int cmap_index, int index_data)
{
    int i = 0;
    std::map<int, long> data;
    for(i = 0; i < 4; i ++)
    {
        data = printfdata(offset_data);
        if(index_data == cmap_index + i)
        {
            return data;
        }
    }
    data.clear();
    return data;
}
std::map<int, long> decode_cmap12(size_t *offset_data, int cmap_index, int index_data)
{
    int i = 0;
    std::map<int, long> data;
    for(i = 0; i < 4; i ++)
    {
        data = printfdata(offset_data);
        if(index_data == cmap_index + i)
        {
            return data;
        }
    }
    data.clear();
    return data;
}
std::map<int, long> decode_cmap(size_t *offset_data, int index_data)
{
    long numbertables = 0;
    long cmap_format = 20;
    int n = 0, i = 0;
    std::map<int, long> data;
    std::map<int, long>::iterator data_iter;
    int cmap_index = 2;
    //printf("cmap:\n");
  //  printf("version\n");
    data = printfdata(offset_data);
    if(index_data == 0)
    {
        return data;
    }
   // printf("numtables\n");
    data = printfdata(offset_data);
    data_iter = data.begin();
    numbertables = data_iter->second;
    if(index_data == 1)
    {
        //return numbertables;
        return data;
    }
    for(n = 0; n < numbertables; n++)
    {
        for(i = 0; i < 3; i ++)
        {
            // printf("platformID\n");
             data = printfdata(offset_data);
             //printf("encodingID\n");
             
            // printf("offset\n");
            if(index_data == cmap_index + i)
            {
                return data;
            }
             
        }
       
        //printf("format\n");
        cmap_index += 3;
        data = printfdata(offset_data);
        data_iter = data.begin();
        cmap_format = data_iter->second;
        if(index_data == cmap_index)
        {
            return data;
        }
        
        cmap_index ++;
        switch (cmap_format) {
            case 0:
               // printf("\ndecode_cmap0:\n");
                data = decode_cmap0(offset_data, cmap_index, index_data);
               // printf("\n");
                cmap_index += 2;
                break;
            case 2:
              //  printf("\ndecode_cmap2:\n");
                data = decode_cmap2(offset_data, cmap_index, index_data);
               // printf("\n");
                cmap_index += 2;
                break;
            case 4:
                //printf("\ndecode_cmap4:\n");
                data = decode_cmap4(offset_data, cmap_index, index_data);
               // printf("\n");
                cmap_index += 6;
                break;
            case 6:
               // printf("\ndecode_cmap6:\n");
                data = decode_cmap6(offset_data, cmap_index, index_data);
               // printf("\n");
                cmap_index += 4;
                break;
            case 8:
               // printf("\ndecode_cmap8:\n");
                data = decode_cmap8(offset_data, cmap_index, index_data);
               // printf("\n");
                cmap_index += 4;
                break;
            case 12:
               // printf("\ndecode_cmap12:\n");
                data = decode_cmap12(offset_data, cmap_index, index_data);
               // printf("\n");
                cmap_index += 4;
                break;
                
            default:
                break;
        }
        if(data.size() > 0)
        {
            return data;
        }
    }
    return data;
    
}
long number_metrics = 0;
std::map<int, long>  decode_hhea(size_t *offset_data, int index_data)
{
    int i = 0;
    std::map<int, long> data;
    std::map<int, long>::iterator data_iter;
    for(i = 0; i < 15; i ++)
    {
        data = printfdata(offset_data);
        if(index_data == i)
        {
            return data;
        }
    }
    data = printfdata(offset_data);
    data_iter = data.begin();
    number_metrics = data_iter->second;
    if(index_data == 15)
    {
        return data;
    }
    data.clear();
    return data;
}
std::map<int, long> decode_hmtx(size_t *offset_data, int index_data)
{
    int i = 0, y = 0;
    std::map<int, long> data;
    std::map<int, long>::iterator data_iter;
    for(y = 0; y < number_metrics; y ++)
    {
        for(i = 0; i < 2; i ++)
        {
            data = printfdata(offset_data);
            if(index_data == (y * 2 + i))
            {
                return data;
            }
        }
       // *offset_data += 4;
    }
   // *offset_data -= 4;
    size_t oldoffsetdata = *offset_data;
    data = printfdata(offset_data);
    data_iter = data.begin();
    int length = number_metrics * 2;
    if(index_data == length)
    {
        return data;
    }
    while (data.size() > 0 && data_iter->first == 1)
    {
        length ++;
        oldoffsetdata = *offset_data;
        data = printfdata(offset_data);
        if(index_data == length)
        {
            return data;
        }
    }
    *offset_data = oldoffsetdata;
    
    
    data.clear();
    return data;
}
std::map<int, long> decode_name(size_t *offset_data, int index_data)
{
    int i = 0, y = 0;
    long namecout = 0;
    std::map<int, long> data;
    std::map<int, long>::iterator data_iter;
    for(i = 0; i < 3; i ++)
    {
        if(i == 1)
        {
            data = printfdata(offset_data);
            data_iter = data.begin();
            namecout = data_iter->second;
            //data = namecout;
        }
        else
        {
            data = printfdata(offset_data);
        }
        if(index_data == i)
        {
            return data;
        }
    }
    
   // printf("\n");
    for(i = 0; i < namecout; i ++)
    {
        for(y = 0; y < 6; y ++)
        {
            data =  printfdata(offset_data);
            if(index_data == (i * 6 + y + 3))
            {
                return data;
            }
        }
       // printf("\n");
    }
    data.clear();
    return data;
    //}
}
std::map<int, long> decode_post(size_t *offset_data, int index_data)
{
    long post_version = 0, i = 0;
    long post_numberglyps = 0;
    std::map<int, long> data;
    std::map<int, long>::iterator data_iter;
    data = printfdata(offset_data);
    data_iter = data.begin();
    post_version = data_iter->second;
    if(index_data == 0)
    {
        return data;
    }
    for(i = 0; i < 8; i ++)
    {
        data = printfdata(offset_data);
        if(index_data == i + 1)
        {
            return data;
        }
    }
    if(post_version == 0x00020000)
    {
        data = printfdata(offset_data);
        data_iter = data.begin();
        post_numberglyps = data_iter->second;
        if(index_data == 9)
        {
            return data;
        }
        for(i = 0; i < post_numberglyps; i ++)
        {
            data = printfdata(offset_data);
            if(index_data == 10 + i)
            {
                return data;
            }
        }
    }
    else if(post_version == 0x00025000)
    {
        data = printfdata(offset_data);
        data_iter = data.begin();
        post_numberglyps = data_iter->second;
        return data;
    }
    data.clear();
    return data;
}
// index_data 为获取数据 index
std::map<int, long> decode_table(std::string table, size_t *offset_data, int index_data)
{
    std::map<int, long> data;
    
    switch (STR2INT(table)) {
        case STR2INT("head"):
            //printf("head:");
            file_acc.table_offset[0] = *offset_data; //0 head
            data = decode_head(offset_data, index_data);
           // printf("\n");
            break;
        case STR2INT("OS/2"):
            //printf("OS/2:");
            break;
        case STR2INT("maxp"):
            //printf("maxp:");
            file_acc.table_offset[1] = *offset_data; //1 maxp
            data = decode_maxp(offset_data, index_data);
            break;
        case STR2INT("name"):
            //printf("\n name:\n");
            file_acc.table_offset[2] = *offset_data;
            data = decode_name(offset_data, index_data);
            break;
        case STR2INT("glyf"):
            //printf("glyf:\n");
            file_acc.table_offset[3] = *offset_data;
            data = decode_glyf(offset_data, index_data);
            break;
        case STR2INT("loca"):
            //printf("loca:\n");
            file_acc.table_offset[4] = *offset_data;
            data = decode_loca(offset_data, index_data);
            break;
        case STR2INT("hmtx"):
           // printf("\nhmtx:\n");
            file_acc.table_offset[5] = *offset_data;
            data = decode_hmtx(offset_data, index_data);
            break;
        case STR2INT("hhea"):
           // printf("\n hhea:\n");
            file_acc.table_offset[6] = *offset_data;
            data = decode_hhea(offset_data, index_data);
            break;
        case STR2INT("post"):
            //printf("post:\n");
            file_acc.table_offset[7] = *offset_data;
            data = decode_post(offset_data, index_data);
            
            break;
        case STR2INT("cmap"):
           // printf("cmap:\n");
            file_acc.table_offset[8] = *offset_data;
            data = decode_cmap(offset_data, index_data);
            break;
            
        default:
            break;
    }
    return data;
}
bool decode_data(int num, bool savedata)
{
    int i, y;
    bool succssful = false;
    size_t offset_data = 36;
    for(i = 0; i < num; i ++)
    {
        char head_name[4] = {0};
        memcpy(head_name, &file_acc.deci_buffer[offset_data], 4);
       
        offset_data += 4;
        std::string head(head_name,4);
        decode_table(head, &offset_data, -1);
        succssful = true;
       
    }
    if(savedata)
    {
        save_outttf(offset_data);
    }
    return succssful;
    
}


bool ttf_tables(std::map<int, long> &get_data)
{
    int count = generator_stack.size();
 
    for (int i = 0; i < count; i ++) {
    
        if(i == 2)
        {
            bool g_cmap = false;
           // printf("%s\n", generator_stack[i].name);
            if(cmap_globle)
             {
                 
                 g_cmap = cmap_table(get_data);
             }
              
           
            if(strcmp(generator_stack[i].name, "length") == 0)
             {
                // return tablelength(get_data);
                 ULONG tablelengthd = 0;
                 if(!generate_parsedata)
                 {
                     if(tableindex < 9)
                     {
                         tablelengthd = get_data_value();
                       
                            
                         memcpy(&file_acc.deci_buffer[tableindex * 4], &tablelengthd, 4);
                        
                         tableindex ++;
                     }
                 }
                 else
                 {
                    
                     if(tableindex < 9)
                     {
                         memcpy(&tablelengthd, &file_acc.deci_buffer[tableindex * 4], 4);
                         
                         tableindex ++;
                         get_data[3] = tablelengthd;
                         if(tablelengthd != 0)
                         {
                             return true;
                         }
                         else
                         {
                             return false;
                         }
                     }
                    
                     
                 }
                 
                
             }
           
                 if(strcmp(generator_stack[i].name, "format0") == 0)
                  {
                      g_cmap = cmap_table_0(get_data);
                  }
                 else if(strcmp(generator_stack[i].name, "format2") == 0)
                  {
                      g_cmap = cmap_table_2(get_data);
                  }
                 else if(strcmp(generator_stack[i].name, "format4") == 0)
                  {
                      g_cmap = cmap_table_4(get_data);
                  }
                 else if(strcmp(generator_stack[i].name, "format6") == 0)
                  {
                      g_cmap = cmap_table_6(get_data);
                  }
                 else if(strcmp(generator_stack[i].name, "format8") == 0)
                  {
                      g_cmap = cmap_table_8(get_data);
                  }
                 else if(strcmp(generator_stack[i].name, "format12") == 0)
                  {
                      g_cmap = cmap_table_12(get_data);
                  }
                 
             
            
             if(strcmp(generator_stack[i].name, "head") == 0)
            {
                return head_table(get_data);
                
            }
            else if(strcmp(generator_stack[i].name, "hhea") == 0)
            {
              //  decode_data(5, false);
                return hhea_table(get_data);
                
            }
            else if(strcmp(generator_stack[i].name, "hmtx") == 0)
            {
                
                return hmtx_table(get_data);
                
            }
            else if(strcmp(generator_stack[i].name, "name") == 0)
            {
                //decode_data(7, false);
                return name_table(get_data);
                
            }
            else if(strcmp(generator_stack[i].name, "post") == 0)
            {
               
                 return post_table(get_data);
                
                
            }
            else if(strcmp(generator_stack[i].name, "prep") == 0)
            {
                
                 //post_table();
                
                decode_data(9, true);
                
            }
            else if(strcmp(generator_stack[i].name, "OS_2") == 0)
            {
                os_2_table();
            }
            else if(strcmp(generator_stack[i].name, "cmap") == 0)
            {
               
                return cmap_table(get_data);
            }
            else if(strcmp(generator_stack[i].name, "maxp") == 0)
            {
               
                
                return maxp_table(get_data);
            }
            else if(strcmp(generator_stack[i].name, "loca") == 0)
            {
                
                return loca_table(get_data);
            }
            else if(strcmp(generator_stack[i].name, "glyf") == 0)
            {
               
                file_acc.deci_number = 0;
                return glyf_table(get_data);
            }
            else
            {
                return g_cmap;
            }
            
        }
    }
}
void end_generation() {
    if (!get_parse_tree && !generate_parsedata)
        return;
    stack_cell& back = generator_stack.back();
    stack_cell& prev = generator_stack[generator_stack.size() - 2];
   // printf("name is %s\n", back.name);
  //  printf("ulUnicodeRange1 sizeof  %d\n",sizeof(GENERATE_GVAR()));
    file_acc.rand_prev = file_acc.rand_pos;
    
    if (smart_mutation && back.rand_start == rand_start && (is_optional || strcmp(back.name, chunk_name) == 0)) {
        unsigned size = MAX_RAND_SIZE - file_acc.rand_pos;
        if (size > MAX_RAND_SIZE - (rand_end + 1))
            size = MAX_RAND_SIZE - (rand_end + 1);
        memmove(file_acc.rand_buffer + file_acc.rand_pos, file_acc.rand_buffer + (rand_end + 1), size);
        if (smart_swapping) {
            if (rand_start2 > rand_end)
                rand_start2 += file_acc.rand_pos - (rand_end + 1);
            rand_end2 += file_acc.rand_pos - (rand_end + 1);
        }
        rand_end = file_acc.rand_pos - 1;
    }
    if (smart_swapping && back.rand_start == rand_start2 && (is_optional || strcmp(back.name, chunk_name2) == 0)) {
        unsigned size = MAX_RAND_SIZE - file_acc.rand_pos;
        if (size > MAX_RAND_SIZE - (rand_end2 + 1))
            size = MAX_RAND_SIZE - (rand_end2 + 1);
        memmove(file_acc.rand_buffer + file_acc.rand_pos, file_acc.rand_buffer + (rand_end2 + 1), size);
        rand_end2 = file_acc.rand_pos - 1;
    }
    if (smart_abstraction && back.rand_start == rand_start && (is_optional || strcmp(back.name, chunk_name) == 0)) {
        if (following_rand_size > MAX_RAND_SIZE - file_acc.rand_pos)
            following_rand_size = MAX_RAND_SIZE - file_acc.rand_pos;
        memcpy(file_acc.rand_buffer + file_acc.rand_pos, following_rand_buffer, following_rand_size);
        smart_abstraction = false;
    }

    if (back.min < prev.min)
        prev.min = back.min;
    if (back.max > prev.max)
        prev.max = back.max;

    if (back.min > back.max) {
        back.min = file_acc.file_pos;
        back.max = file_acc.file_pos - 1;
    }
    if (debug_print && back.min <= back.max) {
        // printf("%u,%u, ", back.rand_start, file_acc.rand_pos - 1);
        printf("%u,%u,", back.min, back.max);
        bool first = true;
        stack_cell* parent = NULL;
        for (auto& cell : generator_stack) {
            if (first) {
                printf("%s", cell.name);
                first = false;
            } else {
                printf("~%s", cell.name);
                if (parent->counts[cell.name])
                    printf("_%u", parent->counts[cell.name]);
            }
            parent = &cell;
        }
        if (file_acc.rand_last != UINT_MAX)
            printf(",Appendable");
        if (back.rand_start != back.rand_start_real)
            printf(",Optional\n");
        else
            printf("\n");
    }
    
    if(!generate_parsedata)
    {
        std::map<int, long> get_data;
        //sunglin
        ttf_tables(get_data);
        
    }
    
    if (get_chunk && back.min == chunk_start && back.max == chunk_end) {
        printf("TARGET CHUNK FOUND\n");
        rand_start = back.rand_start;
        rand_end = file_acc.rand_pos - 1;
        is_optional = back.rand_start != back.rand_start_real;
        chunk_name = back.name;
        if (is_delete) {
            is_following = true;
        }
    }

    if (get_chunk && chunk_end == UINT_MAX && back.max == chunk_start - 1 && file_acc.rand_last != UINT_MAX) {
        printf("APPENDABLE CHUNK FOUND\n");
        rand_start = file_acc.rand_last;
        chunk_name = back.name;
    }
    
    if (get_chunk && chunk_end == UINT_MAX && back.min == chunk_start && back.rand_start != back.rand_start_real) {
        printf("OPTIONAL CHUNK FOUND\n");
        rand_start = back.rand_start;
        chunk_name = back.name;
    }
    
    if (get_all_chunks) {
        if (back.rand_start != back.rand_start_real) {
            optional_chunks.emplace_back(file_index, back.rand_start, file_acc.rand_pos - 1, variable_types[back.name].c_str(), back.name);
            insertion_points[file_index].emplace_back(back.rand_start, variable_types[back.name].c_str(), back.name);
            is_following = true;
            chunk_name = back.name;
            rand_start = back.rand_start;
            rand_end = file_acc.rand_pos - 1;
        } else if (file_acc.rand_pos > back.rand_start) {
            int size = non_optional_index[file_index].size();
            int i;
            for (i = 0; i < size; ++i) {
                if (strcmp(non_optional_index[file_index][i].type, variable_types[back.name].c_str()) == 0) {
                    ++non_optional_index[file_index][i].size;
                    break;
                }
            }
            if (i == size) {
                non_optional_index[file_index].emplace_back(variable_types[back.name].c_str(), non_optional_chunks[variable_types[back.name]].size(), 1);
            }
            non_optional_chunks[variable_types[back.name]].emplace_back(file_index, back.rand_start, file_acc.rand_pos - 1, variable_types[back.name].c_str(), back.name);
        }
        if (file_acc.rand_last != UINT_MAX) {
            insertion_points[file_index].emplace_back(file_acc.rand_last, variable_types[back.name].c_str(), back.name);
        }
    }

    file_acc.rand_last = UINT_MAX;

    ++prev.counts[back.name];
    generator_stack.pop_back();
}
double get_validity() {
    return (double)file_acc.parsed_file_size / (double)file_acc.final_file_size;
}


void start_generation(const char* name) {
    if (!get_parse_tree && !generate_parsedata)
        return;
    generator_stack.emplace_back(name, file_acc.rand_prev, file_acc.rand_pos);
    file_acc.rand_prev = file_acc.rand_pos;
    file_acc.rand_last = UINT_MAX;
    file_acc.deci_number = 0; //first 进入
}




char* get_bin_name(char* arg) {
    char* bin = strrchr(arg, '/');
    if (bin)
        return bin+1;
    return arg;
}


void set_parser() {
    file_acc.generate = false;
}
void set_Decision()
{
    file_acc.Decisiontree = true;
}
bool set_generator_parse(const char* filename)
{
    generate_parsedata = true;
    
    g_cmap_index = 0;
    htmx_index = 0;
    name_index = 0;
    post_index = 0;
    tableindex = 0;
    
    int file_fd;
   
    file_fd = open(filename, O_RDONLY);
    
    if (file_fd == -1) {
        perror(filename);
        exit(1);
    }
    
    struct stat st;
    if (fstat(file_fd, &st)) {
        perror("Failed to stat input file");
        exit(1);
    }
    ssize_t file_size = st.st_size;
    if (file_size > MAX_FILE_SIZE) {
        fprintf(stderr, "File size exceeds MAX_FILE_SIZE\n");
        file_size = MAX_FILE_SIZE;
        return  false;
    }
    ssize_t size = read(file_fd, file_acc.deci_buffer, file_size);
    if (size != file_size) {
        perror("Failed to read input file");
        exit(1);
    }
    return decode_data(9, false);
    
}
void set_generator() {
    file_acc.generate = true;
}


bool setup_input(const char* filename, const char* outdir) {
    bool success = true;
    debug_print = false; //guan
   // debug_print = true; //guan
    /*sunglin*/
    const char ch = '/';
     
    char* retc = strrchr((char*)filename, ch);
    if(strlen(retc) > 100 || strlen(retc) < 1)
    {
        return false;
    }
    if(strlen(outdir) > 100 || strlen(outdir) < 1)
    {
        return false;
    }
    memcpy(file_acc.input_filename, &retc[1], strlen(retc) - 1);
    memcpy(file_acc.outttf_dir, &outdir[0], strlen(outdir));
    printf("filename is %s\n", &file_acc.input_filename[0]);
    printf("outttf_dir is %s\n", &file_acc.outttf_dir[0]);
   
     
    
    int file_fd;
    if (strcmp(filename, "-") == 0)
        file_fd = STDIN_FILENO;
    else
        file_fd = open(filename, O_RDONLY);
    
    if (file_fd == -1) {
        perror(filename);
        exit(1);
    }
    
    if (file_fd == STDIN_FILENO) {
        // Read from stdin, up to MAX_RAND_SIZE
        unsigned char *p = rand_buffer;
        ssize_t size;
        ssize_t chars_left = MAX_RAND_SIZE;
        
        while (chars_left > 0 &&
               (size = read(file_fd, p, chars_left)) > 0)
        {
            p += size;
            chars_left -= size;
        }
        if (chars_left == 0)
        {
            perror("Standard input size exceeds MAX_RAND_SIZE");
            exit(1);
        }
        ssize_t total = p - rand_buffer;
        file_acc.seed(rand_buffer, MAX_RAND_SIZE, total);
    }
    if (file_acc.generate) {
        ssize_t size = read(file_fd, rand_buffer, MAX_RAND_SIZE);
        if (size < 0) {
            perror("Failed to read seed file");
            exit(1);
        }
        file_acc.seed(rand_buffer, size, 0);
    } else {
        get_parse_tree = true;
        struct stat st;
        if (fstat(file_fd, &st)) {
            perror("Failed to stat input file");
            exit(1);
        }
        ssize_t file_size = st.st_size;
        if (file_size > MAX_FILE_SIZE) {
            fprintf(stderr, "File size exceeds MAX_FILE_SIZE\n");
            file_size = MAX_FILE_SIZE;
            success = false;
        }
        ssize_t size = read(file_fd, file_acc.file_buffer, file_size);
        if (size != file_size) {
            perror("Failed to read input file");
            exit(1);
        }
        file_acc.seed(rand_buffer, MAX_RAND_SIZE, file_size);
    }
    
    if (file_fd != STDIN_FILENO)
        close(file_fd);
    return success;
}


int  save_output( char* filedata, int32_t len, int32_t *temlen) {
    int32_t filesize;
    unsigned char *filebuffer;
    if (file_acc.generate) {
        
        filesize = file_acc.file_size;
        filebuffer = file_acc.file_buffer;
       
    } else {
        filesize = file_acc.rand_pos;
        filebuffer = rand_buffer;
        
    }
    
    if(filesize < len)
   {
        //filedata = (char*)ck_alloc_nozero(filesize);
    //filedata = ck_realloc(filedata, filesize);
        *temlen = filesize;
       // if(filedata)
      // memset(filedata, 0, len);
       memcpy(filedata, filebuffer, filesize);
           // filedata = filebuffer;
       // else
           // return 0;
    }
    else
    {
        *temlen = len;
       // memset(filedata, 0, len);
        memcpy(filedata, filebuffer, len);
        
    }
    return 1;
}
void save_outttf(size_t filesize)
{
    int file_fd;
    char* filename;
    
    filename = alloc_printf("%s/outtf_method/%s.jc", &file_acc.outttf_dir[0], &file_acc.input_filename[0]);
   
    
    file_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);

if (file_fd == -1) {
    perror(filename);
    ck_free(filename);
    exit(1);
    }
    ck_free(filename);
    
    ssize_t res = write(file_fd, file_acc.deci_buffer, filesize);
    if (res != filesize)
        fprintf(stderr, "Failed to write file\n");
   
    close(file_fd);
}
void save_outputf(const char* filename) {
    int file_fd;
    if (strcmp(filename, "-") == 0)
        file_fd = STDOUT_FILENO;
    else
        file_fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    
    if (file_fd == -1) {
        perror(filename);
        exit(1);
    }
    if (file_acc.generate) {
        ssize_t res = write(file_fd, file_acc.file_buffer, file_acc.file_size);
        if (res != file_acc.file_size)
            fprintf(stderr, "Failed to write file\n");
    } else {
        ssize_t res = write(file_fd, rand_buffer, file_acc.rand_pos);
        if (res != file_acc.rand_pos)
            fprintf(stderr, "Failed to write file\n");
    }
    
    if (file_fd != STDOUT_FILENO)
        close(file_fd);
}

unsigned copy_rand(unsigned char *dest) {
    memcpy(dest, file_acc.rand_buffer, file_acc.rand_pos);
    return file_acc.rand_pos;
}



extern "C" size_t afl_pre_save_handler(unsigned char* data, size_t size, unsigned char** new_data) {
    file_acc.seed(data, size, 0);
    try {
        ttf_generate_file();
    } catch (int status) {
        ttf_delete_globals();
        if (status) {
            *new_data = NULL;
            return 0;
        }
    } catch (...) {
        ttf_delete_globals();
        *new_data = NULL;
        return 0;
    }
    *new_data = file_acc.file_buffer;
    return file_acc.file_size;
}

extern "C" int afl_post_load_handler(unsigned char* data, size_t size, unsigned char** new_data, size_t* new_size) {
    file_acc.generate = false;

    if (size > MAX_FILE_SIZE) {
        fprintf(stderr, "File size larger than MAX_FILE_SIZE\n");
        size = MAX_FILE_SIZE;
    }
    if (data != file_acc.file_buffer) {
        memcpy(file_acc.file_buffer, data, size);
    }
    memset(file_acc.file_buffer + size, 0, MAX_FILE_SIZE - size);
    file_acc.seed(rand_buffer, MAX_RAND_SIZE, size);
    bool success = true;
    try {
        ttf_generate_file();
    } catch (int status) {
        ttf_delete_globals();
        if (status)
            success = false;
    } catch (...) {
        ttf_delete_globals();
        success = false;
    }
    *new_data = rand_buffer;
    *new_size = file_acc.rand_pos;
    file_acc.generate = true;
    return success;
}

void exit_template(int status) {
    if (debug_print || print_errors)
        fprintf(stderr, "Template exited with code %d\n", status);
    throw status;
}

void exit_template(std::string message) {
    if (debug_print || print_errors)
        fprintf(stderr, "Template exited with message: %s\n", message.c_str());
    throw -1;
}



void check_array_length(unsigned& size) {
    if (change_array_length && size > MAX_FILE_SIZE/16 && file_acc.generate) {
        unsigned new_size = file_acc.rand_int(16, file_acc.parse);
        if (debug_print)
            fprintf(stderr, "Array length too large: %d, replaced with %u\n", (signed)size, new_size);
        size = new_size;
    }
}

void ChangeArrayLength() {
    change_array_length = true;
}

void EndChangeArrayLength() {
    change_array_length = false;
}

void BigEndian() { is_big_endian = true; }
void LittleEndian() { is_big_endian = false; }
int IsBigEndian() { return is_big_endian; }

void BitfieldLeftToRight() {
    is_bitfield_left_to_right[is_big_endian] = true;
}
void BitfieldRightToLeft() {
    is_bitfield_right_to_left[is_big_endian] = true;
}
void BitfieldEnablePadding() {
    is_padded_bitfield = true;
}

void BitfieldDisablePadding() {
    is_padded_bitfield = false;
}

void SetBackColor(int color) { }

void DisplayFormatBinary() { }
void DisplayFormatDecimal() { }
void DisplayFormatHex() { }
void DisplayFormatOctal() { }

int SetEvilBit(int allow) {
    return file_acc.set_evil_bit(allow);
}

uint32 Checksum(int checksum_type, int64 start, int64 size) {
    assert_cond(start + size <= file_acc.file_size, "checksum range invalid");
    switch(checksum_type) {
    case CHECKSUM_CRC32: {
        return crc32(0, file_acc.file_buffer + start, size);
    }
    default:
        abort();
    }
}

void Warning(const std::string fmt, ...) {
    if (!debug_print && !print_errors)
        return;
    fprintf(stderr, "Warning: ");
    va_list args;
    va_start(args,fmt);
    vfprintf(stderr, fmt.c_str(), args);
    va_end(args);
    fprintf(stderr, "\n");
}

void Printf(const std::string fmt, ...) {
    if (!debug_print)
        return;
    va_list args;
    va_start(args,fmt);
    vprintf(fmt.c_str(),args);
    va_end(args);
}

void SPrintf(std::string& s, const char* fmt, ...) {
    char res[4096];
    va_list args;
    va_start(args,fmt);
    vsnprintf(res, 4096, fmt, args);
    va_end(args);
    s = res;
}

std::string::size_type Strlen(std::string s) { return s.size(); }

int Strcmp(std::string s1, std::string s2) {
    return strcmp(s1.c_str(), s2.c_str());
}

int Strncmp(std::string s1, std::string s2, int n) {
    assert ((unsigned) n <= s1.length() && (unsigned) n <= s2.length());
    return strncmp(s1.c_str(), s2.c_str(), n);
}

std::string SubStr(std::string s, int start, int count ) {
    size_t len = s.length();
    assert_cond((unsigned)start < len, "SubStr: invalid position");
    if (count == -1)
        return std::string(s.c_str() + start, len - start);
    assert_cond((unsigned)count <= len - start, "SubStr: invalid count");
    return std::string(s.c_str() + start, count);
}

int Memcmp(std::string s1, std::string s2, int n) {
    assert ((unsigned) n <= s1.length() && (unsigned) n <= s2.length());
    return memcmp(s1.c_str(), s2.c_str(), n);
}

void Memcpy(std::string& dest, std::string src, int n, int destOffset , int srcOffset ) {
    // Other configurations not yet handled
    assert(destOffset == 0 && srcOffset == 0);
    assert ((unsigned) n <= src.length());
    dest = std::string(src.c_str(), n);
}

int IsParsing() {
    return !file_acc.generate;
}

int FEof() { return file_acc.feof(); }

int64 FTell() { return file_acc.file_pos; }

int FSeek(int64 pos, bool print ) {
    assert_cond(0 <= pos && pos <= MAX_FILE_SIZE, "FSeek/FSkip: invalid position");
    if (print && debug_print && file_acc.file_pos != pos)
        fprintf(stderr, "FSeek from %u to %lld\n", file_acc.file_pos, pos);
    if (pos > file_acc.file_size) {
        if (debug_print)
            fprintf(stderr, "Padding file from %u to %lld\n", file_acc.file_size, pos);
        file_acc.file_pos = file_acc.file_size;
        file_acc.is_padding = true;
        while (file_acc.file_pos < pos) {
            file_acc.file_integer(1, 0, 0);
        }
        file_acc.is_padding = false;
    } else {
        file_acc.file_pos = pos;
    }
    return 0;
}

int FSkip(int64 offset) {
    if (debug_print && offset != 0)
        fprintf(stderr, "FSkip from %u to %lld\n", file_acc.file_pos, file_acc.file_pos + offset);
    return FSeek(file_acc.file_pos + offset, false);
}

int64 FileSize() {
    if (!file_acc.has_size) {
        file_acc.lookahead = true;
        if (!file_acc.generate)
            file_acc.parse = [](unsigned char* file_buf) -> long long { return file_acc.final_file_size - file_acc.file_size; };
        unsigned new_file_size = file_acc.file_size + file_acc.rand_int(MAX_FILE_SIZE + 1 - file_acc.file_size, file_acc.parse);
        file_acc.lookahead = false;
        if (debug_print)
            fprintf(stderr, "FileSize %u\n", new_file_size);
        int64 original_pos = FTell();
        FSeek(new_file_size, false);
        FSeek(original_pos, false);
        file_acc.has_size = true;
    }
    return file_acc.file_size;
}

unsigned get_file_size() {
    return file_acc.file_size;
}

//extern std::vector<std::string> ReadBytesInitValues;

bool ReadBytes(std::string& s, int64 pos, int n) {
    assert_cond(n > 0, "ReadBytes: invalid number of bytes");
    int64 original_pos = FTell();
    FSeek(pos);
    file_acc.lookahead = true;

    if (ReadBytesInitValues.size())
        s = file_acc.file_string(ReadBytesInitValues);
    else
        s = file_acc.file_string(n);

    file_acc.lookahead = false;
    FSeek(original_pos);
    return true;
}

bool ReadBytes(std::string& s, int64 pos, int n, std::vector<std::string> preferred_values, std::vector<std::string> possible_values , double p ) {
    assert_cond(n > 0, "ReadBytes: invalid number of bytes");
    int64 original_pos = FTell();
    file_acc.file_pos = pos;
    file_acc.lookahead = true;

    int evil = SetEvilBit(false);
    if (possible_values.size() && ReadBytesInitValues.size()) {
        if (!file_acc.generate && preferred_values.size()) {
            file_acc.parse = [&preferred_values, &possible_values, &n](unsigned char* file_buf) -> long long {
                    if (file_acc.file_pos + n > file_acc.final_file_size)
                        return 0;
                        if (std::find(preferred_values.begin(), preferred_values.end(), std::string((char*)file_buf, n)) != preferred_values.end())
                            return 0;
                        if (std::find(possible_values.begin(), possible_values.end(), std::string((char*)file_buf, n)) != possible_values.end())
                            return 253;
                        return 255;
                    };
        } else if (!file_acc.generate) {
            file_acc.parse = [&possible_values, &n](unsigned char* file_buf) -> long long {
                    if (file_acc.file_pos + n > file_acc.final_file_size)
                        return 0;
                        if (std::find(possible_values.begin(), possible_values.end(), std::string((char*)file_buf, n)) != possible_values.end())
                            return 253;
                        if (std::find(ReadBytesInitValues.begin(), ReadBytesInitValues.end(), std::string((char*)file_buf, n)) != ReadBytesInitValues.end())
                            return 255;
                        return 0;
                    };
        }
        int choice = file_acc.rand_int(256, file_acc.parse);
        if (choice < 255 * p) {
            if (preferred_values.size())
                s = file_acc.file_string(preferred_values);
            else {
                s = "";
            }
        } else if (choice < 254) {
            if (preferred_values.size())
                SetEvilBit(evil);
            s = file_acc.file_string(possible_values);
        } else {
            if (preferred_values.size())
                SetEvilBit(evil);
            s = file_acc.file_string(ReadBytesInitValues);
        }
    } else if (!possible_values.size() && !ReadBytesInitValues.size()) {
        if (preferred_values.size()) {
            SetEvilBit(evil);
            s = file_acc.file_string(preferred_values);
        } else {
            s = "";
        }
    } else {
        std::vector<std::string>& known_values = possible_values.size() ? possible_values : ReadBytesInitValues;
        if (!possible_values.size())
            p = 0.995;
        if (!file_acc.generate && preferred_values.size()) {
            file_acc.parse = [&preferred_values, &n](unsigned char* file_buf) -> long long {
                    if (file_acc.file_pos + n > file_acc.final_file_size)
                        return 0;
                        return 255 * (std::find(preferred_values.begin(), preferred_values.end(), std::string((char*)file_buf, n)) == preferred_values.end());
                    };
        } else if (!file_acc.generate) {
            file_acc.parse = [&known_values, &n](unsigned char* file_buf) -> long long {
                    if (file_acc.file_pos + n > file_acc.final_file_size)
                        return 0;
                        return 255 * (std::find(known_values.begin(), known_values.end(), std::string((char*)file_buf, n)) != known_values.end());
                    };
        }
        int choice = file_acc.rand_int(256, file_acc.parse);
        if (choice < 255 * p) {
            if (preferred_values.size())
                s = file_acc.file_string(preferred_values);
            else {
                s = "";
            }
        } else {
            if (preferred_values.size())
                SetEvilBit(evil);
            s = file_acc.file_string(known_values);
        }
    }
    SetEvilBit(evil);

    file_acc.lookahead = false;
    file_acc.file_pos = original_pos;
    return s.length() != 0;
}

//extern std::vector<byte> ReadByteInitValues;

byte ReadByte(int64 pos ,
              std::vector<byte> possible_values)
{
    int64 original_pos = FTell();
    FSeek(pos);
    file_acc.lookahead = true;
    byte value;
    if (possible_values.size())
        value = (byte)file_acc.file_integer(sizeof(byte), 0, possible_values);
    else if (ReadByteInitValues.size())
        value = (byte)file_acc.file_integer(sizeof(byte), 0, ReadByteInitValues);
    else
        value = (byte)file_acc.file_integer(sizeof(byte), 0, 1);
    file_acc.lookahead = false;
    FSeek(original_pos);
    return value;
}

//extern std::vector<ubyte> ReadUByteInitValues;

ubyte ReadUByte(int64 pos , std::vector<ubyte> possible_values ) {
    int64 original_pos = FTell();
    FSeek(pos);
    file_acc.lookahead = true;
    ubyte value;
    if (possible_values.size())
        value = file_acc.file_integer(sizeof(ubyte), 0, possible_values);
    else if (ReadUByteInitValues.size())
        value = file_acc.file_integer(sizeof(ubyte), 0, ReadUByteInitValues);
    else
        value = file_acc.file_integer(sizeof(ubyte), 0, 1);
    file_acc.lookahead = false;
    FSeek(original_pos);
    return value;
}

//extern std::vector<short> ReadShortInitValues;

short ReadShort(int64 pos , std::vector<short> possible_values ) {
    int64 original_pos = FTell();
    FSeek(pos);
    file_acc.lookahead = true;
    short value;
    if (possible_values.size())
        value = file_acc.file_integer(sizeof(short), 0, possible_values);
    else if (ReadShortInitValues.size())
        value = file_acc.file_integer(sizeof(double), 0, ReadShortInitValues);
    else
        value = file_acc.file_integer(sizeof(short), 0, 1);
    file_acc.lookahead = false;
    FSeek(original_pos);
    return value;
}

//extern std::vector<ushort> ReadUShortInitValues;

ushort ReadUShort(int64 pos , std::vector<ushort> possible_values ) {
    int64 original_pos = FTell();
    FSeek(pos);
    file_acc.lookahead = true;
    ushort value;
    if (possible_values.size())
        value = file_acc.file_integer(sizeof(ushort), 0, possible_values);
    else if (ReadUShortInitValues.size())
        value = file_acc.file_integer(sizeof(ushort), 0, ReadUShortInitValues);
    else
        value = file_acc.file_integer(sizeof(ushort), 0, 1);
    file_acc.lookahead = false;
    FSeek(original_pos);
    return value;
}

//extern std::vector<int> ReadIntInitValues;

int ReadInt(int64 pos , std::vector<int> possible_values ) {
    int64 original_pos = FTell();
    FSeek(pos);
    file_acc.lookahead = true;
    int value;
    if (possible_values.size())
        value = file_acc.file_integer(sizeof(int), 0, possible_values);
    else if (ReadIntInitValues.size())
        value = file_acc.file_integer(sizeof(int), 0, ReadIntInitValues);
    else
        value = file_acc.file_integer(sizeof(int), 0, 1);
    file_acc.lookahead = false;
    FSeek(original_pos);
    return value;
}

//extern std::vector<uint> ReadUIntInitValues;

uint ReadUInt(int64 pos , std::vector<uint> possible_values ) {
    int64 original_pos = FTell();
    FSeek(pos);
    file_acc.lookahead = true;
    uint value;
    if (possible_values.size())
        value = file_acc.file_integer(sizeof(uint), 0, possible_values);
    else if (ReadUIntInitValues.size())
        value = file_acc.file_integer(sizeof(uint), 0, ReadUIntInitValues);
    else
        value = file_acc.file_integer(sizeof(uint), 0, 1);
    file_acc.lookahead = false;
    FSeek(original_pos);
    return value;
}

//extern std::vector<int64> ReadQuadInitValues;

int64 ReadQuad(int64 pos , std::vector<int64> possible_values ) {
    int64 original_pos = FTell();
    FSeek(pos);
    file_acc.lookahead = true;
    int64 value;
    if (possible_values.size())
        value = file_acc.file_integer(sizeof(int64), 0, possible_values);
    else if (ReadQuadInitValues.size())
        value = file_acc.file_integer(sizeof(int64), 0, ReadQuadInitValues);
    else
        value = file_acc.file_integer(sizeof(int64), 0, 1);
    file_acc.lookahead = false;
    FSeek(original_pos);
    return value;
}

//extern std::vector<uint64> ReadUQuadInitValues;

uint64 ReadUQuad(int64 pos , std::vector<uint64> possible_values ) {
    int64 original_pos = FTell();
    FSeek(pos);
    file_acc.lookahead = true;
    uint64 value;
    if (possible_values.size())
        value = file_acc.file_integer(sizeof(uint64), 0, possible_values);
    else if (ReadUQuadInitValues.size())
        value = file_acc.file_integer(sizeof(uint64), 0, ReadUQuadInitValues);
    else
        value = file_acc.file_integer(sizeof(uint64), 0, 1);
    file_acc.lookahead = false;
    FSeek(original_pos);
    return value;
}

//extern std::vector<int64> ReadInt64InitValues;

int64 ReadInt64(int64 pos , std::vector<int64> possible_values ) {
    int64 original_pos = FTell();
    FSeek(pos);
    file_acc.lookahead = true;
    int64 value;
    if (possible_values.size())
        value = file_acc.file_integer(sizeof(int64), 0, possible_values);
    else if (ReadInt64InitValues.size())
        value = file_acc.file_integer(sizeof(int64), 0, ReadInt64InitValues);
    else
        value = file_acc.file_integer(sizeof(int64), 0, 1);
    file_acc.lookahead = false;
    FSeek(original_pos);
    return value;
}

//extern std::vector<uint64> ReadUInt64InitValues;

uint64 ReadUInt64(int64 pos , std::vector<uint64> possible_values ) {
    int64 original_pos = FTell();
    FSeek(pos);
    file_acc.lookahead = true;
    uint64 value;
    if (possible_values.size())
        value = file_acc.file_integer(sizeof(uint64), 0, possible_values);
    else if (ReadUInt64InitValues.size())
        value = file_acc.file_integer(sizeof(uint64), 0, ReadUInt64InitValues);
    else
        value = file_acc.file_integer(sizeof(uint64), 0, 1);
    file_acc.lookahead = false;
    FSeek(original_pos);
    return value;
}

//extern std::vector<hfloat> ReadHFloatInitValues;

hfloat ReadHFloat(int64 pos , std::vector<hfloat> possible_values ) {
    int64 original_pos = FTell();
    FSeek(pos);
    file_acc.lookahead = true;
    hfloat value;
    if (possible_values.size())
        value = file_acc.file_integer(sizeof(hfloat), 0, possible_values);
    else if (ReadHFloatInitValues.size())
        value = file_acc.file_integer(sizeof(hfloat), 0, ReadHFloatInitValues);
    else
        value = file_acc.file_integer(sizeof(hfloat), 0, 1);
    file_acc.lookahead = false;
    FSeek(original_pos);
    return value;
}

//extern std::vector<float> ReadFloatInitValues;

float ReadFloat(int64 pos , std::vector<float> possible_values ) {
    int64 original_pos = FTell();
    FSeek(pos);
    file_acc.lookahead = true;
    float value;
    if (possible_values.size())
        value = file_acc.file_integer(sizeof(float), 0, possible_values);
    else if (ReadFloatInitValues.size())
        value = file_acc.file_integer(sizeof(float), 0, ReadFloatInitValues);
    else
        value = file_acc.file_integer(sizeof(float), 0, 1);
    file_acc.lookahead = false;
    FSeek(original_pos);
    return value;
}

//extern std::vector<double> ReadDoubleInitValues;

double ReadDouble(int64 pos , std::vector<double> possible_values ) {
    int64 original_pos = FTell();
    FSeek(pos);
    file_acc.lookahead = true;
    double value;
    if (possible_values.size())
        value = file_acc.file_integer(sizeof(double), 0, possible_values);
    else if (ReadDoubleInitValues.size())
        value = file_acc.file_integer(sizeof(double), 0, ReadDoubleInitValues);
    else
        value = file_acc.file_integer(sizeof(double), 0, 1);
    file_acc.lookahead = false;
    FSeek(original_pos);
    return value;
}

