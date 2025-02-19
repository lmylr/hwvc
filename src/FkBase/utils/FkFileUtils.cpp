/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*
* AUTHOR: filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
* CREATE TIME: 2022-3-11 20:26:34
*/

#include "FkFileUtils.h"
#include <cerrno>
#include <sys/stat.h>
#include <zconf.h>

#define FK_FILE_READ_BUF_SIZE 1024 * 8

FkResult FkFileUtils::copy(std::string src, std::string &dst) {
    FILE *srcFile = fopen(src.c_str(), "rb");
    if (srcFile == nullptr) {
        FkLogE(FK_DEF_TAG, "Open file failed: %s ", strerror(errno));
        return FK_FILE_NOT_FOUND;
    }
    FILE *dstFile = fopen(dst.c_str(), "wb");
    if (dstFile == nullptr) {
        fclose(srcFile);
        return FK_FILE_OPEN_FAIL;
    }
    int len = 0;
    int64_t byteCountOfRead = 0;
    int64_t byteCountOfWrite = 0;
    uint8_t buf[FK_FILE_READ_BUF_SIZE];
    while ((len = fread(buf, 1, FK_FILE_READ_BUF_SIZE, srcFile)) > 0) {
        byteCountOfRead += len;
        byteCountOfWrite += fwrite(buf, 1, len, dstFile);
    }
    fclose(dstFile);
    fclose(srcFile);
    return byteCountOfRead == byteCountOfWrite ? FK_OK : FK_FAIL;
}

FkResult FkFileUtils::mkdirs(std::string dir) {
    if (exist(dir)) {
        return FK_OK;
    }
    std::string::size_type pos = dir.find_last_of('/');
    if (pos != std::string::npos) {
        auto ret = mkdirs(dir.substr(0, pos));
        if (ret == FK_OK) {
            ret = mkdir(dir.c_str(), 0777) == 0 ? FK_OK : FK_FAIL;
        }
        return ret;
    }
    return FK_FAIL;
}

bool FkFileUtils::exist(std::string &file) {
    return access(file.c_str(), F_OK) == 0;
}

std::string FkFileUtils::name(std::string &file) {
    std::string::size_type pos = file.find_last_of('/');
    if (pos == std::string::npos) {
        return file;
    }
    return file.substr(pos, file.length());
}

std::string FkFileUtils::suffix(std::string &file) {
    std::string::size_type pos = file.find_last_of('.');
    if (pos == std::string::npos) {
        return file;
    }
    return file.substr(pos, file.length());
}

std::string FkFileUtils::parent(std::string &file) {
    std::string::size_type pos = file.find_last_of('/');
    if (pos == std::string::npos) {
        return file;
    }
    return file.substr(0, pos);
}

bool FkFileUtils::remove(std::string &file) {
    return std::remove(file.c_str()) == 0;
}

long FkFileUtils::size(std::string &file) {
    struct stat info{};
    auto ret = stat(file.c_str(), &info);
    return info.st_size;
}

void FkFileUtils::trim(std::string &path) {
    std::string::size_type pos = path.find_last_of('/');
    if (pos != std::string::npos && pos == (path.size() - 1)) {
        path.replace(pos, 1, "");
    }
}
