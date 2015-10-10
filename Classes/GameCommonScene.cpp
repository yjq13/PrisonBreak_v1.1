//
//  GameCommonScene.cpp
//  PrisonBreak
//
//  Created by yjq131250077 on 15/9/11.
//
//

#include "GameCommonScene.h"
USING_NS_CC;

Scene* Game :: createScene(){
    auto scene=Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer=Game::create();
    layer->setPhyWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}
bool Game::init(){
    if(!Layer::init()){
        return false;
    }
    //计数器设为0
    index=0;
    auto contactListener=EventListenerPhysicsContact::create();
    contactListener->onContactBegin=CC_CALLBACK_1(Game::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    setUI();
    
    return true;
}
void Game::setUI(){
    //测试在界面上放置组件
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //    auto gameLabel=Label::createWithTTF("GAME", "fonts/Marker Felt.ttf", 24);
    //    gameLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                                origin.y + visibleSize.height - gameLabel->getContentSize().height));
    //    this->addChild(gameLabel);
    
    auto image1=MenuItemImage::create("01.jpg", "01.jpg");
    image1->setPosition(100, 100);
    auto menu=Menu::create(image1,NULL);
    menu->setPosition(100,100);
    // this->addChild(menu,1);
    
    //下面 测试节点的运动
    //    auto moveTo=MoveTo::create(3.0f, Vec2(origin.x + visibleSize.width/2,
    //                                          origin.y + visibleSize.height - gameLabel->getContentSize().height-200));
    //auto action=Sequence::create(moveTo,Spawn::create(RotateBy::create(1.0f,360),ScaleTo::create(1.0f,1.2f),NULL),Blink::create(1,5),FadeOut::create(0.5f), NULL);
    
    //image1->runAction(action);
    
    //下面测试动画的实现
    
    
    //下面测试触控
    //    sprite=CCSprite::create("03.jpg");
    //    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //    sprite->setScale(1, 0.5);
    
    
    
    auto sprite1=Sprite::create("00.jpg");
    sprite1->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    auto wallBody1=PhysicsBody::createBox(sprite1->getContentSize());
    CCLOG("%f,%f",sprite1->getContentSize().width,sprite1->getContentSize().height);
    wallBody1->setGravityEnable(false);
    //    wallBody1->getShape(0)->setRestitution(1.0f);
    //    wallBody1->getShape(0)->setFriction(0.0);
    //    wallBody1->getShape(0)->setDensity(1.0);
    //    Vect force = Vect(500000.0f, 500000.0f);
    //    wallBody1->applyImpulse(force);
    wallBody1->setContactTestBitmask(0xFFFFFFFF);
    sprite1->setPhysicsBody(wallBody1);
    sprite1->setTag(1);
    this->addChild(sprite1);
    
    auto sprite2=Sprite::create("01.jpg");
    sprite2->setPosition(Vec2(300 , 250));
    auto wallBody2=PhysicsBody::createBox(sprite2->getContentSize());
    wallBody2->setGravityEnable(false);
    wallBody2->setContactTestBitmask(0xFFFFFFFF);
    sprite2->setPhysicsBody(wallBody2);
    sprite2->setTag(2);
    this->addChild(sprite2);
    sprite2->runAction(MoveTo::create(2, Vec2(400, 400)));
    
    Sprite* edgeSpace=Sprite::create();
    PhysicsBody* boundBody=PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
    boundBody->getShape(0)->setFriction(0.0f);
    boundBody->getShape(0)->setRestitution(1.0f);
    
    edgeSpace->setPhysicsBody(boundBody);
    edgeSpace->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(edgeSpace);
    edgeSpace->setTag(0);
    
    auto listener=EventListenerTouchOneByOne::create();
    listener->onTouchMoved=CC_CALLBACK_2(Game::onTouchMoved, this);
    listener->onTouchBegan=CC_CALLBACK_2(Game::onTouchBegan, this);
    listener->onTouchEnded=CC_CALLBACK_2(Game::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //下面检测碰撞
    
    
    
}

bool Game::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    CCLOG("begin");
    //计数器归零,数组清空
    index=0;
    for (int i=0;i<10000;i++){
        points[i]=ccp(0,0);
    }
    return true;
}
void Game::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    isMoved=true;
    points[index]=touch->getLocation();
    auto p=touch->getLocation();
    auto r=DrawNode::create();
    addChild(r);
    if(index>0){
        r->drawSegment(points[index-1], p, 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    }
    index++;
}

void Game::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    printf("ed");
    //下面是主角跟随路线移动
    ballOne=Sprite::create("01.jpg");
    auto mainBox=PhysicsBody::createBox(ballOne->getContentSize());
    mainBox->setGravityEnable(false);
    mainBox->setContactTestBitmask(0xFFFFFFFF);
    ballOne->setPhysicsBody(mainBox);
    //s->autorelease();
    ballOne->setPosition(points[0]);
    addChild(ballOne);
    //下面是填装动作的容器
    Vector<FiniteTimeAction*> actionVector;
    for (int i=0;i<10000;i++){
        if (i!=0&&points[i].x!=0) {
            actionVector.pushBack(MoveTo::create(ccpSub(points[i-1], points[i]).length()/100, points[i]));
        }
    }if(isMoved){
        auto allAction=Sequence::create(actionVector);
        ballOne->runAction(allAction);
    }
    isMoved=false;
}

bool Game::onContactBegin(const cocos2d::PhysicsContact &contact){
    removeChild(ballOne);
    return true;
}

//#include "GameCommonScene.h"
//
//USING_NS_CC;
//
////物理引擎标识
//int ball1Mask = 1 << 0;//球1
//int ball2Mask = 1 << 1;//球2
//int wallMask = 1 << 2;//地面
//
//Scene* Game::createScene()
//{
//    //创建有物理空间的场景
//    Scene* scene=Scene::createWithPhysics();
//    //设置Debug模式，你会看到物体的表面被线条包围，主要为了在调试中更容易地观察
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
//    Game* layer=Game::create();
//    //把空间保持我们创建的层中，就是上面所说m_world的作用，方便后面设置空间的参数
//    layer->setPhyWorld(scene->getPhysicsWorld());
//    scene->addChild(layer);
//    return scene;
//}
//
//// on "init" you need to initialize your instance
//
//bool Game::init()
//{
//    //////////////////////////////
//    // 1. super init first
//    if ( !Layer::init() )
//    {
//        return false;
//    }
//    auto contactListener=EventListenerPhysicsContact::create();
//    //设置监听器的碰撞开始函数
//    contactListener->onContactBegin = CC_CALLBACK_1(Game::onContactBegin, this);
//    //添加到事件分发器中
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
//
//
//
//    Size visibleSize=Director::getInstance()->getVisibleSize();
//    Point origin=Director::getInstance()->getVisibleOrigin();
//
//    ballOne=Sprite::create();
//    ballOne->setContentSize(Size(50, 50));
//    ballOne->setPosition(visibleSize.width/2,visibleSize.height/2);
//    //创建物体，并且物体的形状为圆形，第一参数为半径，第二个参数为物体材质
//    //第三个参数为边的厚度,就是在Debug模式下看到的物体外面线条的厚度，默认为0
//    PhysicsBody* ballBodyOne=PhysicsBody::createCircle(ballOne->getContentSize().width/2,PHYSICSBODY_MATERIAL_DEFAULT, Vec2(1,1));
//    //
//    //ballBodyOne->setCategoryBitmask(1);
//
//    //是否设置物体为静态
//    //ballBody->setDynamic(false);
//    //设置物体的恢复力
//    ballBodyOne->getShape(0)->setRestitution(1.0f);
//    //设置物体的摩擦力
//    ballBodyOne->getShape(0)->setFriction(0.0f);
//    //设置物体密度
//    ballBodyOne->getShape(0)->setDensity(1.0f);
//    //设置质量
//    //ballBodyOne->getShape(0)->setMass(5000);
//    //设置物体是否受重力系数影响
//    ballBodyOne->setGravityEnable(false);
//
//    //设置物体的冲力
//    Vect force=Vect(500000.0f, 500000.0f);
//    ballBodyOne->applyImpulse(force);
//    //把物体添加到精灵中
//    ballOne->setPhysicsBody(ballBodyOne);
//    //设置标志
//    ballOne->setTag(1);
//    this->addChild(ballOne);
//
//    //设置第二个球
//    ballTwo=Sprite::create();
//    ballTwo->setContentSize(Size(100, 100));
//    ballTwo->setPosition(visibleSize.width/3,visibleSize.height/3);
//    PhysicsBody* ballBodyTwo=PhysicsBody::createCircle(ballOne->getContentSize().width/2,PHYSICSBODY_MATERIAL_DEFAULT);
//    //是否设置物体为静态
//    //ballBodyTwo->setDynamic(false);
//    ballBodyTwo->getShape(0)->setRestitution(1.0f);
//    ballBodyTwo->getShape(0)->setFriction(0.0f);
//    ballBodyTwo->getShape(0)->setDensity(1.0f);
//
//    ballBodyTwo->setGravityEnable(false);
//
//    force=Vect(-500000.0f, -500000.0f);
//    ballBodyTwo->applyImpulse(force);
//    ballTwo->setPhysicsBody(ballBodyTwo);
//    ballTwo->setTag(2);
//    this->addChild(ballTwo);
//
//    //创建一个盒子，用来碰撞
//    Sprite* edgeSpace=Sprite::create();
//    PhysicsBody* boundBody=PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
//    boundBody->getShape(0)->setFriction(0.0f);
//    boundBody->getShape(0)->setRestitution(1.0f);
//
//    edgeSpace->setPhysicsBody(boundBody);
//    edgeSpace->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
//    this->addChild(edgeSpace);
//    edgeSpace->setTag(0);
//
//
//
//
//    ballBodyOne->setCategoryBitmask(ball1Mask);
//    ballBodyOne->setCollisionBitmask(wallMask|ball1Mask|ball2Mask);
//    ballBodyOne->setContactTestBitmask(wallMask|ball1Mask|ball2Mask);
//
//    ballBodyTwo->setCategoryBitmask(ball2Mask);
//    ballBodyTwo->setCollisionBitmask(wallMask|ball1Mask|ball2Mask);
//    ballBodyTwo->setContactTestBitmask(wallMask|ball1Mask|ball2Mask);
//
//    boundBody->setCategoryBitmask(wallMask);
//    boundBody->setCollisionBitmask(wallMask | ball1Mask|ball2Mask);
//    boundBody->setContactTestBitmask(wallMask|ball1Mask|ball2Mask);
//
//
//    return true;
//}
//
//bool Game::onContactBegin(const PhysicsContact& contact)
//{
//
//    if ((contact.getShapeA()->getBody()->getCategoryBitmask() & ball1Mask) == ball1Mask) {
//        CCLOG("ball1 touch something");
//    }
//    if ((contact.getShapeB()->getBody()->getCategoryBitmask() & ball1Mask) == ball1Mask) {
//        CCLOG("ball1 touch something");
//    }
//
//
//    if ((contact.getShapeA()->getBody()->getCategoryBitmask() & ball2Mask) == ball2Mask) {
//        CCLOG("ball2 touch something");
//    }
//    if ((contact.getShapeB()->getBody()->getCategoryBitmask() & ball2Mask) == ball2Mask) {
//        CCLOG("ball2 touch something");
//    }
//    
//    return true;
//}
