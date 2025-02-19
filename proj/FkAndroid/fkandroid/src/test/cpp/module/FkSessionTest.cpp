/*
* Copyright (c) 2018-present, filmkilns(email: filmkilns@outlook.com, github: https://github.com/filmkilns).
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "gtest/gtest.h"
#include "FkSession.h"
#include "FkIncreaseQuark.h"
#include "FkOnCreatePrt.h"

TEST(FkSessionTest, Connect) {
    auto quark = std::make_shared<FkIncreaseQuark>();
    auto session = FkSession::with({FkOnCreatePrt_Class::type.getId(), FkOnCreatePrt_Class::type.getName()});
    EXPECT_EQ(session->connectTo(quark), FK_OK);
}

TEST(FkSessionTest, Disconnect) {
    auto quark = std::make_shared<FkIncreaseQuark>();
    auto session = FkSession::with({FkOnCreatePrt_Class::type.getId(), FkOnCreatePrt_Class::type.getName()});
    EXPECT_EQ(session->connectTo(quark), FK_OK);
    EXPECT_EQ(session->disconnect(quark), FK_OK);
}

TEST(FkSessionTest, DisconnectError) {
    auto quark = std::make_shared<FkIncreaseQuark>();
    auto session = FkSession::with({FkOnCreatePrt_Class::type.getId(), FkOnCreatePrt_Class::type.getName()});
    EXPECT_EQ(session->connectTo(quark), FK_OK);
    EXPECT_EQ(session->open(), FK_OK);
    EXPECT_NE(session->disconnect(quark), FK_OK);
}
