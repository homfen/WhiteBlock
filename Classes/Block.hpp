//
//  Block.hpp
//  WhiteBlock
//
//  Created by homfen on 16/4/4.
//
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class Block:public Sprite
{
private:
    static Vector<Block*> *blocks;
    int lineIndex;
    
public:
    static Vector<Block*> *getBlocks();
    static Block * createWithArgs(int type, int lineIndex, Size visibleSize);
    bool initWithArgs(Color3B bg, Size size, int lineIndex);
    void removeBlock();
    
    int getLineIndex();
    void setLineIndex(int lineIndex);
    
    
    
};

#endif /* Block_hpp */
