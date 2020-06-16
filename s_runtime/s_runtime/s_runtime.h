
/**
 * reference objc4-781
 */

#import <objc/runtime.h>
#import <Foundation/Foundation.h>

#if !__LP64__
#define S_FAST_DATA_MASK 0xfffffffcUL
#else
#define S_FAST_DATA_MASK 0x00007ffffffffff8UL
#endif

#if __arm64__
#define ISA_MASK        0x0000000ffffffff8ULL
#elif __x86_64__
#define ISA_MASK        0x00007ffffffffff8ULL
#endif

NS_ASSUME_NONNULL_BEGIN

typedef struct s_objc_class *sClass;

struct method_t {
    SEL name;
    const char *types;
    IMP imp;
};

struct ivar_t {
    int32_t *offset;
    const char *name;
    const char *type;
    uint32_t alignment_raw;
    uint32_t size;
};

struct property_t {
    const char *name;
    const char *attributes;
};

template <typename Element, typename List, uint32_t FlagMask>
struct entsize_list_tt {
    uint32_t entsizeAndFlags;
    uint32_t count;
    Element first;

    uint32_t entsize() const {
        return entsizeAndFlags & ~FlagMask;
    }
    uint32_t flags() const {
        return entsizeAndFlags & FlagMask;
    }

    Element& getOrEnd(uint32_t i) const {
        return *(Element *)((uint8_t *)&first + i*entsize());
    }
    Element& get(uint32_t i) const {
        return getOrEnd(i);
    }
};

struct method_list_t : entsize_list_tt<method_t, method_list_t, 0x3> {
    
};

struct protocol_list_t {
    uintptr_t first;
};

struct ivar_list_t : entsize_list_tt<ivar_t, ivar_list_t, 0> {

};

struct property_list_t : entsize_list_tt<property_t, property_list_t, 0> {

};

struct class_ro_t {
    uint32_t flags;
    uint32_t instanceStart;
    uint32_t instanceSize;
    const uint8_t * ivarLayout;
    const char * name;
    method_list_t * baseMethodList;
    protocol_list_t * baseProtocols;
    ivar_list_t * ivars;
    uint8_t * weakIvarLayout;
    property_list_t *baseProperties;
};

struct class_rw_ext_t {
    class_ro_t *ro;
    method_list_t *methods;
    property_list_t *properties;
    protocol_list_t * protocols;
    char *demangledName;
    uint32_t version;
};

struct class_rw_t {
    uint32_t flags;
    uint16_t witness;
    uint16_t index;
    class_rw_ext_t ro_or_rw_ext;
    sClass firstSubclass;
    sClass nextSiblingClass;
};


struct class_data_bits_t {
    uintptr_t bits;
    
    class_rw_t *data() {
        return (class_rw_t *)(bits & S_FAST_DATA_MASK);
    }
};

struct cache_t {
    struct bucket_t *_buckets;
    uint32_t _mask;
    uint32_t _occupied;
};

struct bucket_t {
    uintptr_t _key;
    IMP _imp;
};

union isa_t {
private:
    sClass cls;
public:
    uintptr_t bits;
    #if defined(ISA_BITFIELD)
        struct {
            ISA_BITFIELD;  // defined in isa.h
        };
    #endif
};

struct s_objc_object {
private:
    isa_t _isa;
public:
     sClass ISA() {
        return (sClass)(_isa.bits & ISA_MASK);
    }
};

struct s_objc_class : s_objc_object {
    sClass superclass;
    cache_t cache;
    class_data_bits_t bits;
    
    class_rw_t *data() {
        return bits.data();
    }
};

NS_ASSUME_NONNULL_END



