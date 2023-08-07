#include <combo.h>
#include <combo/custom.h>

void EnTuboTrap_InitWrapper(Actor_EnTuboTrap* this, GameState_Play* play)
{
    ActorFunc EnTuboTrap_Init;

    /* Set the extended properties */
    this->xflag.sceneId = play->sceneId;
    this->xflag.setupId = g.sceneSetupId;
    this->xflag.roomId = this->base.room;
    this->xflag.id = g.actorIndex;

    /* Forward init */
    EnTuboTrap_Init = actorAddr(AC_EN_TUBO_TRAP, 0x809307e0);
    EnTuboTrap_Init(&this->base, play);
}

static const Gfx kDrawListNormalDangeonTop[] = {
    gsDPLoadTextureBlock(0x05011EC0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, 0, 0),
    gsSPEndDisplayList(),
};

static const Gfx kDrawListNormalDangeonSide[] = {
    gsDPLoadTextureBlock(0x05010EC0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 6, 0, 0),
    gsSPEndDisplayList(),
};

static const Gfx kDrawListMajorTop[] = {
    gsDPLoadTextureBlock(0x09000000 | CUSTOM_KEEP_POT_MAJOR_TOP, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, 0, 0),
    gsSPEndDisplayList(),
};

static const Gfx kDrawListMajorSide[] = {
    gsDPLoadTextureBlock(0x09000000 | CUSTOM_KEEP_POT_MAJOR_SIDE, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 64, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 6, 0, 0),
    gsSPEndDisplayList(),
};

static void EnTuboTrap_Draw(Actor_EnTuboTrap* this, GameState_Play* play)
{
    const void* dlistSide;
    const void* dlistTop;

    /* Checks flag and dangeon_keep */
    if (comboConfig(CFG_MM_SHUFFLE_POTS) && !comboXflagsGet(&this->xflag))
    {
        dlistSide = kDrawListMajorSide;
        dlistTop = kDrawListMajorTop;
    }
    else
    {
        dlistSide = kDrawListNormalDangeonSide;
        dlistTop = kDrawListNormalDangeonTop;
    }

    /* Setup the textures */
    OPEN_DISPS(play->gs.gfx);
    gSPSegment(POLY_OPA_DISP++, 0x09, gCustomKeep);
    gSPSegment(POLY_OPA_DISP++, 0x0a, dlistSide);
    gSPSegment(POLY_OPA_DISP++, 0x0b, dlistTop);
    CLOSE_DISPS();

    /* Draw the pot */
    DrawSimpleOpa(play, 0x05017ea0);
}

PATCH_FUNC(0x809313d8, EnTuboTrap_Draw);

void EnTuboTrap_SpawnShuffledDrop(Actor_EnTuboTrap* this, GameState_Play* play)
{
    u16 var;

    if (comboXflagsGet(&this->xflag))
    {
        /* Already spawned */
        return;
    }

    /* Spawn an extended item */
    DropCustomItem(play, &this->base.position, &this->xflag);
}