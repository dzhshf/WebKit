/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"

#include "ThrottledTextureUploader.h"

#include "FakeWebGraphicsContext3D.h"
#include "GraphicsContext3DPrivate.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <wtf/RefPtr.h>

using namespace WebCore;
using namespace WebKit;

namespace {

class FakeWebGraphicsContext3DWithQueryTesting : public FakeWebGraphicsContext3D {
public:
    FakeWebGraphicsContext3DWithQueryTesting() : m_resultAvailable(0)
    {
    }

    virtual void getQueryObjectuivEXT(WebGLId, GC3Denum type, GC3Duint* value)
    {
        switch (type) {
        case Extensions3DChromium::QUERY_RESULT_AVAILABLE_EXT:
            *value = m_resultAvailable;
            break;
        default:
            *value = 0;
            break;
        }
    }

    void setResultAvailable(unsigned resultAvailable) { m_resultAvailable = resultAvailable; }

private:
    unsigned m_resultAvailable;
};

TEST(ThrottledTextureUploaderTest, IsBusy)
{
    GraphicsContext3D::Attributes attrs;
    RefPtr<GraphicsContext3D> context = GraphicsContext3DPrivate::createGraphicsContextFromWebContext(adoptPtr(new FakeWebGraphicsContext3DWithQueryTesting()), GraphicsContext3D::RenderDirectlyToHostWindow);
    FakeWebGraphicsContext3DWithQueryTesting& fakeContext = *static_cast<FakeWebGraphicsContext3DWithQueryTesting*>(GraphicsContext3DPrivate::extractWebGraphicsContext3D(context.get()));
    OwnPtr<ThrottledTextureUploader> uploader = ThrottledTextureUploader::create(context, 2);

    fakeContext.setResultAvailable(0);
    EXPECT_FALSE(uploader->isBusy());
    uploader->beginUploads();
    uploader->endUploads();
    EXPECT_FALSE(uploader->isBusy());
    uploader->beginUploads();
    uploader->endUploads();
    EXPECT_TRUE(uploader->isBusy());

    fakeContext.setResultAvailable(1);
    EXPECT_FALSE(uploader->isBusy());
    uploader->beginUploads();
    uploader->endUploads();
    EXPECT_FALSE(uploader->isBusy());
    uploader->beginUploads();
    uploader->endUploads();
    EXPECT_FALSE(uploader->isBusy());
    uploader->beginUploads();
    uploader->endUploads();
}

} // namespace
