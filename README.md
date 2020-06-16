# s_runtime

print class struct

```
@interface Person : NSObject
{
    int _a;
}

@property (nonatomic, copy) NSString *b;
@end
```

exec `[[[Person alloc] init] printStruct];`

```
********* class_rw_ext_t methods *********
class_rw_ext_t methods = null

********* class_ro_t baseMethodList *********
0
name: c
types: v16@0:8
imp: 0x100001570
1
name: .cxx_destruct
types: v16@0:8
imp: 0x100001610
2
name: b
types: @16@0:8
imp: 0x1000015a0
3
name: setB:
types: v24@0:8@16
imp: 0x1000015d0

********* class_ro_t ivars *********
0
name: _a
types: i
1
name: _b
types: @"NSString"

********* class_ro_t baseProperties *********
0
name: b
attributes: T@"NSString",C,N,V_b
```
