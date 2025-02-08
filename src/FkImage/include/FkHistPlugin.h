/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns)

* CREATE TIME: 2024-07-15 23:18:37
*/

#ifndef FK_GRAPHIC_FKHISTPLUGIN_H
#define FK_GRAPHIC_FKHISTPLUGIN_H

#include "FkAbsPlugin.h"
#include "FkGraphicTexture.h"
#include "FkGraphicProgram.h"
#include "FkBitmap.h"
#include "FkTexArrayCompo.h"
#include "FkFboCompo.h"
#include "FkVboCompo.h"
#include "FkVertexObject.h"
#include "FkMVPMatrix.h"
#include "FkMatCompo.h"
#include <vector>

FK_SUPER_CLASS(FkHistPlugin, FkAbsPlugin) {
FK_DEF_CLASS_TYPE_FUNC(FkHistPlugin)

public:
    FkHistPlugin();

    FkHistPlugin(const FkHistPlugin &o) = delete;

    virtual ~FkHistPlugin();

    virtual FkResult onCreate() override;

    virtual FkResult onDestroy() override;

    virtual FkPluginRequirements describeRequirements() override;

    virtual FkResult onPreProcess() override;

    virtual FkResult onProcess(const std::shared_ptr<FkPluginBundle> &bundle) override;

    virtual FkResult onPostProcess() override;

private:
    std::shared_ptr<FkVboCompo> _createVBO(const FkSize &size);

    FkResult _calcHistogramV2(const std::shared_ptr<FkTexArrayCompo> &texArray, const std::shared_ptr<FkFboCompo> &fboCompo);

    std::shared_ptr<FkGraphicTexture> _createTex(FkSize size, uint64_t flags, FkColor::kFormat fmt = FkColor::kFormat::RGBA);

    FkResult _createCalcProgram(uint32_t target);

    FkResult _copyHistBuf2Tex();

    FkResult _drawHist2Dst(const std::shared_ptr<FkPluginBundle> &bundle);

    FkResult _createHistBuffer();

    FkResult _resetHistBuffer();

    void _resetMVP(FkSize targetSize, float scale, float ratio);

    void _updateResult(int max);
;
private:
    std::shared_ptr<FkBitmap> bmp = nullptr;
    std::vector<uint8_t> histData;
    uint32_t histBuf = GL_NONE;
    uint32_t histInfoBuf = GL_NONE;
    int pixelCnt[3]{0};
    std::shared_ptr<FkGraphicTexture> histTex = nullptr;
    std::shared_ptr<FkGraphicProgram> viewProgram = nullptr;
    std::shared_ptr<FkGraphicProgram> calcProgram = nullptr;
    std::shared_ptr<FkVertexObjectAllocator> allocator = nullptr;
    std::shared_ptr<FkVboCompo> histVBOCompo = nullptr;
    std::shared_ptr<FkMatCompo> histMVPCompo = nullptr;
};

#endif //FK_GRAPHIC_FKHISTPLUGIN_H