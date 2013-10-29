#pragma once
#ifndef _ER_DIAGRAMSCENE_
#define _ER_DIAGRAMSCENE_
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE

class ER_DiagramScene : public QGraphicsScene
{
	Q_OBJECT
public:
	ER_DiagramScene(QObject *parent = 0);
	~ER_DiagramScene(void);
};
#endif