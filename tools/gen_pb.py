import os
import argparse

if __name__ == '__main__':
    cppOut = "./src/FkImage/pb"
    javaOut = "./proj/FkAndroid/fkandroid/src/main/java"
    dartOut = "./proj/fk_flutter/lib/fk/entity"
    srcDir = "./src/FkImage/pb/proto"
    srcStr = ''
    for name in sorted(os.listdir(srcDir)):
        srcStr += srcDir + "/" + name + " "
    os.system("protoc --plugin ~/AppData/Local/Pub/Cache/bin --proto_path=./src/FkImage/pb/proto --cpp_out=%s --java_out=%s --dart_out=%s %s" % (cppOut, javaOut, dartOut, srcStr))