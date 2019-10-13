/*
    RPG Paper Maker Copyright (C) 2017-2019 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#include "dialogcommands.h"
#include "ui_dialogcommands.h"
#include "dialogcommandshowtext.h"
#include "dialogcommandchangevariables.h"
#include "dialogcommandinputnumber.h"
#include "dialogcommandconditions.h"
#include "dialogcommandmodifyinventory.h"
#include "dialogcommandmodifyteam.h"
#include "dialogcommandstartbattle.h"
#include "dialogcommandchangestate.h"
#include "dialogcommandsendevent.h"
#include "dialogcommandteleportobject.h"
#include "dialogcommandmoveobject.h"
#include "dialogcommandwait.h"
#include "dialogcommandmovecamera.h"
#include "dialogcommandplaysong.h"
#include "dialogcommandstopsong.h"
#include "dialogcommandchangeproperty.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

DialogCommands::DialogCommands(SystemCommonObject *object,
                               QStandardItemModel *parameters,
                               QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCommands),
    m_linkedObject(object),
    m_parameters(parameters)
{
    ui->setupUi(this);

    // Disable change property if no property available
    if (object == nullptr || object->modelProperties() == nullptr || object
        ->modelProperties()->invisibleRootItem()->rowCount() == 1)
    {
        ui->pushButtonChangeProperty->setEnabled(false);
    }
}

DialogCommands::~DialogCommands()
{
    delete ui;
}

EventCommand* DialogCommands::getCommand() const{ return p_command; }

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

DialogCommand* DialogCommands::getDialogCommand(EventCommandKind kind,
                                                EventCommand* command,
                                                SystemCommonObject *object,
                                                QStandardItemModel *parameters)
{
    switch(kind){
    case EventCommandKind::ShowText:
        return new DialogCommandShowText(command);
    case EventCommandKind::ChangeVariables:
        return new DialogCommandChangeVariables(command, object, parameters);
    case EventCommandKind::InputNumber:
        return new DialogCommandInputNumber(command);
    case EventCommandKind::If:
        return new DialogCommandConditions(command, object, parameters);
    case EventCommandKind::ModifyInventory:
        return new DialogCommandModifyInventory(command);
    case EventCommandKind::ModifyTeam:
        return new DialogCommandModifyTeam(command);
    case EventCommandKind::StartBattle:
        return new DialogCommandStartBattle(command, object, parameters);
    case EventCommandKind::ChangeState:
        return new DialogCommandChangeState(command, object, parameters);
    case EventCommandKind::SendEvent:
        return new DialogCommandSendEvent(command, object, parameters);
    case EventCommandKind::TeleportObject:
        return new DialogCommandTeleportObject(command, object, parameters);
    case EventCommandKind::MoveObject:
        return new DialogCommandMoveObject(command, object, parameters);
    case EventCommandKind::Wait:
        return new DialogCommandWait(command);
    case EventCommandKind::MoveCamera:
        return new DialogCommandMoveCamera(command, object, parameters);
    case EventCommandKind::PlayMusic:
        return new DialogCommandPlaySong("Play a music", SongKind::Music,
                                         command, object, parameters);
    case EventCommandKind::StopMusic:
        return new DialogCommandStopSong("Stop a music", SongKind::Music,
                                         command, object, parameters);
    case EventCommandKind::PlayBackgroundSound:
        return new DialogCommandPlaySong("Play a background sound",
                                         SongKind::BackgroundSound,
                                         command, object, parameters);
    case EventCommandKind::StopBackgroundSound:
        return new DialogCommandStopSong("Stop a background sound",
                                         SongKind::BackgroundSound,
                                         command, object, parameters);
    case EventCommandKind::PlayASound:
        return new DialogCommandPlaySong("Play a sound", SongKind::Sound,
                                         command, object, parameters);
    case EventCommandKind::PlayMusicEffect:
        return new DialogCommandPlaySong("Play a music effect",
                                         SongKind::MusicEffect,
                                         command, object, parameters);
    case EventCommandKind::ChangeProperty:
        return new DialogCommandChangeProperty(command, object, parameters);
    default:
        return nullptr;
    }
}

// -------------------------------------------------------

void DialogCommands::openDialogCommand(EventCommandKind kind,
                                       EventCommand* command)
{
    DialogCommand* dialog = getDialogCommand(kind, command, m_linkedObject,
                                             m_parameters);
    if (dialog->exec() == QDialog::Accepted){
        p_command = dialog->getCommand();
        accept();
    }
    delete dialog;
}

// -------------------------------------------------------

void DialogCommands::openNonDialogCommand(EventCommandKind kind){
    p_command = new EventCommand(kind);
    accept();
}

// -------------------------------------------------------
//
//  SLOTS
//
// -------------------------------------------------------

void DialogCommands::on_pushButtonShowText_clicked(){
    openDialogCommand(EventCommandKind::ShowText);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonEndGame_clicked(){
    openNonDialogCommand(EventCommandKind::EndGame);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonChangeVariables_clicked(){
    openDialogCommand(EventCommandKind::ChangeVariables);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonWhile_clicked(){
    openNonDialogCommand(EventCommandKind::While);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonWhileBreak_clicked(){
    openNonDialogCommand(EventCommandKind::WhileBreak);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonInputNumber_clicked(){
    openDialogCommand(EventCommandKind::InputNumber);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonCondition_clicked(){
    openDialogCommand(EventCommandKind::If);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonOpenMainMenu_clicked(){
    openNonDialogCommand(EventCommandKind::OpenMainMenu);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonOpenSavesMenu_clicked(){
    openNonDialogCommand(EventCommandKind::OpenSavesMenu);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonModifyInventory_clicked(){
    openDialogCommand(EventCommandKind::ModifyInventory);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonModifyTeam_clicked(){
    openDialogCommand(EventCommandKind::ModifyTeam);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonStartBattle_clicked(){
    openDialogCommand(EventCommandKind::StartBattle);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonChangeState_clicked(){
    openDialogCommand(EventCommandKind::ChangeState);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonSendEvent_clicked(){
    openDialogCommand(EventCommandKind::SendEvent);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonTeleportObject_clicked(){
    openDialogCommand(EventCommandKind::TeleportObject);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonMoveObject_clicked(){
    openDialogCommand(EventCommandKind::MoveObject);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonWait_clicked(){
    openDialogCommand(EventCommandKind::Wait);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonMoveCamera_clicked() {
    openDialogCommand(EventCommandKind::MoveCamera);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonPlayMusic_clicked() {
    openDialogCommand(EventCommandKind::PlayMusic);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonStopMusic_clicked() {
    openDialogCommand(EventCommandKind::StopMusic);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonPlayBackgroundSound_clicked() {
    openDialogCommand(EventCommandKind::PlayBackgroundSound);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonStopBackgroundSound_clicked() {
    openDialogCommand(EventCommandKind::StopBackgroundSound);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonPlaySound_clicked() {
    openDialogCommand(EventCommandKind::PlayASound);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonPlayMusicEffect_clicked() {
    openDialogCommand(EventCommandKind::PlayMusicEffect);
}

// -------------------------------------------------------

void DialogCommands::on_pushButtonChangeProperty_clicked() {
    openDialogCommand(EventCommandKind::ChangeProperty);
}
