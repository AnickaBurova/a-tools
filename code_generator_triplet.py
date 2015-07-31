
import sys
import ntpath

me = sys.argv[0]
upto = 100 if len(sys.argv) == 1 else int(sys.argv[1])
mydir = ntpath.dirname(me)

with open(mydir+"/long_macro_expansion_triplet.h",'w') as file:

    file.write("#pragma once\n")
    file.write('#define ___ERROR_3 static_assert(false, "Number of values must be 3x")\n')

    for index in xrange(1,upto+1):
        if index == 1:
            file.write("#define ___EV_3_{0}(e,a,b,c,...) e(a,b,c)\n".format(index))
        else:
            file.write("#define ___EV_3_{0}(e,a,b,c,...) e(a,b,c) ___EV_3_{1}(e,__VA_ARGS__)\n".format(index,index-1))

    args1 = ""
    args2 = ""
    for index in xrange(1,upto+1):
        args1 = "{0}_{1},__{1},___{1},".format(args1,index)
        args2 = ",___EV_3_{0},___ERROR_3,___ERROR_3{1}".format(index,args2)
    file.write("#define ___GET_MACRO_3_{0}({1}NAME,...) NAME\n".format(upto,args1))
    file.write("#define ___EXECUTE_3(e,...) ___GET_MACRO_3_{}(__VA_ARGS__{})(e,__VA_ARGS__)\n".format(upto,args2))
