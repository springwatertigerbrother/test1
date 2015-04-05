

#include "MUtils.h"
#include "cocos2d.h"

float get_content_scale_factor()
{
    auto director = cocos2d::Director::getInstance();
    cocos2d::Size frameSize = director->getOpenGLView()->getFrameSize();
    if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    {
        switch (int(frameSize.width * frameSize.height))
        {
            case 480*320:
                return 0.5;
                break;
            case 960*640:
                return 1;
                break;
            case 1136*640:
                return 1;
                break;
            case 1024*768:
                return 1;
                break;
            case 2048*1536:
                return 2;
                break;
                
            default:
                break;
        }
    }
    else
    {
        switch (int(frameSize.width * frameSize.height))
        {
            case 320*240:
                return 240/640.f;
                break;
            case 480*320:
                return 320/640.f;
                break;
            case 640*460:
                return 460/640.f;
                break;
            case 800*480:
                return 480/640.f;
                break;
            case 854*480:
                return 480/640.f;
                break;
            case 888*540:
                return 540/640.f;
                break;
            case 960*540:
                return 540/640.f;
                break;
            case 960*640:
            {
                if (frameSize.width > 1000 || frameSize.height > 1000)
                {
                    // 1024*600
                    return 600/640.f;
                }
                else
                {
                    return 640/640.f;
                }
                break;
            }
            case 1184*720:
                return 720/640.f;
                break;
            case 1280*720:
                return 720/640.f;
                break;
            case 1280*768:
                return 768/640.f;
                break;
            case 1280*800:
                return 800/640.f;
                break;
            case 1800*1080:
                return 1080/640.f;
                break;
            case 1920*1080:
                return 1080/640.f;
                break;
                
            default:
            {
                auto width = frameSize.width;
                if (width > frameSize.height)
                {
                    width = frameSize.height;
                }
                return width/640.f;
                break;
            }
        }
    }
    
    return 1;
}
//
cocos2d::Size get_design_resolution_size()
{
    cocos2d::Size frameSize = cocos2d::Director::getInstance()-> getOpenGLView()->getFrameSize();
    float scaleFactor = get_content_scale_factor();
    
    auto size = cocos2d::Size(frameSize.width/scaleFactor, frameSize.height/scaleFactor);
//    M_ERROR("resolution size: " << size.width << ", " << size.height);
    return size;
}

void initialize_resolution()
{
    auto *pDirector = cocos2d::Director::getInstance();
    cocos2d::GLView *pEGLView = pDirector->getOpenGLView();
    pDirector->setOpenGLView(pEGLView);
    
    pDirector->setContentScaleFactor(get_content_scale_factor());
    
    cocos2d::Size drSize = get_design_resolution_size();
    pEGLView->setDesignResolutionSize(drSize.width, drSize.height, cocos2d::kResolutionShowAll);
    
}

ControlButton *standardButtonWithTitle(const char * title)
{
    /** Creates and return a button with a default background and title color. */
    auto backgroundButton = Scale9Sprite::create("Images/buttonbg.png");
    auto backgroundHighlightedButton = Scale9Sprite::create("Images/buttonbg.png");
    
    auto titleButton = Label::createWithTTF(title, "fonts/Marker Felt.ttf", 30);
    
    //    titleButton->setColor(Color3B(159, 168, 176));
    
    ControlButton *button = ControlButton::create(titleButton, backgroundButton);
    button->setBackgroundSpriteForState(backgroundHighlightedButton, Control::State::HIGH_LIGHTED);
    button->setTitleColorForState(Color3B::WHITE, Control::State::HIGH_LIGHTED);
    button->setPreferredSize(Size(400,150));
    return button;
}

bool ControlButtoninit(Node* obj,std::vector<std::string> vec)
{
        auto screenSize = Director::getInstance()->getWinSize();
        
        // Defines an array of title to create buttons dynamically
//        std::vector<std::string> vec;
        //        vec.push_back("Hello");
        //        vec.push_back("Variable");
        //        vec.push_back("Size");
//        vec.push_back("!trteerterreer\nndf");
    
        auto layer = Node::create();
        obj->addChild(layer, 1);
        
        double total_width = 0, height = 0;
        
        int i = 0;
        
        for (auto& title : vec)
        {
            // Creates a button with this string as title
            ControlButton *button = standardButtonWithTitle(title.c_str());
            
//            button->addTargetWithActionForControlEvents(this, cccontrol_selector(ControlButtonTest_Event::touchDownAction), Control::EventType::TOUCH_DOWN);
            if (i == 0)
            {
                button->setOpacity(50);
                //                button->setColor(Color3B(0, 255, 0));
            }
            else if (i == 1)
            {
                button->setOpacity(200);
                button->setColor(Color3B(0, 255, 0));
            }
            else if (i == 2)
            {
                button->setOpacity(100);
                button->setColor(Color3B(0, 0, 255));
            }
            
            button->setPosition(Vec2 (total_width + button->getContentSize().width / 2, button->getContentSize().height / 2));
            layer->addChild(button);
            
            // Compute the size of the layer
            height = button->getContentSize().height;
            total_width += button->getContentSize().width;
            i++;
        }
        
        layer->setAnchorPoint(Vec2 (0.5, 0.5));
        layer->setContentSize(Size(total_width, height));
        layer->setPosition(Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f));
        
//        // Add the black background
//        auto background = Scale9Sprite::create("extensions/buttonBackground.png");
//        background->setContentSize(Size(total_width + 14, height + 14));
//        background->setPosition(Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f));
//        addChild(background);
    return false;
}