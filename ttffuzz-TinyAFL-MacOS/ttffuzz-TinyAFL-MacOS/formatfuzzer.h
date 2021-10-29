//
//  formatfuzzer.h
//  AFL
//
//  Created by System Administrator on 2021/5/8.
//

#define MAX_RAND_SIZE 1048576
#define MAX_FILE_SIZE 1048576
#define MAX_DECI_SIZE 1048576

#include <vector>
//#include "types.h"
#include <unordered_map>
#include <string>
extern bool formatfuzztojc;
//using namespace std;
struct InsertionPoint {
    unsigned pos;
    const char* type;
    const char* name;
    InsertionPoint(unsigned pos, const char* type, const char* name) : pos(pos), type(type), name(name) {}
};

struct Chunk {
    int file_index;
    unsigned start;
    unsigned end;
    const char* type;
    const char* name;
    Chunk(int file_index, unsigned start, unsigned end, const char* type, const char* name) : file_index(file_index), start(start), end(end), type(type), name(name) {}
};

struct NonOptional {
    const char* type;
    int start;
    int size;
    NonOptional(const char* type, int start, int size) : type(type), start(start), size(size) {}
};

extern std::unordered_map<std::string, std::string> variable_types;
extern std::vector<std::vector<InsertionPoint>> insertion_points;
extern std::vector<std::vector<Chunk>> deletable_chunks;
extern std::vector<Chunk> optional_chunks;
extern std::vector<int> optional_index;
extern std::unordered_map<std::string, std::vector<Chunk>> non_optional_chunks;
extern std::vector<std::vector<NonOptional>> non_optional_index;
extern std::vector<std::string> rand_names;

void set_parser();

void set_generator();

void set_Decision();//sunglin
bool set_generator_parse(const char* filename);//sunglin
bool setup_input(const char* filename, const char* outdir);

//void png_generate_file();
//void jpg_generate_file();
void ttf_generate_file();

unsigned get_file_size();

double get_validity();

//void png_delete_globals();
//void jpg_delete_globals();
void ttf_delete_globals();

char* get_bin_name(char* arg);

int  save_output( char* filedata, int32_t len, int32_t *temlen);

void save_outputf(const char* filename);


