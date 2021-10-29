#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include "file_accessor.h"
typedef unsigned long TT_Fixed;
typedef signed short TT_FWord;
typedef unsigned short TT_UFWord;
typedef signed short TT_Short;
typedef unsigned short TT_UShort;
typedef signed long TT_Long;
typedef unsigned long TT_ULong;
typedef unsigned long TT_Offset;
typedef unsigned long long LONGDATETIME;
typedef signed short F2Dot14;



class unsigned_long_class {
    int small;
    std::vector<ULONG> known_values;
    ULONG value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(ULONG);
    ULONG operator () () { return value; }
    unsigned_long_class(int small, std::vector<ULONG> known_values = {}) : small(small), known_values(known_values) {}

    ULONG generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(ULONG), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(ULONG), 0, known_values);
        }
        return value;
    }

    ULONG generate(std::vector<ULONG> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(ULONG), 0, possible_values);
        return value;
    }
};



class USHORT_class {
    int small;
    std::vector<USHORT> known_values;
    USHORT value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(USHORT);
    USHORT operator () () { return value; }
    USHORT_class(int small, std::vector<USHORT> known_values = {}) : small(small), known_values(known_values) {}

    USHORT generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(USHORT), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(USHORT), 0, known_values);
        }
        return value;
    }

    USHORT generate(std::vector<USHORT> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(USHORT), 0, possible_values);
        return value;
    }
};



class tOffsetTable {
    std::vector<tOffsetTable*>& instances;

    ULONG SFNT_Ver_var;
    USHORT numTables_var;
    USHORT searchRange_var;
    USHORT entrySelector_var;
    USHORT rangeShift_var;

public:
    bool SFNT_Ver_exists = false;
    bool numTables_exists = false;
    bool searchRange_exists = false;
    bool entrySelector_exists = false;
    bool rangeShift_exists = false;

    ULONG SFNT_Ver() {
        assert_cond(SFNT_Ver_exists, "struct field SFNT_Ver does not exist");
        return SFNT_Ver_var;
    }
    USHORT numTables() {
        assert_cond(numTables_exists, "struct field numTables does not exist");
        return numTables_var;
    }
    USHORT searchRange() {
        assert_cond(searchRange_exists, "struct field searchRange does not exist");
        return searchRange_var;
    }
    USHORT entrySelector() {
        assert_cond(entrySelector_exists, "struct field entrySelector does not exist");
        return entrySelector_var;
    }
    USHORT rangeShift() {
        assert_cond(rangeShift_exists, "struct field rangeShift does not exist");
        return rangeShift_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tOffsetTable& operator () () { return *instances.back(); }
    tOffsetTable* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tOffsetTable(std::vector<tOffsetTable*>& instances) : instances(instances) { instances.push_back(this); }
    ~tOffsetTable() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tOffsetTable* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tOffsetTable* generate();
};



class char_class {
    int small;
    std::vector<char> known_values;
    char value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(char);
    char operator () () { return value; }
    char_class(int small, std::vector<char> known_values = {}) : small(small), known_values(known_values) {}

    char generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(char), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(char), 0, known_values);
        }
        return value;
    }

    char generate(std::vector<char> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(char), 0, possible_values);
        return value;
    }
};



class char_array_class {
    char_class& element;
    std::vector<std::string> known_values;
    std::unordered_map<int, std::vector<char>> element_known_values;
    std::string value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::string operator () () { return value; }
    char operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    char_array_class(char_class& element, std::unordered_map<int, std::vector<char>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}
    char_array_class(char_class& element, std::vector<std::string> known_values)
        : element(element), known_values(known_values) {}

    std::string generate(unsigned size, std::vector<std::string> possible_values = {}) {
        check_array_length(size);
        _startof = FTell();
        value = "";
        if (possible_values.size()) {
            value = file_acc.file_string(possible_values);
            assert(value.length() == size);
            _sizeof = size;
            return value;
        }
        if (known_values.size()) {
            value = file_acc.file_string(known_values);
            assert(value.length() == size);
            _sizeof = size;
            return value;
        }
        if (!element_known_values.size()) {
            if (size == 0)
                 return "";
            value = file_acc.file_string(size);
            _sizeof = size;
            return value;
        }
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(char), 0, known->second));
                _sizeof += sizeof(char);
            }
        }
        return value;
    }
};



class ULONG_class {
    int small;
    std::vector<ULONG> known_values;
    ULONG value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(ULONG);
    ULONG operator () () { return value; }
    ULONG_class(int small, std::vector<ULONG> known_values = {}) : small(small), known_values(known_values) {}

    ULONG generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(ULONG), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(ULONG), 0, known_values);
        }
        return value;
    }

    ULONG generate(std::vector<ULONG> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(ULONG), 0, possible_values);
        return value;
    }
};



class CTag {
    std::vector<CTag*>& instances;

// union {
    std::string asName_var;
    ULONG asLong_var;
// };

public:
    bool asName_exists = false;
    bool asLong_exists = false;

    std::string asName() {
        assert_cond(asName_exists, "struct field asName does not exist");
        return asName_var;
    }
    ULONG asLong() {
        assert_cond(asLong_exists, "struct field asLong does not exist");
        return asLong_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    CTag& operator () () { return *instances.back(); }
    CTag* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    CTag(std::vector<CTag*>& instances) : instances(instances) { instances.push_back(this); }
    ~CTag() {
        if (generated == 2)
            return;
        while (instances.size()) {
            CTag* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    CTag* generate();
};



class sTable {
    std::vector<sTable*>& instances;

    CTag* Tag_var;
    ULONG checkSum_var;
    ULONG offset_var;
    ULONG slength_var;

public:
    bool Tag_exists = false;
    bool checkSum_exists = false;
    bool offset_exists = false;
    bool slength_exists = false;

    CTag& Tag() {
        assert_cond(Tag_exists, "struct field Tag does not exist");
        return *Tag_var;
    }
    ULONG checkSum() {
        assert_cond(checkSum_exists, "struct field checkSum does not exist");
        return checkSum_var;
    }
    ULONG offset() {
        assert_cond(offset_exists, "struct field offset does not exist");
        return offset_var;
    }
    ULONG slength() {
        assert_cond(slength_exists, "struct field slength does not exist");
        return slength_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    sTable& operator () () { return *instances.back(); }
    sTable* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    sTable(std::vector<sTable*>& instances) : instances(instances) { instances.push_back(this); }
    ~sTable() {
        if (generated == 2)
            return;
        while (instances.size()) {
            sTable* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    sTable* generate();
};



class LONGDATETIME_class {
    int small;
    std::vector<LONGDATETIME> known_values;
    LONGDATETIME value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(LONGDATETIME);
    LONGDATETIME operator () () { return value; }
    LONGDATETIME_class(int small, std::vector<LONGDATETIME> known_values = {}) : small(small), known_values(known_values) {}

    LONGDATETIME generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(LONGDATETIME), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(LONGDATETIME), 0, known_values);
        }
        return value;
    }

    LONGDATETIME generate(std::vector<LONGDATETIME> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(LONGDATETIME), 0, possible_values);
        return value;
    }
};



class SHORT_class {
    int small;
    std::vector<SHORT> known_values;
    SHORT value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(SHORT);
    SHORT operator () () { return value; }
    SHORT_class(int small, std::vector<SHORT> known_values = {}) : small(small), known_values(known_values) {}

    SHORT generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(SHORT), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(SHORT), 0, known_values);
        }
        return value;
    }

    SHORT generate(std::vector<SHORT> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(SHORT), 0, possible_values);
        return value;
    }
};



class thead {
    std::vector<thead*>& instances;

    ULONG version_var;
    ULONG fontRevision_var;
    ULONG checkSumAdjustment_var;
    ULONG magicNumber_var;
    USHORT flags_var;
    USHORT unitsPerEm_var;
    LONGDATETIME created_var;
    LONGDATETIME modified_var;
    SHORT xMin_var;
    SHORT yMin_var;
    SHORT xMax_var;
    SHORT yMax_var;
    USHORT macStyle_var;
    USHORT lowestRecPPEM_var;
    SHORT fontDirectionHint_var;
    SHORT indexToLocFormat_var;
    SHORT glyphDataFormat_var;

public:
    bool version_exists = false;
    bool fontRevision_exists = false;
    bool checkSumAdjustment_exists = false;
    bool magicNumber_exists = false;
    bool flags_exists = false;
    bool unitsPerEm_exists = false;
    bool created_exists = false;
    bool modified_exists = false;
    bool xMin_exists = false;
    bool yMin_exists = false;
    bool xMax_exists = false;
    bool yMax_exists = false;
    bool macStyle_exists = false;
    bool lowestRecPPEM_exists = false;
    bool fontDirectionHint_exists = false;
    bool indexToLocFormat_exists = false;
    bool glyphDataFormat_exists = false;

    ULONG version() {
        assert_cond(version_exists, "struct field version does not exist");
        return version_var;
    }
    ULONG fontRevision() {
        assert_cond(fontRevision_exists, "struct field fontRevision does not exist");
        return fontRevision_var;
    }
    ULONG checkSumAdjustment() {
        assert_cond(checkSumAdjustment_exists, "struct field checkSumAdjustment does not exist");
        return checkSumAdjustment_var;
    }
    ULONG magicNumber() {
        assert_cond(magicNumber_exists, "struct field magicNumber does not exist");
        return magicNumber_var;
    }
    USHORT flags() {
        assert_cond(flags_exists, "struct field flags does not exist");
        return flags_var;
    }
    USHORT unitsPerEm() {
        assert_cond(unitsPerEm_exists, "struct field unitsPerEm does not exist");
        return unitsPerEm_var;
    }
    LONGDATETIME created() {
        assert_cond(created_exists, "struct field created does not exist");
        return created_var;
    }
    LONGDATETIME modified() {
        assert_cond(modified_exists, "struct field modified does not exist");
        return modified_var;
    }
    SHORT xMin() {
        assert_cond(xMin_exists, "struct field xMin does not exist");
        return xMin_var;
    }
    SHORT yMin() {
        assert_cond(yMin_exists, "struct field yMin does not exist");
        return yMin_var;
    }
    SHORT xMax() {
        assert_cond(xMax_exists, "struct field xMax does not exist");
        return xMax_var;
    }
    SHORT yMax() {
        assert_cond(yMax_exists, "struct field yMax does not exist");
        return yMax_var;
    }
    USHORT macStyle() {
        assert_cond(macStyle_exists, "struct field macStyle does not exist");
        return macStyle_var;
    }
    USHORT lowestRecPPEM() {
        assert_cond(lowestRecPPEM_exists, "struct field lowestRecPPEM does not exist");
        return lowestRecPPEM_var;
    }
    SHORT fontDirectionHint() {
        assert_cond(fontDirectionHint_exists, "struct field fontDirectionHint does not exist");
        return fontDirectionHint_var;
    }
    SHORT indexToLocFormat() {
        assert_cond(indexToLocFormat_exists, "struct field indexToLocFormat does not exist");
        return indexToLocFormat_var;
    }
    SHORT glyphDataFormat() {
        assert_cond(glyphDataFormat_exists, "struct field glyphDataFormat does not exist");
        return glyphDataFormat_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    thead& operator () () { return *instances.back(); }
    thead* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    thead(std::vector<thead*>& instances) : instances(instances) { instances.push_back(this); }
    ~thead() {
        if (generated == 2)
            return;
        while (instances.size()) {
            thead* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    thead* generate();
};



class tcmap {
    std::vector<tcmap*>& instances;

    USHORT version_cmap_var;
    USHORT numTables_var;

public:
    bool version_cmap_exists = false;
    bool numTables_exists = false;

    USHORT version_cmap() {
        assert_cond(version_cmap_exists, "struct field version_cmap does not exist");
        return version_cmap_var;
    }
    USHORT numTables() {
        assert_cond(numTables_exists, "struct field numTables does not exist");
        return numTables_var;
    }

    /* locals */
    quad cmap_table;
    quad next_cmap_record;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tcmap& operator () () { return *instances.back(); }
    tcmap* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tcmap(std::vector<tcmap*>& instances) : instances(instances) { instances.push_back(this); }
    ~tcmap() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tcmap* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tcmap* generate();
};



class BYTE_class {
    int small;
    std::vector<BYTE> known_values;
    BYTE value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(BYTE);
    BYTE operator () () { return value; }
    BYTE_class(int small, std::vector<BYTE> known_values = {}) : small(small), known_values(known_values) {}

    BYTE generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(BYTE), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(BYTE), 0, known_values);
        }
        return value;
    }

    BYTE generate(std::vector<BYTE> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(BYTE), 0, possible_values);
        return value;
    }
};



class BYTE_array_class {
    BYTE_class& element;
    std::vector<std::string> known_values;
    std::unordered_map<int, std::vector<BYTE>> element_known_values;
    std::string value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::string operator () () { return value; }
    BYTE operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    BYTE_array_class(BYTE_class& element, std::unordered_map<int, std::vector<BYTE>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}
    BYTE_array_class(BYTE_class& element, std::vector<std::string> known_values)
        : element(element), known_values(known_values) {}

    std::string generate(unsigned size, std::vector<std::string> possible_values = {}) {
        check_array_length(size);
        _startof = FTell();
        value = "";
        if (possible_values.size()) {
            value = file_acc.file_string(possible_values);
            assert(value.length() == size);
            _sizeof = size;
            return value;
        }
        if (known_values.size()) {
            value = file_acc.file_string(known_values);
            assert(value.length() == size);
            _sizeof = size;
            return value;
        }
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(BYTE), 0, known->second));
                _sizeof += sizeof(BYTE);
            }
        }
        return value;
    }
};



class tcmap_format0 {
    std::vector<tcmap_format0*>& instances;

    USHORT length_var;
    USHORT language_var;
    std::string glyphIdArray_var;

public:
    bool length_exists = false;
    bool language_exists = false;
    bool glyphIdArray_exists = false;

    USHORT length() {
        assert_cond(length_exists, "struct field length does not exist");
        return length_var;
    }
    USHORT language() {
        assert_cond(language_exists, "struct field language does not exist");
        return language_var;
    }
    std::string glyphIdArray() {
        assert_cond(glyphIdArray_exists, "struct field glyphIdArray does not exist");
        return glyphIdArray_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tcmap_format0& operator () () { return *instances.back(); }
    tcmap_format0* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tcmap_format0(std::vector<tcmap_format0*>& instances) : instances(instances) { instances.push_back(this); }
    ~tcmap_format0() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tcmap_format0* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tcmap_format0* generate(quad& cmap_subtable);
};



class uint16_class {
    int small;
    std::vector<uint16> known_values;
    uint16 value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(uint16);
    uint16 operator () () { return value; }
    uint16_class(int small, std::vector<uint16> known_values = {}) : small(small), known_values(known_values) {}

    uint16 generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(uint16), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(uint16), 0, known_values);
        }
        return value;
    }

    uint16 generate(std::vector<uint16> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(uint16), 0, possible_values);
        return value;
    }
};



class int16_class {
    int small;
    std::vector<int16> known_values;
    int16 value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(int16);
    int16 operator () () { return value; }
    int16_class(int small, std::vector<int16> known_values = {}) : small(small), known_values(known_values) {}

    int16 generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(int16), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(int16), 0, known_values);
        }
        return value;
    }

    int16 generate(std::vector<int16> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(int16), 0, possible_values);
        return value;
    }
};


std::vector<USHORT> loca_arrayvalue;
class USHORT_array_class {
    USHORT_class& element;
    std::unordered_map<int, std::vector<USHORT>> element_known_values;
    std::vector<USHORT> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<USHORT> operator () () { return value; }
    USHORT operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    USHORT_array_class(USHORT_class& element, std::unordered_map<int, std::vector<USHORT>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}

    std::vector<USHORT> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(USHORT), 0, known->second));
                _sizeof += sizeof(USHORT);
            }
        }
        loca_arrayvalue.assign(value.begin(), value.end());
        return value;
    }
};



class tcmap_format2 {
    std::vector<tcmap_format2*>& instances;

    USHORT length_var;
    USHORT language_var;
    USHORT subHeaderKeys_var;
    uint16 firstCode_var;
    uint16 entryCount_var;
    int16 idDelta_var;
    uint16 idRangeOffset_var;
    std::vector<USHORT> glyphIdArray_var;

public:
    bool length_exists = false;
    bool language_exists = false;
    bool subHeaderKeys_exists = false;
    bool firstCode_exists = false;
    bool entryCount_exists = false;
    bool idDelta_exists = false;
    bool idRangeOffset_exists = false;
    bool glyphIdArray_exists = false;

    USHORT length() {
        assert_cond(length_exists, "struct field length does not exist");
        return length_var;
    }
    USHORT language() {
        assert_cond(language_exists, "struct field language does not exist");
        return language_var;
    }
    USHORT subHeaderKeys() {
        assert_cond(subHeaderKeys_exists, "struct field subHeaderKeys does not exist");
        return subHeaderKeys_var;
    }
    uint16 firstCode() {
        assert_cond(firstCode_exists, "struct field firstCode does not exist");
        return firstCode_var;
    }
    uint16 entryCount() {
        assert_cond(entryCount_exists, "struct field entryCount does not exist");
        return entryCount_var;
    }
    int16 idDelta() {
        assert_cond(idDelta_exists, "struct field idDelta does not exist");
        return idDelta_var;
    }
    uint16 idRangeOffset() {
        assert_cond(idRangeOffset_exists, "struct field idRangeOffset does not exist");
        return idRangeOffset_var;
    }
    std::vector<USHORT> glyphIdArray() {
        assert_cond(glyphIdArray_exists, "struct field glyphIdArray does not exist");
        return glyphIdArray_var;
    }

    /* locals */
    int maxidx;
    int i;
    uint16 tmp_idrange;
    USHORT format2_length;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tcmap_format2& operator () () { return *instances.back(); }
    tcmap_format2* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tcmap_format2(std::vector<tcmap_format2*>& instances) : instances(instances) { instances.push_back(this); }
    ~tcmap_format2() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tcmap_format2* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tcmap_format2* generate(quad& cmap_subtable);
};



class SHORT_array_class {
    SHORT_class& element;
    std::unordered_map<int, std::vector<SHORT>> element_known_values;
    std::vector<SHORT> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<SHORT> operator () () { return value; }
    SHORT operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    SHORT_array_class(SHORT_class& element, std::unordered_map<int, std::vector<SHORT>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}

    std::vector<SHORT> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(SHORT), 0, known->second));
                _sizeof += sizeof(SHORT);
            }
        }
        return value;
    }
};



class tcmap_format4 {
    std::vector<tcmap_format4*>& instances;

    USHORT length_var;
    USHORT language_var;
    USHORT segCountX2_var;
    USHORT searchRange_var;
    USHORT entrySelector_var;
    USHORT rangeShift_var;
    std::vector<USHORT> endCount_var;
    USHORT reservedPad_var;
    std::vector<USHORT> startCount_var;
    std::vector<SHORT> idDelta_var;
    std::vector<USHORT> idRangeOffset_var;
    std::vector<USHORT> glyphIdArray_var;

public:
    bool length_exists = false;
    bool language_exists = false;
    bool segCountX2_exists = false;
    bool searchRange_exists = false;
    bool entrySelector_exists = false;
    bool rangeShift_exists = false;
    bool endCount_exists = false;
    bool reservedPad_exists = false;
    bool startCount_exists = false;
    bool idDelta_exists = false;
    bool idRangeOffset_exists = false;
    bool glyphIdArray_exists = false;

    USHORT length() {
        assert_cond(length_exists, "struct field length does not exist");
        return length_var;
    }
    USHORT language() {
        assert_cond(language_exists, "struct field language does not exist");
        return language_var;
    }
    USHORT segCountX2() {
        assert_cond(segCountX2_exists, "struct field segCountX2 does not exist");
        return segCountX2_var;
    }
    USHORT searchRange() {
        assert_cond(searchRange_exists, "struct field searchRange does not exist");
        return searchRange_var;
    }
    USHORT entrySelector() {
        assert_cond(entrySelector_exists, "struct field entrySelector does not exist");
        return entrySelector_var;
    }
    USHORT rangeShift() {
        assert_cond(rangeShift_exists, "struct field rangeShift does not exist");
        return rangeShift_var;
    }
    std::vector<USHORT> endCount() {
        assert_cond(endCount_exists, "struct field endCount does not exist");
        return endCount_var;
    }
    USHORT reservedPad() {
        assert_cond(reservedPad_exists, "struct field reservedPad does not exist");
        return reservedPad_var;
    }
    std::vector<USHORT> startCount() {
        assert_cond(startCount_exists, "struct field startCount does not exist");
        return startCount_var;
    }
    std::vector<SHORT> idDelta() {
        assert_cond(idDelta_exists, "struct field idDelta does not exist");
        return idDelta_var;
    }
    std::vector<USHORT> idRangeOffset() {
        assert_cond(idRangeOffset_exists, "struct field idRangeOffset does not exist");
        return idRangeOffset_var;
    }
    std::vector<USHORT> glyphIdArray() {
        assert_cond(glyphIdArray_exists, "struct field glyphIdArray does not exist");
        return glyphIdArray_var;
    }

    /* locals */
    USHORT glyphIdArraylength;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tcmap_format4& operator () () { return *instances.back(); }
    tcmap_format4* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tcmap_format4(std::vector<tcmap_format4*>& instances) : instances(instances) { instances.push_back(this); }
    ~tcmap_format4() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tcmap_format4* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tcmap_format4* generate(quad& cmap_subtable);
};



class tcmap_format6 {
    std::vector<tcmap_format6*>& instances;

    USHORT length_var;
    USHORT language_var;
    USHORT firstCode_var;
    USHORT entryCount_var;
    std::vector<USHORT> glyphIdArray_var;

public:
    bool length_exists = false;
    bool language_exists = false;
    bool firstCode_exists = false;
    bool entryCount_exists = false;
    bool glyphIdArray_exists = false;

    USHORT length() {
        assert_cond(length_exists, "struct field length does not exist");
        return length_var;
    }
    USHORT language() {
        assert_cond(language_exists, "struct field language does not exist");
        return language_var;
    }
    USHORT firstCode() {
        assert_cond(firstCode_exists, "struct field firstCode does not exist");
        return firstCode_var;
    }
    USHORT entryCount() {
        assert_cond(entryCount_exists, "struct field entryCount does not exist");
        return entryCount_var;
    }
    std::vector<USHORT> glyphIdArray() {
        assert_cond(glyphIdArray_exists, "struct field glyphIdArray does not exist");
        return glyphIdArray_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tcmap_format6& operator () () { return *instances.back(); }
    tcmap_format6* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tcmap_format6(std::vector<tcmap_format6*>& instances) : instances(instances) { instances.push_back(this); }
    ~tcmap_format6() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tcmap_format6* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tcmap_format6* generate(quad& cmap_subtable);
};



class tcmap_format8_groupings_struct {
    std::vector<tcmap_format8_groupings_struct*>& instances;

    ULONG startCharCode_var;
    ULONG endCharCode_var;
    ULONG startGlyphID_var;

public:
    bool startCharCode_exists = false;
    bool endCharCode_exists = false;
    bool startGlyphID_exists = false;

    ULONG startCharCode() {
        assert_cond(startCharCode_exists, "struct field startCharCode does not exist");
        return startCharCode_var;
    }
    ULONG endCharCode() {
        assert_cond(endCharCode_exists, "struct field endCharCode does not exist");
        return endCharCode_var;
    }
    ULONG startGlyphID() {
        assert_cond(startGlyphID_exists, "struct field startGlyphID does not exist");
        return startGlyphID_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tcmap_format8_groupings_struct& operator () () { return *instances.back(); }
    tcmap_format8_groupings_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tcmap_format8_groupings_struct(std::vector<tcmap_format8_groupings_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tcmap_format8_groupings_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tcmap_format8_groupings_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tcmap_format8_groupings_struct* generate();
};



class tcmap_format8_groupings_struct_array_class {
    tcmap_format8_groupings_struct& element;
    std::vector<tcmap_format8_groupings_struct*> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<tcmap_format8_groupings_struct*> operator () () { return value; }
    tcmap_format8_groupings_struct operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return *value[index];
    }
    tcmap_format8_groupings_struct_array_class(tcmap_format8_groupings_struct& element) : element(element) {}

    std::vector<tcmap_format8_groupings_struct*> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            value.push_back(element.generate());
            _sizeof += element._sizeof;
        }
        return value;
    }
};



class tcmap_format8 {
    std::vector<tcmap_format8*>& instances;

    USHORT reserved_var;
    ULONG length_var;
    ULONG language_var;
    std::string is32_var;
    ULONG nGroups_var;
    std::vector<tcmap_format8_groupings_struct*> groupings_var;

public:
    bool reserved_exists = false;
    bool length_exists = false;
    bool language_exists = false;
    bool is32_exists = false;
    bool nGroups_exists = false;
    bool groupings_exists = false;

    USHORT reserved() {
        assert_cond(reserved_exists, "struct field reserved does not exist");
        return reserved_var;
    }
    ULONG length() {
        assert_cond(length_exists, "struct field length does not exist");
        return length_var;
    }
    ULONG language() {
        assert_cond(language_exists, "struct field language does not exist");
        return language_var;
    }
    std::string is32() {
        assert_cond(is32_exists, "struct field is32 does not exist");
        return is32_var;
    }
    ULONG nGroups() {
        assert_cond(nGroups_exists, "struct field nGroups does not exist");
        return nGroups_var;
    }
    std::vector<tcmap_format8_groupings_struct*> groupings() {
        assert_cond(groupings_exists, "struct field groupings does not exist");
        return groupings_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tcmap_format8& operator () () { return *instances.back(); }
    tcmap_format8* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tcmap_format8(std::vector<tcmap_format8*>& instances) : instances(instances) { instances.push_back(this); }
    ~tcmap_format8() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tcmap_format8* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tcmap_format8* generate(quad& cmap_subtable);
};



class tcmap_format12_groupings_struct {
    std::vector<tcmap_format12_groupings_struct*>& instances;

    ULONG startCharCode_var;
    ULONG endCharCode_var;
    ULONG startGlyphID_var;

public:
    bool startCharCode_exists = false;
    bool endCharCode_exists = false;
    bool startGlyphID_exists = false;

    ULONG startCharCode() {
        assert_cond(startCharCode_exists, "struct field startCharCode does not exist");
        return startCharCode_var;
    }
    ULONG endCharCode() {
        assert_cond(endCharCode_exists, "struct field endCharCode does not exist");
        return endCharCode_var;
    }
    ULONG startGlyphID() {
        assert_cond(startGlyphID_exists, "struct field startGlyphID does not exist");
        return startGlyphID_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tcmap_format12_groupings_struct& operator () () { return *instances.back(); }
    tcmap_format12_groupings_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tcmap_format12_groupings_struct(std::vector<tcmap_format12_groupings_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tcmap_format12_groupings_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tcmap_format12_groupings_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tcmap_format12_groupings_struct* generate();
};



class tcmap_format12_groupings_struct_array_class {
    tcmap_format12_groupings_struct& element;
    std::vector<tcmap_format12_groupings_struct*> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<tcmap_format12_groupings_struct*> operator () () { return value; }
    tcmap_format12_groupings_struct operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return *value[index];
    }
    tcmap_format12_groupings_struct_array_class(tcmap_format12_groupings_struct& element) : element(element) {}

    std::vector<tcmap_format12_groupings_struct*> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            value.push_back(element.generate());
            _sizeof += element._sizeof;
        }
        return value;
    }
};



class tcmap_format12 {
    std::vector<tcmap_format12*>& instances;

    USHORT reserved_var;
    ULONG length_var;
    ULONG language_var;
    ULONG nGroups_var;
    std::vector<tcmap_format12_groupings_struct*> groupings_var;

public:
    bool reserved_exists = false;
    bool length_exists = false;
    bool language_exists = false;
    bool nGroups_exists = false;
    bool groupings_exists = false;

    USHORT reserved() {
        assert_cond(reserved_exists, "struct field reserved does not exist");
        return reserved_var;
    }
    ULONG length() {
        assert_cond(length_exists, "struct field length does not exist");
        return length_var;
    }
    ULONG language() {
        assert_cond(language_exists, "struct field language does not exist");
        return language_var;
    }
    ULONG nGroups() {
        assert_cond(nGroups_exists, "struct field nGroups does not exist");
        return nGroups_var;
    }
    std::vector<tcmap_format12_groupings_struct*> groupings() {
        assert_cond(groupings_exists, "struct field groupings does not exist");
        return groupings_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tcmap_format12& operator () () { return *instances.back(); }
    tcmap_format12* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tcmap_format12(std::vector<tcmap_format12*>& instances) : instances(instances) { instances.push_back(this); }
    ~tcmap_format12() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tcmap_format12* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tcmap_format12* generate();
};



class TT_FWord_class {
    int small;
    std::vector<TT_FWord> known_values;
    TT_FWord value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(TT_FWord);
    TT_FWord operator () () { return value; }
    TT_FWord_class(int small, std::vector<TT_FWord> known_values = {}) : small(small), known_values(known_values) {}

    TT_FWord generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(TT_FWord), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(TT_FWord), 0, known_values);
        }
        return value;
    }

    TT_FWord generate(std::vector<TT_FWord> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(TT_FWord), 0, possible_values);
        return value;
    }
};



class TT_UFWord_class {
    int small;
    std::vector<TT_UFWord> known_values;
    TT_UFWord value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(TT_UFWord);
    TT_UFWord operator () () { return value; }
    TT_UFWord_class(int small, std::vector<TT_UFWord> known_values = {}) : small(small), known_values(known_values) {}

    TT_UFWord generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(TT_UFWord), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(TT_UFWord), 0, known_values);
        }
        return value;
    }

    TT_UFWord generate(std::vector<TT_UFWord> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(TT_UFWord), 0, possible_values);
        return value;
    }
};



class thhea {
    std::vector<thhea*>& instances;

    ULONG version_var;
    TT_FWord Ascender_var;
    TT_FWord Descender_var;
    TT_FWord LineGap_var;
    TT_UFWord advanceWidthMax_var;
    TT_FWord minLeftSideBearing_var;
    TT_FWord minRightSideBearing_var;
    TT_FWord xMaxExtent_var;
    SHORT caretSlopeRise_var;
    SHORT caretSlopeRun_var;
    SHORT caretOffset_var;
    SHORT reserved_var;
    SHORT reserved1_var;
    SHORT reserved2_var;
    SHORT reserved3_var;
    SHORT metricDataFormat_var;
    USHORT numberOfHMetrics_var;

public:
    bool version_exists = false;
    bool Ascender_exists = false;
    bool Descender_exists = false;
    bool LineGap_exists = false;
    bool advanceWidthMax_exists = false;
    bool minLeftSideBearing_exists = false;
    bool minRightSideBearing_exists = false;
    bool xMaxExtent_exists = false;
    bool caretSlopeRise_exists = false;
    bool caretSlopeRun_exists = false;
    bool caretOffset_exists = false;
    bool reserved_exists = false;
    bool reserved1_exists = false;
    bool reserved2_exists = false;
    bool reserved3_exists = false;
    bool metricDataFormat_exists = false;
    bool numberOfHMetrics_exists = false;

    ULONG version() {
        assert_cond(version_exists, "struct field version does not exist");
        return version_var;
    }
    TT_FWord Ascender() {
        assert_cond(Ascender_exists, "struct field Ascender does not exist");
        return Ascender_var;
    }
    TT_FWord Descender() {
        assert_cond(Descender_exists, "struct field Descender does not exist");
        return Descender_var;
    }
    TT_FWord LineGap() {
        assert_cond(LineGap_exists, "struct field LineGap does not exist");
        return LineGap_var;
    }
    TT_UFWord advanceWidthMax() {
        assert_cond(advanceWidthMax_exists, "struct field advanceWidthMax does not exist");
        return advanceWidthMax_var;
    }
    TT_FWord minLeftSideBearing() {
        assert_cond(minLeftSideBearing_exists, "struct field minLeftSideBearing does not exist");
        return minLeftSideBearing_var;
    }
    TT_FWord minRightSideBearing() {
        assert_cond(minRightSideBearing_exists, "struct field minRightSideBearing does not exist");
        return minRightSideBearing_var;
    }
    TT_FWord xMaxExtent() {
        assert_cond(xMaxExtent_exists, "struct field xMaxExtent does not exist");
        return xMaxExtent_var;
    }
    SHORT caretSlopeRise() {
        assert_cond(caretSlopeRise_exists, "struct field caretSlopeRise does not exist");
        return caretSlopeRise_var;
    }
    SHORT caretSlopeRun() {
        assert_cond(caretSlopeRun_exists, "struct field caretSlopeRun does not exist");
        return caretSlopeRun_var;
    }
    SHORT caretOffset() {
        assert_cond(caretOffset_exists, "struct field caretOffset does not exist");
        return caretOffset_var;
    }
    SHORT reserved() {
        assert_cond(reserved_exists, "struct field reserved does not exist");
        return reserved_var;
    }
    SHORT reserved1() {
        assert_cond(reserved1_exists, "struct field reserved1 does not exist");
        return reserved1_var;
    }
    SHORT reserved2() {
        assert_cond(reserved2_exists, "struct field reserved2 does not exist");
        return reserved2_var;
    }
    SHORT reserved3() {
        assert_cond(reserved3_exists, "struct field reserved3 does not exist");
        return reserved3_var;
    }
    SHORT metricDataFormat() {
        assert_cond(metricDataFormat_exists, "struct field metricDataFormat does not exist");
        return metricDataFormat_var;
    }
    USHORT numberOfHMetrics() {
        assert_cond(numberOfHMetrics_exists, "struct field numberOfHMetrics does not exist");
        return numberOfHMetrics_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    thhea& operator () () { return *instances.back(); }
    thhea* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    thhea(std::vector<thhea*>& instances) : instances(instances) { instances.push_back(this); }
    ~thhea() {
        if (generated == 2)
            return;
        while (instances.size()) {
            thhea* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    thhea* generate();
};



class UBYTE_class {
    int small;
    std::vector<UBYTE> known_values;
    UBYTE value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(UBYTE);
    UBYTE operator () () { return value; }
    UBYTE_class(int small, std::vector<UBYTE> known_values = {}) : small(small), known_values(known_values) {}

    UBYTE generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(UBYTE), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(UBYTE), 0, known_values);
        }
        return value;
    }

    UBYTE generate(std::vector<UBYTE> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(UBYTE), 0, possible_values);
        return value;
    }
};



class tpanose {
    std::vector<tpanose*>& instances;

    UBYTE bFamilyType_var;
    UBYTE bSerifStyle_var;
    UBYTE bWeight_var;
    UBYTE bProportion_var;
    UBYTE bContrast_var;
    UBYTE bStrokeVariation_var;
    UBYTE bArmStyle_var;
    UBYTE bLetterform_var;
    UBYTE bMidline_var;
    UBYTE bXHeight_var;

public:
    bool bFamilyType_exists = false;
    bool bSerifStyle_exists = false;
    bool bWeight_exists = false;
    bool bProportion_exists = false;
    bool bContrast_exists = false;
    bool bStrokeVariation_exists = false;
    bool bArmStyle_exists = false;
    bool bLetterform_exists = false;
    bool bMidline_exists = false;
    bool bXHeight_exists = false;

    UBYTE bFamilyType() {
        assert_cond(bFamilyType_exists, "struct field bFamilyType does not exist");
        return bFamilyType_var;
    }
    UBYTE bSerifStyle() {
        assert_cond(bSerifStyle_exists, "struct field bSerifStyle does not exist");
        return bSerifStyle_var;
    }
    UBYTE bWeight() {
        assert_cond(bWeight_exists, "struct field bWeight does not exist");
        return bWeight_var;
    }
    UBYTE bProportion() {
        assert_cond(bProportion_exists, "struct field bProportion does not exist");
        return bProportion_var;
    }
    UBYTE bContrast() {
        assert_cond(bContrast_exists, "struct field bContrast does not exist");
        return bContrast_var;
    }
    UBYTE bStrokeVariation() {
        assert_cond(bStrokeVariation_exists, "struct field bStrokeVariation does not exist");
        return bStrokeVariation_var;
    }
    UBYTE bArmStyle() {
        assert_cond(bArmStyle_exists, "struct field bArmStyle does not exist");
        return bArmStyle_var;
    }
    UBYTE bLetterform() {
        assert_cond(bLetterform_exists, "struct field bLetterform does not exist");
        return bLetterform_var;
    }
    UBYTE bMidline() {
        assert_cond(bMidline_exists, "struct field bMidline does not exist");
        return bMidline_var;
    }
    UBYTE bXHeight() {
        assert_cond(bXHeight_exists, "struct field bXHeight does not exist");
        return bXHeight_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tpanose& operator () () { return *instances.back(); }
    tpanose* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tpanose(std::vector<tpanose*>& instances) : instances(instances) { instances.push_back(this); }
    ~tpanose() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tpanose* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tpanose* generate();
};



class CHAR_class {
    int small;
    std::vector<CHAR> known_values;
    CHAR value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(CHAR);
    CHAR operator () () { return value; }
    CHAR_class(int small, std::vector<CHAR> known_values = {}) : small(small), known_values(known_values) {}

    CHAR generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(CHAR), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(CHAR), 0, known_values);
        }
        return value;
    }

    CHAR generate(std::vector<CHAR> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(CHAR), 0, possible_values);
        return value;
    }
};



class CHAR_array_class {
    CHAR_class& element;
    std::vector<std::string> known_values;
    std::unordered_map<int, std::vector<CHAR>> element_known_values;
    std::string value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::string operator () () { return value; }
    CHAR operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    CHAR_array_class(CHAR_class& element, std::unordered_map<int, std::vector<CHAR>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}
    CHAR_array_class(CHAR_class& element, std::vector<std::string> known_values)
        : element(element), known_values(known_values) {}

    std::string generate(unsigned size, std::vector<std::string> possible_values = {}) {
        check_array_length(size);
        _startof = FTell();
        value = "";
        if (possible_values.size()) {
            value = file_acc.file_string(possible_values);
            assert(value.length() == size);
            _sizeof = size;
            return value;
        }
        if (known_values.size()) {
            value = file_acc.file_string(known_values);
            assert(value.length() == size);
            _sizeof = size;
            return value;
        }
        if (!element_known_values.size()) {
            if (size == 0)
                 return "";
            value = file_acc.file_string(size);
            _sizeof = size;
            return value;
        }
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(CHAR), 0, known->second));
                _sizeof += sizeof(CHAR);
            }
        }
        return value;
    }
};



class tOS_2 {
    std::vector<tOS_2*>& instances;

    USHORT version_tos_var;
    SHORT xAvgCharWidth_var;
    USHORT usWeightClass_var;
    USHORT usWidthClass_var;
    USHORT fsType_var;
    SHORT ySubscriptXSize_var;
    SHORT ySubscriptYSize_var;
    SHORT ySubscriptXOffset_var;
    SHORT ySubscriptYOffset_var;
    SHORT ySuperscriptXSize_var;
    SHORT ySuperscriptYSize_var;
    SHORT ySuperscriptXOffset_var;
    SHORT ySuperscriptYOffset_var;
    SHORT yStrikeoutSize_var;
    SHORT yStrikeoutPosition_var;
    SHORT sFamilyClass_var;
    tpanose* panose_var;
    ULONG ulUnicodeRange1_var;
    ULONG ulUnicodeRange2_var;
    ULONG ulUnicodeRange3_var;
    ULONG ulUnicodeRange4_var;
    std::string achVendID_var;
    USHORT fsSelection_var;
    USHORT usFirstCharIndex_var;
    USHORT usLastCharIndex_var;
    SHORT sTypoAscender_var;
    SHORT sTypoDescender_var;
    SHORT sTypoLineGap_var;
    USHORT usWinAscent_var;
    USHORT usWinDescent_var;
    ULONG ulCodePageRange1_var;
    ULONG ulCodePageRange2_var;
    SHORT sxHeight_var;
    SHORT sCapHeight_var;
    USHORT usDefaultChar_var;
    USHORT usBreakChar_var;
    USHORT usMaxContext_var;

public:
    bool version_tos_exists = false;
    bool xAvgCharWidth_exists = false;
    bool usWeightClass_exists = false;
    bool usWidthClass_exists = false;
    bool fsType_exists = false;
    bool ySubscriptXSize_exists = false;
    bool ySubscriptYSize_exists = false;
    bool ySubscriptXOffset_exists = false;
    bool ySubscriptYOffset_exists = false;
    bool ySuperscriptXSize_exists = false;
    bool ySuperscriptYSize_exists = false;
    bool ySuperscriptXOffset_exists = false;
    bool ySuperscriptYOffset_exists = false;
    bool yStrikeoutSize_exists = false;
    bool yStrikeoutPosition_exists = false;
    bool sFamilyClass_exists = false;
    bool panose_exists = false;
    bool ulUnicodeRange1_exists = false;
    bool ulUnicodeRange2_exists = false;
    bool ulUnicodeRange3_exists = false;
    bool ulUnicodeRange4_exists = false;
    bool achVendID_exists = false;
    bool fsSelection_exists = false;
    bool usFirstCharIndex_exists = false;
    bool usLastCharIndex_exists = false;
    bool sTypoAscender_exists = false;
    bool sTypoDescender_exists = false;
    bool sTypoLineGap_exists = false;
    bool usWinAscent_exists = false;
    bool usWinDescent_exists = false;
    bool ulCodePageRange1_exists = false;
    bool ulCodePageRange2_exists = false;
    bool sxHeight_exists = false;
    bool sCapHeight_exists = false;
    bool usDefaultChar_exists = false;
    bool usBreakChar_exists = false;
    bool usMaxContext_exists = false;

    USHORT version_tos() {
        assert_cond(version_tos_exists, "struct field version_tos does not exist");
        return version_tos_var;
    }
    SHORT xAvgCharWidth() {
        assert_cond(xAvgCharWidth_exists, "struct field xAvgCharWidth does not exist");
        return xAvgCharWidth_var;
    }
    USHORT usWeightClass() {
        assert_cond(usWeightClass_exists, "struct field usWeightClass does not exist");
        return usWeightClass_var;
    }
    USHORT usWidthClass() {
        assert_cond(usWidthClass_exists, "struct field usWidthClass does not exist");
        return usWidthClass_var;
    }
    USHORT fsType() {
        assert_cond(fsType_exists, "struct field fsType does not exist");
        return fsType_var;
    }
    SHORT ySubscriptXSize() {
        assert_cond(ySubscriptXSize_exists, "struct field ySubscriptXSize does not exist");
        return ySubscriptXSize_var;
    }
    SHORT ySubscriptYSize() {
        assert_cond(ySubscriptYSize_exists, "struct field ySubscriptYSize does not exist");
        return ySubscriptYSize_var;
    }
    SHORT ySubscriptXOffset() {
        assert_cond(ySubscriptXOffset_exists, "struct field ySubscriptXOffset does not exist");
        return ySubscriptXOffset_var;
    }
    SHORT ySubscriptYOffset() {
        assert_cond(ySubscriptYOffset_exists, "struct field ySubscriptYOffset does not exist");
        return ySubscriptYOffset_var;
    }
    SHORT ySuperscriptXSize() {
        assert_cond(ySuperscriptXSize_exists, "struct field ySuperscriptXSize does not exist");
        return ySuperscriptXSize_var;
    }
    SHORT ySuperscriptYSize() {
        assert_cond(ySuperscriptYSize_exists, "struct field ySuperscriptYSize does not exist");
        return ySuperscriptYSize_var;
    }
    SHORT ySuperscriptXOffset() {
        assert_cond(ySuperscriptXOffset_exists, "struct field ySuperscriptXOffset does not exist");
        return ySuperscriptXOffset_var;
    }
    SHORT ySuperscriptYOffset() {
        assert_cond(ySuperscriptYOffset_exists, "struct field ySuperscriptYOffset does not exist");
        return ySuperscriptYOffset_var;
    }
    SHORT yStrikeoutSize() {
        assert_cond(yStrikeoutSize_exists, "struct field yStrikeoutSize does not exist");
        return yStrikeoutSize_var;
    }
    SHORT yStrikeoutPosition() {
        assert_cond(yStrikeoutPosition_exists, "struct field yStrikeoutPosition does not exist");
        return yStrikeoutPosition_var;
    }
    SHORT sFamilyClass() {
        assert_cond(sFamilyClass_exists, "struct field sFamilyClass does not exist");
        return sFamilyClass_var;
    }
    tpanose& panose() {
        assert_cond(panose_exists, "struct field panose does not exist");
        return *panose_var;
    }
    ULONG ulUnicodeRange1() {
        assert_cond(ulUnicodeRange1_exists, "struct field ulUnicodeRange1 does not exist");
        return ulUnicodeRange1_var;
    }
    ULONG ulUnicodeRange2() {
        assert_cond(ulUnicodeRange2_exists, "struct field ulUnicodeRange2 does not exist");
        return ulUnicodeRange2_var;
    }
    ULONG ulUnicodeRange3() {
        assert_cond(ulUnicodeRange3_exists, "struct field ulUnicodeRange3 does not exist");
        return ulUnicodeRange3_var;
    }
    ULONG ulUnicodeRange4() {
        assert_cond(ulUnicodeRange4_exists, "struct field ulUnicodeRange4 does not exist");
        return ulUnicodeRange4_var;
    }
    std::string achVendID() {
        assert_cond(achVendID_exists, "struct field achVendID does not exist");
        return achVendID_var;
    }
    USHORT fsSelection() {
        assert_cond(fsSelection_exists, "struct field fsSelection does not exist");
        return fsSelection_var;
    }
    USHORT usFirstCharIndex() {
        assert_cond(usFirstCharIndex_exists, "struct field usFirstCharIndex does not exist");
        return usFirstCharIndex_var;
    }
    USHORT usLastCharIndex() {
        assert_cond(usLastCharIndex_exists, "struct field usLastCharIndex does not exist");
        return usLastCharIndex_var;
    }
    SHORT sTypoAscender() {
        assert_cond(sTypoAscender_exists, "struct field sTypoAscender does not exist");
        return sTypoAscender_var;
    }
    SHORT sTypoDescender() {
        assert_cond(sTypoDescender_exists, "struct field sTypoDescender does not exist");
        return sTypoDescender_var;
    }
    SHORT sTypoLineGap() {
        assert_cond(sTypoLineGap_exists, "struct field sTypoLineGap does not exist");
        return sTypoLineGap_var;
    }
    USHORT usWinAscent() {
        assert_cond(usWinAscent_exists, "struct field usWinAscent does not exist");
        return usWinAscent_var;
    }
    USHORT usWinDescent() {
        assert_cond(usWinDescent_exists, "struct field usWinDescent does not exist");
        return usWinDescent_var;
    }
    ULONG ulCodePageRange1() {
        assert_cond(ulCodePageRange1_exists, "struct field ulCodePageRange1 does not exist");
        return ulCodePageRange1_var;
    }
    ULONG ulCodePageRange2() {
        assert_cond(ulCodePageRange2_exists, "struct field ulCodePageRange2 does not exist");
        return ulCodePageRange2_var;
    }
    SHORT sxHeight() {
        assert_cond(sxHeight_exists, "struct field sxHeight does not exist");
        return sxHeight_var;
    }
    SHORT sCapHeight() {
        assert_cond(sCapHeight_exists, "struct field sCapHeight does not exist");
        return sCapHeight_var;
    }
    USHORT usDefaultChar() {
        assert_cond(usDefaultChar_exists, "struct field usDefaultChar does not exist");
        return usDefaultChar_var;
    }
    USHORT usBreakChar() {
        assert_cond(usBreakChar_exists, "struct field usBreakChar does not exist");
        return usBreakChar_var;
    }
    USHORT usMaxContext() {
        assert_cond(usMaxContext_exists, "struct field usMaxContext does not exist");
        return usMaxContext_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tOS_2& operator () () { return *instances.back(); }
    tOS_2* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tOS_2(std::vector<tOS_2*>& instances) : instances(instances) { instances.push_back(this); }
    ~tOS_2() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tOS_2* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tOS_2* generate();
};



class tmaxp {
    std::vector<tmaxp*>& instances;

    ULONG version_var;
    USHORT numGlyphs_var;
    USHORT maxPoints_var;
    USHORT maxContours_var;
    USHORT maxCompositePoints_var;
    USHORT maxCompositeContours_var;
    USHORT maxZones_var;
    USHORT maxTwilightPoints_var;
    USHORT maxStorage_var;
    USHORT maxFunctionDefs_var;
    USHORT maxInstructionDefs_var;
    USHORT maxStackElements_var;
    USHORT maxSizeOfInstructions_var;
    USHORT maxComponentElements_var;
    USHORT maxComponentDepth_var;

public:
    bool version_exists = false;
    bool numGlyphs_exists = false;
    bool maxPoints_exists = false;
    bool maxContours_exists = false;
    bool maxCompositePoints_exists = false;
    bool maxCompositeContours_exists = false;
    bool maxZones_exists = false;
    bool maxTwilightPoints_exists = false;
    bool maxStorage_exists = false;
    bool maxFunctionDefs_exists = false;
    bool maxInstructionDefs_exists = false;
    bool maxStackElements_exists = false;
    bool maxSizeOfInstructions_exists = false;
    bool maxComponentElements_exists = false;
    bool maxComponentDepth_exists = false;

    ULONG version() {
        assert_cond(version_exists, "struct field version does not exist");
        return version_var;
    }
    USHORT numGlyphs() {
        assert_cond(numGlyphs_exists, "struct field numGlyphs does not exist");
        return numGlyphs_var;
    }
    USHORT maxPoints() {
        assert_cond(maxPoints_exists, "struct field maxPoints does not exist");
        return maxPoints_var;
    }
    USHORT maxContours() {
        assert_cond(maxContours_exists, "struct field maxContours does not exist");
        return maxContours_var;
    }
    USHORT maxCompositePoints() {
        assert_cond(maxCompositePoints_exists, "struct field maxCompositePoints does not exist");
        return maxCompositePoints_var;
    }
    USHORT maxCompositeContours() {
        assert_cond(maxCompositeContours_exists, "struct field maxCompositeContours does not exist");
        return maxCompositeContours_var;
    }
    USHORT maxZones() {
        assert_cond(maxZones_exists, "struct field maxZones does not exist");
        return maxZones_var;
    }
    USHORT maxTwilightPoints() {
        assert_cond(maxTwilightPoints_exists, "struct field maxTwilightPoints does not exist");
        return maxTwilightPoints_var;
    }
    USHORT maxStorage() {
        assert_cond(maxStorage_exists, "struct field maxStorage does not exist");
        return maxStorage_var;
    }
    USHORT maxFunctionDefs() {
        assert_cond(maxFunctionDefs_exists, "struct field maxFunctionDefs does not exist");
        return maxFunctionDefs_var;
    }
    USHORT maxInstructionDefs() {
        assert_cond(maxInstructionDefs_exists, "struct field maxInstructionDefs does not exist");
        return maxInstructionDefs_var;
    }
    USHORT maxStackElements() {
        assert_cond(maxStackElements_exists, "struct field maxStackElements does not exist");
        return maxStackElements_var;
    }
    USHORT maxSizeOfInstructions() {
        assert_cond(maxSizeOfInstructions_exists, "struct field maxSizeOfInstructions does not exist");
        return maxSizeOfInstructions_var;
    }
    USHORT maxComponentElements() {
        assert_cond(maxComponentElements_exists, "struct field maxComponentElements does not exist");
        return maxComponentElements_var;
    }
    USHORT maxComponentDepth() {
        assert_cond(maxComponentDepth_exists, "struct field maxComponentDepth does not exist");
        return maxComponentDepth_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tmaxp& operator () () { return *instances.back(); }
    tmaxp* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tmaxp(std::vector<tmaxp*>& instances) : instances(instances) { instances.push_back(this); }
    ~tmaxp() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tmaxp* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tmaxp* generate();
};



class tlongHorMetric {
    std::vector<tlongHorMetric*>& instances;

    USHORT advanceWidth_var;
    SHORT lsb_var;

public:
    bool advanceWidth_exists = false;
    bool lsb_exists = false;

    USHORT advanceWidth() {
        assert_cond(advanceWidth_exists, "struct field advanceWidth does not exist");
        return advanceWidth_var;
    }
    SHORT lsb() {
        assert_cond(lsb_exists, "struct field lsb does not exist");
        return lsb_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tlongHorMetric& operator () () { return *instances.back(); }
    tlongHorMetric* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tlongHorMetric(std::vector<tlongHorMetric*>& instances) : instances(instances) { instances.push_back(this); }
    ~tlongHorMetric() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tlongHorMetric* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tlongHorMetric* generate();
};



class tlongHorMetric_array_class {
    tlongHorMetric& element;
    std::vector<tlongHorMetric*> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<tlongHorMetric*> operator () () { return value; }
    tlongHorMetric operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return *value[index];
    }
    tlongHorMetric_array_class(tlongHorMetric& element) : element(element) {}

    std::vector<tlongHorMetric*> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            value.push_back(element.generate());
            _sizeof += element._sizeof;
        }
        return value;
    }
};



class thmtx {
    std::vector<thmtx*>& instances;

    std::vector<tlongHorMetric*> hMetrics_var;
    std::vector<SHORT> leftSideBearing_var;

public:
    bool hMetrics_exists = false;
    bool leftSideBearing_exists = false;

    std::vector<tlongHorMetric*> hMetrics() {
        assert_cond(hMetrics_exists, "struct field hMetrics does not exist");
        return hMetrics_var;
    }
    std::vector<SHORT> leftSideBearing() {
        assert_cond(leftSideBearing_exists, "struct field leftSideBearing does not exist");
        return leftSideBearing_var;
    }

    /* locals */
    ulong numberOfHMetrics;
    ulong numLeftSideBearing;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    thmtx& operator () () { return *instances.back(); }
    thmtx* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    thmtx(std::vector<thmtx*>& instances) : instances(instances) { instances.push_back(this); }
    ~thmtx() {
        if (generated == 2)
            return;
        while (instances.size()) {
            thmtx* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    thmtx* generate();
};



class tname {
    std::vector<tname*>& instances;

    USHORT format_var;
    USHORT count_var;
    USHORT stringOffset_var;
    USHORT platformID_var;
    USHORT encodingID_var;
    USHORT languageID_var;
    USHORT nameID_var;
    USHORT length_var;
    USHORT offset_var;
    std::string name_var;

public:
    bool format_exists = false;
    bool count_exists = false;
    bool stringOffset_exists = false;
    bool platformID_exists = false;
    bool encodingID_exists = false;
    bool languageID_exists = false;
    bool nameID_exists = false;
    bool length_exists = false;
    bool offset_exists = false;
    bool name_exists = false;

    USHORT format() {
        assert_cond(format_exists, "struct field format does not exist");
        return format_var;
    }
    USHORT count() {
        assert_cond(count_exists, "struct field count does not exist");
        return count_var;
    }
    USHORT stringOffset() {
        assert_cond(stringOffset_exists, "struct field stringOffset does not exist");
        return stringOffset_var;
    }
    USHORT platformID() {
        assert_cond(platformID_exists, "struct field platformID does not exist");
        return platformID_var;
    }
    USHORT encodingID() {
        assert_cond(encodingID_exists, "struct field encodingID does not exist");
        return encodingID_var;
    }
    USHORT languageID() {
        assert_cond(languageID_exists, "struct field languageID does not exist");
        return languageID_var;
    }
    USHORT nameID() {
        assert_cond(nameID_exists, "struct field nameID does not exist");
        return nameID_var;
    }
    USHORT length() {
        assert_cond(length_exists, "struct field length does not exist");
        return length_var;
    }
    USHORT offset() {
        assert_cond(offset_exists, "struct field offset does not exist");
        return offset_var;
    }
    std::string name() {
        assert_cond(name_exists, "struct field name does not exist");
        return name_var;
    }

    /* locals */
    quad name_table;
    quad NextNameRecord;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tname& operator () () { return *instances.back(); }
    tname* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tname(std::vector<tname*>& instances) : instances(instances) { instances.push_back(this); }
    ~tname() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tname* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tname* generate();
};



class tpostName {
    std::vector<tpostName*>& instances;

    UBYTE length_var;
    std::string text_var;

public:
    bool length_exists = false;
    bool text_exists = false;

    UBYTE length() {
        assert_cond(length_exists, "struct field length does not exist");
        return length_var;
    }
    std::string text() {
        assert_cond(text_exists, "struct field text does not exist");
        return text_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tpostName& operator () () { return *instances.back(); }
    tpostName* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tpostName(std::vector<tpostName*>& instances) : instances(instances) { instances.push_back(this); }
    ~tpostName() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tpostName* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tpostName* generate();
};



class tpostName_array_class {
    tpostName& element;
    std::vector<tpostName*> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<tpostName*> operator () () { return value; }
    tpostName operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return *value[index];
    }
    tpostName_array_class(tpostName& element) : element(element) {}

    std::vector<tpostName*> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            value.push_back(element.generate());
            _sizeof += element._sizeof;
        }
        return value;
    }
};



class tpost {
    std::vector<tpost*>& instances;

    ULONG version_var;
    ULONG italicAngle_var;
    TT_FWord underlinePosition_var;
    TT_FWord underlineThickness_var;
    ULONG isFixedPitch_var;
    ULONG minMemType42_var;
    ULONG maxMemType42_var;
    ULONG minMemType1_var;
    ULONG maxMemType1_var;
    USHORT numberOfGlyphs_var;
    std::vector<USHORT> glyphNameIndex_var;
    std::vector<tpostName*> name_var;
    std::vector<USHORT> tpostoffset_var;

public:
    bool version_exists = false;
    bool italicAngle_exists = false;
    bool underlinePosition_exists = false;
    bool underlineThickness_exists = false;
    bool isFixedPitch_exists = false;
    bool minMemType42_exists = false;
    bool maxMemType42_exists = false;
    bool minMemType1_exists = false;
    bool maxMemType1_exists = false;
    bool numberOfGlyphs_exists = false;
    bool glyphNameIndex_exists = false;
    bool name_exists = false;
    bool tpostoffset_exists = false;

    ULONG version() {
        assert_cond(version_exists, "struct field version does not exist");
        return version_var;
    }
    ULONG italicAngle() {
        assert_cond(italicAngle_exists, "struct field italicAngle does not exist");
        return italicAngle_var;
    }
    TT_FWord underlinePosition() {
        assert_cond(underlinePosition_exists, "struct field underlinePosition does not exist");
        return underlinePosition_var;
    }
    TT_FWord underlineThickness() {
        assert_cond(underlineThickness_exists, "struct field underlineThickness does not exist");
        return underlineThickness_var;
    }
    ULONG isFixedPitch() {
        assert_cond(isFixedPitch_exists, "struct field isFixedPitch does not exist");
        return isFixedPitch_var;
    }
    ULONG minMemType42() {
        assert_cond(minMemType42_exists, "struct field minMemType42 does not exist");
        return minMemType42_var;
    }
    ULONG maxMemType42() {
        assert_cond(maxMemType42_exists, "struct field maxMemType42 does not exist");
        return maxMemType42_var;
    }
    ULONG minMemType1() {
        assert_cond(minMemType1_exists, "struct field minMemType1 does not exist");
        return minMemType1_var;
    }
    ULONG maxMemType1() {
        assert_cond(maxMemType1_exists, "struct field maxMemType1 does not exist");
        return maxMemType1_var;
    }
    USHORT numberOfGlyphs() {
        assert_cond(numberOfGlyphs_exists, "struct field numberOfGlyphs does not exist");
        return numberOfGlyphs_var;
    }
    std::vector<USHORT> glyphNameIndex() {
        assert_cond(glyphNameIndex_exists, "struct field glyphNameIndex does not exist");
        return glyphNameIndex_var;
    }
    std::vector<tpostName*> name() {
        assert_cond(name_exists, "struct field name does not exist");
        return name_var;
    }
    std::vector<USHORT> tpostoffset() {
        assert_cond(tpostoffset_exists, "struct field tpostoffset does not exist");
        return tpostoffset_var;
    }

    /* locals */
    quad post;
    ushort numGlyphs;
    ushort numberNewGlyphs;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tpost& operator () () { return *instances.back(); }
    tpost* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tpost(std::vector<tpost*>& instances) : instances(instances) { instances.push_back(this); }
    ~tpost() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tpost* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tpost* generate();
};



class TT_FWord_array_class {
    TT_FWord_class& element;
    std::unordered_map<int, std::vector<TT_FWord>> element_known_values;
    std::vector<TT_FWord> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<TT_FWord> operator () () { return value; }
    TT_FWord operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    TT_FWord_array_class(TT_FWord_class& element, std::unordered_map<int, std::vector<TT_FWord>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}

    std::vector<TT_FWord> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(TT_FWord), 0, known->second));
                _sizeof += sizeof(TT_FWord);
            }
        }
        return value;
    }
};



class tcvt {
    std::vector<tcvt*>& instances;

    std::vector<TT_FWord> value_var;

public:
    bool value_exists = false;

    std::vector<TT_FWord> value() {
        assert_cond(value_exists, "struct field value does not exist");
        return value_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tcvt& operator () () { return *instances.back(); }
    tcvt* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tcvt(std::vector<tcvt*>& instances) : instances(instances) { instances.push_back(this); }
    ~tcvt() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tcvt* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tcvt* generate();
};



class UBYTE_array_class {
    UBYTE_class& element;
    std::vector<std::string> known_values;
    std::unordered_map<int, std::vector<UBYTE>> element_known_values;
    std::string value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::string operator () () { return value; }
    UBYTE operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    UBYTE_array_class(UBYTE_class& element, std::unordered_map<int, std::vector<UBYTE>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}
    UBYTE_array_class(UBYTE_class& element, std::vector<std::string> known_values)
        : element(element), known_values(known_values) {}

    std::string generate(unsigned size, std::vector<std::string> possible_values = {}) {
        check_array_length(size);
        _startof = FTell();
        value = "";
        if (possible_values.size()) {
            value = file_acc.file_string(possible_values);
            assert(value.length() == size);
            _sizeof = size;
            return value;
        }
        if (known_values.size()) {
            value = file_acc.file_string(known_values);
            assert(value.length() == size);
            _sizeof = size;
            return value;
        }
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(UBYTE), 0, known->second));
                _sizeof += sizeof(UBYTE);
            }
        }
        return value;
    }
};



class tfpgm {
    std::vector<tfpgm*>& instances;

    std::string bytecode_var;

public:
    bool bytecode_exists = false;

    std::string bytecode() {
        assert_cond(bytecode_exists, "struct field bytecode does not exist");
        return bytecode_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tfpgm& operator () () { return *instances.back(); }
    tfpgm* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tfpgm(std::vector<tfpgm*>& instances) : instances(instances) { instances.push_back(this); }
    ~tfpgm() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tfpgm* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tfpgm* generate();
};



class ULONG_array_class {
    ULONG_class& element;
    std::unordered_map<int, std::vector<ULONG>> element_known_values;
    std::vector<ULONG> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<ULONG> operator () () { return value; }
    ULONG operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    ULONG_array_class(ULONG_class& element, std::unordered_map<int, std::vector<ULONG>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}

    std::vector<ULONG> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(ULONG), 0, known->second));
                _sizeof += sizeof(ULONG);
            }
        }
        return value;
    }
};



class tloca {
    std::vector<tloca*>& instances;


public:


    /* locals */
    ulong tloca_n;
    short format;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tloca& operator () () { return *instances.back(); }
    tloca* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tloca(std::vector<tloca*>& instances) : instances(instances) { instances.push_back(this); }
    ~tloca() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tloca* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tloca* generate();
};



class tPoints {
    std::vector<tPoints*>& instances;


public:


    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tPoints& operator () () { return *instances.back(); }
    tPoints* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tPoints(std::vector<tPoints*>& instances) : instances(instances) { instances.push_back(this); }
    ~tPoints() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tPoints* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tPoints* generate(ulong& i_sgp, quad& xStart, quad& xLast, quad& yStart, quad& yLast, byte& xLastByte, byte& yLastByte, int& g_lenngth);
};



class tSimpleGlyphPoints {
    std::vector<tSimpleGlyphPoints*>& instances;

    std::string SimpleGlyph_flag_var;
    tPoints* points_var;

public:
    bool SimpleGlyph_flag_exists = false;
    bool points_exists = false;

    std::string SimpleGlyph_flag() {
        assert_cond(SimpleGlyph_flag_exists, "struct field SimpleGlyph_flag does not exist");
        return SimpleGlyph_flag_var;
    }
    tPoints& points() {
        assert_cond(points_exists, "struct field points does not exist");
        return *points_var;
    }

    /* locals */
    ulong i_sgp;
    quad yusn_start;
    quad xStart;
    quad xLast;
    quad yStart;
    quad yLast;
    byte xLastByte;
    byte yLastByte;
    int g_lenngth;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tSimpleGlyphPoints& operator () () { return *instances.back(); }
    tSimpleGlyphPoints* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tSimpleGlyphPoints(std::vector<tSimpleGlyphPoints*>& instances) : instances(instances) { instances.push_back(this); }
    ~tSimpleGlyphPoints() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tSimpleGlyphPoints* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tSimpleGlyphPoints* generate(USHORT& numPoints);
};



class tSimpleGlyph {
    std::vector<tSimpleGlyph*>& instances;

    SHORT numberOfContoursl_var;
    SHORT xMin_var;
    SHORT yMin_var;
    SHORT xMax_var;
    SHORT yMax_var;
    SHORT endPtsOfContoursl_var;
    USHORT instructionLengthl_var;
    std::string instructions_var;
    tSimpleGlyphPoints* contours_var;

public:
    bool numberOfContoursl_exists = false;
    bool xMin_exists = false;
    bool yMin_exists = false;
    bool xMax_exists = false;
    bool yMax_exists = false;
    bool endPtsOfContoursl_exists = false;
    bool instructionLengthl_exists = false;
    bool instructions_exists = false;
    bool contours_exists = false;

    SHORT numberOfContoursl() {
        assert_cond(numberOfContoursl_exists, "struct field numberOfContoursl does not exist");
        return numberOfContoursl_var;
    }
    SHORT xMin() {
        assert_cond(xMin_exists, "struct field xMin does not exist");
        return xMin_var;
    }
    SHORT yMin() {
        assert_cond(yMin_exists, "struct field yMin does not exist");
        return yMin_var;
    }
    SHORT xMax() {
        assert_cond(xMax_exists, "struct field xMax does not exist");
        return xMax_var;
    }
    SHORT yMax() {
        assert_cond(yMax_exists, "struct field yMax does not exist");
        return yMax_var;
    }
    SHORT endPtsOfContoursl() {
        assert_cond(endPtsOfContoursl_exists, "struct field endPtsOfContoursl does not exist");
        return endPtsOfContoursl_var;
    }
    USHORT instructionLengthl() {
        assert_cond(instructionLengthl_exists, "struct field instructionLengthl does not exist");
        return instructionLengthl_var;
    }
    std::string instructions() {
        assert_cond(instructions_exists, "struct field instructions does not exist");
        return instructions_var;
    }
    tSimpleGlyphPoints& contours() {
        assert_cond(contours_exists, "struct field contours does not exist");
        return *contours_var;
    }

    /* locals */
    int n;
    USHORT numPoints;
    quad glyf_flag_table;
    quad glyf_flag_index;
    ushort i;
    ubyte repeat;
    ubyte flag_value;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tSimpleGlyph& operator () () { return *instances.back(); }
    tSimpleGlyph* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tSimpleGlyph(std::vector<tSimpleGlyph*>& instances) : instances(instances) { instances.push_back(this); }
    ~tSimpleGlyph() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tSimpleGlyph* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tSimpleGlyph* generate();
};



class tglyf {
    std::vector<tglyf*>& instances;

    tSimpleGlyph* SimpleGlyph_var;

public:
    bool SimpleGlyph_exists = false;

    tSimpleGlyph& SimpleGlyph() {
        assert_cond(SimpleGlyph_exists, "struct field SimpleGlyph does not exist");
        return *SimpleGlyph_var;
    }

    /* locals */
    quad glyf_table;
    quad glyf_offset;
    ulong n;
    USHORT tSimpleGlyph_length;
    int index_g;
    USHORT locaoffsets;
    USHORT l_offset;
    quad start_gly;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tglyf& operator () () { return *instances.back(); }
    tglyf* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tglyf(std::vector<tglyf*>& instances) : instances(instances) { instances.push_back(this); }
    ~tglyf() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tglyf* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tglyf* generate();
};



class tprep {
    std::vector<tprep*>& instances;

    std::string bytecode_var;

public:
    bool bytecode_exists = false;

    std::string bytecode() {
        assert_cond(bytecode_exists, "struct field bytecode does not exist");
        return bytecode_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tprep& operator () () { return *instances.back(); }
    tprep* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tprep(std::vector<tprep*>& instances) : instances(instances) { instances.push_back(this); }
    ~tprep() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tprep* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tprep* generate();
};



class TT_Offset_class {
    int small;
    std::vector<TT_Offset> known_values;
    TT_Offset value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(TT_Offset);
    TT_Offset operator () () { return value; }
    TT_Offset_class(int small, std::vector<TT_Offset> known_values = {}) : small(small), known_values(known_values) {}

    TT_Offset generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(TT_Offset), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(TT_Offset), 0, known_values);
        }
        return value;
    }

    TT_Offset generate(std::vector<TT_Offset> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(TT_Offset), 0, possible_values);
        return value;
    }
};



class tGDEF {
    std::vector<tGDEF*>& instances;

    ULONG Version_var;
    TT_Offset GlyphClassDef_var;
    TT_Offset AttachList_var;
    TT_Offset LigCaretList_var;
    TT_Offset MarkAttachClassDef_var;

public:
    bool Version_exists = false;
    bool GlyphClassDef_exists = false;
    bool AttachList_exists = false;
    bool LigCaretList_exists = false;
    bool MarkAttachClassDef_exists = false;

    ULONG Version() {
        assert_cond(Version_exists, "struct field Version does not exist");
        return Version_var;
    }
    TT_Offset GlyphClassDef() {
        assert_cond(GlyphClassDef_exists, "struct field GlyphClassDef does not exist");
        return GlyphClassDef_var;
    }
    TT_Offset AttachList() {
        assert_cond(AttachList_exists, "struct field AttachList does not exist");
        return AttachList_var;
    }
    TT_Offset LigCaretList() {
        assert_cond(LigCaretList_exists, "struct field LigCaretList does not exist");
        return LigCaretList_var;
    }
    TT_Offset MarkAttachClassDef() {
        assert_cond(MarkAttachClassDef_exists, "struct field MarkAttachClassDef does not exist");
        return MarkAttachClassDef_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tGDEF& operator () () { return *instances.back(); }
    tGDEF* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tGDEF(std::vector<tGDEF*>& instances) : instances(instances) { instances.push_back(this); }
    ~tGDEF() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tGDEF* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tGDEF* generate();
};



class ubyte_class {
    int small;
    std::vector<ubyte> known_values;
    ubyte value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(ubyte);
    ubyte operator () () { return value; }
    ubyte_class(int small, std::vector<ubyte> known_values = {}) : small(small), known_values(known_values) {}

    ubyte generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(ubyte), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(ubyte), 0, known_values);
        }
        return value;
    }

    ubyte generate(std::vector<ubyte> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(ubyte), 0, possible_values);
        return value;
    }
};



class uint16_array_class {
    uint16_class& element;
    std::unordered_map<int, std::vector<uint16>> element_known_values;
    std::vector<uint16> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<uint16> operator () () { return value; }
    uint16 operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    uint16_array_class(uint16_class& element, std::unordered_map<int, std::vector<uint16>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}

    std::vector<uint16> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(uint16), 0, known->second));
                _sizeof += sizeof(uint16);
            }
        }
        return value;
    }
};



class tLangSysTable {
    std::vector<tLangSysTable*>& instances;

    USHORT LookupOrder_var;
    uint16 ReqFeatureIndex_var;
    ubyte FeatureCounth_var;
    ubyte FeatureCountl_var;
    std::vector<uint16> FeatureIndex_var;

public:
    bool LookupOrder_exists = false;
    bool ReqFeatureIndex_exists = false;
    bool FeatureCounth_exists = false;
    bool FeatureCountl_exists = false;
    bool FeatureIndex_exists = false;

    USHORT LookupOrder() {
        assert_cond(LookupOrder_exists, "struct field LookupOrder does not exist");
        return LookupOrder_var;
    }
    uint16 ReqFeatureIndex() {
        assert_cond(ReqFeatureIndex_exists, "struct field ReqFeatureIndex does not exist");
        return ReqFeatureIndex_var;
    }
    ubyte FeatureCounth() {
        assert_cond(FeatureCounth_exists, "struct field FeatureCounth does not exist");
        return FeatureCounth_var;
    }
    ubyte FeatureCountl() {
        assert_cond(FeatureCountl_exists, "struct field FeatureCountl does not exist");
        return FeatureCountl_var;
    }
    std::vector<uint16> FeatureIndex() {
        assert_cond(FeatureIndex_exists, "struct field FeatureIndex does not exist");
        return FeatureIndex_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tLangSysTable& operator () () { return *instances.back(); }
    tLangSysTable* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tLangSysTable(std::vector<tLangSysTable*>& instances) : instances(instances) { instances.push_back(this); }
    ~tLangSysTable() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tLangSysTable* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tLangSysTable* generate();
};



class tLangSysRecord {
    std::vector<tLangSysRecord*>& instances;

    std::string LangSysTag_var;
    USHORT Offset_var;
    tLangSysTable* LangSysTable_var;

public:
    bool LangSysTag_exists = false;
    bool Offset_exists = false;
    bool LangSysTable_exists = false;

    std::string LangSysTag() {
        assert_cond(LangSysTag_exists, "struct field LangSysTag does not exist");
        return LangSysTag_var;
    }
    USHORT Offset() {
        assert_cond(Offset_exists, "struct field Offset does not exist");
        return Offset_var;
    }
    tLangSysTable& LangSysTable() {
        assert_cond(LangSysTable_exists, "struct field LangSysTable does not exist");
        return *LangSysTable_var;
    }

    /* locals */
    USHORT tLanglength;
    quad next;
    quad LangSys;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tLangSysRecord& operator () () { return *instances.back(); }
    tLangSysRecord* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tLangSysRecord(std::vector<tLangSysRecord*>& instances) : instances(instances) { instances.push_back(this); }
    ~tLangSysRecord() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tLangSysRecord* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tLangSysRecord* generate(ubyte LangSysCount);
};



class tScriptRecord_ScriptTable_struct {
    std::vector<tScriptRecord_ScriptTable_struct*>& instances;

    USHORT DefaultLangSys_var;
    ubyte LangSysCounth_var;
    ubyte LangSysCountl_var;
    tLangSysRecord* LangSysRecord_var;

public:
    bool DefaultLangSys_exists = false;
    bool LangSysCounth_exists = false;
    bool LangSysCountl_exists = false;
    bool LangSysRecord_exists = false;

    USHORT DefaultLangSys() {
        assert_cond(DefaultLangSys_exists, "struct field DefaultLangSys does not exist");
        return DefaultLangSys_var;
    }
    ubyte LangSysCounth() {
        assert_cond(LangSysCounth_exists, "struct field LangSysCounth does not exist");
        return LangSysCounth_var;
    }
    ubyte LangSysCountl() {
        assert_cond(LangSysCountl_exists, "struct field LangSysCountl does not exist");
        return LangSysCountl_var;
    }
    tLangSysRecord& LangSysRecord() {
        assert_cond(LangSysRecord_exists, "struct field LangSysRecord does not exist");
        return *LangSysRecord_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tScriptRecord_ScriptTable_struct& operator () () { return *instances.back(); }
    tScriptRecord_ScriptTable_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tScriptRecord_ScriptTable_struct(std::vector<tScriptRecord_ScriptTable_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tScriptRecord_ScriptTable_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tScriptRecord_ScriptTable_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tScriptRecord_ScriptTable_struct* generate(int& l_cont);
};



class tScriptRecord {
    std::vector<tScriptRecord*>& instances;

    std::string ScriptTag_var;
    USHORT Offset_var;
    tScriptRecord_ScriptTable_struct* ScriptTable_var;
    USHORT DefaultLangSys_var;
    tLangSysTable* DefaultLangSysTable_var;

public:
    bool ScriptTag_exists = false;
    bool Offset_exists = false;
    bool ScriptTable_exists = false;
    bool DefaultLangSys_exists = false;
    bool DefaultLangSysTable_exists = false;

    std::string ScriptTag() {
        assert_cond(ScriptTag_exists, "struct field ScriptTag does not exist");
        return ScriptTag_var;
    }
    USHORT Offset() {
        assert_cond(Offset_exists, "struct field Offset does not exist");
        return Offset_var;
    }
    tScriptRecord_ScriptTable_struct& ScriptTable() {
        assert_cond(ScriptTable_exists, "struct field ScriptTable does not exist");
        return *ScriptTable_var;
    }
    USHORT DefaultLangSys() {
        assert_cond(DefaultLangSys_exists, "struct field DefaultLangSys does not exist");
        return DefaultLangSys_var;
    }
    tLangSysTable& DefaultLangSysTable() {
        assert_cond(DefaultLangSysTable_exists, "struct field DefaultLangSysTable does not exist");
        return *DefaultLangSysTable_var;
    }

    /* locals */
    USHORT soffset_l;
    quad next;
    int l_cont;
    USHORT DefaultLangSyslength;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tScriptRecord& operator () () { return *instances.back(); }
    tScriptRecord* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tScriptRecord(std::vector<tScriptRecord*>& instances) : instances(instances) { instances.push_back(this); }
    ~tScriptRecord() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tScriptRecord* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tScriptRecord* generate(ubyte ScriptCount, USHORT& ScriptRecordlength);
};



class tScriptList {
    std::vector<tScriptList*>& instances;

    USHORT Offset_var;
    uint16 ScriptCountl_var;
    tScriptRecord* ScriptRecord_var;

public:
    bool Offset_exists = false;
    bool ScriptCountl_exists = false;
    bool ScriptRecord_exists = false;

    USHORT Offset() {
        assert_cond(Offset_exists, "struct field Offset does not exist");
        return Offset_var;
    }
    uint16 ScriptCountl() {
        assert_cond(ScriptCountl_exists, "struct field ScriptCountl does not exist");
        return ScriptCountl_var;
    }
    tScriptRecord& ScriptRecord() {
        assert_cond(ScriptRecord_exists, "struct field ScriptRecord does not exist");
        return *ScriptRecord_var;
    }

    /* locals */
    quad next;
    USHORT ScriptRecordlength;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tScriptList& operator () () { return *instances.back(); }
    tScriptList* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tScriptList(std::vector<tScriptList*>& instances) : instances(instances) { instances.push_back(this); }
    ~tScriptList() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tScriptList* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tScriptList* generate(quad& GSUBorGPOS_table);
};



class tFeatureRecord_FeatureTable_struct {
    std::vector<tFeatureRecord_FeatureTable_struct*>& instances;

    uint16 FeatureParams_var;
    ubyte LookupListCounth_var;
    ubyte LookupListCountl_var;
    std::vector<uint16> LookupListIndex_var;

public:
    bool FeatureParams_exists = false;
    bool LookupListCounth_exists = false;
    bool LookupListCountl_exists = false;
    bool LookupListIndex_exists = false;

    uint16 FeatureParams() {
        assert_cond(FeatureParams_exists, "struct field FeatureParams does not exist");
        return FeatureParams_var;
    }
    ubyte LookupListCounth() {
        assert_cond(LookupListCounth_exists, "struct field LookupListCounth does not exist");
        return LookupListCounth_var;
    }
    ubyte LookupListCountl() {
        assert_cond(LookupListCountl_exists, "struct field LookupListCountl does not exist");
        return LookupListCountl_var;
    }
    std::vector<uint16> LookupListIndex() {
        assert_cond(LookupListIndex_exists, "struct field LookupListIndex does not exist");
        return LookupListIndex_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tFeatureRecord_FeatureTable_struct& operator () () { return *instances.back(); }
    tFeatureRecord_FeatureTable_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tFeatureRecord_FeatureTable_struct(std::vector<tFeatureRecord_FeatureTable_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tFeatureRecord_FeatureTable_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tFeatureRecord_FeatureTable_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tFeatureRecord_FeatureTable_struct* generate();
};



class tFeatureRecord {
    std::vector<tFeatureRecord*>& instances;

    std::string FeatureTag_var;
    USHORT Offset_var;
    tFeatureRecord_FeatureTable_struct* FeatureTable_var;

public:
    bool FeatureTag_exists = false;
    bool Offset_exists = false;
    bool FeatureTable_exists = false;

    std::string FeatureTag() {
        assert_cond(FeatureTag_exists, "struct field FeatureTag does not exist");
        return FeatureTag_var;
    }
    USHORT Offset() {
        assert_cond(Offset_exists, "struct field Offset does not exist");
        return Offset_var;
    }
    tFeatureRecord_FeatureTable_struct& FeatureTable() {
        assert_cond(FeatureTable_exists, "struct field FeatureTable does not exist");
        return *FeatureTable_var;
    }

    /* locals */
    USHORT tmptFeatureRecord;
    quad next;
    quad FeatureTable_table;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tFeatureRecord& operator () () { return *instances.back(); }
    tFeatureRecord* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tFeatureRecord(std::vector<tFeatureRecord*>& instances) : instances(instances) { instances.push_back(this); }
    ~tFeatureRecord() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tFeatureRecord* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tFeatureRecord* generate(ubyte FeatureCount, USHORT& tFeatureRecordlength);
};



class tFeatureList {
    std::vector<tFeatureList*>& instances;

    USHORT Offset_var;
    ubyte FeatureCounth_var;
    ubyte FeatureCountl_var;
    tFeatureRecord* FeatureRecord_var;

public:
    bool Offset_exists = false;
    bool FeatureCounth_exists = false;
    bool FeatureCountl_exists = false;
    bool FeatureRecord_exists = false;

    USHORT Offset() {
        assert_cond(Offset_exists, "struct field Offset does not exist");
        return Offset_var;
    }
    ubyte FeatureCounth() {
        assert_cond(FeatureCounth_exists, "struct field FeatureCounth does not exist");
        return FeatureCounth_var;
    }
    ubyte FeatureCountl() {
        assert_cond(FeatureCountl_exists, "struct field FeatureCountl does not exist");
        return FeatureCountl_var;
    }
    tFeatureRecord& FeatureRecord() {
        assert_cond(FeatureRecord_exists, "struct field FeatureRecord does not exist");
        return *FeatureRecord_var;
    }

    /* locals */
    quad next;
    USHORT tFeatureRecordlength;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tFeatureList& operator () () { return *instances.back(); }
    tFeatureList* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tFeatureList(std::vector<tFeatureList*>& instances) : instances(instances) { instances.push_back(this); }
    ~tFeatureList() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tFeatureList* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tFeatureList* generate(USHORT tFeaturelength, quad& GSUBorGPOS_table);
};



class tLookupRecord {
    std::vector<tLookupRecord*>& instances;

    USHORT Offset_var;
    uint16 LookupType_var;
    uint16 LookupFlag_var;
    ubyte SubTableCounth_var;
    ubyte SubTableCountl_var;
    std::vector<USHORT> SubTable_var;

public:
    bool Offset_exists = false;
    bool LookupType_exists = false;
    bool LookupFlag_exists = false;
    bool SubTableCounth_exists = false;
    bool SubTableCountl_exists = false;
    bool SubTable_exists = false;

    USHORT Offset() {
        assert_cond(Offset_exists, "struct field Offset does not exist");
        return Offset_var;
    }
    uint16 LookupType() {
        assert_cond(LookupType_exists, "struct field LookupType does not exist");
        return LookupType_var;
    }
    uint16 LookupFlag() {
        assert_cond(LookupFlag_exists, "struct field LookupFlag does not exist");
        return LookupFlag_var;
    }
    ubyte SubTableCounth() {
        assert_cond(SubTableCounth_exists, "struct field SubTableCounth does not exist");
        return SubTableCounth_var;
    }
    ubyte SubTableCountl() {
        assert_cond(SubTableCountl_exists, "struct field SubTableCountl does not exist");
        return SubTableCountl_var;
    }
    std::vector<USHORT> SubTable() {
        assert_cond(SubTable_exists, "struct field SubTable does not exist");
        return SubTable_var;
    }

    /* locals */
    USHORT tmptLookupRecord;
    quad next;
    quad tLookupRecord_table;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tLookupRecord& operator () () { return *instances.back(); }
    tLookupRecord* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tLookupRecord(std::vector<tLookupRecord*>& instances) : instances(instances) { instances.push_back(this); }
    ~tLookupRecord() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tLookupRecord* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tLookupRecord* generate(ubyte LookupCount, USHORT& tLookupRecordlength, quad& tLookupListend);
};



class tLookupList {
    std::vector<tLookupList*>& instances;

    USHORT Offset_var;
    ubyte LookupCounth_var;
    ubyte LookupCountl_var;
    tLookupRecord* LookupRecord_var;

public:
    bool Offset_exists = false;
    bool LookupCounth_exists = false;
    bool LookupCountl_exists = false;
    bool LookupRecord_exists = false;

    USHORT Offset() {
        assert_cond(Offset_exists, "struct field Offset does not exist");
        return Offset_var;
    }
    ubyte LookupCounth() {
        assert_cond(LookupCounth_exists, "struct field LookupCounth does not exist");
        return LookupCounth_var;
    }
    ubyte LookupCountl() {
        assert_cond(LookupCountl_exists, "struct field LookupCountl does not exist");
        return LookupCountl_var;
    }
    tLookupRecord& LookupRecord() {
        assert_cond(LookupRecord_exists, "struct field LookupRecord does not exist");
        return *LookupRecord_var;
    }

    /* locals */
    quad next;
    USHORT tLookupRecordlength;
    quad tLookupListend;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tLookupList& operator () () { return *instances.back(); }
    tLookupList* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tLookupList(std::vector<tLookupList*>& instances) : instances(instances) { instances.push_back(this); }
    ~tLookupList() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tLookupList* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tLookupList* generate(USHORT tLookupListlength, quad& GSUBorGPOS_table);
};



class tGSUBorGPOS {
    std::vector<tGSUBorGPOS*>& instances;

    ULONG Version_var;
    tScriptList* ScriptList_var;
    tFeatureList* FeatureList_var;
    tLookupList* LookupList_var;

public:
    bool Version_exists = false;
    bool ScriptList_exists = false;
    bool FeatureList_exists = false;
    bool LookupList_exists = false;

    ULONG Version() {
        assert_cond(Version_exists, "struct field Version does not exist");
        return Version_var;
    }
    tScriptList& ScriptList() {
        assert_cond(ScriptList_exists, "struct field ScriptList does not exist");
        return *ScriptList_var;
    }
    tFeatureList& FeatureList() {
        assert_cond(FeatureList_exists, "struct field FeatureList does not exist");
        return *FeatureList_var;
    }
    tLookupList& LookupList() {
        assert_cond(LookupList_exists, "struct field LookupList does not exist");
        return *LookupList_var;
    }

    /* locals */
    quad GSUBorGPOS_table;
    USHORT Fllength;
    USHORT Lllength;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tGSUBorGPOS& operator () () { return *instances.back(); }
    tGSUBorGPOS* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tGSUBorGPOS(std::vector<tGSUBorGPOS*>& instances) : instances(instances) { instances.push_back(this); }
    ~tGSUBorGPOS() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tGSUBorGPOS* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tGSUBorGPOS* generate();
};



class tDSIG {
    std::vector<tDSIG*>& instances;

    ULONG ulVersion_var;
    UBYTE usNumSigsh_var;
    UBYTE usNumSigsl_var;
    USHORT usFlag_var;
    ULONG ulFormat_var;
    ULONG ulLength_var;
    ULONG ulOffset_var;
    USHORT usReserved1_var;
    USHORT usReserved2_var;
    USHORT cbSignatureh_var;
    USHORT cbSignaturel_var;
    std::string bSignature_var;

public:
    bool ulVersion_exists = false;
    bool usNumSigsh_exists = false;
    bool usNumSigsl_exists = false;
    bool usFlag_exists = false;
    bool ulFormat_exists = false;
    bool ulLength_exists = false;
    bool ulOffset_exists = false;
    bool usReserved1_exists = false;
    bool usReserved2_exists = false;
    bool cbSignatureh_exists = false;
    bool cbSignaturel_exists = false;
    bool bSignature_exists = false;

    ULONG ulVersion() {
        assert_cond(ulVersion_exists, "struct field ulVersion does not exist");
        return ulVersion_var;
    }
    UBYTE usNumSigsh() {
        assert_cond(usNumSigsh_exists, "struct field usNumSigsh does not exist");
        return usNumSigsh_var;
    }
    UBYTE usNumSigsl() {
        assert_cond(usNumSigsl_exists, "struct field usNumSigsl does not exist");
        return usNumSigsl_var;
    }
    USHORT usFlag() {
        assert_cond(usFlag_exists, "struct field usFlag does not exist");
        return usFlag_var;
    }
    ULONG ulFormat() {
        assert_cond(ulFormat_exists, "struct field ulFormat does not exist");
        return ulFormat_var;
    }
    ULONG ulLength() {
        assert_cond(ulLength_exists, "struct field ulLength does not exist");
        return ulLength_var;
    }
    ULONG ulOffset() {
        assert_cond(ulOffset_exists, "struct field ulOffset does not exist");
        return ulOffset_var;
    }
    USHORT usReserved1() {
        assert_cond(usReserved1_exists, "struct field usReserved1 does not exist");
        return usReserved1_var;
    }
    USHORT usReserved2() {
        assert_cond(usReserved2_exists, "struct field usReserved2 does not exist");
        return usReserved2_var;
    }
    USHORT cbSignatureh() {
        assert_cond(cbSignatureh_exists, "struct field cbSignatureh does not exist");
        return cbSignatureh_var;
    }
    USHORT cbSignaturel() {
        assert_cond(cbSignaturel_exists, "struct field cbSignaturel does not exist");
        return cbSignaturel_var;
    }
    std::string bSignature() {
        assert_cond(bSignature_exists, "struct field bSignature does not exist");
        return bSignature_var;
    }

    /* locals */
    USHORT SigsulLength;
    ULONG tmpSigul;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tDSIG& operator () () { return *instances.back(); }
    tDSIG* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tDSIG(std::vector<tDSIG*>& instances) : instances(instances) { instances.push_back(this); }
    ~tDSIG() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tDSIG* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tDSIG* generate();
};



class DeviceRecord_struct {
    std::vector<DeviceRecord_struct*>& instances;

    UBYTE pixelSize_var;
    UBYTE maxWidth_var;
    std::string widths_var;

public:
    bool pixelSize_exists = false;
    bool maxWidth_exists = false;
    bool widths_exists = false;

    UBYTE pixelSize() {
        assert_cond(pixelSize_exists, "struct field pixelSize does not exist");
        return pixelSize_var;
    }
    UBYTE maxWidth() {
        assert_cond(maxWidth_exists, "struct field maxWidth does not exist");
        return maxWidth_var;
    }
    std::string widths() {
        assert_cond(widths_exists, "struct field widths does not exist");
        return widths_var;
    }

    /* locals */
    quad numGlyphs;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    DeviceRecord_struct& operator () () { return *instances.back(); }
    DeviceRecord_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    DeviceRecord_struct(std::vector<DeviceRecord_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~DeviceRecord_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            DeviceRecord_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    DeviceRecord_struct* generate();
};



class DeviceRecord_struct_array_class {
    DeviceRecord_struct& element;
    std::vector<DeviceRecord_struct*> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<DeviceRecord_struct*> operator () () { return value; }
    DeviceRecord_struct operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return *value[index];
    }
    DeviceRecord_struct_array_class(DeviceRecord_struct& element) : element(element) {}

    std::vector<DeviceRecord_struct*> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            value.push_back(element.generate());
            _sizeof += element._sizeof;
        }
        return value;
    }
};



class thdmx {
    std::vector<thdmx*>& instances;

    USHORT version_var;
    UBYTE numRecordsh_var;
    UBYTE numRecordsl_var;
    USHORT sizeDeviceRecordh_var;
    USHORT sizeDeviceRecordl_var;
    std::vector<DeviceRecord_struct*> DeviceRecord_var;

public:
    bool version_exists = false;
    bool numRecordsh_exists = false;
    bool numRecordsl_exists = false;
    bool sizeDeviceRecordh_exists = false;
    bool sizeDeviceRecordl_exists = false;
    bool DeviceRecord_exists = false;

    USHORT version() {
        assert_cond(version_exists, "struct field version does not exist");
        return version_var;
    }
    UBYTE numRecordsh() {
        assert_cond(numRecordsh_exists, "struct field numRecordsh does not exist");
        return numRecordsh_var;
    }
    UBYTE numRecordsl() {
        assert_cond(numRecordsl_exists, "struct field numRecordsl does not exist");
        return numRecordsl_var;
    }
    USHORT sizeDeviceRecordh() {
        assert_cond(sizeDeviceRecordh_exists, "struct field sizeDeviceRecordh does not exist");
        return sizeDeviceRecordh_var;
    }
    USHORT sizeDeviceRecordl() {
        assert_cond(sizeDeviceRecordl_exists, "struct field sizeDeviceRecordl does not exist");
        return sizeDeviceRecordl_var;
    }
    std::vector<DeviceRecord_struct*> DeviceRecord() {
        assert_cond(DeviceRecord_exists, "struct field DeviceRecord does not exist");
        return DeviceRecord_var;
    }

    /* locals */
    quad hdmx_DeviceRecord;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    thdmx& operator () () { return *instances.back(); }
    thdmx* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    thdmx(std::vector<thdmx*>& instances) : instances(instances) { instances.push_back(this); }
    ~thdmx() {
        if (generated == 2)
            return;
        while (instances.size()) {
            thdmx* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    thdmx* generate();
};



class tLTSH {
    std::vector<tLTSH*>& instances;

    USHORT ver_var;
    USHORT numGlyphs_var;
    std::string yPels_var;

public:
    bool ver_exists = false;
    bool numGlyphs_exists = false;
    bool yPels_exists = false;

    USHORT ver() {
        assert_cond(ver_exists, "struct field ver does not exist");
        return ver_var;
    }
    USHORT numGlyphs() {
        assert_cond(numGlyphs_exists, "struct field numGlyphs does not exist");
        return numGlyphs_var;
    }
    std::string yPels() {
        assert_cond(yPels_exists, "struct field yPels does not exist");
        return yPels_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tLTSH& operator () () { return *instances.back(); }
    tLTSH* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tLTSH(std::vector<tLTSH*>& instances) : instances(instances) { instances.push_back(this); }
    ~tLTSH() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tLTSH* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tLTSH* generate();
};



class RatioRange {
    std::vector<RatioRange*>& instances;

    UBYTE bCharSet_var;
    UBYTE xRatio_var;
    UBYTE yStartRatio_var;
    UBYTE yEndRatio_var;

public:
    bool bCharSet_exists = false;
    bool xRatio_exists = false;
    bool yStartRatio_exists = false;
    bool yEndRatio_exists = false;

    UBYTE bCharSet() {
        assert_cond(bCharSet_exists, "struct field bCharSet does not exist");
        return bCharSet_var;
    }
    UBYTE xRatio() {
        assert_cond(xRatio_exists, "struct field xRatio does not exist");
        return xRatio_var;
    }
    UBYTE yStartRatio() {
        assert_cond(yStartRatio_exists, "struct field yStartRatio does not exist");
        return yStartRatio_var;
    }
    UBYTE yEndRatio() {
        assert_cond(yEndRatio_exists, "struct field yEndRatio does not exist");
        return yEndRatio_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    RatioRange& operator () () { return *instances.back(); }
    RatioRange* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    RatioRange(std::vector<RatioRange*>& instances) : instances(instances) { instances.push_back(this); }
    ~RatioRange() {
        if (generated == 2)
            return;
        while (instances.size()) {
            RatioRange* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    RatioRange* generate();
};



class RatioRange_array_class {
    RatioRange& element;
    std::vector<RatioRange*> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<RatioRange*> operator () () { return value; }
    RatioRange operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return *value[index];
    }
    RatioRange_array_class(RatioRange& element) : element(element) {}

    std::vector<RatioRange*> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            value.push_back(element.generate());
            _sizeof += element._sizeof;
        }
        return value;
    }
};



class VDMXRecord {
    std::vector<VDMXRecord*>& instances;

    USHORT yPelHeight_var;
    SHORT yMax_var;
    SHORT yMin_var;

public:
    bool yPelHeight_exists = false;
    bool yMax_exists = false;
    bool yMin_exists = false;

    USHORT yPelHeight() {
        assert_cond(yPelHeight_exists, "struct field yPelHeight does not exist");
        return yPelHeight_var;
    }
    SHORT yMax() {
        assert_cond(yMax_exists, "struct field yMax does not exist");
        return yMax_var;
    }
    SHORT yMin() {
        assert_cond(yMin_exists, "struct field yMin does not exist");
        return yMin_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    VDMXRecord& operator () () { return *instances.back(); }
    VDMXRecord* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    VDMXRecord(std::vector<VDMXRecord*>& instances) : instances(instances) { instances.push_back(this); }
    ~VDMXRecord() {
        if (generated == 2)
            return;
        while (instances.size()) {
            VDMXRecord* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    VDMXRecord* generate();
};



class VDMXRecord_array_class {
    VDMXRecord& element;
    std::vector<VDMXRecord*> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<VDMXRecord*> operator () () { return value; }
    VDMXRecord operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return *value[index];
    }
    VDMXRecord_array_class(VDMXRecord& element) : element(element) {}

    std::vector<VDMXRecord*> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            value.push_back(element.generate());
            _sizeof += element._sizeof;
        }
        return value;
    }
};



class VDMXGroup {
    std::vector<VDMXGroup*>& instances;

    UBYTE recsh_var;
    UBYTE recsl_var;
    BYTE startsz_var;
    BYTE endsz_var;
    std::vector<VDMXRecord*> entry_var;

public:
    bool recsh_exists = false;
    bool recsl_exists = false;
    bool startsz_exists = false;
    bool endsz_exists = false;
    bool entry_exists = false;

    UBYTE recsh() {
        assert_cond(recsh_exists, "struct field recsh does not exist");
        return recsh_var;
    }
    UBYTE recsl() {
        assert_cond(recsl_exists, "struct field recsl does not exist");
        return recsl_var;
    }
    BYTE startsz() {
        assert_cond(startsz_exists, "struct field startsz does not exist");
        return startsz_var;
    }
    BYTE endsz() {
        assert_cond(endsz_exists, "struct field endsz does not exist");
        return endsz_var;
    }
    std::vector<VDMXRecord*> entry() {
        assert_cond(entry_exists, "struct field entry does not exist");
        return entry_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    VDMXGroup& operator () () { return *instances.back(); }
    VDMXGroup* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    VDMXGroup(std::vector<VDMXGroup*>& instances) : instances(instances) { instances.push_back(this); }
    ~VDMXGroup() {
        if (generated == 2)
            return;
        while (instances.size()) {
            VDMXGroup* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    VDMXGroup* generate();
};



class tVDMX {
    std::vector<tVDMX*>& instances;

    USHORT version_var;
    USHORT numRecs_var;
    UBYTE numRatiosh_var;
    UBYTE numRatiosl_var;
    std::vector<RatioRange*> ratRange_var;
    std::vector<USHORT> offsetl_var;
    USHORT offset_var;
    VDMXGroup* groups_var;

public:
    bool version_exists = false;
    bool numRecs_exists = false;
    bool numRatiosh_exists = false;
    bool numRatiosl_exists = false;
    bool ratRange_exists = false;
    bool offsetl_exists = false;
    bool offset_exists = false;
    bool groups_exists = false;

    USHORT version() {
        assert_cond(version_exists, "struct field version does not exist");
        return version_var;
    }
    USHORT numRecs() {
        assert_cond(numRecs_exists, "struct field numRecs does not exist");
        return numRecs_var;
    }
    UBYTE numRatiosh() {
        assert_cond(numRatiosh_exists, "struct field numRatiosh does not exist");
        return numRatiosh_var;
    }
    UBYTE numRatiosl() {
        assert_cond(numRatiosl_exists, "struct field numRatiosl does not exist");
        return numRatiosl_var;
    }
    std::vector<RatioRange*> ratRange() {
        assert_cond(ratRange_exists, "struct field ratRange does not exist");
        return ratRange_var;
    }
    std::vector<USHORT> offsetl() {
        assert_cond(offsetl_exists, "struct field offsetl does not exist");
        return offsetl_var;
    }
    USHORT offset() {
        assert_cond(offset_exists, "struct field offset does not exist");
        return offset_var;
    }
    VDMXGroup& groups() {
        assert_cond(groups_exists, "struct field groups does not exist");
        return *groups_var;
    }

    /* locals */
    USHORT tmpVDMXGrouplength;
    int64 tVDMXoffset;
    int64 VDMXGroupstar;
    int64 VDMXGroupseek;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tVDMX& operator () () { return *instances.back(); }
    tVDMX* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tVDMX(std::vector<tVDMX*>& instances) : instances(instances) { instances.push_back(this); }
    ~tVDMX() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tVDMX* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tVDMX* generate();
};



class uint16_bitfield {
    int small;
    std::vector<uint16> known_values;
    uint16 value;
public:
    uint16 operator () () { return value; }
    uint16_bitfield(int small, std::vector<uint16> known_values = {}) : small(small), known_values(known_values) {}

    uint16 generate(unsigned bits) {
        if (!bits)
            return 0;
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(uint16), bits, small);
        } else {
            value = file_acc.file_integer(sizeof(uint16), bits, known_values);
        }
        return value;
    }

    uint16 generate(unsigned bits, std::vector<uint16> possible_values) {
        if (!bits)
            return 0;
        value = file_acc.file_integer(sizeof(uint16), bits, possible_values);
        return value;
    }
};



class GaspBehavior {
    std::vector<GaspBehavior*>& instances;

    uint16 gridfit_var : 1;
    uint16 doGray_var : 1;
    uint16 symMetricGridfit_var : 1;
    uint16 symMetricSmoothing_var : 1;
    uint16 Reserved_var : 12;

public:
    bool gridfit_exists = false;
    bool doGray_exists = false;
    bool symMetricGridfit_exists = false;
    bool symMetricSmoothing_exists = false;
    bool Reserved_exists = false;

    uint16 gridfit() {
        assert_cond(gridfit_exists, "struct field gridfit does not exist");
        return gridfit_var;
    }
    uint16 doGray() {
        assert_cond(doGray_exists, "struct field doGray does not exist");
        return doGray_var;
    }
    uint16 symMetricGridfit() {
        assert_cond(symMetricGridfit_exists, "struct field symMetricGridfit does not exist");
        return symMetricGridfit_var;
    }
    uint16 symMetricSmoothing() {
        assert_cond(symMetricSmoothing_exists, "struct field symMetricSmoothing does not exist");
        return symMetricSmoothing_var;
    }
    uint16 Reserved() {
        assert_cond(Reserved_exists, "struct field Reserved does not exist");
        return Reserved_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    GaspBehavior& operator () () { return *instances.back(); }
    GaspBehavior* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    GaspBehavior(std::vector<GaspBehavior*>& instances) : instances(instances) { instances.push_back(this); }
    ~GaspBehavior() {
        if (generated == 2)
            return;
        while (instances.size()) {
            GaspBehavior* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    GaspBehavior* generate();
};



class tgaspRange {
    std::vector<tgaspRange*>& instances;

    uint16 rangeMaxPPEM_var;
    GaspBehavior* rangeGaspBehavior_var;

public:
    bool rangeMaxPPEM_exists = false;
    bool rangeGaspBehavior_exists = false;

    uint16 rangeMaxPPEM() {
        assert_cond(rangeMaxPPEM_exists, "struct field rangeMaxPPEM does not exist");
        return rangeMaxPPEM_var;
    }
    GaspBehavior& rangeGaspBehavior() {
        assert_cond(rangeGaspBehavior_exists, "struct field rangeGaspBehavior does not exist");
        return *rangeGaspBehavior_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tgaspRange& operator () () { return *instances.back(); }
    tgaspRange* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tgaspRange(std::vector<tgaspRange*>& instances) : instances(instances) { instances.push_back(this); }
    ~tgaspRange() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tgaspRange* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tgaspRange* generate();
};



class tgaspRange_array_class {
    tgaspRange& element;
    std::vector<tgaspRange*> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<tgaspRange*> operator () () { return value; }
    tgaspRange operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return *value[index];
    }
    tgaspRange_array_class(tgaspRange& element) : element(element) {}

    std::vector<tgaspRange*> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            value.push_back(element.generate());
            _sizeof += element._sizeof;
        }
        return value;
    }
};



class tgasp {
    std::vector<tgasp*>& instances;

    uint16 version_var;
    uint16 numRanges_var;
    std::vector<tgaspRange*> gaspRanges_var;

public:
    bool version_exists = false;
    bool numRanges_exists = false;
    bool gaspRanges_exists = false;

    uint16 version() {
        assert_cond(version_exists, "struct field version does not exist");
        return version_var;
    }
    uint16 numRanges() {
        assert_cond(numRanges_exists, "struct field numRanges does not exist");
        return numRanges_var;
    }
    std::vector<tgaspRange*> gaspRanges() {
        assert_cond(gaspRanges_exists, "struct field gaspRanges does not exist");
        return gaspRanges_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tgasp& operator () () { return *instances.back(); }
    tgasp* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tgasp(std::vector<tgasp*>& instances) : instances(instances) { instances.push_back(this); }
    ~tgasp() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tgasp* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tgasp* generate();
};



class tTable {
    std::vector<tTable*>& instances;

    ULONG checkSum_var;
    ULONG offset_var;
    ULONG length_var;
    thead* head_var;
    tcmap* cmap_var;
    USHORT platformID_var;
    USHORT encodingID_var;
    USHORT format_var;
    tcmap_format0* format0_var;
    tcmap_format2* format2_var;
    tcmap_format4* format4_var;
    tcmap_format6* format6_var;
    tcmap_format8* format8_var;
    tcmap_format12* format12_var;
    thhea* hhea_var;
    tOS_2* OS_2_var;
    tmaxp* maxp_var;
    thmtx* hmtx_var;
    tname* name_var;
    tpost* post_var;
    tcvt* cvt_var;
    tfpgm* fpgm_var;
    tloca* loca_var;
    tglyf* glyf_var;
    tprep* prep_var;
    tGDEF* GDEF_var;
    tGSUBorGPOS* GSUB_var;
    tDSIG* DSIG_var;
    thdmx* hdmx_var;
    tLTSH* LTSH_var;
    tVDMX* VDMX_var;
    tgasp* gasp_var;
    ULONG length2_var;

public:
    bool checkSum_exists = false;
    bool offset_exists = false;
    bool length_exists = false;
    bool head_exists = false;
    bool cmap_exists = false;
    bool platformID_exists = false;
    bool encodingID_exists = false;
    bool format_exists = false;
    bool format0_exists = false;
    bool format2_exists = false;
    bool format4_exists = false;
    bool format6_exists = false;
    bool format8_exists = false;
    bool format12_exists = false;
    bool hhea_exists = false;
    bool OS_2_exists = false;
    bool maxp_exists = false;
    bool hmtx_exists = false;
    bool name_exists = false;
    bool post_exists = false;
    bool cvt_exists = false;
    bool fpgm_exists = false;
    bool loca_exists = false;
    bool glyf_exists = false;
    bool prep_exists = false;
    bool GDEF_exists = false;
    bool GSUB_exists = false;
    bool DSIG_exists = false;
    bool hdmx_exists = false;
    bool LTSH_exists = false;
    bool VDMX_exists = false;
    bool gasp_exists = false;
    bool length2_exists = false;

    ULONG checkSum() {
        assert_cond(checkSum_exists, "struct field checkSum does not exist");
        return checkSum_var;
    }
    ULONG offset() {
        assert_cond(offset_exists, "struct field offset does not exist");
        return offset_var;
    }
    ULONG length() {
        assert_cond(length_exists, "struct field length does not exist");
        return length_var;
    }
    thead& head() {
        assert_cond(head_exists, "struct field head does not exist");
        return *head_var;
    }
    tcmap& cmap() {
        assert_cond(cmap_exists, "struct field cmap does not exist");
        return *cmap_var;
    }
    USHORT platformID() {
        assert_cond(platformID_exists, "struct field platformID does not exist");
        return platformID_var;
    }
    USHORT encodingID() {
        assert_cond(encodingID_exists, "struct field encodingID does not exist");
        return encodingID_var;
    }
    USHORT format() {
        assert_cond(format_exists, "struct field format does not exist");
        return format_var;
    }
    tcmap_format0& format0() {
        assert_cond(format0_exists, "struct field format0 does not exist");
        return *format0_var;
    }
    tcmap_format2& format2() {
        assert_cond(format2_exists, "struct field format2 does not exist");
        return *format2_var;
    }
    tcmap_format4& format4() {
        assert_cond(format4_exists, "struct field format4 does not exist");
        return *format4_var;
    }
    tcmap_format6& format6() {
        assert_cond(format6_exists, "struct field format6 does not exist");
        return *format6_var;
    }
    tcmap_format8& format8() {
        assert_cond(format8_exists, "struct field format8 does not exist");
        return *format8_var;
    }
    tcmap_format12& format12() {
        assert_cond(format12_exists, "struct field format12 does not exist");
        return *format12_var;
    }
    thhea& hhea() {
        assert_cond(hhea_exists, "struct field hhea does not exist");
        return *hhea_var;
    }
    tOS_2& OS_2() {
        assert_cond(OS_2_exists, "struct field OS_2 does not exist");
        return *OS_2_var;
    }
    tmaxp& maxp() {
        assert_cond(maxp_exists, "struct field maxp does not exist");
        return *maxp_var;
    }
    thmtx& hmtx() {
        assert_cond(hmtx_exists, "struct field hmtx does not exist");
        return *hmtx_var;
    }
    tname& name() {
        assert_cond(name_exists, "struct field name does not exist");
        return *name_var;
    }
    tpost& post() {
        assert_cond(post_exists, "struct field post does not exist");
        return *post_var;
    }
    tcvt& cvt() {
        assert_cond(cvt_exists, "struct field cvt does not exist");
        return *cvt_var;
    }
    tfpgm& fpgm() {
        assert_cond(fpgm_exists, "struct field fpgm does not exist");
        return *fpgm_var;
    }
    tloca& loca() {
        assert_cond(loca_exists, "struct field loca does not exist");
        return *loca_var;
    }
    tglyf& glyf() {
        assert_cond(glyf_exists, "struct field glyf does not exist");
        return *glyf_var;
    }
    tprep& prep() {
        assert_cond(prep_exists, "struct field prep does not exist");
        return *prep_var;
    }
    tGDEF& GDEF() {
        assert_cond(GDEF_exists, "struct field GDEF does not exist");
        return *GDEF_var;
    }
    tGSUBorGPOS& GSUB() {
        assert_cond(GSUB_exists, "struct field GSUB does not exist");
        return *GSUB_var;
    }
    tDSIG& DSIG() {
        assert_cond(DSIG_exists, "struct field DSIG does not exist");
        return *DSIG_var;
    }
    thdmx& hdmx() {
        assert_cond(hdmx_exists, "struct field hdmx does not exist");
        return *hdmx_var;
    }
    tLTSH& LTSH() {
        assert_cond(LTSH_exists, "struct field LTSH does not exist");
        return *LTSH_var;
    }
    tVDMX& VDMX() {
        assert_cond(VDMX_exists, "struct field VDMX does not exist");
        return *VDMX_var;
    }
    tgasp& gasp() {
        assert_cond(gasp_exists, "struct field gasp does not exist");
        return *gasp_var;
    }
    ULONG length2() {
        assert_cond(length2_exists, "struct field length2 does not exist");
        return length2_var;
    }

    /* locals */
    std::string asName;
    int64 pos_start;
    int64 pos_start_offset;
    int c;
    ULONG cmap_length;
    std::vector<USHORT> possible_cmap;
    quad cmap_subtable;
    quad cmap_record;
    quad format_seek;
    ULONG cmap_l;
    int64 pos_end;
    uint32 correct_length;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tTable& operator () () { return *instances.back(); }
    tTable* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tTable(std::vector<tTable*>& instances) : instances(instances) { instances.push_back(this); }
    ~tTable() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tTable* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tTable* generate();
};

std::vector<byte> ReadByteInitValues;
std::vector<ubyte> ReadUByteInitValues;
std::vector<short> ReadShortInitValues;
std::vector<ushort> ReadUShortInitValues;
std::vector<int> ReadIntInitValues;
std::vector<uint> ReadUIntInitValues;
std::vector<int64> ReadQuadInitValues;
std::vector<uint64> ReadUQuadInitValues;
std::vector<int64> ReadInt64InitValues;
std::vector<uint64> ReadUInt64InitValues;
std::vector<hfloat> ReadHFloatInitValues;
std::vector<float> ReadFloatInitValues;
std::vector<double> ReadDoubleInitValues;
std::vector<std::string> ReadBytesInitValues;


std::vector<tOffsetTable*> tOffsetTable_OffsetTable_instances;
std::vector<CTag*> CTag_Tag_instances;
std::vector<sTable*> sTable_stable_instances;
std::vector<thead*> thead_head_instances;
std::vector<tcmap*> tcmap_cmap_instances;
std::vector<tcmap_format0*> tcmap_format0_format0_instances;
std::vector<tcmap_format2*> tcmap_format2_format2_instances;
std::vector<tcmap_format4*> tcmap_format4_format4_instances;
std::vector<tcmap_format6*> tcmap_format6_format6_instances;
std::vector<tcmap_format8_groupings_struct*> tcmap_format8_groupings_struct_groupings_element_instances;
std::vector<tcmap_format8*> tcmap_format8_format8_instances;
std::vector<tcmap_format12_groupings_struct*> tcmap_format12_groupings_struct_groupings__element_instances;
std::vector<tcmap_format12*> tcmap_format12_format12_instances;
std::vector<thhea*> thhea_hhea_instances;
std::vector<tpanose*> tpanose_panose_instances;
std::vector<tOS_2*> tOS_2_OS_2_instances;
std::vector<tmaxp*> tmaxp_maxp_instances;
std::vector<tlongHorMetric*> tlongHorMetric_hMetrics_element_instances;
std::vector<thmtx*> thmtx_hmtx_instances;
std::vector<tname*> tname_name__instances;
std::vector<tpostName*> tpostName_name___element_instances;
std::vector<tpost*> tpost_post_instances;
std::vector<tcvt*> tcvt_cvt_instances;
std::vector<tfpgm*> tfpgm_fpgm_instances;
std::vector<tloca*> tloca_loca_instances;
std::vector<tPoints*> tPoints_points_instances;
std::vector<tSimpleGlyphPoints*> tSimpleGlyphPoints_contours_instances;
std::vector<tSimpleGlyph*> tSimpleGlyph_SimpleGlyph_instances;
std::vector<tglyf*> tglyf_glyf_instances;
std::vector<tprep*> tprep_prep_instances;
std::vector<tGDEF*> tGDEF_GDEF_instances;
std::vector<tLangSysTable*> tLangSysTable_LangSysTable_instances;
std::vector<tLangSysRecord*> tLangSysRecord_LangSysRecord_instances;
std::vector<tScriptRecord_ScriptTable_struct*> tScriptRecord_ScriptTable_struct_ScriptTable_instances;
std::vector<tLangSysTable*> tLangSysTable_DefaultLangSysTable_instances;
std::vector<tScriptRecord*> tScriptRecord_ScriptRecord_instances;
std::vector<tScriptList*> tScriptList_ScriptList_instances;
std::vector<tFeatureRecord_FeatureTable_struct*> tFeatureRecord_FeatureTable_struct_FeatureTable_instances;
std::vector<tFeatureRecord*> tFeatureRecord_FeatureRecord_instances;
std::vector<tFeatureList*> tFeatureList_FeatureList_instances;
std::vector<tLookupRecord*> tLookupRecord_LookupRecord_instances;
std::vector<tLookupList*> tLookupList_LookupList_instances;
std::vector<tGSUBorGPOS*> tGSUBorGPOS_GSUB_instances;
std::vector<tDSIG*> tDSIG_DSIG_instances;
std::vector<DeviceRecord_struct*> DeviceRecord_struct_DeviceRecord_element_instances;
std::vector<thdmx*> thdmx_hdmx_instances;
std::vector<tLTSH*> tLTSH_LTSH_instances;
std::vector<RatioRange*> RatioRange_ratRange_element_instances;
std::vector<VDMXRecord*> VDMXRecord_entry_element_instances;
std::vector<VDMXGroup*> VDMXGroup_groups_instances;
std::vector<tVDMX*> tVDMX_VDMX_instances;
std::vector<GaspBehavior*> GaspBehavior_rangeGaspBehavior_instances;
std::vector<tgaspRange*> tgaspRange_gaspRanges_element_instances;
std::vector<tgasp*> tgasp_gasp_instances;
std::vector<tTable*> tTable_Table_instances;


std::unordered_map<std::string, std::string> variable_types = { { "SFNT_Ver", "unsigned_long_class" }, { "numTables", "USHORT_class" }, { "searchRange", "USHORT_class" }, { "entrySelector", "USHORT_class" }, { "rangeShift", "USHORT_class" }, { "OffsetTable", "tOffsetTable" }, { "asName", "char_array_class" }, { "asLong", "ULONG_class" }, { "Tag", "CTag" }, { "checkSum", "ULONG_class" }, { "offset", "ULONG_class" }, { "slength", "ULONG_class" }, { "stable", "sTable" }, { "length", "ULONG_class" }, { "version", "unsigned_long_class" }, { "fontRevision", "unsigned_long_class" }, { "checkSumAdjustment", "ULONG_class" }, { "magicNumber", "ULONG_class" }, { "flags", "USHORT_class" }, { "unitsPerEm", "USHORT_class" }, { "created", "LONGDATETIME_class" }, { "modified", "LONGDATETIME_class" }, { "xMin", "SHORT_class" }, { "yMin", "SHORT_class" }, { "xMax", "SHORT_class" }, { "yMax", "SHORT_class" }, { "macStyle", "USHORT_class" }, { "lowestRecPPEM", "USHORT_class" }, { "fontDirectionHint", "SHORT_class" }, { "indexToLocFormat", "SHORT_class" }, { "glyphDataFormat", "SHORT_class" }, { "head", "thead" }, { "version_cmap", "USHORT_class" }, { "cmap", "tcmap" }, { "platformID", "USHORT_class" }, { "encodingID", "USHORT_class" }, { "format", "USHORT_class" }, { "length_", "USHORT_class" }, { "language", "USHORT_class" }, { "glyphIdArray", "BYTE_array_class" }, { "format0", "tcmap_format0" }, { "subHeaderKeys", "USHORT_class" }, { "firstCode", "uint16_class" }, { "entryCount", "uint16_class" }, { "idDelta", "int16_class" }, { "idRangeOffset", "uint16_class" }, { "glyphIdArray_", "USHORT_array_class" }, { "format2", "tcmap_format2" }, { "segCountX2", "USHORT_class" }, { "endCount", "USHORT_array_class" }, { "reservedPad", "USHORT_class" }, { "startCount", "USHORT_array_class" }, { "idDelta_", "SHORT_array_class" }, { "idRangeOffset_", "USHORT_array_class" }, { "format4", "tcmap_format4" }, { "firstCode_", "USHORT_class" }, { "entryCount_", "USHORT_class" }, { "format6", "tcmap_format6" }, { "reserved", "USHORT_class" }, { "language_", "ULONG_class" }, { "is32", "BYTE_array_class" }, { "nGroups", "ULONG_class" }, { "startCharCode", "ULONG_class" }, { "endCharCode", "ULONG_class" }, { "startGlyphID", "ULONG_class" }, { "groupings", "tcmap_format8_groupings_struct_array_class" }, { "format8", "tcmap_format8" }, { "groupings_", "tcmap_format12_groupings_struct_array_class" }, { "format12", "tcmap_format12" }, { "Ascender", "TT_FWord_class" }, { "Descender", "TT_FWord_class" }, { "LineGap", "TT_FWord_class" }, { "advanceWidthMax", "TT_UFWord_class" }, { "minLeftSideBearing", "TT_FWord_class" }, { "minRightSideBearing", "TT_FWord_class" }, { "xMaxExtent", "TT_FWord_class" }, { "caretSlopeRise", "SHORT_class" }, { "caretSlopeRun", "SHORT_class" }, { "caretOffset", "SHORT_class" }, { "reserved_", "SHORT_class" }, { "reserved1", "SHORT_class" }, { "reserved2", "SHORT_class" }, { "reserved3", "SHORT_class" }, { "metricDataFormat", "SHORT_class" }, { "numberOfHMetrics", "USHORT_class" }, { "hhea", "thhea" }, { "version_tos", "USHORT_class" }, { "xAvgCharWidth", "SHORT_class" }, { "usWeightClass", "USHORT_class" }, { "usWidthClass", "USHORT_class" }, { "fsType", "USHORT_class" }, { "ySubscriptXSize", "SHORT_class" }, { "ySubscriptYSize", "SHORT_class" }, { "ySubscriptXOffset", "SHORT_class" }, { "ySubscriptYOffset", "SHORT_class" }, { "ySuperscriptXSize", "SHORT_class" }, { "ySuperscriptYSize", "SHORT_class" }, { "ySuperscriptXOffset", "SHORT_class" }, { "ySuperscriptYOffset", "SHORT_class" }, { "yStrikeoutSize", "SHORT_class" }, { "yStrikeoutPosition", "SHORT_class" }, { "sFamilyClass", "SHORT_class" }, { "bFamilyType", "UBYTE_class" }, { "bSerifStyle", "UBYTE_class" }, { "bWeight", "UBYTE_class" }, { "bProportion", "UBYTE_class" }, { "bContrast", "UBYTE_class" }, { "bStrokeVariation", "UBYTE_class" }, { "bArmStyle", "UBYTE_class" }, { "bLetterform", "UBYTE_class" }, { "bMidline", "UBYTE_class" }, { "bXHeight", "UBYTE_class" }, { "panose", "tpanose" }, { "ulUnicodeRange1", "ULONG_class" }, { "ulUnicodeRange2", "ULONG_class" }, { "ulUnicodeRange3", "ULONG_class" }, { "ulUnicodeRange4", "ULONG_class" }, { "achVendID", "CHAR_array_class" }, { "fsSelection", "USHORT_class" }, { "usFirstCharIndex", "USHORT_class" }, { "usLastCharIndex", "USHORT_class" }, { "sTypoAscender", "SHORT_class" }, { "sTypoDescender", "SHORT_class" }, { "sTypoLineGap", "SHORT_class" }, { "usWinAscent", "USHORT_class" }, { "usWinDescent", "USHORT_class" }, { "ulCodePageRange1", "ULONG_class" }, { "ulCodePageRange2", "ULONG_class" }, { "sxHeight", "SHORT_class" }, { "sCapHeight", "SHORT_class" }, { "usDefaultChar", "USHORT_class" }, { "usBreakChar", "USHORT_class" }, { "usMaxContext", "USHORT_class" }, { "OS_2", "tOS_2" }, { "numGlyphs", "USHORT_class" }, { "maxPoints", "USHORT_class" }, { "maxContours", "USHORT_class" }, { "maxCompositePoints", "USHORT_class" }, { "maxCompositeContours", "USHORT_class" }, { "maxZones", "USHORT_class" }, { "maxTwilightPoints", "USHORT_class" }, { "maxStorage", "USHORT_class" }, { "maxFunctionDefs", "USHORT_class" }, { "maxInstructionDefs", "USHORT_class" }, { "maxStackElements", "USHORT_class" }, { "maxSizeOfInstructions", "USHORT_class" }, { "maxComponentElements", "USHORT_class" }, { "maxComponentDepth", "USHORT_class" }, { "maxp", "tmaxp" }, { "advanceWidth", "USHORT_class" }, { "lsb", "SHORT_class" }, { "hMetrics", "tlongHorMetric_array_class" }, { "leftSideBearing", "SHORT_array_class" }, { "hmtx", "thmtx" }, { "count", "USHORT_class" }, { "stringOffset", "USHORT_class" }, { "languageID", "USHORT_class" }, { "nameID", "USHORT_class" }, { "offset_", "USHORT_class" }, { "name", "char_array_class" }, { "name_", "tname" }, { "italicAngle", "unsigned_long_class" }, { "underlinePosition", "TT_FWord_class" }, { "underlineThickness", "TT_FWord_class" }, { "isFixedPitch", "ULONG_class" }, { "minMemType42", "ULONG_class" }, { "maxMemType42", "ULONG_class" }, { "minMemType1", "ULONG_class" }, { "maxMemType1", "ULONG_class" }, { "numberOfGlyphs", "USHORT_class" }, { "glyphNameIndex", "USHORT_array_class" }, { "length__", "UBYTE_class" }, { "text", "CHAR_array_class" }, { "name__", "tpostName_array_class" }, { "tpostoffset", "USHORT_array_class" }, { "post", "tpost" }, { "value", "TT_FWord_array_class" }, { "cvt", "tcvt" }, { "bytecode", "UBYTE_array_class" }, { "fpgm", "tfpgm" }, { "offsets", "USHORT_array_class" }, { "offsets_", "ULONG_array_class" }, { "loca", "tloca" }, { "local_offset", "USHORT_class" }, { "local_offset_", "ULONG_class" }, { "numberOfContoursl", "SHORT_class" }, { "endPtsOfContoursl", "SHORT_class" }, { "instructionLengthl", "USHORT_class" }, { "instructions", "UBYTE_array_class" }, { "SimpleGlyph_flag", "UBYTE_array_class" }, { "xDelta", "UBYTE_class" }, { "xDeltaRepeat", "UBYTE_class" }, { "xDeltaRepeat_", "SHORT_class" }, { "xDelta_", "SHORT_class" }, { "yDelta", "UBYTE_class" }, { "yDeltaRepeat", "UBYTE_class" }, { "yDeltaRepeat_", "SHORT_class" }, { "yDelta_", "SHORT_class" }, { "points", "tPoints" }, { "contours", "tSimpleGlyphPoints" }, { "SimpleGlyph", "tSimpleGlyph" }, { "glyf", "tglyf" }, { "prep", "tprep" }, { "Version", "unsigned_long_class" }, { "GlyphClassDef", "TT_Offset_class" }, { "AttachList", "TT_Offset_class" }, { "LigCaretList", "TT_Offset_class" }, { "MarkAttachClassDef", "TT_Offset_class" }, { "GDEF", "tGDEF" }, { "Offset", "USHORT_class" }, { "ScriptCountl", "uint16_class" }, { "ScriptTag", "char_array_class" }, { "DefaultLangSys", "USHORT_class" }, { "LangSysCounth", "ubyte_class" }, { "LangSysCountl", "ubyte_class" }, { "LangSysTag", "char_array_class" }, { "LookupOrder", "USHORT_class" }, { "ReqFeatureIndex", "uint16_class" }, { "FeatureCounth", "ubyte_class" }, { "FeatureCountl", "ubyte_class" }, { "FeatureIndex", "uint16_array_class" }, { "LangSysTable", "tLangSysTable" }, { "LangSysRecord", "tLangSysRecord" }, { "ScriptTable", "tScriptRecord_ScriptTable_struct" }, { "DefaultLangSysTable", "tLangSysTable" }, { "ScriptRecord", "tScriptRecord" }, { "ScriptList", "tScriptList" }, { "FeatureTag", "char_array_class" }, { "FeatureParams", "uint16_class" }, { "LookupListCounth", "ubyte_class" }, { "LookupListCountl", "ubyte_class" }, { "LookupListIndex", "uint16_array_class" }, { "FeatureTable", "tFeatureRecord_FeatureTable_struct" }, { "FeatureRecord", "tFeatureRecord" }, { "FeatureList", "tFeatureList" }, { "LookupCounth", "ubyte_class" }, { "LookupCountl", "ubyte_class" }, { "LookupType", "uint16_class" }, { "LookupFlag", "uint16_class" }, { "SubTableCounth", "ubyte_class" }, { "SubTableCountl", "ubyte_class" }, { "SubTable", "USHORT_array_class" }, { "LookupRecord", "tLookupRecord" }, { "LookupList", "tLookupList" }, { "GSUB", "tGSUBorGPOS" }, { "ulVersion", "ULONG_class" }, { "usNumSigsh", "UBYTE_class" }, { "usNumSigsl", "UBYTE_class" }, { "usFlag", "USHORT_class" }, { "ulFormat", "ULONG_class" }, { "ulLength", "ULONG_class" }, { "ulOffset", "ULONG_class" }, { "usReserved1", "USHORT_class" }, { "usReserved2", "USHORT_class" }, { "cbSignatureh", "USHORT_class" }, { "cbSignaturel", "USHORT_class" }, { "bSignature", "UBYTE_array_class" }, { "DSIG", "tDSIG" }, { "version_", "USHORT_class" }, { "numRecordsh", "UBYTE_class" }, { "numRecordsl", "UBYTE_class" }, { "sizeDeviceRecordh", "USHORT_class" }, { "sizeDeviceRecordl", "USHORT_class" }, { "pixelSize", "UBYTE_class" }, { "maxWidth", "UBYTE_class" }, { "widths", "UBYTE_array_class" }, { "DeviceRecord", "DeviceRecord_struct_array_class" }, { "hdmx", "thdmx" }, { "ver", "USHORT_class" }, { "yPels", "UBYTE_array_class" }, { "LTSH", "tLTSH" }, { "numRecs", "USHORT_class" }, { "numRatiosh", "UBYTE_class" }, { "numRatiosl", "UBYTE_class" }, { "bCharSet", "UBYTE_class" }, { "xRatio", "UBYTE_class" }, { "yStartRatio", "UBYTE_class" }, { "yEndRatio", "UBYTE_class" }, { "ratRange", "RatioRange_array_class" }, { "offsetl", "USHORT_array_class" }, { "recsh", "UBYTE_class" }, { "recsl", "UBYTE_class" }, { "startsz", "BYTE_class" }, { "endsz", "BYTE_class" }, { "yPelHeight", "USHORT_class" }, { "entry", "VDMXRecord_array_class" }, { "groups", "VDMXGroup" }, { "VDMX", "tVDMX" }, { "version__", "uint16_class" }, { "numRanges", "uint16_class" }, { "rangeMaxPPEM", "uint16_class" }, { "gridfit", "uint16_bitfield1" }, { "doGray", "uint16_bitfield1" }, { "symMetricGridfit", "uint16_bitfield1" }, { "symMetricSmoothing", "uint16_bitfield1" }, { "Reserved", "uint16_bitfield12" }, { "rangeGaspBehavior", "GaspBehavior" }, { "gaspRanges", "tgaspRange_array_class" }, { "gasp", "tgasp" }, { "length2", "ULONG_class" }, { "Table", "tTable" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 } };

class globals_class {
public:
    /*local*/ int maxGlyfRead;
    /*local*/ USHORT ARG_1_AND_2_ARE_WORDS;
    /*local*/ USHORT ARGS_ARE_XY_VALUES;
    /*local*/ USHORT ROUND_XY_TO_GRID;
    /*local*/ USHORT WE_HAVE_A_SCALE;
    /*local*/ USHORT RESERVED;
    /*local*/ USHORT MORE_COMPONENTS;
    /*local*/ USHORT WE_HAVE_AN_X_AND_Y_SCALE;
    /*local*/ USHORT WE_HAVE_A_TWO_BY_TWO;
    /*local*/ USHORT WE_HAVE_INSTRUCTIONS;
    /*local*/ USHORT USE_MY_METRICS;
    /*local*/ USHORT OVERLAP_COMPOUND;
    /*local*/ USHORT SCALED_COMPONENT_OFFSET;
    /*local*/ USHORT UNSCALED_COMPONENT_OFFSET;
    /*local*/ UBYTE ON_CURVE;
    /*local*/ UBYTE X_BYTE;
    /*local*/ UBYTE Y_BYTE;
    /*local*/ UBYTE REPEAT;
    /*local*/ UBYTE X_TYPE;
    /*local*/ UBYTE Y_TYPE;
    /*local*/ UBYTE RES_1;
    /*local*/ UBYTE RES_2;
    /*local*/ quad numTables_offset;
    /*local*/ USHORT numTables_n;
    /*local*/ ulong hmtx_length;
    /*local*/ quad tLangSysTable_ftell;
    /*local*/ USHORT tLangSysTablelength;
    /*local*/ quad ScriptTable_table;
    /*local*/ USHORT LangSysRecordlength;
    /*local*/ quad ScriptList_seek;
    /*local*/ quad FeatureList_seek;
    /*local*/ quad tFeatureListlengthseek;
    /*local*/ quad LookupList_table;
    /*local*/ quad nextSig;
    /*local*/ quad DSIG_table;
    /*local*/ USHORT sizeDeviceRecord;
    /*local*/ int i;
    /*local*/ ULONG offset_tag;
    /*local*/ uint32 ttfId;
    /*local*/ uint32 t_numFonts;
    /*local*/ ULONG curTblOffset;
    /*local*/ ULONG curTblLength;
    /*local*/ USHORT attf_numberOfHMetrics;
    /*local*/ USHORT attf_numGlyphs;
    /*local*/ SHORT attf_indexToLocFormat;
    /*local*/ quad attf_glyf_offset;
    /*local*/ int64 attf_locatell;
    unsigned_long_class SFNT_Ver;
    USHORT_class numTables;
    USHORT_class searchRange;
    USHORT_class entrySelector;
    USHORT_class rangeShift;
    tOffsetTable OffsetTable;
    /*local*/ std::string tag_type;
    /*local*/ USHORT tablecount;
    /*local*/ quad table_start_pos;
    /*local*/ std::vector<std::string> preferred_tables;
    char_class asName_element;
    char_array_class asName;
    ULONG_class asLong;
    CTag Tag;
    ULONG_class checkSum;
    ULONG_class offset;
    ULONG_class slength;
    sTable stable;
    /*local*/ std::vector<std::string> possible_tables;
    /*local*/ int t;
    ULONG_class length;
    unsigned_long_class version;
    unsigned_long_class fontRevision;
    ULONG_class checkSumAdjustment;
    ULONG_class magicNumber;
    USHORT_class flags;
    USHORT_class unitsPerEm;
    LONGDATETIME_class created;
    LONGDATETIME_class modified;
    SHORT_class xMin;
    SHORT_class yMin;
    SHORT_class xMax;
    SHORT_class yMax;
    USHORT_class macStyle;
    USHORT_class lowestRecPPEM;
    SHORT_class fontDirectionHint;
    SHORT_class indexToLocFormat;
    SHORT_class glyphDataFormat;
    thead head;
    USHORT_class version_cmap;
    tcmap cmap;
    USHORT_class platformID;
    USHORT_class encodingID;
    USHORT_class format;
    USHORT_class length_;
    USHORT_class language;
    BYTE_class glyphIdArray_element;
    BYTE_array_class glyphIdArray;
    tcmap_format0 format0;
    USHORT_class subHeaderKeys;
    uint16_class firstCode;
    uint16_class entryCount;
    int16_class idDelta;
    uint16_class idRangeOffset;
    USHORT_class glyphIdArray__element;
    USHORT_array_class glyphIdArray_;
    tcmap_format2 format2;
    USHORT_class segCountX2;
    USHORT_class endCount_element;
    USHORT_array_class endCount;
    USHORT_class reservedPad;
    USHORT_class startCount_element;
    USHORT_array_class startCount;
    SHORT_class idDelta__element;
    SHORT_array_class idDelta_;
    USHORT_class idRangeOffset__element;
    USHORT_array_class idRangeOffset_;
    tcmap_format4 format4;
    USHORT_class firstCode_;
    USHORT_class entryCount_;
    tcmap_format6 format6;
    USHORT_class reserved;
    ULONG_class language_;
    BYTE_class is32_element;
    BYTE_array_class is32;
    ULONG_class nGroups;
    ULONG_class startCharCode;
    ULONG_class endCharCode;
    ULONG_class startGlyphID;
    tcmap_format8_groupings_struct groupings_element;
    tcmap_format8_groupings_struct_array_class groupings;
    tcmap_format8 format8;
    tcmap_format12_groupings_struct groupings__element;
    tcmap_format12_groupings_struct_array_class groupings_;
    tcmap_format12 format12;
    TT_FWord_class Ascender;
    TT_FWord_class Descender;
    TT_FWord_class LineGap;
    TT_UFWord_class advanceWidthMax;
    TT_FWord_class minLeftSideBearing;
    TT_FWord_class minRightSideBearing;
    TT_FWord_class xMaxExtent;
    SHORT_class caretSlopeRise;
    SHORT_class caretSlopeRun;
    SHORT_class caretOffset;
    SHORT_class reserved_;
    SHORT_class reserved1;
    SHORT_class reserved2;
    SHORT_class reserved3;
    SHORT_class metricDataFormat;
    USHORT_class numberOfHMetrics;
    thhea hhea;
    USHORT_class version_tos;
    SHORT_class xAvgCharWidth;
    USHORT_class usWeightClass;
    USHORT_class usWidthClass;
    USHORT_class fsType;
    SHORT_class ySubscriptXSize;
    SHORT_class ySubscriptYSize;
    SHORT_class ySubscriptXOffset;
    SHORT_class ySubscriptYOffset;
    SHORT_class ySuperscriptXSize;
    SHORT_class ySuperscriptYSize;
    SHORT_class ySuperscriptXOffset;
    SHORT_class ySuperscriptYOffset;
    SHORT_class yStrikeoutSize;
    SHORT_class yStrikeoutPosition;
    SHORT_class sFamilyClass;
    UBYTE_class bFamilyType;
    UBYTE_class bSerifStyle;
    UBYTE_class bWeight;
    UBYTE_class bProportion;
    UBYTE_class bContrast;
    UBYTE_class bStrokeVariation;
    UBYTE_class bArmStyle;
    UBYTE_class bLetterform;
    UBYTE_class bMidline;
    UBYTE_class bXHeight;
    tpanose panose;
    ULONG_class ulUnicodeRange1;
    ULONG_class ulUnicodeRange2;
    ULONG_class ulUnicodeRange3;
    ULONG_class ulUnicodeRange4;
    CHAR_class achVendID_element;
    CHAR_array_class achVendID;
    USHORT_class fsSelection;
    USHORT_class usFirstCharIndex;
    USHORT_class usLastCharIndex;
    SHORT_class sTypoAscender;
    SHORT_class sTypoDescender;
    SHORT_class sTypoLineGap;
    USHORT_class usWinAscent;
    USHORT_class usWinDescent;
    ULONG_class ulCodePageRange1;
    ULONG_class ulCodePageRange2;
    SHORT_class sxHeight;
    SHORT_class sCapHeight;
    USHORT_class usDefaultChar;
    USHORT_class usBreakChar;
    USHORT_class usMaxContext;
    tOS_2 OS_2;
    USHORT_class numGlyphs;
    USHORT_class maxPoints;
    USHORT_class maxContours;
    USHORT_class maxCompositePoints;
    USHORT_class maxCompositeContours;
    USHORT_class maxZones;
    USHORT_class maxTwilightPoints;
    USHORT_class maxStorage;
    USHORT_class maxFunctionDefs;
    USHORT_class maxInstructionDefs;
    USHORT_class maxStackElements;
    USHORT_class maxSizeOfInstructions;
    USHORT_class maxComponentElements;
    USHORT_class maxComponentDepth;
    tmaxp maxp;
    USHORT_class advanceWidth;
    SHORT_class lsb;
    tlongHorMetric hMetrics_element;
    tlongHorMetric_array_class hMetrics;
    SHORT_class leftSideBearing_element;
    SHORT_array_class leftSideBearing;
    thmtx hmtx;
    USHORT_class count;
    USHORT_class stringOffset;
    USHORT_class languageID;
    USHORT_class nameID;
    USHORT_class offset_;
    char_class name_element;
    char_array_class name;
    tname name_;
    unsigned_long_class italicAngle;
    TT_FWord_class underlinePosition;
    TT_FWord_class underlineThickness;
    ULONG_class isFixedPitch;
    ULONG_class minMemType42;
    ULONG_class maxMemType42;
    ULONG_class minMemType1;
    ULONG_class maxMemType1;
    USHORT_class numberOfGlyphs;
    USHORT_class glyphNameIndex_element;
    USHORT_array_class glyphNameIndex;
    UBYTE_class length__;
    CHAR_class text_element;
    CHAR_array_class text;
    tpostName name___element;
    tpostName_array_class name__;
    USHORT_class tpostoffset_element;
    USHORT_array_class tpostoffset;
    tpost post;
    TT_FWord_class value_element;
    TT_FWord_array_class value;
    tcvt cvt;
    UBYTE_class bytecode_element;
    UBYTE_array_class bytecode;
    tfpgm fpgm;
    USHORT_class offsets_element;
    USHORT_array_class offsets;
    ULONG_class offsets__element;
    ULONG_array_class offsets_;
    tloca loca;
    USHORT_class local_offset;
    ULONG_class local_offset_;
    SHORT_class numberOfContoursl;
    SHORT_class endPtsOfContoursl;
    USHORT_class instructionLengthl;
    UBYTE_class instructions_element;
    UBYTE_array_class instructions;
    UBYTE_class SimpleGlyph_flag_element;
    UBYTE_array_class SimpleGlyph_flag;
    UBYTE_class xDelta;
    UBYTE_class xDeltaRepeat;
    SHORT_class xDeltaRepeat_;
    SHORT_class xDelta_;
    UBYTE_class yDelta;
    UBYTE_class yDeltaRepeat;
    SHORT_class yDeltaRepeat_;
    SHORT_class yDelta_;
    tPoints points;
    tSimpleGlyphPoints contours;
    tSimpleGlyph SimpleGlyph;
    tglyf glyf;
    tprep prep;
    unsigned_long_class Version;
    TT_Offset_class GlyphClassDef;
    TT_Offset_class AttachList;
    TT_Offset_class LigCaretList;
    TT_Offset_class MarkAttachClassDef;
    tGDEF GDEF;
    USHORT_class Offset;
    uint16_class ScriptCountl;
    char_class ScriptTag_element;
    char_array_class ScriptTag;
    USHORT_class DefaultLangSys;
    ubyte_class LangSysCounth;
    ubyte_class LangSysCountl;
    char_class LangSysTag_element;
    char_array_class LangSysTag;
    USHORT_class LookupOrder;
    uint16_class ReqFeatureIndex;
    ubyte_class FeatureCounth;
    ubyte_class FeatureCountl;
    uint16_class FeatureIndex_element;
    uint16_array_class FeatureIndex;
    tLangSysTable LangSysTable;
    tLangSysRecord LangSysRecord;
    tScriptRecord_ScriptTable_struct ScriptTable;
    tLangSysTable DefaultLangSysTable;
    tScriptRecord ScriptRecord;
    tScriptList ScriptList;
    char_class FeatureTag_element;
    char_array_class FeatureTag;
    uint16_class FeatureParams;
    ubyte_class LookupListCounth;
    ubyte_class LookupListCountl;
    uint16_class LookupListIndex_element;
    uint16_array_class LookupListIndex;
    tFeatureRecord_FeatureTable_struct FeatureTable;
    tFeatureRecord FeatureRecord;
    tFeatureList FeatureList;
    ubyte_class LookupCounth;
    ubyte_class LookupCountl;
    uint16_class LookupType;
    uint16_class LookupFlag;
    ubyte_class SubTableCounth;
    ubyte_class SubTableCountl;
    USHORT_class SubTable_element;
    USHORT_array_class SubTable;
    tLookupRecord LookupRecord;
    tLookupList LookupList;
    tGSUBorGPOS GSUB;
    ULONG_class ulVersion;
    UBYTE_class usNumSigsh;
    UBYTE_class usNumSigsl;
    USHORT_class usFlag;
    ULONG_class ulFormat;
    ULONG_class ulLength;
    ULONG_class ulOffset;
    USHORT_class usReserved1;
    USHORT_class usReserved2;
    USHORT_class cbSignatureh;
    USHORT_class cbSignaturel;
    UBYTE_class bSignature_element;
    UBYTE_array_class bSignature;
    tDSIG DSIG;
    USHORT_class version_;
    UBYTE_class numRecordsh;
    UBYTE_class numRecordsl;
    USHORT_class sizeDeviceRecordh;
    USHORT_class sizeDeviceRecordl;
    UBYTE_class pixelSize;
    UBYTE_class maxWidth;
    UBYTE_class widths_element;
    UBYTE_array_class widths;
    DeviceRecord_struct DeviceRecord_element;
    DeviceRecord_struct_array_class DeviceRecord;
    thdmx hdmx;
    USHORT_class ver;
    UBYTE_class yPels_element;
    UBYTE_array_class yPels;
    tLTSH LTSH;
    USHORT_class numRecs;
    UBYTE_class numRatiosh;
    UBYTE_class numRatiosl;
    UBYTE_class bCharSet;
    UBYTE_class xRatio;
    UBYTE_class yStartRatio;
    UBYTE_class yEndRatio;
    RatioRange ratRange_element;
    RatioRange_array_class ratRange;
    USHORT_class offsetl_element;
    USHORT_array_class offsetl;
    UBYTE_class recsh;
    UBYTE_class recsl;
    BYTE_class startsz;
    BYTE_class endsz;
    USHORT_class yPelHeight;
    VDMXRecord entry_element;
    VDMXRecord_array_class entry;
    VDMXGroup groups;
    tVDMX VDMX;
    uint16_class version__;
    uint16_class numRanges;
    uint16_class rangeMaxPPEM;
    uint16_bitfield gridfit;
    uint16_bitfield doGray;
    uint16_bitfield symMetricGridfit;
    uint16_bitfield symMetricSmoothing;
    uint16_bitfield Reserved;
    GaspBehavior rangeGaspBehavior;
    tgaspRange gaspRanges_element;
    tgaspRange_array_class gaspRanges;
    tgasp gasp;
    ULONG_class length2;
    tTable Table;


    globals_class() :
        SFNT_Ver(1),
        numTables(1),
        searchRange(1),
        entrySelector(1),
        rangeShift(1),
        OffsetTable(tOffsetTable_OffsetTable_instances),
        tag_type(4, 0),
        asName_element(false),
        asName(asName_element),
        asLong(1),
        Tag(CTag_Tag_instances),
        checkSum(1),
        offset(1),
        slength(1),
        stable(sTable_stable_instances),
        length(1),
        version(1, { 0x00005000, 0x00020000, 0x00025000 }),
        fontRevision(1),
        checkSumAdjustment(1),
        magicNumber(1),
        flags(1),
        unitsPerEm(1),
        created(1),
        modified(1),
        xMin(1),
        yMin(1),
        xMax(1),
        yMax(1),
        macStyle(1),
        lowestRecPPEM(1),
        fontDirectionHint(1),
        indexToLocFormat(1),
        glyphDataFormat(1),
        head(thead_head_instances),
        version_cmap(1),
        cmap(tcmap_cmap_instances),
        platformID(1),
        encodingID(1),
        format(1),
        length_(1),
        language(1),
        glyphIdArray_element(false),
        glyphIdArray(glyphIdArray_element),
        format0(tcmap_format0_format0_instances),
        subHeaderKeys(1),
        firstCode(1),
        entryCount(1),
        idDelta(1),
        idRangeOffset(1),
        glyphIdArray__element(false),
        glyphIdArray_(glyphIdArray__element),
        format2(tcmap_format2_format2_instances),
        segCountX2(1),
        endCount_element(false),
        endCount(endCount_element),
        reservedPad(1),
        startCount_element(false),
        startCount(startCount_element),
        idDelta__element(false),
        idDelta_(idDelta__element),
        idRangeOffset__element(false),
        idRangeOffset_(idRangeOffset__element),
        format4(tcmap_format4_format4_instances),
        firstCode_(1),
        entryCount_(1),
        format6(tcmap_format6_format6_instances),
        reserved(1),
        language_(1),
        is32_element(false),
        is32(is32_element),
        nGroups(1),
        startCharCode(1),
        endCharCode(1),
        startGlyphID(1),
        groupings_element(tcmap_format8_groupings_struct_groupings_element_instances),
        groupings(groupings_element),
        format8(tcmap_format8_format8_instances),
        groupings__element(tcmap_format12_groupings_struct_groupings__element_instances),
        groupings_(groupings__element),
        format12(tcmap_format12_format12_instances),
        Ascender(1),
        Descender(1),
        LineGap(1),
        advanceWidthMax(1),
        minLeftSideBearing(1),
        minRightSideBearing(1),
        xMaxExtent(1),
        caretSlopeRise(1),
        caretSlopeRun(1),
        caretOffset(1),
        reserved_(1),
        reserved1(1),
        reserved2(1),
        reserved3(1),
        metricDataFormat(1),
        numberOfHMetrics(1),
        hhea(thhea_hhea_instances),
        version_tos(1),
        xAvgCharWidth(1),
        usWeightClass(1),
        usWidthClass(1),
        fsType(1),
        ySubscriptXSize(1),
        ySubscriptYSize(1),
        ySubscriptXOffset(1),
        ySubscriptYOffset(1),
        ySuperscriptXSize(1),
        ySuperscriptYSize(1),
        ySuperscriptXOffset(1),
        ySuperscriptYOffset(1),
        yStrikeoutSize(1),
        yStrikeoutPosition(1),
        sFamilyClass(1),
        bFamilyType(1),
        bSerifStyle(1),
        bWeight(1),
        bProportion(1),
        bContrast(1),
        bStrokeVariation(1),
        bArmStyle(1),
        bLetterform(1),
        bMidline(1),
        bXHeight(1),
        panose(tpanose_panose_instances),
        ulUnicodeRange1(1),
        ulUnicodeRange2(1),
        ulUnicodeRange3(1),
        ulUnicodeRange4(1),
        achVendID_element(false),
        achVendID(achVendID_element),
        fsSelection(1),
        usFirstCharIndex(1),
        usLastCharIndex(1),
        sTypoAscender(1),
        sTypoDescender(1),
        sTypoLineGap(1),
        usWinAscent(1),
        usWinDescent(1),
        ulCodePageRange1(1),
        ulCodePageRange2(1),
        sxHeight(1),
        sCapHeight(1),
        usDefaultChar(1),
        usBreakChar(1),
        usMaxContext(1),
        OS_2(tOS_2_OS_2_instances),
        numGlyphs(1),
        maxPoints(1),
        maxContours(1),
        maxCompositePoints(1),
        maxCompositeContours(1),
        maxZones(1),
        maxTwilightPoints(1),
        maxStorage(1),
        maxFunctionDefs(1),
        maxInstructionDefs(1),
        maxStackElements(1),
        maxSizeOfInstructions(1),
        maxComponentElements(1),
        maxComponentDepth(1),
        maxp(tmaxp_maxp_instances),
        advanceWidth(1),
        lsb(1),
        hMetrics_element(tlongHorMetric_hMetrics_element_instances),
        hMetrics(hMetrics_element),
        leftSideBearing_element(false),
        leftSideBearing(leftSideBearing_element),
        hmtx(thmtx_hmtx_instances),
        count(1),
        stringOffset(1),
        languageID(1),
        nameID(1),
        offset_(1),
        name_element(false),
        name(name_element),
        name_(tname_name__instances),
        italicAngle(1),
        underlinePosition(1),
        underlineThickness(1),
        isFixedPitch(1),
        minMemType42(1),
        maxMemType42(1),
        minMemType1(1),
        maxMemType1(1),
        numberOfGlyphs(1),
        glyphNameIndex_element(false),
        glyphNameIndex(glyphNameIndex_element),
        length__(1),
        text_element(false),
        text(text_element),
        name___element(tpostName_name___element_instances),
        name__(name___element),
        tpostoffset_element(false),
        tpostoffset(tpostoffset_element),
        post(tpost_post_instances),
        value_element(false),
        value(value_element),
        cvt(tcvt_cvt_instances),
        bytecode_element(false),
        bytecode(bytecode_element),
        fpgm(tfpgm_fpgm_instances),
        offsets_element(false),
        offsets(offsets_element),
        offsets__element(false),
        offsets_(offsets__element),
        loca(tloca_loca_instances),
        local_offset(1),
        local_offset_(1),
        numberOfContoursl(1),
        endPtsOfContoursl(1),
        instructionLengthl(1),
        instructions_element(false),
        instructions(instructions_element),
        SimpleGlyph_flag_element(false),
        SimpleGlyph_flag(SimpleGlyph_flag_element),
        xDelta(1),
        xDeltaRepeat(1),
        xDeltaRepeat_(1),
        xDelta_(1),
        yDelta(1),
        yDeltaRepeat(1),
        yDeltaRepeat_(1),
        yDelta_(1),
        points(tPoints_points_instances),
        contours(tSimpleGlyphPoints_contours_instances),
        SimpleGlyph(tSimpleGlyph_SimpleGlyph_instances),
        glyf(tglyf_glyf_instances),
        prep(tprep_prep_instances),
        Version(1),
        GlyphClassDef(1),
        AttachList(1),
        LigCaretList(1),
        MarkAttachClassDef(1),
        GDEF(tGDEF_GDEF_instances),
        Offset(1),
        ScriptCountl(1),
        ScriptTag_element(false),
        ScriptTag(ScriptTag_element),
        DefaultLangSys(1),
        LangSysCounth(1),
        LangSysCountl(1),
        LangSysTag_element(false),
        LangSysTag(LangSysTag_element),
        LookupOrder(1),
        ReqFeatureIndex(1),
        FeatureCounth(1),
        FeatureCountl(1),
        FeatureIndex_element(false),
        FeatureIndex(FeatureIndex_element),
        LangSysTable(tLangSysTable_LangSysTable_instances),
        LangSysRecord(tLangSysRecord_LangSysRecord_instances),
        ScriptTable(tScriptRecord_ScriptTable_struct_ScriptTable_instances),
        DefaultLangSysTable(tLangSysTable_DefaultLangSysTable_instances),
        ScriptRecord(tScriptRecord_ScriptRecord_instances),
        ScriptList(tScriptList_ScriptList_instances),
        FeatureTag_element(false),
        FeatureTag(FeatureTag_element),
        FeatureParams(1),
        LookupListCounth(1),
        LookupListCountl(1),
        LookupListIndex_element(false),
        LookupListIndex(LookupListIndex_element),
        FeatureTable(tFeatureRecord_FeatureTable_struct_FeatureTable_instances),
        FeatureRecord(tFeatureRecord_FeatureRecord_instances),
        FeatureList(tFeatureList_FeatureList_instances),
        LookupCounth(1),
        LookupCountl(1),
        LookupType(1),
        LookupFlag(1),
        SubTableCounth(1),
        SubTableCountl(1),
        SubTable_element(false),
        SubTable(SubTable_element),
        LookupRecord(tLookupRecord_LookupRecord_instances),
        LookupList(tLookupList_LookupList_instances),
        GSUB(tGSUBorGPOS_GSUB_instances),
        ulVersion(1),
        usNumSigsh(1),
        usNumSigsl(1),
        usFlag(1),
        ulFormat(1),
        ulLength(1),
        ulOffset(1),
        usReserved1(1),
        usReserved2(1),
        cbSignatureh(1),
        cbSignaturel(1),
        bSignature_element(false),
        bSignature(bSignature_element),
        DSIG(tDSIG_DSIG_instances),
        version_(1),
        numRecordsh(1),
        numRecordsl(1),
        sizeDeviceRecordh(1),
        sizeDeviceRecordl(1),
        pixelSize(1),
        maxWidth(1),
        widths_element(false),
        widths(widths_element),
        DeviceRecord_element(DeviceRecord_struct_DeviceRecord_element_instances),
        DeviceRecord(DeviceRecord_element),
        hdmx(thdmx_hdmx_instances),
        ver(1),
        yPels_element(false),
        yPels(yPels_element),
        LTSH(tLTSH_LTSH_instances),
        numRecs(1),
        numRatiosh(1),
        numRatiosl(1),
        bCharSet(1),
        xRatio(1),
        yStartRatio(1),
        yEndRatio(1),
        ratRange_element(RatioRange_ratRange_element_instances),
        ratRange(ratRange_element),
        offsetl_element(false),
        offsetl(offsetl_element),
        recsh(1),
        recsl(1),
        startsz(1),
        endsz(1),
        yPelHeight(1),
        entry_element(VDMXRecord_entry_element_instances),
        entry(entry_element),
        groups(VDMXGroup_groups_instances),
        VDMX(tVDMX_VDMX_instances),
        version__(1),
        numRanges(1),
        rangeMaxPPEM(1),
        gridfit(1),
        doGray(1),
        symMetricGridfit(1),
        symMetricSmoothing(1),
        Reserved(1),
        rangeGaspBehavior(GaspBehavior_rangeGaspBehavior_instances),
        gaspRanges_element(tgaspRange_gaspRanges_element_instances),
        gaspRanges(gaspRanges_element),
        gasp(tgasp_gasp_instances),
        length2(1),
        Table(tTable_Table_instances)
    {}
};

globals_class* g;


tOffsetTable* tOffsetTable::generate() {
    if (generated == 1) {
        tOffsetTable* new_instance = new tOffsetTable(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(SFNT_Ver, ::g->SFNT_Ver.generate({ 0x00010000 }));
    ::g->numTables_offset = FTell();
    GENERATE_VAR(numTables, ::g->numTables.generate({ 5, 10, 16 }));
    ::g->numTables_n = numTables();
    GENERATE_VAR(searchRange, ::g->searchRange.generate());
    GENERATE_VAR(entrySelector, ::g->entrySelector.generate());
    GENERATE_VAR(rangeShift, ::g->rangeShift.generate());

    _sizeof = FTell() - _startof;
    return this;
}


CTag* CTag::generate() {
    if (generated == 1) {
        CTag* new_instance = new CTag(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(asName, ::g->asName.generate(4));
    GENERATE_EXISTS(asLong, ::g->asLong.generate());

    _sizeof = FTell() - _startof;
    return this;
}


sTable* sTable::generate() {
    if (generated == 1) {
        sTable* new_instance = new sTable(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(Tag, ::g->Tag.generate());
    GENERATE_VAR(checkSum, ::g->checkSum.generate());
    GENERATE_VAR(offset, ::g->offset.generate());
    GENERATE_VAR(slength, ::g->slength.generate());

    _sizeof = FTell() - _startof;
    return this;
}


thead* thead::generate() {
    if (generated == 1) {
        thead* new_instance = new thead(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(version, ::g->version.generate({ 0x00010000 }));
    GENERATE_VAR(fontRevision, ::g->fontRevision.generate({ 0x00010000 }));
    GENERATE_VAR(checkSumAdjustment, ::g->checkSumAdjustment.generate({ 0 }));
    GENERATE_VAR(magicNumber, ::g->magicNumber.generate({ 0x5F0F3CF5 }));
    GENERATE_VAR(flags, ::g->flags.generate());
    GENERATE_VAR(unitsPerEm, ::g->unitsPerEm.generate());
    GENERATE_VAR(created, ::g->created.generate());
    GENERATE_VAR(modified, ::g->modified.generate());
    GENERATE_VAR(xMin, ::g->xMin.generate());
    GENERATE_VAR(yMin, ::g->yMin.generate());
    GENERATE_VAR(xMax, ::g->xMax.generate());
    GENERATE_VAR(yMax, ::g->yMax.generate());
    GENERATE_VAR(macStyle, ::g->macStyle.generate());
    GENERATE_VAR(lowestRecPPEM, ::g->lowestRecPPEM.generate());
    GENERATE_VAR(fontDirectionHint, ::g->fontDirectionHint.generate());
    GENERATE_VAR(indexToLocFormat, ::g->indexToLocFormat.generate({ 0 }));
    GENERATE_VAR(glyphDataFormat, ::g->glyphDataFormat.generate({ 0 }));

    _sizeof = FTell() - _startof;
    return this;
}


tcmap* tcmap::generate() {
    if (generated == 1) {
        tcmap* new_instance = new tcmap(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    cmap_table = FTell();
    GENERATE_VAR(version_cmap, ::g->version_cmap.generate({ 0 }));
    GENERATE_VAR(numTables, ::g->numTables.generate());

    _sizeof = FTell() - _startof;
    return this;
}


tcmap_format0* tcmap_format0::generate(quad& cmap_subtable) {
    if (generated == 1) {
        tcmap_format0* new_instance = new tcmap_format0(instances);
        new_instance->generated = 2;
        return new_instance->generate(cmap_subtable);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    cmap_subtable = FTell();
    GENERATE_VAR(length, ::g->length_.generate({ 262 }));
    GENERATE_VAR(language, ::g->language.generate());
    GENERATE_VAR(glyphIdArray, ::g->glyphIdArray.generate(256));

    _sizeof = FTell() - _startof;
    return this;
}


tcmap_format2* tcmap_format2::generate(quad& cmap_subtable) {
    if (generated == 1) {
        tcmap_format2* new_instance = new tcmap_format2(instances);
        new_instance->generated = 2;
        return new_instance->generate(cmap_subtable);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    cmap_subtable = FTell();
    GENERATE_VAR(length, ::g->length_.generate());
    GENERATE_VAR(language, ::g->language.generate());
    maxidx = 0;
    i = 0;
    for (i = 0; (i < 256); ++i) {
            GENERATE_VAR(subHeaderKeys, ::g->subHeaderKeys.generate({ 0, 1000 }));
        if ((subHeaderKeys() > maxidx)) {
        maxidx = subHeaderKeys();
        };
    ;
    };
    maxidx = (maxidx / 8);
    for (i = maxidx; (i >= 0); i--) {
            GENERATE_VAR(firstCode, ::g->firstCode.generate());
        GENERATE_VAR(entryCount, ::g->entryCount.generate({ 100 }));
        GENERATE_VAR(idDelta, ::g->idDelta.generate());
        tmp_idrange = ((i * 8) + 4);
        GENERATE_VAR(idRangeOffset, ::g->idRangeOffset.generate({ tmp_idrange }));
    ;
    };
    format2_length = length();
    GENERATE_VAR(glyphIdArray, ::g->glyphIdArray_.generate(100));

    _sizeof = FTell() - _startof;
    return this;
}


tcmap_format4* tcmap_format4::generate(quad& cmap_subtable) {
    if (generated == 1) {
        tcmap_format4* new_instance = new tcmap_format4(instances);
        new_instance->generated = 2;
        return new_instance->generate(cmap_subtable);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    cmap_subtable = FTell();
    GENERATE_VAR(length, ::g->length_.generate());
    GENERATE_VAR(language, ::g->language.generate());
    GENERATE_VAR(segCountX2, ::g->segCountX2.generate());
    GENERATE_VAR(searchRange, ::g->searchRange.generate());
    GENERATE_VAR(entrySelector, ::g->entrySelector.generate());
    GENERATE_VAR(rangeShift, ::g->rangeShift.generate());
    GENERATE_VAR(endCount, ::g->endCount.generate((segCountX2() / 2)));
    GENERATE_VAR(reservedPad, ::g->reservedPad.generate());
    GENERATE_VAR(startCount, ::g->startCount.generate((segCountX2() / 2)));
    GENERATE_VAR(idDelta, ::g->idDelta_.generate((segCountX2() / 2)));
    GENERATE_VAR(idRangeOffset, ::g->idRangeOffset_.generate((segCountX2() / 2)));
    glyphIdArraylength = (length() - (FTell() - cmap_subtable));
    GENERATE_VAR(glyphIdArray, ::g->glyphIdArray_.generate((glyphIdArraylength / 2)));

    _sizeof = FTell() - _startof;
    return this;
}


tcmap_format6* tcmap_format6::generate(quad& cmap_subtable) {
    if (generated == 1) {
        tcmap_format6* new_instance = new tcmap_format6(instances);
        new_instance->generated = 2;
        return new_instance->generate(cmap_subtable);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    cmap_subtable = FTell();
    GENERATE_VAR(length, ::g->length_.generate());
    GENERATE_VAR(language, ::g->language.generate());
    GENERATE_VAR(firstCode, ::g->firstCode_.generate());
    GENERATE_VAR(entryCount, ::g->entryCount_.generate());
    GENERATE_VAR(glyphIdArray, ::g->glyphIdArray_.generate(entryCount()));

    _sizeof = FTell() - _startof;
    return this;
}


tcmap_format8_groupings_struct* tcmap_format8_groupings_struct::generate() {
    if (generated == 1) {
        tcmap_format8_groupings_struct* new_instance = new tcmap_format8_groupings_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(startCharCode, ::g->startCharCode.generate());
    GENERATE_VAR(endCharCode, ::g->endCharCode.generate());
    GENERATE_VAR(startGlyphID, ::g->startGlyphID.generate());

    _sizeof = FTell() - _startof;
    return this;
}


tcmap_format8* tcmap_format8::generate(quad& cmap_subtable) {
    if (generated == 1) {
        tcmap_format8* new_instance = new tcmap_format8(instances);
        new_instance->generated = 2;
        return new_instance->generate(cmap_subtable);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    cmap_subtable = FTell();
    GENERATE_VAR(reserved, ::g->reserved.generate());
    GENERATE_VAR(length, ::g->length.generate());
    GENERATE_VAR(language, ::g->language_.generate());
    GENERATE_VAR(is32, ::g->is32.generate(8192));
    GENERATE_VAR(nGroups, ::g->nGroups.generate());
    GENERATE_VAR(groupings, ::g->groupings.generate(nGroups()));

    _sizeof = FTell() - _startof;
    return this;
}


tcmap_format12_groupings_struct* tcmap_format12_groupings_struct::generate() {
    if (generated == 1) {
        tcmap_format12_groupings_struct* new_instance = new tcmap_format12_groupings_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(startCharCode, ::g->startCharCode.generate());
    GENERATE_VAR(endCharCode, ::g->endCharCode.generate());
    GENERATE_VAR(startGlyphID, ::g->startGlyphID.generate());

    _sizeof = FTell() - _startof;
    return this;
}


tcmap_format12* tcmap_format12::generate() {
    if (generated == 1) {
        tcmap_format12* new_instance = new tcmap_format12(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(reserved, ::g->reserved.generate());
    GENERATE_VAR(length, ::g->length.generate());
    GENERATE_VAR(language, ::g->language_.generate());
    GENERATE_VAR(nGroups, ::g->nGroups.generate());
    GENERATE_VAR(groupings, ::g->groupings_.generate(nGroups()));

    _sizeof = FTell() - _startof;
    return this;
}


thhea* thhea::generate() {
    if (generated == 1) {
        thhea* new_instance = new thhea(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(version, ::g->version.generate({ 0x00010000 }));
    GENERATE_VAR(Ascender, ::g->Ascender.generate());
    GENERATE_VAR(Descender, ::g->Descender.generate());
    GENERATE_VAR(LineGap, ::g->LineGap.generate());
    GENERATE_VAR(advanceWidthMax, ::g->advanceWidthMax.generate());
    GENERATE_VAR(minLeftSideBearing, ::g->minLeftSideBearing.generate());
    GENERATE_VAR(minRightSideBearing, ::g->minRightSideBearing.generate());
    GENERATE_VAR(xMaxExtent, ::g->xMaxExtent.generate());
    GENERATE_VAR(caretSlopeRise, ::g->caretSlopeRise.generate());
    GENERATE_VAR(caretSlopeRun, ::g->caretSlopeRun.generate());
    GENERATE_VAR(caretOffset, ::g->caretOffset.generate());
    GENERATE_VAR(reserved, ::g->reserved_.generate({ 0 }));
    GENERATE_VAR(reserved1, ::g->reserved1.generate({ 0 }));
    GENERATE_VAR(reserved2, ::g->reserved2.generate({ 0 }));
    GENERATE_VAR(reserved3, ::g->reserved3.generate({ 0 }));
    GENERATE_VAR(metricDataFormat, ::g->metricDataFormat.generate({ 0 }));
    GENERATE_VAR(numberOfHMetrics, ::g->numberOfHMetrics.generate());

    _sizeof = FTell() - _startof;
    return this;
}


tpanose* tpanose::generate() {
    if (generated == 1) {
        tpanose* new_instance = new tpanose(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(bFamilyType, ::g->bFamilyType.generate());
    GENERATE_VAR(bSerifStyle, ::g->bSerifStyle.generate());
    GENERATE_VAR(bWeight, ::g->bWeight.generate());
    GENERATE_VAR(bProportion, ::g->bProportion.generate());
    GENERATE_VAR(bContrast, ::g->bContrast.generate());
    GENERATE_VAR(bStrokeVariation, ::g->bStrokeVariation.generate());
    GENERATE_VAR(bArmStyle, ::g->bArmStyle.generate());
    GENERATE_VAR(bLetterform, ::g->bLetterform.generate());
    GENERATE_VAR(bMidline, ::g->bMidline.generate());
    GENERATE_VAR(bXHeight, ::g->bXHeight.generate());

    _sizeof = FTell() - _startof;
    return this;
}


tOS_2* tOS_2::generate() {
    if (generated == 1) {
        tOS_2* new_instance = new tOS_2(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(version_tos, ::g->version_tos.generate({ 0x0003 }));
    GENERATE_VAR(xAvgCharWidth, ::g->xAvgCharWidth.generate());
    GENERATE_VAR(usWeightClass, ::g->usWeightClass.generate());
    GENERATE_VAR(usWidthClass, ::g->usWidthClass.generate());
    GENERATE_VAR(fsType, ::g->fsType.generate());
    GENERATE_VAR(ySubscriptXSize, ::g->ySubscriptXSize.generate());
    GENERATE_VAR(ySubscriptYSize, ::g->ySubscriptYSize.generate());
    GENERATE_VAR(ySubscriptXOffset, ::g->ySubscriptXOffset.generate());
    GENERATE_VAR(ySubscriptYOffset, ::g->ySubscriptYOffset.generate());
    GENERATE_VAR(ySuperscriptXSize, ::g->ySuperscriptXSize.generate());
    GENERATE_VAR(ySuperscriptYSize, ::g->ySuperscriptYSize.generate());
    GENERATE_VAR(ySuperscriptXOffset, ::g->ySuperscriptXOffset.generate());
    GENERATE_VAR(ySuperscriptYOffset, ::g->ySuperscriptYOffset.generate());
    GENERATE_VAR(yStrikeoutSize, ::g->yStrikeoutSize.generate());
    GENERATE_VAR(yStrikeoutPosition, ::g->yStrikeoutPosition.generate());
    GENERATE_VAR(sFamilyClass, ::g->sFamilyClass.generate());
    GENERATE_VAR(panose, ::g->panose.generate());
    GENERATE_VAR(ulUnicodeRange1, ::g->ulUnicodeRange1.generate());
    GENERATE_VAR(ulUnicodeRange2, ::g->ulUnicodeRange2.generate());
    GENERATE_VAR(ulUnicodeRange3, ::g->ulUnicodeRange3.generate());
    GENERATE_VAR(ulUnicodeRange4, ::g->ulUnicodeRange4.generate());
    GENERATE_VAR(achVendID, ::g->achVendID.generate(4));
    GENERATE_VAR(fsSelection, ::g->fsSelection.generate());
    GENERATE_VAR(usFirstCharIndex, ::g->usFirstCharIndex.generate());
    GENERATE_VAR(usLastCharIndex, ::g->usLastCharIndex.generate());
    GENERATE_VAR(sTypoAscender, ::g->sTypoAscender.generate());
    GENERATE_VAR(sTypoDescender, ::g->sTypoDescender.generate());
    GENERATE_VAR(sTypoLineGap, ::g->sTypoLineGap.generate());
    GENERATE_VAR(usWinAscent, ::g->usWinAscent.generate());
    GENERATE_VAR(usWinDescent, ::g->usWinDescent.generate());
    GENERATE_VAR(ulCodePageRange1, ::g->ulCodePageRange1.generate());
    GENERATE_VAR(ulCodePageRange2, ::g->ulCodePageRange2.generate());
    GENERATE_VAR(sxHeight, ::g->sxHeight.generate());
    GENERATE_VAR(sCapHeight, ::g->sCapHeight.generate());
    GENERATE_VAR(usDefaultChar, ::g->usDefaultChar.generate());
    GENERATE_VAR(usBreakChar, ::g->usBreakChar.generate());
    GENERATE_VAR(usMaxContext, ::g->usMaxContext.generate());

    _sizeof = FTell() - _startof;
    return this;
}


tmaxp* tmaxp::generate() {
    if (generated == 1) {
        tmaxp* new_instance = new tmaxp(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(version, ::g->version.generate({ 0x00010000 }));
    if ((version() == 0x00005000)) {
        GENERATE_VAR(numGlyphs, ::g->numGlyphs.generate());
    } else {
        GENERATE_VAR(numGlyphs, ::g->numGlyphs.generate());
        GENERATE_VAR(maxPoints, ::g->maxPoints.generate());
        GENERATE_VAR(maxContours, ::g->maxContours.generate());
        GENERATE_VAR(maxCompositePoints, ::g->maxCompositePoints.generate());
        GENERATE_VAR(maxCompositeContours, ::g->maxCompositeContours.generate());
        GENERATE_VAR(maxZones, ::g->maxZones.generate());
        GENERATE_VAR(maxTwilightPoints, ::g->maxTwilightPoints.generate());
        GENERATE_VAR(maxStorage, ::g->maxStorage.generate());
        GENERATE_VAR(maxFunctionDefs, ::g->maxFunctionDefs.generate());
        GENERATE_VAR(maxInstructionDefs, ::g->maxInstructionDefs.generate());
        GENERATE_VAR(maxStackElements, ::g->maxStackElements.generate());
        GENERATE_VAR(maxSizeOfInstructions, ::g->maxSizeOfInstructions.generate());
        GENERATE_VAR(maxComponentElements, ::g->maxComponentElements.generate());
        GENERATE_VAR(maxComponentDepth, ::g->maxComponentDepth.generate());
    };

    _sizeof = FTell() - _startof;
    return this;
}


tlongHorMetric* tlongHorMetric::generate() {
    if (generated == 1) {
        tlongHorMetric* new_instance = new tlongHorMetric(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(advanceWidth, ::g->advanceWidth.generate());
    GENERATE_VAR(lsb, ::g->lsb.generate());

    _sizeof = FTell() - _startof;
    return this;
}


thmtx* thmtx::generate() {
    if (generated == 1) {
        thmtx* new_instance = new thmtx(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    numberOfHMetrics = ::g->attf_numberOfHMetrics;
    GENERATE_VAR(hMetrics, ::g->hMetrics.generate(numberOfHMetrics));
    numLeftSideBearing = ((::g->hmtx_length - (numberOfHMetrics * 4)) / 2);
    GENERATE_VAR(leftSideBearing, ::g->leftSideBearing.generate(numLeftSideBearing));

    _sizeof = FTell() - _startof;
    return this;
}


tname* tname::generate() {
    if (generated == 1) {
        tname* new_instance = new tname(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    name_table = FTell();
    GENERATE_VAR(format, ::g->format.generate());
    GENERATE_VAR(count, ::g->count.generate());
    GENERATE_VAR(stringOffset, ::g->stringOffset.generate());
    for (::g->i = 0; (::g->i < count()); ::g->i++) {
            GENERATE_VAR(platformID, ::g->platformID.generate());
        GENERATE_VAR(encodingID, ::g->encodingID.generate());
        GENERATE_VAR(languageID, ::g->languageID.generate());
        GENERATE_VAR(nameID, ::g->nameID.generate());
        GENERATE_VAR(length, ::g->length_.generate());
        GENERATE_VAR(offset, ::g->offset_.generate());
        NextNameRecord = FTell();
        FSeek(((name_table + stringOffset()) + offset()));
        GENERATE_VAR(name, ::g->name.generate(length()));
        FSeek(NextNameRecord);
    ;
    };

    _sizeof = FTell() - _startof;
    return this;
}


tpostName* tpostName::generate() {
    if (generated == 1) {
        tpostName* new_instance = new tpostName(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(length, ::g->length__.generate());
    GENERATE_VAR(text, ::g->text.generate(length()));

    _sizeof = FTell() - _startof;
    return this;
}


tpost* tpost::generate() {
    if (generated == 1) {
        tpost* new_instance = new tpost(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    post = FTell();
    GENERATE_VAR(version, ::g->version.generate({ 0x00020000, 0x00025000 }));
    GENERATE_VAR(italicAngle, ::g->italicAngle.generate());
    GENERATE_VAR(underlinePosition, ::g->underlinePosition.generate());
    GENERATE_VAR(underlineThickness, ::g->underlineThickness.generate());
    GENERATE_VAR(isFixedPitch, ::g->isFixedPitch.generate());
    GENERATE_VAR(minMemType42, ::g->minMemType42.generate());
    GENERATE_VAR(maxMemType42, ::g->maxMemType42.generate());
    GENERATE_VAR(minMemType1, ::g->minMemType1.generate());
    GENERATE_VAR(maxMemType1, ::g->maxMemType1.generate());
    if ((version() == 0x00020000)) {
        GENERATE_VAR(numberOfGlyphs, ::g->numberOfGlyphs.generate());
        numGlyphs = numberOfGlyphs();
        GENERATE_VAR(glyphNameIndex, ::g->glyphNameIndex.generate(numGlyphs));
        numberNewGlyphs = numberOfGlyphs();
        GENERATE_VAR(name, ::g->name__.generate(10));
    };
    if ((version() == 0x00025000)) {
        GENERATE_VAR(numberOfGlyphs, ::g->numberOfGlyphs.generate());
        numGlyphs = numberOfGlyphs();
        GENERATE_VAR(tpostoffset, ::g->tpostoffset.generate(numGlyphs));
    };

    _sizeof = FTell() - _startof;
    return this;
}


tcvt* tcvt::generate() {
    if (generated == 1) {
        tcvt* new_instance = new tcvt(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(value, ::g->value.generate(500));

    _sizeof = FTell() - _startof;
    return this;
}


tfpgm* tfpgm::generate() {
    if (generated == 1) {
        tfpgm* new_instance = new tfpgm(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(bytecode, ::g->bytecode.generate(1000));

    _sizeof = FTell() - _startof;
    return this;
}


tloca* tloca::generate() {
    if (generated == 1) {
        tloca* new_instance = new tloca(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    tloca_n = (::g->attf_numGlyphs + 1);
    format = ::g->attf_indexToLocFormat;
    if ((format == 0)) {
        GENERATE(offsets, ::g->offsets.generate(tloca_n));
    } else {
        GENERATE(offsets, ::g->offsets_.generate(tloca_n));
    };

    _sizeof = FTell() - _startof;
    return this;
}


tPoints* tPoints::generate(ulong& i_sgp, quad& xStart, quad& xLast, quad& yStart, quad& yLast, byte& xLastByte, byte& yLastByte, int& g_lenngth) {
    if (generated == 1) {
        tPoints* new_instance = new tPoints(instances);
        new_instance->generated = 2;
        return new_instance->generate(i_sgp, xStart, xLast, yStart, yLast, xLastByte, yLastByte, g_lenngth);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    if ((::g->SimpleGlyph_flag()[i_sgp] & ::g->X_BYTE)) {
        xLast = FTell();
        xLastByte = 1;
        GENERATE(xDelta, ::g->xDelta.generate());
        g_lenngth++;
        xStart = FTell();
    } else {
        if ((::g->SimpleGlyph_flag()[i_sgp] & ::g->X_TYPE)) {
            FSeek(xLast);
            if ((xLast > 0)) {
                if (xLastByte) {
                    GENERATE(xDeltaRepeat, ::g->xDeltaRepeat.generate());
                    g_lenngth++;
                } else {
                    GENERATE(xDeltaRepeat, ::g->xDeltaRepeat_.generate());
                    g_lenngth += 2;
                };
            };
        } else {
            xLast = FTell();
            xLastByte = 0;
            GENERATE(xDelta, ::g->xDelta_.generate());
            g_lenngth += 2;
            xStart = FTell();
        };
    };
    FSeek(yStart);
    if ((::g->SimpleGlyph_flag()[i_sgp] & ::g->Y_BYTE)) {
        yLast = FTell();
        yLastByte = 1;
        GENERATE(yDelta, ::g->yDelta.generate());
        g_lenngth++;
        yStart = FTell();
    } else {
        if ((::g->SimpleGlyph_flag()[i_sgp] & ::g->Y_TYPE)) {
            FSeek(yLast);
            if ((yLast > 0)) {
                if (yLastByte) {
                    GENERATE(yDeltaRepeat, ::g->yDeltaRepeat.generate());
                    g_lenngth++;
                } else {
                    GENERATE(yDeltaRepeat, ::g->yDeltaRepeat_.generate());
                    g_lenngth += 2;
                };
            };
        } else {
            yLast = FTell();
            yLastByte = 0;
            GENERATE(yDelta, ::g->yDelta_.generate());
            g_lenngth += 2;
            yStart = FTell();
        };
    };
    FSeek(xStart);

    _sizeof = FTell() - _startof;
    return this;
}


tSimpleGlyphPoints* tSimpleGlyphPoints::generate(USHORT& numPoints) {
    if (generated == 1) {
        tSimpleGlyphPoints* new_instance = new tSimpleGlyphPoints(instances);
        new_instance->generated = 2;
        return new_instance->generate(numPoints);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    yusn_start = xStart = xLast = FTell();
    yStart = FTell();
    yLast = 0;
    xLastByte = 0;
    yLastByte = 0;
    GENERATE_VAR(SimpleGlyph_flag, ::g->SimpleGlyph_flag.generate(numPoints));
    for (i_sgp = 0; (i_sgp < numPoints); i_sgp++) {
            if (((SimpleGlyph_flag()[i_sgp] & ::g->X_BYTE) && !(SimpleGlyph_flag()[i_sgp] & ::g->X_TYPE))) {
            yStart++;
            if (!(SimpleGlyph_flag()[i_sgp] & ::g->X_BYTE)) {
                yStart++;
            };
        };
    ;
    };
    g_lenngth = 0;
    for (i_sgp = 0; (i_sgp < numPoints); i_sgp++) {
            if ((!(SimpleGlyph_flag()[i_sgp] & ::g->X_BYTE) && (SimpleGlyph_flag()[i_sgp] & ::g->X_TYPE))) {
        FSeek(xLast);
        } else {
        FSeek(xStart);
        };
        GENERATE_VAR(points, ::g->points.generate(i_sgp, xStart, xLast, yStart, yLast, xLastByte, yLastByte, g_lenngth));
    ;
    };

    _sizeof = FTell() - _startof;
    return this;
}


tSimpleGlyph* tSimpleGlyph::generate() {
    if (generated == 1) {
        tSimpleGlyph* new_instance = new tSimpleGlyph(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(numberOfContoursl, ::g->numberOfContoursl.generate());
    GENERATE_VAR(xMin, ::g->xMin.generate());
    GENERATE_VAR(yMin, ::g->yMin.generate());
    GENERATE_VAR(xMax, ::g->xMax.generate());
    GENERATE_VAR(yMax, ::g->yMax.generate());
    for (n = 0; (n < numberOfContoursl()); n++) {
            GENERATE_VAR(endPtsOfContoursl, ::g->endPtsOfContoursl.generate());
        if ((n == (numberOfContoursl() - 1))) {
            numPoints = endPtsOfContoursl();
            if ((numPoints > 2000)) {
                numPoints = 255;
            };
        };
    ;
    };
    GENERATE_VAR(instructionLengthl, ::g->instructionLengthl.generate());
    if ((instructionLengthl() > 0)) {
        GENERATE_VAR(instructions, ::g->instructions.generate(instructionLengthl()));
    };
    glyf_flag_table = FTell();
    glyf_flag_index = FTell();
    repeat = 0;
    GENERATE_VAR(contours, ::g->contours.generate(numPoints));

    _sizeof = FTell() - _startof;
    return this;
}


tglyf* tglyf::generate() {
    if (generated == 1) {
        tglyf* new_instance = new tglyf(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    glyf_table = FTell();
    if ((::g->maxGlyfRead == 0)) {
    ::g->maxGlyfRead = ::g->attf_numGlyphs;
    };
    tSimpleGlyph_length = 0;
    for (n = 0; (n <= ::g->maxGlyfRead); n++) {
            index_g = 0;
        if ((::g->attf_indexToLocFormat == 0)) {
            index_g = 2;
        } else {
            index_g = 4;
        };
        FSeek((::g->attf_locatell + (index_g * n)));
        if ((::g->attf_indexToLocFormat == 0)) {
            locaoffsets = 0;
            l_offset = (locaoffsets + tSimpleGlyph_length);
            GENERATE(local_offset, ::g->local_offset.generate({ l_offset }));
            if(formatfuzztojc)
            {
                glyf_offset = loca_arrayvalue[n];
            }
            else
            {
                glyf_offset = l_offset;
            }
            
            
        } else {
            locaoffsets = 0;
            l_offset = (locaoffsets + tSimpleGlyph_length);
            GENERATE(local_offset, ::g->local_offset_.generate({ l_offset }));
            glyf_offset = l_offset;
        };
        if ((::g->attf_indexToLocFormat == 0)) {
            glyf_offset *= 2;
        };
        FSeek((glyf_table + glyf_offset));
        start_gly = FTell();
        GENERATE_VAR(SimpleGlyph, ::g->SimpleGlyph.generate());
        tSimpleGlyph_length += (FTell() - start_gly);
    ;
    };

    _sizeof = FTell() - _startof;
    return this;
}


tprep* tprep::generate() {
    if (generated == 1) {
        tprep* new_instance = new tprep(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(bytecode, ::g->bytecode.generate(1000));

    _sizeof = FTell() - _startof;
    return this;
}


tGDEF* tGDEF::generate() {
    if (generated == 1) {
        tGDEF* new_instance = new tGDEF(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(Version, ::g->Version.generate({ 0x00010000 }));
    GENERATE_VAR(GlyphClassDef, ::g->GlyphClassDef.generate());
    GENERATE_VAR(AttachList, ::g->AttachList.generate());
    GENERATE_VAR(LigCaretList, ::g->LigCaretList.generate());
    GENERATE_VAR(MarkAttachClassDef, ::g->MarkAttachClassDef.generate());

    _sizeof = FTell() - _startof;
    return this;
}


tLangSysTable* tLangSysTable::generate() {
    if (generated == 1) {
        tLangSysTable* new_instance = new tLangSysTable(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(LookupOrder, ::g->LookupOrder.generate({ 0 }));
    GENERATE_VAR(ReqFeatureIndex, ::g->ReqFeatureIndex.generate({ 0xFFFF }));
    GENERATE_VAR(FeatureCounth, ::g->FeatureCounth.generate({ 0 }));
    GENERATE_VAR(FeatureCountl, ::g->FeatureCountl.generate({ 5 }));
    GENERATE_VAR(FeatureIndex, ::g->FeatureIndex.generate(FeatureCountl()));
    ::g->tLangSysTablelength = (6 + (2 * FeatureCountl()));

    _sizeof = FTell() - _startof;
    return this;
}


tLangSysRecord* tLangSysRecord::generate(ubyte LangSysCount) {
    if (generated == 1) {
        tLangSysRecord* new_instance = new tLangSysRecord(instances);
        new_instance->generated = 2;
        return new_instance->generate(LangSysCount);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(LangSysTag, ::g->LangSysTag.generate(4));
    tLanglength = ((4 + (LangSysCount * 6)) + ::g->LangSysRecordlength);
    GENERATE_VAR(Offset, ::g->Offset.generate({ tLanglength }));
    next = FTell();
    FSeek((::g->ScriptTable_table + Offset()));
    LangSys = FTell();
    GENERATE_VAR(LangSysTable, ::g->LangSysTable.generate());
    ::g->LangSysRecordlength += (FTell() - LangSys);
    ::g->tLangSysTable_ftell = FTell();
    FSeek(next);

    _sizeof = FTell() - _startof;
    return this;
}


tScriptRecord_ScriptTable_struct* tScriptRecord_ScriptTable_struct::generate(int& l_cont) {
    if (generated == 1) {
        tScriptRecord_ScriptTable_struct* new_instance = new tScriptRecord_ScriptTable_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate(l_cont);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(DefaultLangSys, ::g->DefaultLangSys.generate());
    GENERATE_VAR(LangSysCounth, ::g->LangSysCounth.generate({ 0 }));
    GENERATE_VAR(LangSysCountl, ::g->LangSysCountl.generate({ 3 }));
    ::g->LangSysRecordlength = 0;
    for (l_cont = 0; (l_cont < LangSysCountl()); l_cont++) {
            GENERATE_VAR(LangSysRecord, ::g->LangSysRecord.generate(LangSysCountl()));
    ;
    };

    _sizeof = FTell() - _startof;
    return this;
}


tScriptRecord* tScriptRecord::generate(ubyte ScriptCount, USHORT& ScriptRecordlength) {
    if (generated == 1) {
        tScriptRecord* new_instance = new tScriptRecord(instances);
        new_instance->generated = 2;
        return new_instance->generate(ScriptCount, ScriptRecordlength);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(ScriptTag, ::g->ScriptTag.generate(4));
    soffset_l = ((2 + (ScriptCount * 6)) + ScriptRecordlength);
    GENERATE_VAR(Offset, ::g->Offset.generate({ soffset_l }));
    next = FTell();
    FSeek((::g->ScriptList_seek + Offset()));
    ::g->ScriptTable_table = FTell();
    GENERATE_VAR(ScriptTable, ::g->ScriptTable.generate(l_cont));
    DefaultLangSyslength = (4 + (::g->LangSysCountl() * 6));
    FSeek(::g->ScriptTable_table);
    GENERATE_VAR(DefaultLangSys, ::g->DefaultLangSys.generate({ DefaultLangSyslength }));
    FSeek(((::g->ScriptList_seek + Offset()) + DefaultLangSyslength));
    GENERATE_VAR(DefaultLangSysTable, ::g->DefaultLangSysTable.generate());
    ScriptRecordlength += ::g->LangSysRecordlength;
    ScriptRecordlength += ::g->tLangSysTablelength;
    ScriptRecordlength += DefaultLangSyslength;
    ScriptRecordlength += 6;
    FSeek(next);

    _sizeof = FTell() - _startof;
    return this;
}


tScriptList* tScriptList::generate(quad& GSUBorGPOS_table) {
    if (generated == 1) {
        tScriptList* new_instance = new tScriptList(instances);
        new_instance->generated = 2;
        return new_instance->generate(GSUBorGPOS_table);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(Offset, ::g->Offset.generate({ 10 }));
    next = FTell();
    FSeek((GSUBorGPOS_table + Offset()));
    ::g->ScriptList_seek = FTell();
    GENERATE_VAR(ScriptCountl, ::g->ScriptCountl.generate({ 3 }));
    ScriptRecordlength = 0;
    for (::g->i = 0; (::g->i < ScriptCountl()); ::g->i++) {
            GENERATE_VAR(ScriptRecord, ::g->ScriptRecord.generate(ScriptCountl(), ScriptRecordlength));
    ;
    };
    FSeek(next);

    _sizeof = FTell() - _startof;
    return this;
}


tFeatureRecord_FeatureTable_struct* tFeatureRecord_FeatureTable_struct::generate() {
    if (generated == 1) {
        tFeatureRecord_FeatureTable_struct* new_instance = new tFeatureRecord_FeatureTable_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(FeatureParams, ::g->FeatureParams.generate());
    GENERATE_VAR(LookupListCounth, ::g->LookupListCounth.generate({ 0 }));
    GENERATE_VAR(LookupListCountl, ::g->LookupListCountl.generate({ 10 }));
    GENERATE_VAR(LookupListIndex, ::g->LookupListIndex.generate(LookupListCountl()));

    _sizeof = FTell() - _startof;
    return this;
}


tFeatureRecord* tFeatureRecord::generate(ubyte FeatureCount, USHORT& tFeatureRecordlength) {
    if (generated == 1) {
        tFeatureRecord* new_instance = new tFeatureRecord(instances);
        new_instance->generated = 2;
        return new_instance->generate(FeatureCount, tFeatureRecordlength);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(FeatureTag, ::g->FeatureTag.generate(4));
    tmptFeatureRecord = ((2 + (6 * FeatureCount)) + tFeatureRecordlength);
    GENERATE_VAR(Offset, ::g->Offset.generate({ tmptFeatureRecord }));
    next = FTell();
    FSeek((::g->FeatureList_seek + Offset()));
    FeatureTable_table = FTell();
    GENERATE_VAR(FeatureTable, ::g->FeatureTable.generate());
    tFeatureRecordlength += (FTell() - FeatureTable_table);
    ::g->tFeatureListlengthseek = FTell();
    FSeek(next);

    _sizeof = FTell() - _startof;
    return this;
}


tFeatureList* tFeatureList::generate(USHORT tFeaturelength, quad& GSUBorGPOS_table) {
    if (generated == 1) {
        tFeatureList* new_instance = new tFeatureList(instances);
        new_instance->generated = 2;
        return new_instance->generate(tFeaturelength, GSUBorGPOS_table);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(Offset, ::g->Offset.generate({ tFeaturelength }));
    next = FTell();
    FSeek((GSUBorGPOS_table + Offset()));
    ::g->FeatureList_seek = FTell();
    GENERATE_VAR(FeatureCounth, ::g->FeatureCounth.generate({ 0 }));
    GENERATE_VAR(FeatureCountl, ::g->FeatureCountl.generate({ 5 }));
    tFeatureRecordlength = 0;
    for (::g->i = 0; (::g->i < FeatureCountl()); ::g->i++) {
            GENERATE_VAR(FeatureRecord, ::g->FeatureRecord.generate(FeatureCountl(), tFeatureRecordlength));
    ;
    };
    FSeek(next);

    _sizeof = FTell() - _startof;
    return this;
}


tLookupRecord* tLookupRecord::generate(ubyte LookupCount, USHORT& tLookupRecordlength, quad& tLookupListend) {
    if (generated == 1) {
        tLookupRecord* new_instance = new tLookupRecord(instances);
        new_instance->generated = 2;
        return new_instance->generate(LookupCount, tLookupRecordlength, tLookupListend);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    tmptLookupRecord = (((LookupCount * 2) + 2) + tLookupRecordlength);
    GENERATE_VAR(Offset, ::g->Offset.generate({ tmptLookupRecord }));
    next = FTell();
    FSeek((::g->LookupList_table + Offset()));
    tLookupRecord_table = FTell();
    GENERATE_VAR(LookupType, ::g->LookupType.generate());
    GENERATE_VAR(LookupFlag, ::g->LookupFlag.generate());
    GENERATE_VAR(SubTableCounth, ::g->SubTableCounth.generate({ 0 }));
    GENERATE_VAR(SubTableCountl, ::g->SubTableCountl.generate());
    GENERATE_VAR(SubTable, ::g->SubTable.generate(SubTableCountl()));
    tLookupRecordlength += (FTell() - tLookupRecord_table);
    tLookupListend = FTell();
    FSeek(next);

    _sizeof = FTell() - _startof;
    return this;
}


tLookupList* tLookupList::generate(USHORT tLookupListlength, quad& GSUBorGPOS_table) {
    if (generated == 1) {
        tLookupList* new_instance = new tLookupList(instances);
        new_instance->generated = 2;
        return new_instance->generate(tLookupListlength, GSUBorGPOS_table);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(Offset, ::g->Offset.generate({ tLookupListlength }));
    next = FTell();
    FSeek((GSUBorGPOS_table + Offset()));
    ::g->LookupList_table = FTell();
    GENERATE_VAR(LookupCounth, ::g->LookupCounth.generate({ 0 }));
    GENERATE_VAR(LookupCountl, ::g->LookupCountl.generate());
    tLookupRecordlength = 0;
    tLookupListend = 0;
    for (::g->i = 0; (::g->i < LookupCountl()); ::g->i++) {
            GENERATE_VAR(LookupRecord, ::g->LookupRecord.generate(LookupCountl(), tLookupRecordlength, tLookupListend));
    ;
    };
    FSeek(tLookupListend);

    _sizeof = FTell() - _startof;
    return this;
}


tGSUBorGPOS* tGSUBorGPOS::generate() {
    if (generated == 1) {
        tGSUBorGPOS* new_instance = new tGSUBorGPOS(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GSUBorGPOS_table = FTell();
    GENERATE_VAR(Version, ::g->Version.generate({ 0x00010000 }));
    GENERATE_VAR(ScriptList, ::g->ScriptList.generate(GSUBorGPOS_table));
    Fllength = (::g->tLangSysTable_ftell - GSUBorGPOS_table);
    GENERATE_VAR(FeatureList, ::g->FeatureList.generate(Fllength, GSUBorGPOS_table));
    Lllength = (::g->tFeatureListlengthseek - GSUBorGPOS_table);
    GENERATE_VAR(LookupList, ::g->LookupList.generate(Lllength, GSUBorGPOS_table));

    _sizeof = FTell() - _startof;
    return this;
}


tDSIG* tDSIG::generate() {
    if (generated == 1) {
        tDSIG* new_instance = new tDSIG(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    ::g->DSIG_table = FTell();
    GENERATE_VAR(ulVersion, ::g->ulVersion.generate({ 0x00000001 }));
    GENERATE_VAR(usNumSigsh, ::g->usNumSigsh.generate({ 0 }));
    GENERATE_VAR(usNumSigsl, ::g->usNumSigsl.generate());
    GENERATE_VAR(usFlag, ::g->usFlag.generate({ 1 }));
    SigsulLength = 0;
    for (::g->i = 0; (::g->i < usNumSigsl()); ::g->i++) {
            ::g->nextSig = FTell();
        FSeek(::g->nextSig);
        GENERATE_VAR(ulFormat, ::g->ulFormat.generate());
        GENERATE_VAR(ulLength, ::g->ulLength.generate());
        tmpSigul = ((FTell() - ::g->DSIG_table) + 4);
        GENERATE_VAR(ulOffset, ::g->ulOffset.generate({ tmpSigul }));
        ::g->nextSig = FTell();
        FSeek((::g->DSIG_table + ulOffset()));
        GENERATE_VAR(usReserved1, ::g->usReserved1.generate({ 0 }));
        GENERATE_VAR(usReserved2, ::g->usReserved2.generate({ 0 }));
        GENERATE_VAR(cbSignatureh, ::g->cbSignatureh.generate({ 0 }));
        GENERATE_VAR(cbSignaturel, ::g->cbSignaturel.generate());
        GENERATE_VAR(bSignature, ::g->bSignature.generate(cbSignaturel()));
        SigsulLength = cbSignaturel();
        FSeek((::g->nextSig - 8));
        tmpSigul = (SigsulLength + 8);
        GENERATE_VAR(ulLength, ::g->ulLength.generate({ tmpSigul }));
        FSeek(((::g->nextSig + 8) + cbSignaturel()));
    ;
    };

    _sizeof = FTell() - _startof;
    return this;
}


DeviceRecord_struct* DeviceRecord_struct::generate() {
    if (generated == 1) {
        DeviceRecord_struct* new_instance = new DeviceRecord_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(pixelSize, ::g->pixelSize.generate());
    GENERATE_VAR(maxWidth, ::g->maxWidth.generate());
    numGlyphs = ((::g->sizeDeviceRecord - 2) / 1);
    GENERATE_VAR(widths, ::g->widths.generate(numGlyphs));

    _sizeof = FTell() - _startof;
    return this;
}


thdmx* thdmx::generate() {
    if (generated == 1) {
        thdmx* new_instance = new thdmx(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(version, ::g->version_.generate({ 0 }));
    GENERATE_VAR(numRecordsh, ::g->numRecordsh.generate({ 0 }));
    GENERATE_VAR(numRecordsl, ::g->numRecordsl.generate());
    GENERATE_VAR(sizeDeviceRecordh, ::g->sizeDeviceRecordh.generate({ 0 }));
    hdmx_DeviceRecord = FTell();
    GENERATE_VAR(sizeDeviceRecordl, ::g->sizeDeviceRecordl.generate());
    ::g->sizeDeviceRecord = sizeDeviceRecordl();
    while ((::g->sizeDeviceRecord < 3)) {
        FSeek(hdmx_DeviceRecord);
        GENERATE_VAR(sizeDeviceRecordl, ::g->sizeDeviceRecordl.generate());
        ::g->sizeDeviceRecord = sizeDeviceRecordl();
        if ((::g->sizeDeviceRecord < 3)) {
            ::g->sizeDeviceRecord = 2;
            break;
        };
    };
    GENERATE_VAR(DeviceRecord, ::g->DeviceRecord.generate(numRecordsl()));

    _sizeof = FTell() - _startof;
    return this;
}


tLTSH* tLTSH::generate() {
    if (generated == 1) {
        tLTSH* new_instance = new tLTSH(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(ver, ::g->ver.generate());
    GENERATE_VAR(numGlyphs, ::g->numGlyphs.generate());
    GENERATE_VAR(yPels, ::g->yPels.generate(numGlyphs()));

    _sizeof = FTell() - _startof;
    return this;
}


RatioRange* RatioRange::generate() {
    if (generated == 1) {
        RatioRange* new_instance = new RatioRange(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(bCharSet, ::g->bCharSet.generate());
    GENERATE_VAR(xRatio, ::g->xRatio.generate());
    GENERATE_VAR(yStartRatio, ::g->yStartRatio.generate());
    GENERATE_VAR(yEndRatio, ::g->yEndRatio.generate());

    _sizeof = FTell() - _startof;
    return this;
}


VDMXRecord* VDMXRecord::generate() {
    if (generated == 1) {
        VDMXRecord* new_instance = new VDMXRecord(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(yPelHeight, ::g->yPelHeight.generate());
    GENERATE_VAR(yMax, ::g->yMax.generate());
    GENERATE_VAR(yMin, ::g->yMin.generate());

    _sizeof = FTell() - _startof;
    return this;
}


VDMXGroup* VDMXGroup::generate() {
    if (generated == 1) {
        VDMXGroup* new_instance = new VDMXGroup(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(recsh, ::g->recsh.generate({ 0 }));
    GENERATE_VAR(recsl, ::g->recsl.generate());
    GENERATE_VAR(startsz, ::g->startsz.generate());
    GENERATE_VAR(endsz, ::g->endsz.generate());
    GENERATE_VAR(entry, ::g->entry.generate(recsl()));

    _sizeof = FTell() - _startof;
    return this;
}


tVDMX* tVDMX::generate() {
    if (generated == 1) {
        tVDMX* new_instance = new tVDMX(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(version, ::g->version_.generate());
    GENERATE_VAR(numRecs, ::g->numRecs.generate());
    GENERATE_VAR(numRatiosh, ::g->numRatiosh.generate({ 0 }));
    GENERATE_VAR(numRatiosl, ::g->numRatiosl.generate());
    GENERATE_VAR(ratRange, ::g->ratRange.generate(numRatiosl()));
    tmpVDMXGrouplength = (((numRatiosl() * 2) + 6) + (numRatiosl() * 4));
    tVDMXoffset = FTell();
    GENERATE_VAR(offsetl, ::g->offsetl.generate(numRatiosl()));
    for (::g->i = 0; (::g->i < numRatiosl()); ::g->i++) {
            VDMXGroupstar = FTell();
        FSeek((tVDMXoffset + (::g->i * 2)));
        GENERATE_VAR(offset, ::g->offset_.generate({ tmpVDMXGrouplength }));
        FSeek(VDMXGroupstar);
        GENERATE_VAR(groups, ::g->groups.generate());
        VDMXGroupseek = FTell();
        tmpVDMXGrouplength = (VDMXGroupseek - tVDMXoffset);
    ;
    };

    _sizeof = FTell() - _startof;
    return this;
}


GaspBehavior* GaspBehavior::generate() {
    if (generated == 1) {
        GaspBehavior* new_instance = new GaspBehavior(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(gridfit, ::g->gridfit.generate(1));
    GENERATE_VAR(doGray, ::g->doGray.generate(1));
    GENERATE_VAR(symMetricGridfit, ::g->symMetricGridfit.generate(1));
    GENERATE_VAR(symMetricSmoothing, ::g->symMetricSmoothing.generate(1));
    GENERATE_VAR(Reserved, ::g->Reserved.generate(12));

    _sizeof = FTell() - _startof;
    return this;
}


tgaspRange* tgaspRange::generate() {
    if (generated == 1) {
        tgaspRange* new_instance = new tgaspRange(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(rangeMaxPPEM, ::g->rangeMaxPPEM.generate());
    GENERATE_VAR(rangeGaspBehavior, ::g->rangeGaspBehavior.generate());

    _sizeof = FTell() - _startof;
    return this;
}


tgasp* tgasp::generate() {
    if (generated == 1) {
        tgasp* new_instance = new tgasp(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(version, ::g->version__.generate({ 0 }));
    GENERATE_VAR(numRanges, ::g->numRanges.generate());
    GENERATE_VAR(gaspRanges, ::g->gaspRanges.generate(numRanges()));

    _sizeof = FTell() - _startof;
    return this;
}


tTable* tTable::generate() {
    if (generated == 1) {
        tTable* new_instance = new tTable(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    ReadBytes(asName, FTell(), 4);
    FSeek((FTell() + 4));
    GENERATE_VAR(checkSum, ::g->checkSum.generate());
    GENERATE_VAR(offset, ::g->offset.generate({ ((12 + (::g->numTables_n * 16)) + ::g->offset_tag) }));
    GENERATE_VAR(length, ::g->length.generate());
    pos_start = FTell();
    FSeek(offset());
    pos_start_offset = FTell();
    if ((asName == "head")) {
        GENERATE_VAR(head, ::g->head.generate());
        ::g->attf_indexToLocFormat = head().indexToLocFormat();
    } else {
    if ((asName == "cmap")) {
        GENERATE_VAR(cmap, ::g->cmap.generate());
        cmap_length = 4;
        possible_cmap = { 0, 2, 4, 6, 8, 12 };
        for (c = 0; (c < cmap().numTables()); c++) {
                cmap_record = FTell();
            GENERATE_VAR(platformID, ::g->platformID.generate());
            GENERATE_VAR(encodingID, ::g->encodingID.generate());
            GENERATE_VAR(offset, ::g->offset.generate({ (cmap_length + (8 * cmap().numTables())) }));
            cmap().next_cmap_record = FTell();
            format_seek = (cmap().cmap_table + offset());
            FSeek(format_seek);
            GENERATE_VAR(format, ::g->format.generate());
            switch (format()) {
            case 0:
                GENERATE_VAR(format0, ::g->format0.generate(cmap_subtable));
                break;
            case 2:
                GENERATE_VAR(format2, ::g->format2.generate(cmap_subtable));
                break;
            case 4:
                GENERATE_VAR(format4, ::g->format4.generate(cmap_subtable));
                break;
            case 6:
                GENERATE_VAR(format6, ::g->format6.generate(cmap_subtable));
                break;
            case 8:
                GENERATE_VAR(format8, ::g->format8.generate(cmap_subtable));
                break;
            case 12:
                GENERATE_VAR(format12, ::g->format12.generate());
                break;
            };
            cmap_l = (FTell() - format_seek);
            cmap_length += cmap_l;
            FSeek(cmap().next_cmap_record);
        ;
        };
        format_seek = ((cmap().cmap_table + cmap_length) + (8 * cmap().numTables()));
        FSeek(format_seek);
    } else {
    if ((asName == "hhea")) {
        GENERATE_VAR(hhea, ::g->hhea.generate());
        ::g->attf_numberOfHMetrics = hhea().numberOfHMetrics();
    } else {
    if ((asName == "OS/2")) {
        GENERATE_VAR(OS_2, ::g->OS_2.generate());
    } else {
    if ((asName == "maxp")) {
        GENERATE_VAR(maxp, ::g->maxp.generate());
        ::g->attf_numGlyphs = maxp().numGlyphs();
    } else {
    if ((asName == "hmtx")) {
        ::g->hmtx_length = length();
        GENERATE_VAR(hmtx, ::g->hmtx.generate());
    } else {
    if ((asName == "name")) {
        GENERATE_VAR(name, ::g->name_.generate());
    } else {
    if ((asName == "post")) {
        GENERATE_VAR(post, ::g->post.generate());
    } else {
    if ((asName == "cvt ")) {
        GENERATE_VAR(cvt, ::g->cvt.generate());
    } else {
    if ((asName == "fpgm")) {
        GENERATE_VAR(fpgm, ::g->fpgm.generate());
    } else {
    if ((asName == "loca")) {
        ::g->attf_locatell = FTell();
        GENERATE_VAR(loca, ::g->loca.generate());
    } else {
    if ((asName == "glyf")) {
        GENERATE_VAR(glyf, ::g->glyf.generate());
    } else {
    if ((asName == "prep")) {
        GENERATE_VAR(prep, ::g->prep.generate());
    } else {
    if ((asName == "GDEF")) {
        GENERATE_VAR(GDEF, ::g->GDEF.generate());
    } else {
    if ((asName == "GSUB")) {
        GENERATE_VAR(GSUB, ::g->GSUB.generate());
    } else {
    if ((asName == "DSIG")) {
        GENERATE_VAR(DSIG, ::g->DSIG.generate());
    } else {
    if ((asName == "hdmx")) {
        GENERATE_VAR(hdmx, ::g->hdmx.generate());
    } else {
    if ((asName == "LTSH")) {
        GENERATE_VAR(LTSH, ::g->LTSH.generate());
    } else {
    if ((asName == "VDMX")) {
        GENERATE_VAR(VDMX, ::g->VDMX.generate());
    } else {
    if ((asName == "gasp")) {
        GENERATE_VAR(gasp, ::g->gasp.generate());
    };
    };
    };
    };
    };
    };
    };
    };
    };
    };
    };
    };
    };
    };
    };
    };
    };
    };
    };
    };
    pos_end = FTell();
    correct_length = (pos_end - pos_start_offset);
    ::g->offset_tag += correct_length;
    FSeek((pos_start - 4));
    GENERATE_VAR(length2, ::g->length2.generate({ correct_length }));

    _sizeof = FTell() - _startof;
    return this;
}



void ttf_generate_file() {
    ::g = new globals_class();

    BigEndian();
    ::g->maxGlyfRead = 0;
    ::g->ARG_1_AND_2_ARE_WORDS = (1 << 0);
    ::g->ARGS_ARE_XY_VALUES = (1 << 1);
    ::g->ROUND_XY_TO_GRID = (1 << 2);
    ::g->WE_HAVE_A_SCALE = (1 << 3);
    ::g->RESERVED = (1 << 4);
    ::g->MORE_COMPONENTS = (1 << 5);
    ::g->WE_HAVE_AN_X_AND_Y_SCALE = (1 << 6);
    ::g->WE_HAVE_A_TWO_BY_TWO = (1 << 7);
    ::g->WE_HAVE_INSTRUCTIONS = (1 << 8);
    ::g->USE_MY_METRICS = (1 << 9);
    ::g->OVERLAP_COMPOUND = (1 << 10);
    ::g->SCALED_COMPONENT_OFFSET = (1 << 11);
    ::g->UNSCALED_COMPONENT_OFFSET = (1 << 12);
    ::g->ON_CURVE = (1 << 0);
    ::g->X_BYTE = (1 << 1);
    ::g->Y_BYTE = (1 << 2);
    ::g->REPEAT = (1 << 3);
    ::g->X_TYPE = (1 << 4);
    ::g->Y_TYPE = (1 << 5);
    ::g->RES_1 = (1 << 6);
    ::g->RES_2 = (1 << 7);
    ::g->hmtx_length = 0;
    ::g->tLangSysTablelength = 0;
    ::g->i = 0;
    ::g->offset_tag = 0;
    ::g->ttfId = 0;
    ::g->t_numFonts = 1;
    GENERATE(OffsetTable, ::g->OffsetTable.generate());
    ::g->tablecount = 0;
    ::g->table_start_pos = FTell();
    ::g->preferred_tables = { "head" };
    while (ReadBytes(::g->tag_type, FTell(), 4, ::g->preferred_tables, ::g->possible_tables)) {
        GENERATE(stable, ::g->stable.generate());
        ::g->tablecount++;
        switch (STR2INT(::g->tag_type)) {
        case STR2INT("head"):
            ::g->preferred_tables = { "maxp" };
            ::g->possible_tables = { "maxp" };
            break;
        case STR2INT("hhea"):
            VectorRemove(::g->possible_tables, { "hhea" });
            ::g->possible_tables.insert(::g->possible_tables.end(), { "hmtx" });
            ::g->preferred_tables = { "hmtx" };
            break;
        case STR2INT("OS/2"):
            VectorRemove(::g->possible_tables, { "OS/2" });
            break;
        case STR2INT("maxp"):
            ::g->preferred_tables = { "loca" };
            VectorRemove(::g->possible_tables, { "maxp" });
            ::g->possible_tables.insert(::g->possible_tables.end(), { "loca" });
            break;
        case STR2INT("name"):
            VectorRemove(::g->possible_tables, { "name" });
            ::g->possible_tables.insert(::g->possible_tables.end(), { "post" });
            ::g->preferred_tables = { "post" };
            break;
        case STR2INT("hmtx"):
            VectorRemove(::g->possible_tables, { "hmtx" });
            ::g->possible_tables.insert(::g->possible_tables.end(), { "name" });
            ::g->preferred_tables = { "name" };
            break;
        case STR2INT("post"):
            VectorRemove(::g->possible_tables, { "post" });
            ::g->possible_tables.insert(::g->possible_tables.end(), { "prep" });
            ::g->preferred_tables = { "prep" };
            break;
        case STR2INT("cvt "):
            VectorRemove(::g->possible_tables, { "cvt " });
            ::g->possible_tables.insert(::g->possible_tables.end(), { "fpgm" });
            ::g->preferred_tables = { "fpgm" };
            break;
        case STR2INT("fpgm"):
            VectorRemove(::g->possible_tables, { "fpgm" });
            ::g->possible_tables.insert(::g->possible_tables.end(), { "hdmx" });
            ::g->preferred_tables = { "hdmx" };
            break;
        case STR2INT("loca"):
            ::g->preferred_tables = { "glyf" };
            VectorRemove(::g->possible_tables, { "loca" });
            ::g->possible_tables.insert(::g->possible_tables.end(), { "glyf" });
            break;
        case STR2INT("glyf"):
            VectorRemove(::g->possible_tables, { "glyf" });
            ::g->possible_tables.insert(::g->possible_tables.end(), { "cmap" });
            ::g->preferred_tables = { "cmap" };
            break;
        case STR2INT("prep"):
            VectorRemove(::g->possible_tables, { "prep" });
            ::g->possible_tables.insert(::g->possible_tables.end(), { "cvt " });
            ::g->preferred_tables = { "cvt " };
            break;
        case STR2INT("GDEF"):
            VectorRemove(::g->possible_tables, { "GDEF" });
            break;
        case STR2INT("GSUB"):
            VectorRemove(::g->possible_tables, { "GSUB" });
            break;
        case STR2INT("GPOS"):
            VectorRemove(::g->possible_tables, { "GPOS" });
            break;
        case STR2INT("DSIG"):
            VectorRemove(::g->possible_tables, { "DSIG" });
            break;
        case STR2INT("hdmx"):
            VectorRemove(::g->possible_tables, { "hdmx" });
            ::g->preferred_tables = {  };
            ::g->possible_tables = { "OS/2", "GDEF", "GSUB", "DSIG", "LTSH", "VDMX", "gasp" };
            break;
        case STR2INT("LTSH"):
            VectorRemove(::g->possible_tables, { "LTSH" });
            break;
        case STR2INT("VDMX"):
            VectorRemove(::g->possible_tables, { "VDMX" });
            break;
        case STR2INT("gasp"):
            VectorRemove(::g->possible_tables, { "gasp" });
            break;
        case STR2INT("cmap"):
            VectorRemove(::g->possible_tables, { "cmap" });
            ::g->possible_tables.insert(::g->possible_tables.end(), { "hhea" });
            ::g->preferred_tables = { "hhea" };
            break;
        };
    };
    FSeek(::g->numTables_offset);
    GENERATE(numTables, ::g->numTables.generate({ ::g->tablecount }));
    ::g->numTables_n = ::g->tablecount;
    FSeek(::g->table_start_pos);
    for (::g->t = 0; (::g->t < ::g->numTables_n); ::g->t++) {
            GENERATE(Table, ::g->Table.generate());
    ;
    };
    Printf("numTables_n is %d\n", ::g->numTables_n);

    file_acc.finish();
    ttf_delete_globals();
}

void ttf_delete_globals() { delete ::g; }

