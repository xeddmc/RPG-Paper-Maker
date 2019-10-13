/*
    RPG Paper Maker Copyright (C) 2017-2019 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#include "dialogcompleteliststates.h"
#include "ui_dialogcompleteliststates.h"
#include "rpm.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

DialogCompleteListStates::DialogCompleteListStates(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCompleteListStates)
{
    ui->setupUi(this);

    ui->panelSuperListStates->list()->initializeNewItemInstance(
                new SuperListItem);
    ui->panelSuperListStates->initializeModel(RPM::get()->project()->gameDatas()
        ->commonEventsDatas()->modelStates());
    QModelIndex index = ui->panelSuperListStates->list()->getModel()
        ->index(0,0);
    ui->panelSuperListStates->list()->setCurrentIndex(index);
}

DialogCompleteListStates::~DialogCompleteListStates()
{
    delete ui;
}
