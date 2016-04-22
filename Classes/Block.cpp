//
//  Block.cpp
//  WhiteBlock
//
//  Created by homfen on 16/4/4.
//
//

#include "Block.hpp"

Vector<Block*> * Block::blocks = new Vector<Block*>();

Vector<Block*> * Block::getBlocks()
{
    return blocks;
}

Block * Block::createWithArgs(int type, int lineIndex, Size visibleSize)
{
    Color3B bg;
    Size size;
    switch (type)
    {
        case 0:
            bg = Color3B::WHITE;
            size = Size(visibleSize.width/4, visibleSize.height/4);
            break;
        case 1:
            bg = Color3B::BLACK;
            size = Size(visibleSize.width/4, visibleSize.height/4);
            break;
        case 2:
            bg = Color3B::YELLOW;
            size = Size(visibleSize.width, visibleSize.height/4);
            break;
        case 3:
            bg = Color3B::GREEN;
            size = Size(visibleSize.width, visibleSize.height);
            break;
        default:
            bg = Color3B::WHITE;
            size = Size(visibleSize.width/4, visibleSize.height/4);
            break;
    }
    
    Block *b = new Block();
    b->initWithArgs(bg, size, lineIndex);
    b->autorelease();
    
    blocks->pushBack(b);
    
    return b;
    
};

bool Block::initWithArgs(Color3B bg, Size size, int lineIndex)
{
    Sprite::init();
    
    setColor(bg);
    setContentSize(size);
    setAnchorPoint(Point::ZERO);
    setTextureRect(Rect(1, 1, size.width-2, size.height-2));
    setLineIndex(lineIndex);
    
    return true;
}

void Block::removeBlock()
{
    CCLOG("remove block");
    removeFromParent();
    blocks->eraseObject(this);
}

int Block::getLineIndex()
{
    return this->lineIndex;
}

void Block::setLineIndex(int lineIndex)
{
    this->lineIndex = lineIndex;
}