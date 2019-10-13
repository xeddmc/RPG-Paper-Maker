/*
    RPG Paper Maker Copyright (C) 2017-2019 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#include "systemsong.h"
#include "rpm.h"
#include "common.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

SystemSong::SystemSong() :
    SystemSong(-1, "<None>", false)
{

}

SystemSong::SystemSong(int i, QString n, bool isBR) :
    SuperListItem(i,n),
    m_isBR(isBR)
{

}

SystemSong::~SystemSong() {

}

bool SystemSong::isBR() const { return m_isBR; }

void SystemSong::setIsBR(bool b) { m_isBR = b; }

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

QString SystemSong::getFolder(SongKind kind, bool isBR) {
    QString folder = isBR ? RPM::get()->project()->gameDatas()->systemDatas()
                            ->pathBR()
                          : RPM::get()->project()->pathCurrentProject();

    return Common::pathCombine(folder, getLocalFolder(kind));
}

// -------------------------------------------------------

QString SystemSong::getLocalFolder(SongKind kind){
    switch (kind){
    case SongKind::Music:
        return RPM::PATH_MUSICS;
    case SongKind::BackgroundSound:
        return RPM::PATH_BACKGROUND_SOUNDS;
    case SongKind::Sound:
        return RPM::PATH_SOUNDS;
    case SongKind::MusicEffect:
        return RPM::PATH_MUSIC_EFFECTS;
    default:
        throw std::invalid_argument("Kind of song path not implemented");
    }
}

// -------------------------------------------------------

QString SystemSong::getSongTitle(SongKind kind) {
    switch(kind) {
    case SongKind::Music:
        return "Musics";
    case SongKind::BackgroundSound:
        return "Background sounds";
    case SongKind::Sound:
        return "Sounds";
    case SongKind::MusicEffect:
        return "Music effects";
    default:
        return "";
    }
}

// -------------------------------------------------------

QString SystemSong::getPath(SongKind kind) const{
    if (id() == -1)
        return "";

    QString folder = getFolder(kind, m_isBR);

    return Common::pathCombine(folder, name());
}

// -------------------------------------------------------

QString SystemSong::getLocalPath(SongKind kind) const{
    QString folder = getLocalFolder(kind);

    return Common::pathCombine(folder, name());
}

// -------------------------------------------------------

SuperListItem* SystemSong::createCopy() const{
    SystemSong* super = new SystemSong;
    super->setCopy(*this);
    return super;
}

// -------------------------------------------------------

void SystemSong::setCopy(const SystemSong& super){
    SuperListItem::setCopy(super);

    m_isBR = super.m_isBR;
}

// -------------------------------------------------------

QList<QStandardItem *> SystemSong::getModelRow() const{
    QList<QStandardItem*> row = QList<QStandardItem*>();
    QStandardItem* item = new QStandardItem;
    QIcon icon = m_isBR ? QIcon(SuperListItem::pathIconBlue)
                        : QIcon(SuperListItem::pathIconRed);

    item->setData(QVariant::fromValue(reinterpret_cast<quintptr>(this)));

    if (id() != -1)
        item->setIcon(icon);

    item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled));
    item->setText(toString());
    row.append(item);

    return row;
}

// -------------------------------------------------------
//
//  READ / WRITE
//
// -------------------------------------------------------

void SystemSong::read(const QJsonObject &json){
    SuperListItem::read(json);

    m_isBR = json["br"].toBool();
}

// -------------------------------------------------------

void SystemSong::write(QJsonObject &json) const{
    SuperListItem::write(json);

    json["br"] = m_isBR;
}
