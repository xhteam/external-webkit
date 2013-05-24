/*
 * Copyright (C) 2012 Freescale Semiconductor
 */

#include "config.h"

#if defined(USE_CANVAS_LAYER)

#include "CanvasLayerAndroid.h"
#include "TilesManager.h"
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "ImageBuffer.h"


namespace WebCore {

CanvasLayerAndroid::CanvasLayerAndroid(HTMLCanvasElement *src)
    : LayerAndroid((RenderLayer*)0)
{
    m_src = src;
}

CanvasLayerAndroid::CanvasLayerAndroid(const CanvasLayerAndroid& layer)
    : LayerAndroid(layer)
{
    m_src = layer.m_src;
}

CanvasLayerAndroid::~CanvasLayerAndroid()
{
}

void CanvasLayerAndroid::commitLayer()
{
    m_src->commitLayer();
}

//#define EGL_NATIVE_BUFFER_ANDROID 0x3140
//#define EGL_IMAGE_PRESERVED_KHR   0x30D2

bool CanvasLayerAndroid::updateTexture()
{
//    RenderLayer * pRenderLayer = ((RenderBoxModelObject*)m_src->renderer())->layer();
    bool ret = false;
#if 0
    GlTexture* text = m_src->getGlTexture();
    text->Lock();

    if(text->getConfig() == SkBitmap::kARGB_8888_Config)
    {
        void *pixels = text->getPixels();
        glBindTexture(GL_TEXTURE_2D, m_textureId);

        // FIXME! take care of stride
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGBA,
            text->getWidth(),
            text->getHeight(),
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            pixels);

        ret = true;
    }
    text->Unlock();
#endif
    return ret;
}

bool CanvasLayerAndroid::drawGL()
{
    if(m_src->getTexture() == 0)
    {
        // create texture in drawing thread
        m_src->createTexture();
    }

    if(m_src->getTexture() != 0 && m_src->getEglImage() != EGL_NO_IMAGE_KHR)
    {
//        FloatRect clippingRect = TilesManager::instance()->shader()->rectInScreenCoord(drawClip());
//        TilesManager::instance()->shader()->clip(clippingRect);

        SkRect rect = SkRect::MakeSize(getSize());

        TilesManager::instance()->shader()->drawLayerQuad(
            m_drawTransform,
            rect,
            m_src->getTexture(),
            1,
            true,
            GL_TEXTURE_2D);
    }

    return false;
}

}
#endif

