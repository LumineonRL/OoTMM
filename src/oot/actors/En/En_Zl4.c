#include <combo.h>

void EnZl4_Update6(Actor* actor, GameState_Play* play)
{
    TransitionContext* t;

    SetEventChk(EV_OOT_CHK_ZELDA_LETTER);
    SetEventChk(EV_OOT_CHK_SONG_ZELDA);
    ActorDestroy(actor);

    t = &play->transition;
    t->type = TRANS_TYPE_NORMAL;
    t->gfx = TRANS_GFX_SHORTCUT;
    t->entrance = 0x0594;
}

void EnZl4_Update5(Actor* actor, GameState_Play* play)
{
    if (Message_GetState(&play->msgCtx) == 2)
    {
        EnZl4_Update6(actor, play);
        actor->update = EnZl4_Update6;
    }
}

void EnZl4_Update4(Actor* actor, GameState_Play* play)
{
    s16 gi;

    if (Actor_HasParent(actor))
    {
        actor->attachedA = NULL;
        EnZl4_Update5(actor, play);
        actor->update = EnZl4_Update5;
    }
    else
    {
        gi = comboOverride(OV_NPC, 0, NPC_OOT_ZELDA_SONG, GI_OOT_SONG_ZELDA);
        GiveItem(actor, play, gi, 10000.f, 400.f);
    }
}

void EnZl4_Update3(Actor* actor, GameState_Play* play)
{
    s16 gi;

    if (Actor_HasParent(actor))
    {
        actor->attachedA = NULL;
        EnZl4_Update4(actor, play);
        actor->update = EnZl4_Update4;
    }
    else
    {
        gi = comboOverride(OV_NPC, 0, NPC_OOT_ZELDA_LETTER, GI_OOT_ZELDA_LETTER);
        GiveItem(actor, play, gi, 10000.f, 400.f);
    }
}

void EnZl4_Update2(Actor* actor, GameState_Play* play)
{
    Message_Close(play);
    EnZl4_Update3(actor, play);
    actor->update = EnZl4_Update3;
}

void EnZl4_Update(Actor* actor, GameState_Play* play)
{
    actor->messageId = 0x2005;
    if (ActorTalkedTo(actor))
    {
        actor->update = EnZl4_Update2;
    }
    else
    {
        ActorEnableTalk(actor, play, 100.f);
    }
}

PATCH_FUNC(0x80b83374, EnZl4_Update);