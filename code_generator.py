
import sys
import ntpath

me = sys.argv[0]
upto = 100 if len(sys.argv) == 1 else int(sys.argv[1])
mydir = ntpath.dirname(me)

with open(mydir+"/long_macro_expansion.h",'w') as file:

    file.write("#pragma once\n")

    for index in xrange(1,upto+1):
        if index == 1:
            file.write("#define ___EV{0}(e,f,...) e(f)\n".format(index))
        else:
            file.write("#define ___EV{0}(e,f,...) e(f) ___EV{1}(e,__VA_ARGS__)\n".format(index,index-1))

    args1 = ""
    args2 = ""
    for index in xrange(1,upto+1):
        args1 = "{0}_{1},".format(args1,index)
        args2 = ",___EV{0}{1}".format(index,args2)
    file.write("#define ___GET_MACRO{0}({1}NAME,...) NAME\n".format(upto,args1))
    file.write("#define ___EXECUTE(e,...) ___GET_MACRO{}(__VA_ARGS__{})(e,__VA_ARGS__)\n".format(upto,args2))
