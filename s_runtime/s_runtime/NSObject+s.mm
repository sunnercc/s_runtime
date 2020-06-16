//
//  NSObject+s.m
//  s_runtime
//
//  Created by sunner.
//
//

#import "NSObject+s.h"
#import "s_runtime.h"

@implementation NSObject (s)

- (void)printStruct {
    [[self class] printStruct];
}

+ (void)printStruct {
    
    sClass cls = (__bridge sClass)self;
    
    class_rw_ext_t ext = cls->bits.data()->ro_or_rw_ext;
    printf("\n********* class_rw_ext_t methods *********\n");
    method_list_t *methods = ext.methods;
    if (methods != NULL) {
        for (int i= 0; i < methods->count; i++) {
            method_t method = methods->get(i);
            printf("%d\n", i);
            printf("name: %s\n", method.name);
            printf("types: %s\n", method.types);
            printf("imp: %p\n", method.imp);
        }
    } else {
        printf("class_rw_ext_t methods = null\n");
    }
    
    
    class_ro_t *ro = ext.ro;
    printf("\n********* class_ro_t baseMethodList *********\n");
    method_list_t *baseMethodList = ro->baseMethodList;
    if (baseMethodList !=  NULL) {
        for (int i= 0; i < baseMethodList->count; i++) {
            method_t method = baseMethodList->get(i);
            printf("%d\n", i);
            printf("name: %s\n", method.name);
            printf("types: %s\n", method.types);
            printf("imp: %p\n", method.imp);
        }
    } else {
        printf("class_ro_t baseMethodList = null\n");
    }
    
    
    printf("\n********* class_ro_t ivars *********\n");
    ivar_list_t *ivars = ro->ivars;
    if (ivars != NULL) {
        for (int i= 0; i < ivars->count; i++) {
            ivar_t ivar = ivars->get(i);
            printf("%d\n", i);
            printf("name: %s\n", ivar.name);
            printf("types: %s\n", ivar.type);
        }
    } else {
        printf("class_ro_t ivars == null\n");
    }
    
    printf("\n********* class_ro_t baseProperties *********\n");
    property_list_t *baseProperties = ro->baseProperties;
    if (baseProperties != NULL) {
        for (int i= 0; i < baseProperties->count; i++) {
            property_t property = baseProperties->get(i);
            printf("%d\n", i);
            printf("name: %s\n", property.name);
            printf("attributes: %s\n", property.attributes);
        }
    } else {
        printf("class_ro_t baseProperties == null\n");
    }
}

@end
