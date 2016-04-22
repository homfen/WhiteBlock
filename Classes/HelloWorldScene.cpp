#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Block.hpp"
#include<sstream>

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto bg = LayerColor::create(Color4B::GRAY);
    addChild(bg);
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    gameLayer = Node::create();
    addChild(gameLayer);
    
    addTime();
    startGame();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void HelloWorld::startGame()
{
    resetTime();
    Vector<Block*> * blocks = Block::getBlocks();
    Block *block;
    for(Vector<Block*>::iterator it = blocks->begin();it != blocks->end(); ++it)
    {
        block = *it;
        block->removeBlock();
        --it;
    }
    startTime = 0;
    count = 0;
    addStartLine();
    addNormalLine(1);
    addNormalLine(2);
    addNormalLine(3);
}

void HelloWorld::addStartLine()
{
    Block *block = Block::createWithArgs(2, 0, visibleSize);
    block->setPosition(Vec2(0, 0));
    gameLayer->addChild(block);
}

void HelloWorld::addEndLine()
{
    Block *block = Block::createWithArgs(3, 4, visibleSize);
    block->setPosition(Vec2(0, visibleSize.height));
    gameLayer->addChild(block);
}

void HelloWorld::addNormalLine(int lineIndex)
{
    Block *block;
    int black = rand() % 4;
    int width = visibleSize.width / 4;
    int height = visibleSize.height / 4;
    int type;
    for(int i = 0;i < 4;i++) {
        if (black == i)
        {
            type = 1;
        }
        else
        {
            type = 0;
        }
        block = Block::createWithArgs(type, lineIndex, visibleSize);
        Vec2 pos = Vec2(i * width, lineIndex * height);
        block->setPosition(pos);
        gameLayer->addChild(block);
    }
}

void HelloWorld::moveDown()
{
    if (count < totalCount - 3)
    {
        this->addNormalLine(4);
    }
    else if (count == totalCount - 3)
    {
        this->addEndLine();
    }
    int lineIndex;
    int height = visibleSize.height / 4;
    Vector<Block*> * blocks = Block::getBlocks();
    Block *block;
    for(Vector<Block*>::iterator it = blocks->begin();it != blocks->end(); ++it)
    {
        block = *it;
        lineIndex = block->getLineIndex() - 1;
        if (lineIndex < 0)
        {
            block->removeBlock();
            --it;
        }
        else
        {
            block->setLineIndex(lineIndex);
            Vec2 pos = Vec2(block->getPositionX(), lineIndex * height);
            block->setPosition(pos);
        }
    }
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    Vector<Block*> *blocks = Block::getBlocks();
    Block *b;
    for(Vector<Block*>::iterator it = blocks->begin(); it != blocks->end(); it++)
    {
        b = *it;
        if(b && b->getLineIndex() == 1 && b->getBoundingBox().containsPoint(touch->getLocation())) {
            if (b->getColor() == Color3B::BLACK)
            {
                if (count == 0)
                {
                    scheduleUpdate();
                    startTime = getNowTime();
                }
                b->setColor(Color3B::GRAY);
                this->moveDown();
                if (count < totalCount) {
                    count++;
                }
                break;
            }
            else {
                string s = "";
                if (count == totalCount) {
                    double pass = getNowTime() - startTime;
                    s = StringUtils::format("%.6f", pass);
                }
                MessageBox("GameOver", s.c_str());
                startGame();
                unscheduleUpdate();
            }
        }
    }
    return true;
}

double HelloWorld::getNowTime()
{
    long now = clock();
    return ((double)now)/1000000;
}

void HelloWorld::addTime()
{
    time = Label::create();
    time->setSystemFontSize(48);
    time->setAnchorPoint(Vec2(0.5f, 0.5f));
    time->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 7 / 8));
    time->setContentSize(Size(visibleSize.width, visibleSize.height / 4));
    time->setTextColor(Color4B::BLUE);
    addChild(time);
}

void HelloWorld::resetTime()
{
    time->setString("0.000000");
}

void HelloWorld::update(float dt)
{
    if (startTime != 0)
    {
        double now = getNowTime();
        double pass = now - startTime;
        string s = StringUtils::format("%.6f", pass);
        time->setString(s);
    }
}
