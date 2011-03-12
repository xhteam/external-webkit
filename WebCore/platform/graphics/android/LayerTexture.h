/*
 * Copyright 2010, The Android Open Source Project
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LayerTexture_h
#define LayerTexture_h

#include "BackedDoubleBufferedTexture.h"
#include "ClassTracker.h"
#include "IntRect.h"

namespace WebCore {

class LayerTexture : public BackedDoubleBufferedTexture {
 public:
    LayerTexture(uint32_t w, uint32_t h,
                 SkBitmap::Config config = SkBitmap::kARGB_8888_Config)
        : BackedDoubleBufferedTexture(w, h, 0, config)
        , m_id(0)
        , m_scale(1)
        , m_pictureUsed(0)
        , m_ready(false)
    {
#ifdef DEBUG_COUNT
        ClassTracker::instance()->increment("LayerTexture");
#endif
    }
    virtual ~LayerTexture()
    {
#ifdef DEBUG_COUNT
        ClassTracker::instance()->decrement("LayerTexture");
#endif
    };

    int id() { return m_id; }
    void setId(int id) { m_id = id; }
    bool ready() { return m_ready; }

    unsigned int pictureUsed() { return m_pictureUsed; }
    void setPictureUsed(unsigned pictureUsed)
    {
          if (!m_ready)
              m_ready = true;
          m_pictureUsed = pictureUsed;
    }
    void setRect(const IntRect& r) { m_rect = r; }
    IntRect& rect() { return m_rect; }
    float scale() { return m_scale; }
    void setScale(float scale) { m_scale = scale; }

 private:

    int m_id;
    IntRect m_rect;
    float m_scale;
    unsigned int m_pictureUsed;
    bool m_ready;
};

} // namespace WebCore

#endif // LayerTexture_h