/*
    RPG Paper Maker Copyright (C) 2017-2019 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#include "dialogsystemtitlecommand.h"
#include "ui_dialogsystemtitlecommand.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

DialogSystemTitleCommand::DialogSystemTitleCommand(SystemTitleCommand &tc,
    QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSystemTitleCommand),
    m_titleCommand(tc)
{
    QSizePolicy sp_retain;

    ui->setupUi(this);

    // Keep space when hiding script widget
    sp_retain = ui->plainTextEditScript->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->plainTextEditScript->setSizePolicy(sp_retain);
    ui->plainTextEditScript->hide();

    this->initialize();
}

DialogSystemTitleCommand::~DialogSystemTitleCommand() {
    delete ui;
}

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

void DialogSystemTitleCommand::initialize() {
    ui->widgetTextLangName->initializeNamesTrans(m_titleCommand.names());
    ui->comboBoxTypeCommand->setCurrentIndex(static_cast<int>(m_titleCommand
        .kind()));
    ui->plainTextEditScript->insertPlainText(m_titleCommand.script());
}

// -------------------------------------------------------
//
//  SLOTS
//
// -------------------------------------------------------

void DialogSystemTitleCommand::on_comboBoxTypeCommand_currentIndexChanged(int
    index)
{
    m_titleCommand.setKind(static_cast<TitleCommandKind>(index));
    ui->plainTextEditScript->setVisible(index == static_cast<int>(
        TitleCommandKind::Script));
}

// -------------------------------------------------------

void DialogSystemTitleCommand::on_plainTextEditScript_textChanged() {
    m_titleCommand.setScript(ui->plainTextEditScript->toPlainText());
}
