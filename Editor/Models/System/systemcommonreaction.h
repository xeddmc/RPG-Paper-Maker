/*
    RPG Paper Maker Copyright (C) 2017-2019 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#ifndef SystemCommonReaction_H
#define SystemCommonReaction_H

#include "systemreaction.h"
#include "superlistitem.h"

// -------------------------------------------------------
//
//  CLASS SystemCommonReaction
//
//  A particulary common reactor.
//
// -------------------------------------------------------

class SystemCommonReaction : public SystemReaction
{
public:
    SystemCommonReaction();
    SystemCommonReaction(int i, QString n, QStandardItemModel *params,
                         QStandardItemModel *commands, bool bHero);
    virtual ~SystemCommonReaction();
    QStandardItemModel* modelParameters() const;
    virtual SuperListItem* createCopy() const;
    void setCopy(const SystemCommonReaction& copy);

    virtual void read(const QJsonObject &json);
    virtual void write(QJsonObject &json) const;

protected:
    QStandardItemModel* m_modelParameters;
};

Q_DECLARE_METATYPE(SystemCommonReaction)

#endif // SystemCommonReaction_H
