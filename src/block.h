#ifndef BLOCK_H
#define BLOCK_H


#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <iostream>

#define Block_DENSITY 10.0f
#define Block_FRICTION 0.2f
#define Block_RESTITUTION 0.5f

class block : public GameItem
{
public:
    block(float x, float y, float wide, float tall, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
};

#endif // BLOCK_H
