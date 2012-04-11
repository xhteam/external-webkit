#ifndef CanvasLayerAndroid_h
#define CanvasLayerAndroid_h

#if defined(USE_CANVAS_LAYER)

#include "LayerAndroid.h"
#include "HTMLCanvasElement.h"
#include "GLUtils.h"

namespace WebCore {

class CanvasLayerAndroid : public LayerAndroid {
public:
	CanvasLayerAndroid(HTMLCanvasElement *src);
    explicit CanvasLayerAndroid(const CanvasLayerAndroid& layer);
	virtual ~CanvasLayerAndroid();
    virtual LayerAndroid* copy() const { return new CanvasLayerAndroid(*this); }
    virtual void commitLayer();
	bool updateTexture();

	virtual bool drawGL();
	virtual bool isCanvas() const {return true; }
private:

private:
	HTMLCanvasElement *m_src;
	// do not hold too many data since this object's lifecycle is very short
};

} // namespace WebCore

#endif // USE_CANVAS_LAYER
#endif // CanvasLayerAndroid_h
