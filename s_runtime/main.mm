//
//  main.m
//  s_runtime
//
//  Created by sunner.
//
//

#import <Foundation/Foundation.h>
#import "Person.h"
#import "NSObject+s.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        [[[Person alloc] init] printStruct];
    }
    return 0;
}
