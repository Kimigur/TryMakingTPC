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

static const int WIDTH = 20;  // Ширина x
static const int HEIGHT = 20; // Высота y

#endif // CONSTANTS_H
