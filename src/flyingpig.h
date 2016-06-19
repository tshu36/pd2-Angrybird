#ifndef FLYINGPIG_H
#define FLYINGPIG_H


#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>


#define pig_DENSITY 10.0f
#define pig_FRICTION 0.2f
#define pig_RESTITUTION 0.5f


class flyingpig :public GameItem
{
public:
    flyingpig(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    b2Vec2 get_velocity();
};

#endif // FLYINGPIG_H
