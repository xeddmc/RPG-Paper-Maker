/*
    RPG Paper Maker Copyright (C) 2017-2019 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#include "dialogsystemkeyboardgeneral.h"
#include "ui_dialogsystemkeyboardgeneral.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

DialogSystemKeyBoardGeneral::DialogSystemKeyBoardGeneral(SystemKeyBoard& key,
                                                         QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSystemKeyBoardGeneral),
    m_key(key)
{
    ui->setupUi(this);
    

    initialize();
}

DialogSystemKeyBoardGeneral::~DialogSystemKeyBoardGeneral()
{
    delete ui;
}

SystemKeyBoard& DialogSystemKeyBoardGeneral::key() const { return m_key; }

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

void DialogSystemKeyBoardGeneral::initialize(){
    ui->lineEditAbbreviation->setText(m_key.abbreviation());
    ui->lineEditDescription->setText(m_key.name());
    ui->labelShortcut->setText(m_key.shortCutString());
}

// -------------------------------------------------------
//
//  SLOTS
//
// -------------------------------------------------------

void DialogSystemKeyBoardGeneral::on_pushButtonChange_clicked(){
    SystemKeyBoard key;
    key.setCopy(m_key);
    DialogSystemKeyBoard dialog(key);
    if (dialog.exec() == QDialog::Accepted){
        m_key.setCopy(key);
        ui->labelShortcut->setText(m_key.shortCutString());
    }
}

// -------------------------------------------------------

void DialogSystemKeyBoardGeneral::on_lineEditAbbreviation_textChanged(
        const QString &text)
{
    m_key.setAbbreviation(text);
}

// -------------------------------------------------------

void DialogSystemKeyBoardGeneral::on_lineEditDescription_textChanged(
        const QString &text)
{
    m_key.setName(text);
}
