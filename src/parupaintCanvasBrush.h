#ifndef PARUPAINTCANVASBRUSH_H
#define PARUPAINTCANVASBRUSH_H

#include <QColor>
#include <QPen>

#include "parupaintBrush.h"
#include <QGraphicsItem>

// todo: extends ParupaintBrush?
class ParupaintCanvasBrush : public QGraphicsItem, public ParupaintBrush 
{
	public:
	ParupaintCanvasBrush();

	QPen ToPen();
	void Paint(QPainter *);

	void SetPosition(QPointF);

	private:
	QRectF boundingRect() const;
	void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

};

#endif
