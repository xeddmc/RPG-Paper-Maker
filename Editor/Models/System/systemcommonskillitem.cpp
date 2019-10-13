/*
    RPG Paper Maker Copyright (C) 2017-2019 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#include "systemcommonskillitem.h"
#include "rpm.h"
#include "systemeffect.h"
#include "systemcost.h"
#include "systemcharacteristic.h"

const QString SystemCommonSkillItem::JSON_TYPE = "t";
const QString SystemCommonSkillItem::JSON_CONSUMABLE = "con";
const QString SystemCommonSkillItem::JSON_ONE_HAND = "oh";
const QString SystemCommonSkillItem::JSON_DESCRIPTION = "d";
const QString SystemCommonSkillItem::JSON_TARGET_KIND = "tk";
const QString SystemCommonSkillItem::JSON_TARGET_CONDITION_FORMULA = "tcf";
const QString SystemCommonSkillItem::JSON_CONDITION_FORMULA = "cf";
const QString SystemCommonSkillItem::JSON_AVAILABLE_KIND = "ak";
const QString SystemCommonSkillItem::JSON_SOUND = "s";
const QString SystemCommonSkillItem::JSON_ANIMATION_USER_ID = "auid";
const QString SystemCommonSkillItem::JSON_ANIMATION_TARGET_ID = "atid";
const QString SystemCommonSkillItem::JSON_PRICE = "p";
const QString SystemCommonSkillItem::JSON_COSTS = "cos";
const QString SystemCommonSkillItem::JSON_EFFECTS = "e";
const QString SystemCommonSkillItem::JSON_CHARACTERISTICS = "car";

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

SystemCommonSkillItem::SystemCommonSkillItem() :
    SystemCommonSkillItem(1, new LangsTranslation, -1, 1, false, true, new
    LangsTranslation, TargetKind::None, new PrimitiveValue(PrimitiveValueKind
    ::None), new PrimitiveValue(PrimitiveValueKind::None), AvailableKind::Never,
    new SystemPlaySong(-1, SongKind::Sound), new PrimitiveValue(
    PrimitiveValueKind::None), new PrimitiveValue(PrimitiveValueKind::None), new
    PrimitiveValue(0), new QStandardItemModel, new QStandardItemModel, new
    QStandardItemModel)
{
    m_modelCosts->setHorizontalHeaderLabels(QStringList({"Cost"}));
    m_modelEffects->setHorizontalHeaderLabels(QStringList({"Effect"}));
    m_modelCharacteristics->setHorizontalHeaderLabels(QStringList({"Characteristic"}));
}

SystemCommonSkillItem::SystemCommonSkillItem(int i, LangsTranslation *names, int
    pictureID, int type, bool consumable, bool oneHand, LangsTranslation
    *description, TargetKind targetKind, PrimitiveValue *targetConditionFormula,
    PrimitiveValue *conditionFormula, AvailableKind availableKind,
    SystemPlaySong *sound, PrimitiveValue *animationUserID, PrimitiveValue
    *animationTargetID, PrimitiveValue *price, QStandardItemModel *modelCosts,
    QStandardItemModel*modelEffects, QStandardItemModel *modelCharacteristics) :
    SystemIcon(i, names, pictureID),
    m_type(type),
    m_consumable(consumable),
    m_oneHand(oneHand),
    m_description(description),
    m_targetKind(targetKind),
    m_targetConditionFormula(targetConditionFormula),
    m_conditionFormula(conditionFormula),
    m_availableKind(availableKind),
    m_sound(sound),
    m_animationUserID(animationUserID),
    m_animationTargetID(animationTargetID),
    m_price(price),
    m_modelCosts(modelCosts),
    m_modelEffects(modelEffects),
    m_modelCharacteristics(modelCharacteristics)
{

}

SystemCommonSkillItem::~SystemCommonSkillItem() {
    delete m_description;
    delete m_targetConditionFormula;
    delete m_conditionFormula;
    delete m_sound;
    delete m_animationUserID;
    delete m_animationTargetID;
    delete m_price;
    SuperListItem::deleteModel(m_modelCosts);
    SuperListItem::deleteModel(m_modelEffects);
    SuperListItem::deleteModel(m_modelCharacteristics);
}

int SystemCommonSkillItem::type() const {
    return m_type;
}

void SystemCommonSkillItem::setType(int t) {
    m_type = t;
}

bool SystemCommonSkillItem::consumable() const {
    return m_consumable;
}

void SystemCommonSkillItem::setConsumable(bool b) {
    m_consumable = b;
}

bool SystemCommonSkillItem::oneHand() const {
    return m_oneHand;
}

void SystemCommonSkillItem::setOneHand(bool b) {
    m_oneHand = b;
}

LangsTranslation * SystemCommonSkillItem::description() const {
    return m_description;
}

TargetKind SystemCommonSkillItem::targetKind() const {
    return m_targetKind;
}

void SystemCommonSkillItem::setTargetKind(TargetKind k) {
    m_targetKind = k;
}

PrimitiveValue * SystemCommonSkillItem::targetConditionFormula() const {
    return m_targetConditionFormula;
}

PrimitiveValue * SystemCommonSkillItem::conditionFormula() const {
    return m_conditionFormula;
}

AvailableKind SystemCommonSkillItem::availableKind() const {
    return m_availableKind;
}

void SystemCommonSkillItem::setAvailableKind(AvailableKind k) {
    m_availableKind = k;
}

SystemPlaySong * SystemCommonSkillItem::sound() const {
    return m_sound;
}

PrimitiveValue * SystemCommonSkillItem::animationUserID() const {
    return m_animationUserID;
}

PrimitiveValue * SystemCommonSkillItem::animationTargetID() const {
    return m_animationTargetID;
}

PrimitiveValue * SystemCommonSkillItem::price() const {
    return m_price;
}

QStandardItemModel * SystemCommonSkillItem::modelCosts() const {
    return m_modelCosts;
}

QStandardItemModel * SystemCommonSkillItem::modelEffects() const {
    return m_modelEffects;
}

QStandardItemModel * SystemCommonSkillItem::modelCharacteristics() const {
    return m_modelCharacteristics;
}

// -------------------------------------------------------
//
//  VIRTUAL FUNCTIONS
//
// -------------------------------------------------------

SuperListItem* SystemCommonSkillItem::createCopy() const {
    SystemCommonSkillItem* super = new SystemCommonSkillItem;
    super->setCopy(*this);
    return super;
}

// -------------------------------------------------------

void SystemCommonSkillItem::setCopy(const SystemCommonSkillItem &skillItem) {
    SystemIcon::setCopy(skillItem);
    int i, l;

    m_type = skillItem.m_type;
    m_consumable = skillItem.m_consumable;
    m_oneHand = skillItem.m_oneHand;
    m_description->setCopy(*skillItem.m_description);
    m_targetKind = skillItem.m_targetKind;
    m_targetConditionFormula->setCopy(*skillItem.m_targetConditionFormula);
    m_conditionFormula->setCopy(*skillItem.m_conditionFormula);
    m_availableKind = skillItem.m_availableKind;
    m_sound->setCopy(*skillItem.m_sound);
    m_animationUserID->setCopy(*skillItem.m_animationUserID);
    m_animationTargetID->setCopy(*skillItem.m_animationTargetID);
    m_price->setCopy(*skillItem.m_price);

    SuperListItem::deleteModel(m_modelCosts, false);
    for (i = 0, l = skillItem.m_modelCosts->invisibleRootItem()->rowCount(); i
        < l - 1; i++)
    {
        m_modelCosts->insertRow(i, reinterpret_cast<SystemCost *>(skillItem
            .m_modelCosts->item(i)->data().value<quintptr>())->createCopy()
            ->getModelRow());
    }
    m_modelCosts->appendRow(new QStandardItem(SuperListItem::beginningText));
    SuperListItem::deleteModel(m_modelEffects, false);
    for (i = 0, l = skillItem.m_modelEffects->invisibleRootItem()->rowCount(); i
        < l - 1; i++)
    {
        m_modelEffects->insertRow(i, reinterpret_cast<SystemEffect *>(skillItem
            .m_modelEffects->item(i)->data().value<quintptr>())->createCopy()
            ->getModelRow());
    }
    m_modelEffects->appendRow(new QStandardItem(SuperListItem::beginningText));
    SuperListItem::deleteModel(m_modelCharacteristics, false);
    for (i = 0, l = skillItem.m_modelCharacteristics->invisibleRootItem()
        ->rowCount(); i < l - 1; i++)
    {
        m_modelCharacteristics->insertRow(i, reinterpret_cast<SystemCharacteristic
             *>(skillItem.m_modelCharacteristics->item(i)->data().value<quintptr>
            ())->createCopy()->getModelRow());
    }
    m_modelCharacteristics->appendRow(new QStandardItem(SuperListItem
        ::beginningText));
    m_modelCosts->setHorizontalHeaderLabels(QStringList({"Cost"}));
    m_modelEffects->setHorizontalHeaderLabels(QStringList({"Effect"}));
    m_modelCharacteristics->setHorizontalHeaderLabels(QStringList({
        "Characteristic"}));
}

// -------------------------------------------------------

void SystemCommonSkillItem::read(const QJsonObject &json){
    SystemIcon::read(json);
    QJsonArray tab;
    QList<QStandardItem *> row;

    if (json.contains(JSON_TYPE)) {
        m_type = json[JSON_TYPE].toInt();
    }
    if (json.contains(JSON_CONSUMABLE)) {
        m_consumable = json[JSON_CONSUMABLE].toBool();
    }
    if (json.contains(JSON_ONE_HAND)) {
        m_oneHand = json[JSON_ONE_HAND].toBool();
    }
    if (json.contains(JSON_DESCRIPTION)) {
        m_description->read(json[JSON_DESCRIPTION].toObject());
    }
    if (json.contains(JSON_TARGET_KIND)) {
        m_targetKind = static_cast<TargetKind>(json[JSON_TARGET_KIND].toInt());
    }
    if (json.contains(JSON_TARGET_CONDITION_FORMULA)) {
        m_targetConditionFormula->read(json[JSON_TARGET_CONDITION_FORMULA]
            .toObject());
    }
    if (json.contains(JSON_CONDITION_FORMULA)) {
        m_conditionFormula->read(json[JSON_CONDITION_FORMULA].toObject());
    }
    if (json.contains(JSON_AVAILABLE_KIND)) {
        m_availableKind = static_cast<AvailableKind>(json[JSON_AVAILABLE_KIND]
            .toInt());
    }
    if (json.contains(JSON_SOUND)) {
        m_sound->read(json[JSON_SOUND].toObject());
    }
    if (json.contains(JSON_ANIMATION_USER_ID)) {
        m_animationUserID->read(json[JSON_ANIMATION_USER_ID].toObject());
    }
    m_animationUserID->setModelDataBase(RPM::get()->project()->gameDatas()
        ->animationsDatas()->model());
    if (json.contains(JSON_ANIMATION_TARGET_ID)) {
        m_animationTargetID->read(json[JSON_ANIMATION_TARGET_ID].toObject());
    }
    m_animationTargetID->setModelDataBase(RPM::get()->project()->gameDatas()
        ->animationsDatas()->model());
    if (json.contains(JSON_PRICE)) {
        m_price->read(json[JSON_PRICE].toObject());
    }

    // Costs
    SuperListItem::readTree(m_modelCosts, new SystemCost, json, JSON_COSTS);

    // Effects
    SuperListItem::readTree(m_modelEffects, new SystemEffect, json, JSON_EFFECTS);

    // Characteristics
    SuperListItem::readTree(m_modelCharacteristics, new SystemCharacteristic,
        json, JSON_CHARACTERISTICS);
}

// -------------------------------------------------------

void SystemCommonSkillItem::write(QJsonObject &json) const{
    SystemIcon::write(json);
    QJsonObject obj;
    QJsonArray tab;

    if (m_type != 1) {
        json[JSON_TYPE] = m_type;
    }
    if (m_consumable) {
        json[JSON_CONSUMABLE] = m_consumable;
    }
    if (!m_oneHand) {
        json[JSON_ONE_HAND] = m_oneHand;
    }
    if (!m_description->isEmpty()) {
        obj = QJsonObject();
        m_description->write(obj);
        json[JSON_DESCRIPTION] = obj;
    }
    if (m_targetKind != TargetKind::None) {
        json[JSON_TARGET_KIND] = static_cast<int>(m_targetKind);
    }
    if (m_targetConditionFormula->kind() != PrimitiveValueKind::None) {
        obj = QJsonObject();
        m_targetConditionFormula->write(obj);
        json[JSON_TARGET_CONDITION_FORMULA] = obj;
    }
    if (m_conditionFormula->kind() != PrimitiveValueKind::None) {
        obj = QJsonObject();
        m_conditionFormula->write(obj);
        json[JSON_CONDITION_FORMULA] = obj;
    }
    if (m_availableKind != AvailableKind::Never) {
        json[JSON_AVAILABLE_KIND] = static_cast<int>(m_availableKind);
    }
    if (!m_sound->isNone()) {
        obj = QJsonObject();
        m_sound->write(obj);
        json[JSON_SOUND] = obj;
    }
    if (m_animationUserID->kind() != PrimitiveValueKind::None) {
        obj = QJsonObject();
        m_animationUserID->write(obj);
        json[JSON_ANIMATION_USER_ID] = obj;
    }
    if (m_animationTargetID->kind() != PrimitiveValueKind::None) {
        obj = QJsonObject();
        m_animationTargetID->write(obj);
        json[JSON_ANIMATION_TARGET_ID] = obj;
    }
    if (m_price->kind() != PrimitiveValueKind::Number || m_price->numberValue()
        != 0)
    {
        obj = QJsonObject();
        m_price->write(obj);
        json[JSON_PRICE] = obj;
    }

    // Costs
    SuperListItem::writeTree(m_modelCosts, json, JSON_COSTS);

    // Effects
    SuperListItem::writeTree(m_modelEffects, json, JSON_EFFECTS);

    // Characteristics
    SuperListItem::writeTree(m_modelCharacteristics, json, JSON_CHARACTERISTICS);
}
