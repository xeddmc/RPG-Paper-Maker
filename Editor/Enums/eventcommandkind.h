/*
    RPG Paper Maker Copyright (C) 2017-2019 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#ifndef EVENTCOMMANDKIND_H
#define EVENTCOMMANDKIND_H

// -------------------------------------------------------
//
//  ENUM EventCommandKind
//
//  All the types of possible commands. The same order should
//  be respected in the interpreter.
//
// -------------------------------------------------------

enum class EventCommandKind {
    None,
    ShowText,
    ChangeVariables,
    EndGame,
    While,
    EndWhile,
    WhileBreak,
    InputNumber,
    If,
    Else,
    EndIf,
    OpenMainMenu,
    OpenSavesMenu,
    ModifyInventory,
    ModifyTeam,
    StartBattle,
    IfWin,
    IfLose,
    ChangeState,
    SendEvent,
    TeleportObject,
    MoveObject,
    Wait,
    MoveCamera,
    PlayMusic,
    StopMusic,
    PlayBackgroundSound,
    StopBackgroundSound,
    PlayASound,
    PlayMusicEffect,
    ChangeProperty,
    Last
};

#endif // EVENTCOMMANDKIND_H
