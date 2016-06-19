#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    ui->graphicsView->setBackgroundBrush(QPixmap(":/back").scaled(960, 540));
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);

    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));


    // Setting Size

    GameItem::setGlobalSize(QSizeF(32,18),size());
    creat_a_world();
    restart();
    restart_but = new QPushButton;
    restart_but->setText("restart the level");
    restart_but->setGeometry(10,10,150,45);
    restart_but->setStyleSheet("color:black;font:bold 20px;");
    connect(restart_but,SIGNAL(clicked(bool)),this,SLOT(reset()));
    scene->addWidget(restart_but);
    exit_but = new QPushButton;
    exit_but->setText("End the game");
    exit_but->setGeometry(750,10,150,45);
    exit_but->setStyleSheet("color:black;font:bold 20px");
    connect(exit_but,SIGNAL(clicked(bool)),this,SLOT(end_the_game()));
    scene->addWidget(exit_but);
    score = new QLabel(this);
    score->setStyleSheet("color:red;font: bold 30px;");
    score->setText("score : " +QString::number(final_score));
    score->setGeometry(400, 10, 200, 60);
    score->show();


    // Setting the Velocity

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {
        firstx = QCursor::pos().x();
        firsty = QCursor::pos().y();
    }
    if(event->type() == QEvent::MouseButtonDblClick)
    {
        if(special_use[4-last_bird]==false&&launch[4-last_bird]==true&&bird_exist[4-last_bird]==true&&bird_spical[4-last_bird]==true){
                if(4-last_bird==1){
                    birdie[4-last_bird]->setLinearVelocity(b2Vec2((birdie[4-last_bird]->get_velocity().x)*5,(birdie[4-last_bird]->get_velocity().y)*(1/2)));
                    special_use[4-last_bird]=true;
                }
                if(4-last_bird==2){
                    birdie[4-last_bird]->setLinearVelocity(b2Vec2(0,(birdie[4-last_bird]->get_velocity().y)*10));
                    special_use[4-last_bird]=true;
                }
                if(4-last_bird==3){
                    birdie[4-last_bird]->setLinearVelocity(b2Vec2(-(birdie[4-last_bird]->get_velocity().x),birdie[4-last_bird]->get_velocity().y));
                    special_use[4-last_bird]=true;
                }
        }
    }
    if(event->type() == QEvent::MouseMove)
    {

    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        lastx = QCursor::pos().x();
        lasty = QCursor::pos().y();
        if(end==true&&launch[4-last_bird]==false){
            birdie[4-last_bird]->setLinearVelocity(b2Vec2((firstx-lastx)/20,(lasty-firsty)/20));
            launch[4-last_bird]=true;
            end=false;
        }
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::creat_a_world()
{
    //test = new block(25,5,4,1,&timer,QPixmap(":/wide"),world,scene);
    //itemList.push_back(test);
    birdie[0] = new Bird(5.0f,5.0f,0.27f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);
    birdie[1] = new Bird(3.0f,5.0f,0.27f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);
    birdie[2] = new Bird(2.0f,5.0f,0.27f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);
    birdie[3] = new Bird(1.0f,5.0f,0.27f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);
    for(int i=0;i<4;++i){itemList.push_back(birdie[i]);}
    pig[0] = new flyingpig(20.0f,5.0f,0.27f,&timer,QPixmap(":/pig").scaled(height()/9.0,height()/9.0),world,scene);
    pig[1] = new flyingpig(24.0f,5.0f,0.27f,&timer,QPixmap(":/pig").scaled(height()/9.0,height()/9.0),world,scene);
    for(int j=0;j<2;++j)itemList.push_back(pig[j]);
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));



}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
    if(launch[4-last_bird]==true && birdstop[4-last_bird]==false){
        birdies = birdie[4-last_bird]->get_velocity().x + birdie[4-last_bird]->get_velocity().y;
        birdplace = birdie[4-last_bird]->get_place().y;
        if(birdies==0||birdplace<5.0){
            how_many++;
            if(how_many==100){
                birdstop[4-last_bird]=true;
                end=true;
                bird_exist[4-last_bird]=false;
                delete birdie[4-last_bird];
                last_bird=last_bird-1;
                if(last_bird!=0){
                    delete birdie[4-last_bird];
                    birdie[4-last_bird] = new Bird(5.0f,5.0f,0.27f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);
                    itemList.push_back(birdie[4-last_bird]);
                }
                how_many=0;
            }
        }
        else{
            how_many=0;
        }
    }
    for(int j=0;j<2;++j){
        if(dead[j]==false){
            pigs = pig[j]->get_velocity().x + pig[j]->get_velocity().y;
            if(pigs>=2){
                dead[j]=true;
                pig_exist[j]=false;
                final_score=final_score+last_bird*11111;
                score->setText("score : " +QString::number(final_score));
                delete pig[j];
            }
        }
    }
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}
void MainWindow::restart()
{
    dead[0] = false;
    dead[1] = false;
    pig_exist[0]=true;
    pig_exist[1]=true;
    bird_spical[0]=false;
    special_use[0]=false;
    for(int i=1;i<4;++i){special_use[i]=false;bird_spical[i]=true;}
    for(int i=0;i<4;++i){launch[i] = false;birdstop[i]=false;bird_exist[i]=true;}
    end=true;
    last_bird = 4;
    final_score = 0;
}
void MainWindow::reset()
{
    for(int i=0;i<4;++i){if(bird_exist[i]==true){delete birdie[i];}}
    for(int i=0;i<2;++i){if(pig_exist[i]==true)delete pig[i];}
    itemList.clear();
    creat_a_world();
    restart();
}

void MainWindow::end_the_game()
{
    exit(0);
}

