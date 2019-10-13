/*
    RPG Paper Maker Copyright (C) 2017-2019 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#include "dialogsystemstatistic.h"
#include "ui_dialogsystemstatistic.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

DialogSystemStatistic::DialogSystemStatistic(SystemStatistic &statistic,
                                             QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSystemStatistic),
    m_statistic(statistic)
{
    ui->setupUi(this);
    

    initialize();
}

DialogSystemStatistic::~DialogSystemStatistic()
{
    delete ui;
}

SystemStatistic& DialogSystemStatistic::statistic() const {
    return m_statistic;
}

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

void DialogSystemStatistic::initialize(){
    ui->widgetName->initializeNamesLang(&m_statistic);
    ui->lineEditAbbrevation->setText(m_statistic.abbreviation());

    if (m_statistic.isFix())
        ui->radioButtonFix->setChecked(true);
    else
        ui->radioButtonBar->setChecked(true);
}

// -------------------------------------------------------
//
//  SLOTS
//
// -------------------------------------------------------

void DialogSystemStatistic::on_lineEditAbbrevation_textChanged(
        const QString & text)
{
    m_statistic.setAbbreviation(text);
}

// -------------------------------------------------------

void DialogSystemStatistic::on_radioButtonFix_toggled(bool check){
    m_statistic.setIsFix(check);
}
