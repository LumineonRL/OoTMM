#ifndef MM_ACTOR_H
#define MM_ACTOR_H

#include <combo/types.h>

#define AC_EN_BOX       0x006
#define AC_ITEM_CUSTOM  0x013

typedef struct PACKED ALIGNED(0x4) Actor
{
    u16     id;
    u8      type;
    u8      room;
    s32     flags;
    char    unk[0x14];
    u16     variable;
    char    unk2[0x126];
}
Actor;

_Static_assert(sizeof(Actor) == 0x144, "MM Actor size is wrong");

#endif /* OOT_ACTOR_H */
