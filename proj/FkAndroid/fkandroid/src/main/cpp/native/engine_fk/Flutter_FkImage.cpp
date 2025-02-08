#include <stdint.h>
#include "FkEngine.h"
#include "FkImageEngine.h"
#include "FkRenderEngine.h"
#include "FkPicModelBuilder.h"
#include "FkJniDefinition.h"
#include "FkInstanceHolder.h"
#include "FkColorAdjustPlugin.h"

#define RENDER_ALIAS "RenderEngine"
#define IMAGE_ENGINE_ALIAS "ImageEngine"

#ifdef __cplusplus
extern "C" {
#endif

static std::shared_ptr<FkImageEngine> findImageEngine(void *handle) {
    if (!FkInstanceHolder::getInstance().contains((long) handle)) {
        return nullptr;
    }
    return FkInstanceHolder::getInstance().find<std::shared_ptr<FkImageEngine>>((long) handle);
}

void *createImageEngine(const char *workspace) {
    std::string workspaceStr(workspace);
    std::shared_ptr<FkEngine> renderEngine = std::make_shared<FkRenderEngine>(RENDER_ALIAS);
    auto engine = std::make_shared<FkImageEngine>(renderEngine, workspaceStr, IMAGE_ENGINE_ALIAS);
    return (void *) FkInstanceHolder::getInstance().put(engine);
}

int engineCreate(void *engine) {
    auto ptr = findImageEngine(engine);
    if (ptr) {
        return ptr->create();
    }
    return FK_INVALID_STATE;
}

int engineDestroy(void *engine) {
    auto ret = FK_INVALID_STATE;
    auto ptr = findImageEngine(engine);
    if (ptr) {
        ret = ptr->destroy();
    }
    FkInstanceHolder::getInstance().release((long) engine);
    return ret;
}

int engineStart(void *engine) {
    auto ptr = findImageEngine(engine);
    if (ptr) {
        return ptr->start();
    }
    return FK_INVALID_STATE;
}

int engineStop(void *engine) {
    auto ptr = findImageEngine(engine);
    if (ptr) {
        return ptr->stop();
    }
    return FK_INVALID_STATE;
}

int newLayerWithColor(void *engine, int width, int height) {
    auto ptr = findImageEngine(engine);
    if (ptr) {
        FkSize size(width, height);
        return ptr->newLayerWithColor(size, FkColor::red());
    }
    return FK_INVALID_STATE;
}

int newLayerWithFile(void *engine, const char *path) {
    auto ptr = findImageEngine(engine);
    if (ptr) {
        std::string pathStr(path);
        return ptr->newLayerWithFile(pathStr);
    }
    return FK_INVALID_STATE;
}

int notifyRender(void *engine) {
    auto ptr = findImageEngine(engine);
    if (ptr) {
        return ptr->notifyRender();
    }
    return FK_INVALID_STATE;
}

int setBackgroundColor(void *engine, int layerId, int color) {
    auto ptr = findImageEngine(engine);
    if (ptr) {
        return ptr->setBackgroundColor(layerId, FkColor::makeFrom(color));
    }
    return FK_INVALID_STATE;
}

int newLayerWithPlugin(void *engine, void *pluginHandle) {
    auto ptr = findImageEngine(engine);
    auto plugin = FkInstanceHolder::getInstance().find<std::shared_ptr<FkAbsPlugin>>((long) pluginHandle);
    if (ptr && plugin) {
        return ptr->newLayerWithPlugin(plugin);
    }
    return FK_INVALID_STATE;
}

int FkImage_removeLayer(void *engine, int layerId) {
    auto ptr = findImageEngine(engine);
    if (ptr) {
        return ptr->removeLayer(layerId);
    }
    return FK_INVALID_STATE;
}

int setProjectionLayer(void *engine, int layerId, int srcLayerId) {
    auto ptr = findImageEngine(engine);
    if (ptr) {
        return ptr->setProjectionLayer(layerId, srcLayerId);
    }
    return FK_INVALID_STATE;
}

int FkImage_setTranslate(void *engine, int layerId, int x, int y) {
    auto ptr = findImageEngine(engine);
    if (ptr) {
        return ptr->setTranslate(layerId, x, y);
    }
    return FK_INVALID_STATE;
}

int FkImage_setVisibility(void *engine, int layerId, int visibility) {
    auto ptr = findImageEngine(engine);
    if (ptr) {
        return ptr->setVisibility(layerId, static_cast<kVisibility>(visibility));
    }
    return FK_INVALID_STATE;
}

int FkImage_exportFile(void *engine, const char *path, int w, int h) {
    auto ptr = findImageEngine(engine);
    if (ptr) {
        FkIntVec2 pos(0, 0);
        FkSize size(w, h);
        return ptr->exportImage(Fk_CANVAS_ID, pos, size, std::string(path), [](int ret) {

        });
    }
    return FK_INVALID_STATE;
}

#ifdef __cplusplus
}
#endif