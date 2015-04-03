//
//  config.h
//  changeableball
//
//  Created by mac on 14-9-6.
//
//

#ifndef changeableball_config_h
#define changeableball_config_h

#define TOTALX 6
#define TOTALY 6
#define TOTALS 36

#define SPAWN_DROPDOWN_TIME 0.5
#define SPAWN_JUMP_TIME 0.3

#define RESET_DROPDOWN_TIME 0.2
#define RESET_JUMP_TIME 0.3
#define RESET_JUMP_TIMES 3

#define DRAWSPRITE_RADIUES 18
#define DRAWSPRITE_WIDTH 24.0
#define DRAWSPRITE_HEIGH 24.0

#define AddHeigh 130
#define addWidth 40

#define TOTAL_TYPE 5
#define ELIMINABLE_NUM 3

#define TOTAL_TYPE 5
#define MAX_TYPE_VALUE 5
#define CONTINIOUS_NUM 3
#define DEFAULT_COUNT_TIME 3

#define ccc4fBlue ccc4f(88/255.f,34/255.f,241/255.f,1)
#define ccc4fOrange ccc4f(244/255.f,148/255.f,37/255.f,1)
#define ccc4fRed ccc4f(242/255.f,13/255.f,43/255.f,1)
#define ccc4fPurple ccc4f(148/255.f,35/255.f,242/255.f,1)
#define ccc4fGreen ccc4f(52/255.f,241/255.f,44/255.f,1)
#define ccc4fYellow ccc4f(242/255.f,207/255.f,48/255.f,1)

#define ccc3Red Color3B(242,13,43)

#define USE_LIFE_LIQUID "use_life_liquid"
#define BUY_LIFE_LIQUID "buy_life_liquid"
#define REFESH_BUYLIFE_UI "refresh_buylife_ui"

#define RIVIVE_COSUMED_DIAMOND  30

#define GAME_RULE "游戏规则\n     1,有连续三个以上相同元素便可以消除，且最后一个元素在当前值下加1后进化成相应元素，消除3个加1，消除4个加2，依此类推，最大进化为5；\n     2，比如消除3个1变成2，消除4个1变成3，消除五个1变成4，消除6个和六个以上的1变成5；\n    3，消除3个2进化为3。。。。。。"
typedef enum {
    tooltime = 0,
    toolDisappearAll = 1,
    toolDisappearOne = 2,
}PLAYERTOOLTYPE;


static const long int expArray[] = {0,100,150,225,338,506,759,1139,1709,2563,3844,5767,8650,12975,19462,29192,43789,65684,98526,147789,184736,230921,288651,360813,451017,563771,704714,880892,1101115,1376394,1720493,2150616,2688270,3360337,4200421,5250527,6563158,8203948,10254935,12818669,14421002,16223628,18251581,20533029,23099657,25987114,29235504,32889942,37001184,41626332,46829624,52683327,59268743,66677336,75012003,84388503,94937066,106804199,120154724,135174064,143622443,152598846,162136247,172269791,183036653,194476444,206631222,219545673,233267277,247846482,263336887,279795443,297282658,315862824,335604251,356579516,378865736,402544845,427703898,454435391};

#endif

