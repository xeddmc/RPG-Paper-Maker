/*
    RPG Paper Maker Copyright (C) 2017-2019 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QStandardPaths>
#include <QDirIterator>
#include <cmath>
#include "rpm.h"
#include "common.h"

// COLORS
const QColor RPM::COLOR_GRAY_SELECTION_DARKER = QColor(60, 60, 60);
const QColor RPM::COLOR_GRAY_SELECTION = QColor(80, 80, 80);
const QColor RPM::COLOR_GRAY_SELECTION_LIGHTER = QColor(220, 220, 220);
const QColor RPM::COLOR_GRAY_SELECTION_BACKGROUND = QColor(80, 80, 80, 75);
const QColor RPM::COLOR_GRAY_HOVER_BACKGROUND = QColor(50, 50, 50, 75);
const QColor RPM::COLOR_PURPLE_SELECTION = QColor(134, 29, 226);
const QColor RPM::COLOR_PURPLE_SELCTION_BACKGROUND = QColor(134, 29, 226, 75);
const QColor RPM::COLOR_ALMOST_WHITE = QColor(245, 245, 245);
const QColor RPM::COLOR_ALMOST_BLACK = QColor(25, 25, 25);
const QColor RPM::COLOR_ALMOST_TRANSPARENT = QColor(0, 0, 0, 20);
const QColor RPM::COLOR_FORTY_TRANSPARENT = QColor(0, 0, 0, 40);
const QColor RPM::COLOR_GREY = QColor(90, 90, 90);
const QColor RPM::COLOR_MENU_SELECTION_BLUE = QColor(47, 139, 196);

// COMMON JSON
const QString RPM::JSON_KEY = "k";
const QString RPM::JSON_VALUE = "v";

// EXTENSIONS
const QString RPM::EXTENSION_JSON = ".json";
const QString RPM::EXTENSION_QSS = ".qss";
const QString RPM::EXTENSION_RPM = ".rpm";
const QString RPM::EXTENSION_PNG = ".png";
const QString RPM::EXTENSION_JPG = ".jpg";

// STRING SYMBOLS
const QString RPM::DASH = "-";
const QString RPM::TRUE_BOOL_STRING = "1";
const QString RPM::FALSE_BOOL_STRING = "0";

// FILE / FOLDER NAMES
const QString RPM::FILE_MAP_INFOS = "infos" + EXTENSION_JSON;
const QString RPM::FILE_MAP_OBJECTS = "objects" + EXTENSION_JSON;
const QString RPM::FOLDER_GAMES = "RPG Paper Maker Games";
const QString RPM::FOLDER_DESKTOP = "desktop";
const QString RPM::FOLDER_CONTENT = "Content";
const QString RPM::FOLDER_TEMP_MAP = "temp";
const QString RPM::FOLDER_UNDO_REDO_TEMP_MAP = "tempUndoRedo";

// PATHS
const QString RPM::PATH_BASIC = Common::pathCombine(FOLDER_CONTENT, "basic");
const QString RPM::PATH_BR = Common::pathCombine(FOLDER_CONTENT, "BR");
const QString RPM::PATH_DATAS = Common::pathCombine(FOLDER_CONTENT, "Datas");
const QString RPM::PATH_MAPS = Common::pathCombine(PATH_DATAS, "Maps");
const QString RPM::PATH_SCRIPTS_DIR = Common::pathCombine(PATH_DATAS, "Scripts");
const QString RPM::PATH_SCRIPTS_SYSTEM_DIR = Common::pathCombine(
    PATH_SCRIPTS_DIR, "System");
const QString RPM::PATH_SCRIPTS_PLUGINS_DIR = Common::pathCombine(
    PATH_SCRIPTS_DIR, "Plugins");
const QString RPM::PATH_COMMON_EVENTS = Common::pathCombine(PATH_DATAS,
    "commonEvents" + EXTENSION_JSON);
const QString RPM::PATH_VARIABLES = Common::pathCombine(PATH_DATAS,
    "variables" + EXTENSION_JSON);
const QString RPM::PATH_SYSTEM = Common::pathCombine(PATH_DATAS,
    "system" + EXTENSION_JSON);
const QString RPM::PATH_BATTLE_SYSTEM = Common::pathCombine(PATH_DATAS,
    "battleSystem" + EXTENSION_JSON);
const QString RPM::PATH_ITEMS = Common::pathCombine(PATH_DATAS,
    "items" + EXTENSION_JSON);
const QString RPM::PATH_SKILLS = Common::pathCombine(PATH_DATAS,
    "skills" + EXTENSION_JSON);
const QString RPM::PATH_WEAPONS = Common::pathCombine(PATH_DATAS,
    "weapons" + EXTENSION_JSON);
const QString RPM::PATH_ARMORS = Common::pathCombine(PATH_DATAS,
    "armors" + EXTENSION_JSON);
const QString RPM::PATH_HEROES = Common::pathCombine(PATH_DATAS,
    "heroes" + EXTENSION_JSON);
const QString RPM::PATH_MONSTERS = Common::pathCombine(PATH_DATAS,
    "monsters" + EXTENSION_JSON);
const QString RPM::PATH_TROOPS = Common::pathCombine(PATH_DATAS,
    "troops" + EXTENSION_JSON);
const QString RPM::PATH_CLASSES = Common::pathCombine(PATH_DATAS,
    "classes" + EXTENSION_JSON);
const QString RPM::PATH_TILESETS_DATAS = Common::pathCombine(PATH_DATAS,
    "tilesets" + EXTENSION_JSON);
const QString RPM::PATH_ANIMATIONS = Common::pathCombine(PATH_DATAS,
    "animations" + EXTENSION_JSON);
const QString RPM::PATH_STATUS = Common::pathCombine(PATH_DATAS,
    "status" + EXTENSION_JSON);
const QString RPM::PATH_SPECIAL_ELEMENTS = Common::pathCombine(PATH_DATAS,
    "specialElements" + EXTENSION_JSON);
const QString RPM::PATH_TITLE_SCREEN_GAME_OVER = Common::pathCombine(PATH_DATAS,
    "titlescreenGameover" + EXTENSION_JSON);
const QString RPM::PATH_TREE_MAP = Common::pathCombine(PATH_DATAS,
    "treeMap" + EXTENSION_JSON);
const QString RPM::PATH_LANGS = Common::pathCombine(PATH_DATAS,
    "langs" + EXTENSION_JSON);
const QString RPM::PATH_SCRIPTS = Common::pathCombine(PATH_DATAS,
    "scripts" + EXTENSION_JSON);
const QString RPM::PATH_KEYBOARD = Common::pathCombine(PATH_DATAS,
    "keyBoard" + EXTENSION_JSON);
const QString RPM::PATH_PICTURES_DATAS = Common::pathCombine(PATH_DATAS,
    "pictures" + EXTENSION_JSON);
const QString RPM::PATH_VIDEOS_DATAS = Common::pathCombine(PATH_DATAS,
    "videos" + EXTENSION_JSON);
const QString RPM::PATH_SONGS_DATAS = Common::pathCombine(PATH_DATAS,
    "songs" + EXTENSION_JSON);
const QString RPM::PATH_SHAPES_DATAS = Common::pathCombine(PATH_DATAS,
    "shapes" + EXTENSION_JSON);
const QString RPM::PATH_SAVES = Common::pathCombine(PATH_DATAS,
    "saves" + EXTENSION_JSON);
const QString RPM::PATH_PICTURES = Common::pathCombine(FOLDER_CONTENT,
    "Pictures");
const QString RPM::PATH_HUD = Common::pathCombine(PATH_PICTURES,
    "HUD");
const QString RPM::PATH_TEXTURES_2D = Common::pathCombine(PATH_PICTURES,
    "Textures2D");
const QString RPM::PATH_BARS = Common::pathCombine(PATH_HUD,
    "Bars");
const QString RPM::PATH_ICONS = Common::pathCombine(PATH_HUD,
    "Icons");
const QString RPM::PATH_FACESETS = Common::pathCombine(PATH_HUD,
    "Facesets");
const QString RPM::PATH_WINDOW_SKINS = Common::pathCombine(PATH_HUD,
    "WindowSkins");
const QString RPM::PATH_TITLE_SCREEN = Common::pathCombine(PATH_HUD,
    "TitleScreen");
const QString RPM::PATH_AUTOTILES = Common::pathCombine(PATH_TEXTURES_2D,
    "Autotiles");
const QString RPM::PATH_CHARACTERS = Common::pathCombine(PATH_TEXTURES_2D,
    "Characters");
const QString RPM::PATH_TILESETS = Common::pathCombine(PATH_TEXTURES_2D,
    "Tilesets");
const QString RPM::PATH_SPRITE_WALLS = Common::pathCombine(PATH_TEXTURES_2D,
    "Walls");
const QString RPM::PATH_RELIEFS = Common::pathCombine(PATH_TEXTURES_2D,
    "Reliefs");
const QString RPM::PATH_MOUNTAINS = Common::pathCombine(PATH_TEXTURES_2D,
    "Mountains");
const QString RPM::PATH_TEXTURES_OBJECT_3D = Common::pathCombine(PATH_TEXTURES_2D,
    "Objects3D");
const QString RPM::PATH_BATTLERS = Common::pathCombine(PATH_TEXTURES_2D,
    "Battlers");
const QString RPM::PATH_VIDEOS = Common::pathCombine(FOLDER_CONTENT,
    "Videos");
const QString RPM::PATH_SONGS = Common::pathCombine(FOLDER_CONTENT,
    "Songs");
const QString RPM::PATH_MUSICS = Common::pathCombine(PATH_SONGS,
    "Musics");
const QString RPM::PATH_BACKGROUND_SOUNDS = Common::pathCombine(PATH_SONGS,
    "BackgroundSounds");
const QString RPM::PATH_SOUNDS = Common::pathCombine(PATH_SONGS,
    "Sounds");
const QString RPM::PATH_MUSIC_EFFECTS = Common::pathCombine(PATH_SONGS,
    "MusicEffects");
const QString RPM::PATH_SHAPES = Common::pathCombine(FOLDER_CONTENT,
    "Shapes");
const QString RPM::PATH_OBJ = Common::pathCombine(PATH_SHAPES,
    "OBJ");
const QString RPM::PATH_MTL = Common::pathCombine(PATH_SHAPES,
    "MTL");
const QString RPM::PATH_COLLISIONS = Common::pathCombine(PATH_SHAPES,
    "Collisions");
const QString RPM::PATH_ENGINE_SETTINGS = Common::pathCombine(FOLDER_CONTENT,
    "engineSettings" + EXTENSION_JSON);
const QString RPM::PATH_TRANSLATIONS = Common::pathCombine(FOLDER_CONTENT,
    "translations");
const QString RPM::PATH_TRANSLATIONS_LANGUAGES = Common::pathCombine(RPM
    ::PATH_TRANSLATIONS, "languages" + EXTENSION_JSON);
const QString RPM::PATH_GAMES = Common::pathCombine(QStandardPaths
    ::writableLocation(QStandardPaths::StandardLocation::DocumentsLocation),
    FOLDER_GAMES);
const QString RPM::PATH_TEXTURE_MISSING = ":/textures/Ressources/missing.png";

// INTEGERS
const int RPM::PORTION_SIZE = 16;
const int RPM::BASIC_SQUARE_SIZE = 32;
const int RPM::MAX_PIXEL_SIZE = 4096;

// ENUM TO STRING
const QStringList RPM::ENUM_TO_STRING_DAMAGES_KIND = {
    "Statistic", "Currency", "Variable"
};
const QStringList RPM::ENUM_TO_STRING_EFFECT_SPECIAL_ACTION_KIND = {
    "Apply weapon(s) effects and properties", "Open skills choice",
    "Open items choice", "Escape", "End turn"
};
const QStringList RPM::ENUM_TO_STRING_INCREASE_DECREASE_KIND = {
    "Statistic value", "Element resistance", "Status resistance",
    "Experience gain", "Currency gain", "Skill cost", "Variable"
};
const QStringList RPM::ENUM_TO_STRING_OS_KIND = {
    "Windows", "Linux", "Mac"
};

const QStringList RPM::ENUM_TO_STRING_TEAM = {
    "team", "reserve", "hidden"
};

const QStringList RPM::ENUM_TO_STRING_OPERATION = {
    "= (Equal to)", "!= (Not equal to)", ">= (Greater than or equal to)",
    "<= (Lesser than or equal to)", "> (Greater than)", "< (Lesser than)"
};

const QStringList RPM::ENUM_TO_STRING_OPERATION_SIMPLE = {
    "=", "!=", ">=", "<=", ">", "<"
};

const QStringList RPM::ENUM_TO_STRING_FORMULA_STAT = {
    "Statistic", "Currency", "Variable"
};

const QStringList RPM::ENUM_TO_STRING_TITLE_SETTINGS = {
    "Keyboard assigments"
};

const QStringList RPM::ENUM_TO_STRING_AXIS_KIND = {
    "X", "Y", "Z"
};

// OTHER STATIC VALUES
QSet<int> RPM::mapsToSave;
QSet<int> RPM::mapsUndoRedo;
QString RPM::shadersExtension = "-3.0";
bool RPM::isInConfig = false;
bool RPM::isInObjectConfig = false;

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

RPM::RPM() :
    m_project(nullptr),
    m_engineSettings(new EngineSettings),
    m_translations(new Translations)
{

}

RPM::~RPM() {
    if (m_project != nullptr) {
        delete m_project;
        m_project = nullptr;
    }
    delete m_engineSettings;
    delete m_translations;
}

Project* RPM::project() const {
    return m_project;
}

EngineSettings* RPM::engineSettings() const {
    return m_engineSettings;
}

Translations * RPM::translations() const {
    return m_translations;
}

void RPM::setProject(Project *p) {
    m_project = p;
}

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

void RPM::writeJSON(QString path, const Serializable &obj) {
    QJsonObject gameObject;
    obj.write(gameObject);
    Common::writeOtherJSON(path, gameObject);
}

// -------------------------------------------------------

void RPM::readJSON(QString path, Serializable &obj) {
    QJsonDocument loadDoc;
    Common::readOtherJSON(path, loadDoc);
    obj.read(loadDoc.object());
}

// -------------------------------------------------------

float RPM::coefSquareSize() {
    return RPM::get()->getSquareSize() / (static_cast<float>(RPM
        ::BASIC_SQUARE_SIZE));
}

// -------------------------------------------------------

float RPM::coefReverseSquareSize() {
    return static_cast<float>(RPM::BASIC_SQUARE_SIZE) / RPM::get()
        ->getSquareSize();
}

// -------------------------------------------------------

int RPM::getPortionsRay() {
    return RPM::get()->project()->gameDatas()->systemDatas()->portionsRay();
}

// -------------------------------------------------------

int RPM::getSquareSize() {
    return RPM::get()->project()->gameDatas()->systemDatas()->squareSize();
}

// -------------------------------------------------------

void RPM::readEngineSettings() {
    QFile fileSettings(Common::pathCombine(QDir::currentPath(), RPM
        ::PATH_ENGINE_SETTINGS));

    if (fileSettings.exists()) {
        RPM::get()->engineSettings()->read();
    } else {
        RPM::get()->engineSettings()->setDefault();
        RPM::get()->engineSettings()->write();
    }
}

// -------------------------------------------------------

void RPM::readTranslations() {
    RPM::get()->translations()->read();
}

// -------------------------------------------------------

void RPM::saveEngineSettings() {
    RPM::get()->engineSettings()->write();
}

// -------------------------------------------------------

QString RPM::translate(const QString &key) {
    return RPM::get()->translations()->get(key);
}

// -------------------------------------------------------

void RPM::loadEngineSettings() {
    delete m_engineSettings;

    m_engineSettings = new EngineSettings;
    m_engineSettings->read();
}
