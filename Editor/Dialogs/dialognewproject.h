/*
    RPG Paper Maker Copyright (C) 2017-2019 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#ifndef DIALOGNEWPROJECT_H
#define DIALOGNEWPROJECT_H

#include <QDialog>
#include "controlnewproject.h"

// -------------------------------------------------------
//
//  CLASS DialogNewProject
//
//  A dialog used for creating a new project.
//
// -------------------------------------------------------

namespace Ui {
class DialogNewProject;
}

class DialogNewProject : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewProject(QWidget *parent = 0);
    ~DialogNewProject();
    void filterDirectoryName(const QString & s);
    QString getProjectName() const;
    QString getDirectoryName() const;
    QString getLocation() const;

private:
    Ui::DialogNewProject *ui;
    ControlNewproject m_control;

private slots:
    void on_lineEditProjectName_textChanged(const QString & s);
    void on_lineEditDirectoryName_editingFinished();
    void on_pushButtonLocation_clicked();
    void accept();
};

#endif // DIALOGNEWPROJECT_H
