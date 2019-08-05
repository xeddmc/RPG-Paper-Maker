/*
    RPG Paper Maker Copyright (C) 2017-2019 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#include <QDirIterator>
#include <QtMath>
#include "common.h"

void Common::writeJSON(QString path, const Serializable &obj) {
    QJsonObject gameObject;
    obj.write(gameObject);
    Common::writeOtherJSON(path, gameObject);
}

// -------------------------------------------------------

void Common::readJSON(QString path, Serializable &obj) {
    QJsonDocument loadDoc;
    Common::readOtherJSON(path, loadDoc);
    obj.read(loadDoc.object());
}

// -------------------------------------------------------

void Common::writeRect(QJsonArray &json, const QRect &rect) {
    json.append(rect.x());
    json.append(rect.y());
    json.append(rect.width());
    json.append(rect.height());
}

// -------------------------------------------------------

void Common::readRect(QJsonArray &json, QRect &rect) {
    rect.setX(json[0].toInt());
    rect.setY(json[1].toInt());
    rect.setWidth(json[2].toInt());
    rect.setHeight(json[3].toInt());
}

// -------------------------------------------------------

void Common::writeRectF(QJsonArray &json, const QRectF &rect) {
    json.append(rect.x());
    json.append(rect.y());
    json.append(rect.width());
    json.append(rect.height());
}

// -------------------------------------------------------

void Common::readRectF(QJsonArray &json, QRectF &rect) {
    rect.setX(json[0].toDouble());
    rect.setY(json[1].toDouble());
    rect.setWidth(json[2].toDouble());
    rect.setHeight(json[3].toDouble());
}

// -------------------------------------------------------

void Common::writeOtherJSON(QString path, const QJsonObject &obj, QJsonDocument
    ::JsonFormat format)
{
    QFile saveFile(path);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        return;
    }

    QJsonDocument saveDoc(obj);
    saveFile.write(saveDoc.toJson(format));
    saveFile.close();
}

// -------------------------------------------------------

void Common::readOtherJSON(QString path, QJsonDocument &loadDoc) {
    QByteArray saveDatas;

    QFile loadFile(path);
    loadFile.open(QIODevice::ReadOnly);
    saveDatas = loadFile.readAll();
    loadFile.close();
    loadDoc = QJsonDocument::fromJson(saveDatas);
}

// -------------------------------------------------------

void Common::writeArrayJSON(QString path, const QJsonArray &tab) {
    QFile saveFile(path);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        return;
    }

    QJsonDocument saveDoc(tab);
    saveFile.write(saveDoc.toJson(QJsonDocument::Compact));
    saveFile.close();
}

// -------------------------------------------------------

void Common::readArrayJSON(QString path, QJsonDocument& loadDoc) {
    QByteArray saveDatas;

    QFile loadFile(path);
    loadFile.open(QIODevice::ReadOnly);
    saveDatas = loadFile.readAll();
    loadFile.close();
    loadDoc = QJsonDocument::fromJson(saveDatas);
}

// -------------------------------------------------------

QString Common::pathCombine(const QString &p1, const QString &p2) {
    return QDir::cleanPath(p1 + QDir::separator() + p2);
}

// -------------------------------------------------------

bool Common::copyPath(QString src, QString dst) {
    QDir dir(src);
    QString dstPath;

    if (!dir.exists()) {
        return false;
    }

    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        dstPath = pathCombine(dst, d);
        if (!dir.mkpath(dstPath)) {
            return false;
        }
        if (!copyPath(pathCombine(src, d), dstPath)) {
            return false;
        }
    }

    foreach (QString f, dir.entryList(QDir::Files)) {
        if (!QFile::copy(pathCombine(src, f), pathCombine(dst, f))) {
            return false;
        }
    }

    return true;
}

// -------------------------------------------------------

QString Common::getDirectoryPath(QString &file) {
    return QFileInfo(file).dir().absolutePath();
}

// -------------------------------------------------------

bool Common::isDirEmpty(QString path) {
    return QDir(path).entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries)
        .count() == 0;
}

// -------------------------------------------------------

void Common::copyAllFiles(QString pathSource, QString pathTarget) {
    QDirIterator files(pathSource, QDir::Files);
    QString path;

    while (files.hasNext()) {
        files.next();
        path = Common::pathCombine(pathTarget, files.fileName());
        QFile::remove(path);
        QFile::copy(files.filePath(), path);
    }
}

// -------------------------------------------------------

void Common::deleteAllFiles(QString pathSource) {
    QDirIterator files(pathSource, QDir::Files);

    while (files.hasNext()) {
        files.next();
        QFile(files.filePath()).remove();
    }
}

// -------------------------------------------------------

QString Common::getFormatNumber(int number, int format, int type) {
    return QString("%1").arg(number, format, type, QChar('0'));
}

// -------------------------------------------------------

int Common::modulo(int x, int m) {
    int r = x % m;
    return r < 0 ? r + m : r;
}

// -------------------------------------------------------

int Common::ceil(qreal r) {
    return r < 0 ? qFloor(r) : qCeil(r);
}

// -------------------------------------------------------

QKeySequence Common::getKeySequence(QKeyEvent *event) {
    Qt::KeyboardModifiers modifiers;
    int keyInt;
    Qt::Key key;

    keyInt = event->key();
    key = static_cast<Qt::Key>(keyInt);
    if (key != Qt::Key_unknown) {
        // the user have clicked just and only the special keys Ctrl, Shift,
        // Alt, Meta.
        if (key != Qt::Key_Control && key != Qt::Key_Shift && key != Qt::Key_Alt
            && key != Qt::Key_Meta)
        {
            // check for a combination of user clicks
            modifiers = event->modifiers();
            if (modifiers & Qt::ShiftModifier) {
                keyInt += Qt::SHIFT;
            }
            if (modifiers & Qt::ControlModifier) {
                keyInt += Qt::CTRL;
            }
            if (modifiers & Qt::AltModifier) {
                keyInt += Qt::ALT;
            }
            if (modifiers & Qt::MetaModifier) {
                keyInt += Qt::META;
            }

            return QKeySequence(keyInt);
        }
    }

    return QKeySequence();
}

// -------------------------------------------------------

QString Common::keyToString(int keyInt) {
    Qt::Key key;

    QKeySequence seq(keyInt);
    key = static_cast<Qt::Key>(keyInt);
    if (key != Qt::Key_unknown) {
        switch (key) {
        case Qt::Key_Control:
            return "CTRL";
        case Qt::Key_Shift:
            return "SHIFT";
        case Qt::Key_Alt:
            return "ALT";
        case Qt::Key_Meta:
            return "META";
        case Qt::Key_AltGr:
            return "ALTGR";
        default:
            return seq.toString();
        }
    }

    return "?";
}

// -------------------------------------------------------

bool Common::isPressingEnter(QKeyEvent *event) {
    return event->key() == Qt::Key_Space || event->key() == Qt::Key_Enter ||
        event->key() == Qt::Key_Return;
}

// -------------------------------------------------------

bool Common::getMinDistance(float& finalDistance, float newDistance) {
    if (std::isnan(finalDistance)) {
        finalDistance = 0;
    }
    if (std::isnan(newDistance)) {
        newDistance = 0;
    }
    if (finalDistance == 0.0f) {
        if (newDistance > 0) {
            finalDistance = newDistance;
            return true;
        }
    } else {
        if (newDistance > 0) {
            if (newDistance < finalDistance) {
                finalDistance = newDistance;
                return true;
            }
        }
    }

    return false;
}
