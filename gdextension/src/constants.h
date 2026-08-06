#ifndef CONSTANTS_H
#define CONSTANTS_H

enum EquipSlot {
    SLOT_MAIN_HAND = 0,
    SLOT_OFF_HAND,
    SLOT_ARMOR,
    SLOT_HELM,
    SLOT_GLOVES,
    SLOT_BOOTS,
    SLOT_ACC_1,
    SLOT_ACC_2,
    SLOT_ACC_3,
    SLOT_ACC_4,
    SLOT_COUNT
};

enum ActionCostType {
    FREE = 0,
    MAIN,
    BONUS,
    REACTION,
    LEGENDARY
};

enum DamageType {
    NONE = 0,     // без типа
    BLUDGEONING,  // Дробящий
    PIERCING,     // Колющий
    SLASHING,     // Рубящий

    FIRE,         // Огонь
    COLD,         // Холод
    LIGHTHING,    // Молния
    ACID,         // Кислота
    POISON,       // Яд

    FORCE,        // Силовой урон
    RADIANT,      // Лучистый урон
    NECROTIC,     // Некротический урон
    PSYCHIC,      // Психический урон
};

enum TargetType {
    TARGET_EMPTY = -2,      //< Пустые клетки (не блокируют луч/BFS).
    TARGET_ANY = -1,        //< Любой юнит.
    TARGET_DM_DUMMY = 0,    //< Кукла ДМ-а.
    TARGET_ADVENTURER = 1,  //< Авантюрист (игрок/враг).
    TARGET_ENVIRONMENT = 2  //< Нейтральный (деревья и т.п.).
};

static const int WIDTH = 20;  // Ширина x
static const int HEIGHT = 20; // Высота y

#endif // CONSTANTS_H
