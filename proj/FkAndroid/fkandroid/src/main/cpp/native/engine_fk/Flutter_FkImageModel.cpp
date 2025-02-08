#include <stdint.h>
#include "FkEngine.h"
#include "FkImageEngine.h"
#include "FkImageModelEngine.h"
#include "FkPicModelBuilder.h"
#include "FkJniDefinition.h"
#include "FkInstanceHolder.h"

#define RENDER_ALIAS "RenderEngine"
#define IMAGE_MODEL_ENGINE_ALIAS "ImageModelEngine"

#ifdef __cplusplus
extern "C" {
#endif

static std::shared_ptr<FkImageModelEngine> findImageModelEngine(void *handle) {
    if (!FkInstanceHolder::getInstance().contains((long) handle)) {
        return nullptr;
    }
    return FkInstanceHolder::getInstance().find<std::shared_ptr<FkImageModelEngine>>((long) handle);
}

void *createImageModelEngine(void *imageEngineHandle) {
    if (!FkInstanceHolder::getInstance().contains((long) imageEngineHandle)) {
        return nullptr;
    }
    auto imageEngine =  FkInstanceHolder::getInstance().find<std::shared_ptr<FkImageEngine>>((long) imageEngineHandle);
    auto engine = std::make_shared<FkImageModelEngine>(imageEngine, IMAGE_MODEL_ENGINE_ALIAS);
    return (void *) FkInstanceHolder::getInstance().put(engine);
}

int FkImageModel_engineCreate(void *engine) {
    auto ptr = findImageModelEngine(engine);
    if (ptr) {
        return ptr->create();
    }
    return FK_INVALID_STATE;
}

int FkImageModel_engineDestroy(void *engine) {
    auto ret = FK_INVALID_STATE;
    auto ptr = findImageModelEngine(engine);
    if (ptr) {
        ret = ptr->destroy();
    }
    FkInstanceHolder::getInstance().release((long) engine);
    return ret;
}

int FkImageModel_engineStart(void *engine) {
    auto ptr = findImageModelEngine(engine);
    if (ptr) {
        return ptr->start();
    }
    return FK_INVALID_STATE;
}

int FkImageModel_engineStop(void *engine) {
    auto ptr = findImageModelEngine(engine);
    if (ptr) {
        return ptr->stop();
    }
    return FK_INVALID_STATE;
}

int FkImageModel_save(void *engine, const char *outputPath) {
    auto ptr = findImageModelEngine(engine);
    if (ptr) {
        std::string outputPathStr(outputPath);
        return ptr->save(outputPathStr);
    }
    return FK_INVALID_STATE;
}

int FkImageModel_load(void *engine, const char *inputPath) {
    auto ptr = findImageModelEngine(engine);
    if (ptr) {
        std::string inputPathStr(inputPath);
        return ptr->load(inputPathStr, []() {

        });
    }
    return FK_INVALID_STATE;
}

Array FkImageModel_getPictureModelBuffer(void *engine) {
    auto ptr = findImageModelEngine(engine);
    if (ptr) {
        std::promise<Array> promise;
        ptr->getLayers([&promise](std::shared_ptr<pb::FkPictureModel> &model){
            Array array;
            array.len = model->ByteSizeLong();
            array.data = new uint8_t[array.len];
            if (!model->SerializeToArray(array.data, array.len)) {
                array.len = 0;
                delete[] array.data;
            }
            promise.set_value(array);
        });
        return promise.get_future().get();
    }
    return {};
}

#ifdef __cplusplus
}
#endif