#ifndef PARUPAINTCANVASSTROKEOBJECT_H
#define PARUPAINTCANVASSTROKEOBJECT_H

#include "stroke/parupaintStroke.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>

class ParupaintCanvasPool;

class ParupaintCanvasStrokeObject : public QGraphicsPixmapItem, public ParupaintStroke
{
	private:
	QRectF region_limit;
	QRectF region;

	public:
	ParupaintCanvasStrokeObject(QRectF);
	void SetRegionLimit(QRectF);
	virtual void AddStroke(ParupaintStrokeStep *);
};

#endif
