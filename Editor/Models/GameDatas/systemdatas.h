/*
    RPG Paper Maker Copyright (C) 2017-2019 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#ifndef SYSTEMDATAS_H
#define SYSTEMDATAS_H

#include <QStandardItemModel>
#include "serializable.h"
#include "primitivevalue.h"
#include "langstranslation.h"

// -------------------------------------------------------
//
//  CLASS SystemDatas
//
//  Contains all the system datas regrouping general project datas,
//  and menus datas.
//  The data file is located in Content/Datas/system.json
//
// -------------------------------------------------------

class SystemDatas : public Serializable
{
public:
    static const QString JSON_PROJECT_NAME;
    static const QString JSON_SCREEN_WIDTH;
    static const QString JSON_SCREEN_HEIGHT;
    static const QString JSON_IS_SCREEN_WINDOW;
    static const QString JSON_COLORS;
    static const QString JSON_WINDOW_SKINS;
    static const QString JSON_CAMERA_PROPERTIES;
    static const QString JSON_DETECTIONS;
    static const QString JSON_SPEED_FREQUENCIES;
    static const QString JSON_LAST_MAJOR_VERSION;
    static const QString JSON_LAST_MINOR_VERSION;
    static const QString JSON_MOUNTAIN_COLLISION_HEIGHT;
    static const QString JSON_MOUNTAIN_COLLISION_ANGLE;

    SystemDatas();
    virtual ~SystemDatas();

    void read(QString path);
    SystemDatas(QString path);
    LangsTranslation * projectName() const;
    int screenWidth() const;
    void setScreenWidth(int w);
    int screenHeight() const;
    void setScreenHeight(int h);
    bool isScreenWindow() const;
    void setIsScreenWinow(bool b);
    int portionsRay() const;
    void setPortionRay(int p);
    int squareSize() const;
    void setSquareSize(int i);
    PrimitiveValue * mountainCollisionHeight() const;
    PrimitiveValue * mountainCollisionAngle() const;
    int idMapHero() const;
    void setIdMapHero(int i);
    int idObjectHero() const;
    void setIdObjectHero(int i);
    QString pathBR() const;
    void setPathBR(QString p);
    int framesAnimation() const;
    void setFramesAnimation(int f);
    bool showBB() const;
    void setShowBB(bool b);
    int idWindowSkin() const;
    void setIdWindowSkin(int i);
    QStandardItemModel * modelColors() const;
    QStandardItemModel * modelCurrencies() const;
    QStandardItemModel * modelItemsTypes() const;
    QStandardItemModel * modelWindowSkins() const;
    QStandardItemModel * modelcameraProperties() const;
    QStandardItemModel * modelDetections() const;
    QStandardItemModel * modelSpeedFrequencies() const;
    int lastMajorVersion() const;
    void setLastMajorVersion(int v);
    int lastMinorVersion() const;
    void setLastMinorVersion(int v);

    void setDefault();
    void setDefaultColors();
    void setDefaultCurrencies();
    void setDefaultItemsTypes();
    void setDefaultWindowSkins();
    void setDefaultCameraProperties();
    void setDefaultDetections();
    void setDefaultSpeedFrequencies();

    virtual void read(const QJsonObject &json);
    virtual void write(QJsonObject &json) const;

private:
    LangsTranslation *m_projectName;
    int m_screenWidth;
    int m_screenHeight;
    bool m_isScreenWindow;
    int m_portionsRay;
    int m_squareSize;
    PrimitiveValue *m_mountainCollisionHeight;
    PrimitiveValue *m_mountainCollisionAngle;
    int m_idMapHero;
    int m_idObjectHero;
    QString m_pathBR;
    int m_framesAnimation;
    bool m_showBB;
    int m_idWindowSkin;
    QStandardItemModel *m_modelColors;
    QStandardItemModel *m_modelCurrencies;
    QStandardItemModel *m_modelItemsTypes;
    QStandardItemModel *m_modelWindowSkins;
    QStandardItemModel *m_modelCameraProperties;
    QStandardItemModel *m_modelDetections;
    QStandardItemModel *m_modelSpeedFrequencies;
    int m_lastMajorVersion;
    int m_lastMinorVersion;
};

#endif // SYSTEMDATAS_H
