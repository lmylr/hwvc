//
// Created by Alimin on 2025/2/19.
//

#include "FkJavaRegister.h"
#include "FkJniDefinition.h"
#include "../source/Java_FkNativeTestObject.h"

namespace f_kilns {
    const char *TAG = "FkJavaRegister";

    void jni_register_all(JNIEnv *env) {
        Java_FkNativeTestObject::reg(env);
    }
}
